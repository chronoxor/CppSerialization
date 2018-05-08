//
// Created by Ivan Shynkarenka on 30.03.2018
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

const uint64_t iterations = 1000000;

class SerializationFixture
{
protected:
    MyDomain::Account account;
    std::string buffer;

    SerializationFixture() : account(1, "Test", "USD", 1000)
    {
        // Create a new account with some orders
        account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));
    }

    ~SerializationFixture()
    {
        // Delete all global objects allocated by Protobuf
        google::protobuf::ShutdownProtobufLibrary();
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "Protobuf-Serialize", iterations)
{
    // Serialize the account to the Protobuf stream
    MyDomain::protobuf::Account output;
    account.Serialize(output);
    output.SerializeToString(&buffer);

    context.metrics().AddBytes(buffer.size());
    context.metrics().SetCustom("Size", (unsigned)buffer.size());
}

BENCHMARK_MAIN()
