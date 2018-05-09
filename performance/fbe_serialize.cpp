//
// Created by Ivan Shynkarenka on 08.05.2018
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

const uint64_t iterations = 1000000;

class SerializationFixture
{
protected:
    FBE::AccountModel<FBE::WriteBuffer> writer;
    MyDomain::Account account;

    SerializationFixture() : account(1, "Test", "USD", 1000)
    {
        // Create a new account with some orders
        account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "FlatBuffers-Serialize", iterations)
{
    // Serialize the account to the FBE stream
    writer.reset();
    size_t model_begin = writer.create_begin();
    account.Serialize(writer.model);
    size_t serialized = writer.create_end(model_begin);

    context.metrics().AddBytes(serialized);
    context.metrics().SetCustom("Size", (unsigned)serialized);
}

BENCHMARK_MAIN()
