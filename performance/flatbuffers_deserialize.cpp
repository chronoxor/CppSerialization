//
// Created by Ivan Shynkarenka on 03.03.2017
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

using namespace MyDomain;

const uint64_t iterations = 1000000;

class DeserializationFixture
{
protected:
    flatbuffers::DefaultAllocator allocator;
    flatbuffers::FlatBufferBuilder builder;
    Account account;

    DeserializationFixture() : builder(1024, &allocator)
    {
        // Create a new account with some orders
        account.AddOrder(Order(1, "EURUSD", OrderSide::BUY, OrderType::MARKET, 1.23456, 1000));
        account.AddOrder(Order(2, "EURUSD", OrderSide::SELL, OrderType::LIMIT, 1.0, 100));
        account.AddOrder(Order(3, "EURUSD", OrderSide::BUY, OrderType::STOP, 1.5, 10));

        // Serialize the account to the FlatBuffer stream
        builder.Finish(account.SerializeFlatBuffer(builder));
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "FlatBuffers-Deserialize", iterations)
{
    auto root = flat::GetAccount(builder.GetBufferPointer());
    account.DeserializeFlatBuffer(*root);
    context.metrics().AddBytes(builder.GetSize());
    context.metrics().SetCustom("Size", builder.GetSize());
}

BENCHMARK_MAIN()
