//
// Created by Ivan Shynkarenka on 31.03.2018
//

#include "benchmark/cppbenchmark.h"

#include "../domain/domain.h"

const uint64_t operations = 1000000;

namespace local {

capnp::MallocMessageBuilder output;
kj::VectorOutputStream buffer;

}

class DeserializationFixture
{
protected:
    MyDomain::Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        MyDomain::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

        // Serialize the account to the Cap'n'Proto stream
        MyDomain::capnproto::Account::Builder builder = local::output.initRoot<MyDomain::capnproto::Account>();
        account.Serialize(builder);
        writeMessage(local::buffer, local::output);
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "Cap'n'Proto-Deserialize", operations)
{
    context.metrics().AddBytes(local::buffer.getArray().size());
    context.metrics().SetCustom("Size", (unsigned)local::buffer.getArray().size());

    // Deserialize the account from the Cap'n'Proto stream
    kj::ArrayInputStream array(local::buffer.getArray());
    capnp::InputStreamMessageReader input(array);
    deserialized.Deserialize(input.getRoot<MyDomain::capnproto::Account>());
}

BENCHMARK_MAIN()
