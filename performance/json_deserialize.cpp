//
// Created by Ivan Shynkarenka on 28.02.2017
//

#include "benchmark/cppbenchmark.h"

#include "domain/domain.h"
#include "serialization/json/parser.h"

using namespace CppSerialization::JSON;
using namespace MyDomain;

const uint64_t iterations = 1000000;

class DeserializationFixture
{
protected:
    Document json;
    Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        Account account(1, "Test", "USD", 1000);
        account.AddOrder(Order(1, "EURUSD", OrderSide::BUY, OrderType::MARKET, 1.23456, 1000));
        account.AddOrder(Order(2, "EURUSD", OrderSide::SELL, OrderType::LIMIT, 1.0, 100));
        account.AddOrder(Order(3, "EURUSD", OrderSide::BUY, OrderType::STOP, 1.5, 10));

        // Serialize the account to the JSON file stream
        StringBuffer buffer;
        Serializer<StringBuffer> serializer(buffer);
        account.SerializeJSON(serializer);

        // Parse JSON string
        json = Parser::Parse(buffer.GetString());
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "JSON-Deserialize", iterations)
{
    deserialized.DeserializeJSON(json);
}

BENCHMARK_MAIN()
