//
// Created by Ivan Shynkarenka on 28.02.2017
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

#include "serialization/json/parser.h"

using namespace CppSerialization::JSON;

class DeserializationFixture
{
protected:
    size_t size;
    Document json;
    TradeProto::Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        TradeProto::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

        // Serialize the account to the JSON stream
        StringBuffer buffer;
        Serializer<StringBuffer> serializer(buffer);
        account.Serialize(serializer);

        // Parse JSON string
        json = Parser::Parse(buffer.GetString());
        size = buffer.GetSize();
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "JSON-Deserialize")
{
    context.metrics().AddBytes(json.Size());
    context.metrics().SetCustom("MessageSize", (unsigned)size);

    // Deserialize the account from the JSON stream
    deserialized.Deserialize(json);

    context.metrics().SetCustom("OriginalSize", (unsigned)deserialized.size());
}

BENCHMARK_MAIN()
