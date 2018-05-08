//
// Created by Ivan Shynkarenka on 28.02.2017
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

#include "serialization/json/parser.h"

using namespace CppSerialization::JSON;

const uint64_t iterations = 1000000;

class ParserFixture
{
protected:
    StringBuffer buffer;

    ParserFixture()
    {
        // Create a new account with some orders
        MyDomain::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

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
