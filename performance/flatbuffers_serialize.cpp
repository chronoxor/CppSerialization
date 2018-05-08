//
// Created by Ivan Shynkarenka on 03.03.2017
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

const uint64_t iterations = 1000000;

class SerializationFixture
{
protected:
    flatbuffers::DefaultAllocator allocator;
    flatbuffers::FlatBufferBuilder builder;
    MyDomain::Account account;

    SerializationFixture() : builder(1024, &allocator), account(1, "Test", "USD", 1000)
    {
        // Create a new account with some orders
        account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "FlatBuffers-Serialize", iterations)
{
    // Serialize the account to the FlatBuffer stream
    builder.Clear();
    builder.Finish(account.Serialize(builder));

    context.metrics().AddBytes(builder.GetSize());
    context.metrics().SetCustom("Size", builder.GetSize());
}

BENCHMARK_MAIN()
