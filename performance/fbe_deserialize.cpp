//
// Created by Ivan Shynkarenka on 08.05.2018
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

const uint64_t iterations = 1000000;

class DeserializationFixture
{
protected:
    FBE::AccountModel<FBE::WriteBuffer> writer;
    FBE::AccountModel<FBE::ReadBuffer> reader;
    MyDomain::Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        MyDomain::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

        // Serialize the account to the FBE stream
        size_t model_begin = writer.create_begin();
        account.Serialize(writer.model);
        writer.create_end(model_begin);
        assert(writer.verify() && "Model is broken!");
        reader.attach(writer.buffer());
        assert(reader.verify() && "Model is broken!");
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "FastBinaryEncoding-Deserialize", iterations)
{
    context.metrics().AddBytes(reader.buffer().size());
    context.metrics().SetCustom("Size", (unsigned)reader.buffer().size());

    // Deserialize the account from the FBE stream
    deserialized.Deserialize(reader.model);
}

BENCHMARK_MAIN()
