//
// Created by Ivan Shynkarenka on 31.03.2018
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

using namespace MyDomain;

const uint64_t iterations = 1000000;

namespace local {

capnp::MallocMessageBuilder output;
kj::VectorOutputStream buffer;

}

class DeserializationFixture
{
protected:
    Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        Account account(1, "Test", "USD", 1000);
        account.AddOrder(Order(1, "EURUSD", OrderSide::BUY, OrderType::MARKET, 1.23456, 1000));
        account.AddOrder(Order(2, "EURUSD", OrderSide::SELL, OrderType::LIMIT, 1.0, 100));
        account.AddOrder(Order(3, "EURUSD", OrderSide::BUY, OrderType::STOP, 1.5, 10));

        // Serialize the account to the Cap'n'Proto stream
        MyDomain::capnproto::Account::Builder builder = local::output.initRoot<MyDomain::capnproto::Account>();
        account.Serialize(builder);
        writeMessage(local::buffer, local::output);
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "Cap'n'Proto-Deserialize", iterations)
{
    context.metrics().AddBytes(local::buffer.getArray().size());
    context.metrics().SetCustom("Size", (unsigned)local::buffer.getArray().size());

    // Deserialize the account from the Cap'n'Proto stream
    kj::ArrayInputStream array(local::buffer.getArray());
    capnp::InputStreamMessageReader input(array);
    deserialized.Deserialize(input.getRoot<MyDomain::capnproto::Account>());
}

BENCHMARK_MAIN()
