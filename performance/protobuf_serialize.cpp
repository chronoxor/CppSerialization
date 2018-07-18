//
// Created by Ivan Shynkarenka on 30.03.2018
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class SerializationFixture
{
protected:
    TradeProto::Account account;
    std::string buffer;

    SerializationFixture() : account(1, "Test", "USD", 1000)
    {
        // Create a new account with some orders
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));
    }

    ~SerializationFixture()
    {
        // Delete all global objects allocated by Protobuf
        google::protobuf::ShutdownProtobufLibrary();
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "Protobuf-Serialize")
{
    // Serialize the account to the Protobuf stream
    Trade::protobuf::Account output;
    account.Serialize(output);
    output.SerializeToString(&buffer);

    context.metrics().AddBytes(buffer.size());
    context.metrics().SetCustom("Size", (unsigned)buffer.size());
}

BENCHMARK_MAIN()
