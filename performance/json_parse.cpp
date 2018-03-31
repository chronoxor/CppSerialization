//
// Created by Ivan Shynkarenka on 28.02.2017
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

#include "serialization/json/parser.h"

using namespace CppSerialization::JSON;
using namespace MyDomain;

const uint64_t iterations = 1000000;

class ParserFixture
{
protected:
    StringBuffer buffer;

    ParserFixture()
    {
        // Create a new account with some orders
        Account account(1, "Test", "USD", 1000);
        account.AddOrder(Order(1, "EURUSD", OrderSide::BUY, OrderType::MARKET, 1.23456, 1000));
        account.AddOrder(Order(2, "EURUSD", OrderSide::SELL, OrderType::LIMIT, 1.0, 100));
        account.AddOrder(Order(3, "EURUSD", OrderSide::BUY, OrderType::STOP, 1.5, 10));

        // Serialize the account to the JSON stream
        Serializer<StringBuffer> serializer(buffer);
        account.Serialize(serializer);
    }
};

BENCHMARK_FIXTURE(ParserFixture, "JSON-Parse", iterations)
{
    context.metrics().AddBytes(buffer.GetSize());
    context.metrics().SetCustom("Size", (unsigned)buffer.GetSize());

    // Parse JSON document from the JSON stream
    Document json = Parser::Parse(buffer.GetString());
}

BENCHMARK_MAIN()
