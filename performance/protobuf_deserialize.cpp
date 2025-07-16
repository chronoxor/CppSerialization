//
// Created by Ivan Shynkarenka on 30.03.2018
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class DeserializationFixture
{
protected:
    std::string buffer;
    TradeProto::Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        TradeProto::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000);
        account.Orders.emplace_back(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100);
        account.Orders.emplace_back(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10);

        // Serialize the account to the Protobuf buffer
        Trade::protobuf::Account output;
        account.Serialize(output);
        buffer = output.SerializeAsString();
    }

    ~DeserializationFixture()
    {
        // Delete all global objects allocated by Protobuf
        google::protobuf::ShutdownProtobufLibrary();
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "Protobuf-Deserialize")
{
    context.metrics().AddBytes(buffer.size());
    context.metrics().SetCustom("MessageSize", (unsigned)buffer.size());

    // Deserialize the account from the Protobuf buffer
    Trade::protobuf::Account input;
    input.ParseFromString(buffer);
    deserialized.Deserialize(input);

    context.metrics().SetCustom("OriginalSize", (unsigned)deserialized.size());
}

BENCHMARK_MAIN()
