//
// Created by Ivan Shynkarenka on 03.03.2017
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

using namespace MyDomain;

const uint64_t iterations = 1000000;

class SerializationFixture
{
protected:
    flatbuffers::DefaultAllocator allocator;
    flatbuffers::FlatBufferBuilder builder;
    Account account;

    SerializationFixture() : builder(1024, &allocator), account(1, "Test", "USD", 1000)
    {
        // Create a new account with some orders
        account.AddOrder(Order(1, "EURUSD", OrderSide::BUY, OrderType::MARKET, 1.23456, 1000));
        account.AddOrder(Order(2, "EURUSD", OrderSide::SELL, OrderType::LIMIT, 1.0, 100));
        account.AddOrder(Order(3, "EURUSD", OrderSide::BUY, OrderType::STOP, 1.5, 10));
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "FlatBuffers-Serialize", iterations)
{
    builder.Clear();
    builder.Finish(account.SerializeFlatBuffer(builder));
}

BENCHMARK_MAIN()
