//
// Created by Ivan Shynkarenka on 03.03.2017
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

const uint64_t operations = 1000000;

class DeserializationFixture
{
protected:
    flatbuffers::DefaultAllocator allocator;
    flatbuffers::FlatBufferBuilder builder;
    MyDomain::Account deserialized;

    DeserializationFixture() : builder(1024, &allocator)
    {
        // Create a new account with some orders
        MyDomain::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

        // Serialize the account to the FlatBuffer stream
        builder.Finish(account.Serialize(builder));
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "FlatBuffers-Deserialize", operations)
{
    context.metrics().AddBytes(builder.GetSize());
    context.metrics().SetCustom("Size", builder.GetSize());

    // Deserialize the account from the FlatBuffer stream
    deserialized.Deserialize(*MyDomain::flatbuf::GetAccount(builder.GetBufferPointer()));
}

BENCHMARK_MAIN()
