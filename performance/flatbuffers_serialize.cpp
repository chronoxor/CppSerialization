//
// Created by Ivan Shynkarenka on 03.03.2017
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class SerializationFixture
{
protected:
    flatbuffers::DefaultAllocator allocator;
    flatbuffers::FlatBufferBuilder builder;
    TradeProto::Account account;

    SerializationFixture() : builder(1024, &allocator), account(1, "Test", "USD", 1000)
    {
        // Create a new account with some orders
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "FlatBuffers-Serialize")
{
    // Serialize the account to the FlatBuffer buffer
    builder.Clear();
    builder.Finish(account.Serialize(builder));

    context.metrics().AddBytes(builder.GetSize());
    context.metrics().SetCustom("OriginalSize", (unsigned)account.size());
    context.metrics().SetCustom("MessageSize", builder.GetSize());
}

BENCHMARK_MAIN()
