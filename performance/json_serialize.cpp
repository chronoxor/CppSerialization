//
// Created by Ivan Shynkarenka on 28.02.2017
//

#include "benchmark/cppbenchmark.h"

#include "../examples/domain.h"

using namespace CppSerialization::JSON;

const uint64_t iterations = 1000000;

class SerializationFixture
{
protected:
    Account account;
    StringBuffer buffer;
    Serializer<StringBuffer> serializer;

    SerializationFixture() : account(1, "Test", "USD", 1000)
    {
        account.AddOrder(Order(1, "EURUSD", OrderSide::BUY, OrderType::MARKET, 1.23456, 1000));
        account.AddOrder(Order(2, "EURUSD", OrderSide::SELL, OrderType::LIMIT, 1.0, 100));
        account.AddOrder(Order(3, "EURUSD", OrderSide::BUY, OrderType::STOP, 1.5, 10));
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "JSON-Serialize", iterations)
{
    buffer.Clear();
    serializer.Reset(buffer);
    account.SerializeJSON(serializer);
    context.metrics().AddBytes(buffer.GetSize());
}

BENCHMARK_MAIN()
