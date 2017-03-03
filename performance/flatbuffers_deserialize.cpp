//
// Created by Ivan Shynkarenka on 03.03.2017
//

#include "benchmark/cppbenchmark.h"

#include "domain/domain.h"

using namespace MyDomain;

const uint64_t iterations = 1000000;

class DeserializationFixture
{
protected:
    flatbuffers::FlatBufferBuilder builder;
    Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        Account account(1, "Test", "USD", 1000);
        account.AddOrder(Order(1, "EURUSD", OrderSide::BUY, OrderType::MARKET, 1.23456, 1000));
        account.AddOrder(Order(2, "EURUSD", OrderSide::SELL, OrderType::LIMIT, 1.0, 100));
        account.AddOrder(Order(3, "EURUSD", OrderSide::BUY, OrderType::STOP, 1.5, 10));

        // Serialize the account to the FlatBuffer stream
        builder.Finish(account.SerializeFlatBuffer(builder));
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "FlatBuffers-Deserialize", iterations)
{
    auto root = MyDomain::flat::GetAccount(builder.GetBufferPointer());
    deserialized.DeserializeFlatBuffer(*root);
}

BENCHMARK_MAIN()
