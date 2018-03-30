//
// Created by Ivan Shynkarenka on 30.03.2018
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

using namespace MyDomain;

const uint64_t iterations = 1000000;

class SerializationFixture
{
protected:
    Account account;
	std::string buffer;

    SerializationFixture() : account(1, "Test", "USD", 1000)
    {
        // Create a new account with some orders
        account.AddOrder(Order(1, "EURUSD", OrderSide::BUY, OrderType::MARKET, 1.23456, 1000));
        account.AddOrder(Order(2, "EURUSD", OrderSide::SELL, OrderType::LIMIT, 1.0, 100));
        account.AddOrder(Order(3, "EURUSD", OrderSide::BUY, OrderType::STOP, 1.5, 10));
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "Protobuf-Serialize", iterations)
{
    // Serialize the account to the Protobuf stream
    protobuf::Account ouput;
    account.Serialize(ouput);
    ouput.SerializeToString(&buffer);
    context.metrics().AddBytes(buffer.size());
    context.metrics().SetCustom("Size", buffer.size());
}

BENCHMARK_MAIN()
