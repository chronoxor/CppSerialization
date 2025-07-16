//
// Created by Ivan Shynkarenka on 31.03.2018
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

namespace local {

capnp::MallocMessageBuilder output;
kj::VectorOutputStream buffer;

}

class DeserializationFixture
{
protected:
    TradeProto::Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        TradeProto::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

        // Serialize the account to the Cap'n'Proto buffer
        Trade::capnproto::Account::Builder builder = local::output.initRoot<Trade::capnproto::Account>();
        account.Serialize(builder);
        writeMessage(local::buffer, local::output);
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "Cap'n'Proto-Deserialize")
{
    context.metrics().AddBytes(local::buffer.getArray().size());
    context.metrics().SetCustom("MessageSize", (unsigned)local::buffer.getArray().size());

    // Deserialize the account from the Cap'n'Proto buffer
    kj::ArrayInputStream array(local::buffer.getArray());
    capnp::InputStreamMessageReader input(array);
    deserialized.Deserialize(input.getRoot<Trade::capnproto::Account>());

    context.metrics().SetCustom("OriginalSize", (unsigned)deserialized.size());
}

BENCHMARK_MAIN()
