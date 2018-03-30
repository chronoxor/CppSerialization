//
// Created by Ivan Shynkarenka on 30.03.2018
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

using namespace MyDomain;

const uint64_t iterations = 1000000;

class DeserializationFixture
{
protected:
    std::string buffer;
    Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        Account account(1, "Test", "USD", 1000);
        account.AddOrder(Order(1, "EURUSD", OrderSide::BUY, OrderType::MARKET, 1.23456, 1000));
        account.AddOrder(Order(2, "EURUSD", OrderSide::SELL, OrderType::LIMIT, 1.0, 100));
        account.AddOrder(Order(3, "EURUSD", OrderSide::BUY, OrderType::STOP, 1.5, 10));

        // Serialize the account to the Protobuf stream
        protobuf::Account ouput;
        account.Serialize(ouput);
        buffer = ouput.SerializeAsString();
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "Protobuf-Deserialize", iterations)
{
    // Deserialize the account from the Protobuf stream
    protobuf::Account input;
    input.ParseFromString(buffer);
    deserialized.Deserialize(input);
    context.metrics().AddBytes(buffer.size());
    context.metrics().SetCustom("Size", (unsigned)buffer.size());
}

BENCHMARK_MAIN()
