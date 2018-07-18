//
// Created by Ivan Shynkarenka on 31.03.2018
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class SerializationFixture
{
protected:
    TradeProto::Account account;

    SerializationFixture() : account(1, "Test", "USD", 1000)
    {
        // Create a new account with some orders
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "Cap'n'Proto-Serialize")
{
    // Serialize the account to the Cap'n'Proto stream
    capnp::MallocMessageBuilder output;
    Trade::capnproto::Account::Builder builder = output.initRoot<Trade::capnproto::Account>();
    account.Serialize(builder);
    kj::VectorOutputStream buffer;
    writeMessage(buffer, output);

    context.metrics().AddBytes(buffer.getArray().size());
    context.metrics().SetCustom("Size", (unsigned)buffer.getArray().size());
}

BENCHMARK_MAIN()
