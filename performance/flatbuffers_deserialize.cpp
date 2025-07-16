//
// Created by Ivan Shynkarenka on 03.03.2017
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class DeserializationFixture
{
protected:
    flatbuffers::DefaultAllocator allocator;
    flatbuffers::FlatBufferBuilder builder;
    TradeProto::Account deserialized;

    DeserializationFixture() : builder(1024, &allocator)
    {
        // Create a new account with some orders
        TradeProto::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

        // Serialize the account to the FlatBuffer buffer
        builder.Finish(account.Serialize(builder));
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "FlatBuffers-Deserialize")
{
    context.metrics().AddBytes(builder.GetSize());
    context.metrics().SetCustom("MessageSize", builder.GetSize());

    // Deserialize the account from the FlatBuffer buffer
    deserialized.Deserialize(*Trade::flatbuf::GetAccount(builder.GetBufferPointer()));

    context.metrics().SetCustom("OriginalSize", (unsigned)deserialized.size());
}

BENCHMARK_MAIN()
