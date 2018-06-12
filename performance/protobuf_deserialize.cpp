//
// Created by Ivan Shynkarenka on 30.03.2018
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

const uint64_t operations = 1000000;

class DeserializationFixture
{
protected:
    std::string buffer;
    MyDomain::Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        MyDomain::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

        // Serialize the account to the Protobuf stream
        MyDomain::protobuf::Account output;
        account.Serialize(output);
        buffer = output.SerializeAsString();
    }

    ~DeserializationFixture()
    {
        // Delete all global objects allocated by Protobuf
        google::protobuf::ShutdownProtobufLibrary();
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "Protobuf-Deserialize", operations)
{
    context.metrics().AddBytes(buffer.size());
    context.metrics().SetCustom("Size", (unsigned)buffer.size());

    // Deserialize the account from the Protobuf stream
    MyDomain::protobuf::Account input;
    input.ParseFromString(buffer);
    deserialized.Deserialize(input);
}

BENCHMARK_MAIN()
