//
// Created by Ivan Shynkarenka on 08.05.2018
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class SerializationFixture
{
protected:
    FBE::trade::AccountModel<FBE::WriteBuffer> writer;
    TradeProto::Account account;

    SerializationFixture() : account(1, "Test", "USD", 1000)
    {
        // Create a new account with some orders
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "FastBinaryEncoding-Serialize")
{
    // Serialize the account to the FBE stream
    writer.reset();
    size_t model_begin = writer.create_begin();
    account.Serialize(writer.model);
    size_t serialized = writer.create_end(model_begin);

    context.metrics().AddBytes(serialized);
    context.metrics().SetCustom("Size", (unsigned)serialized);
}

BENCHMARK_MAIN()
