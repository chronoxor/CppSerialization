//
// Created by Ivan Shynkarenka on 28.02.2017
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

using namespace CppSerialization::JSON;

const uint64_t operations = 1000000;

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

BENCHMARK_FIXTURE(SerializationFixture, "JSON-Serialize", operations)
{
    // Serialize the account to the JSON stream
    buffer.Clear();
    serializer.Reset(buffer);
    account.Serialize(serializer);

    context.metrics().AddBytes(buffer.GetSize());
    context.metrics().SetCustom("Size", (unsigned)buffer.GetSize());
}

BENCHMARK_MAIN()
