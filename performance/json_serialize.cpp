//
// Created by Ivan Shynkarenka on 28.02.2017
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

using namespace CppSerialization::JSON;

class SerializationFixture
{
protected:
    TradeProto::Account account;
    StringBuffer buffer;
    Serializer<StringBuffer> serializer;

    SerializationFixture() : account(1, "Test", "USD", 1000)
    {
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "JSON-Serialize")
{
    // Serialize the account to the JSON buffer
    buffer.Clear();
    serializer.Reset(buffer);
    account.Serialize(serializer);

    context.metrics().AddBytes(buffer.GetSize());
    context.metrics().SetCustom("OriginalSize", (unsigned)account.size());
    context.metrics().SetCustom("MessageSize", (unsigned)buffer.GetSize());
}

BENCHMARK_MAIN()
