//
// Created by Ivan Shynkarenka on 28.02.2017
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

using namespace CppSerialization::JSON;

const uint64_t operations = 1000000;

class SerializationFixture
{
protected:
    MyDomain::Account account;
    StringBuffer buffer;
    Serializer<StringBuffer> serializer;

    SerializationFixture() : account(1, "Test", "USD", 1000)
    {
        account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));
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
