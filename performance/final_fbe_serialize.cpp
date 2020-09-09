//
// Created by Ivan Shynkarenka on 05.01.2019
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class SerializationFixture
{
protected:
    FBE::trade::AccountFinalModel writer;
    trade::Account account;

    SerializationFixture()
    {
        // Create a new account with some orders
        account.id = 1;
        account.name = "Test";
        account.wallet.currency = "USD";
        account.wallet.amount = 1000;
        account.orders.emplace_back(trade::Order(1, "EURUSD", trade::OrderSide::buy, trade::OrderType::market, 1.23456, 1000));
        account.orders.emplace_back(trade::Order(2, "EURUSD", trade::OrderSide::sell, trade::OrderType::limit, 1.0, 100));
        account.orders.emplace_back(trade::Order(3, "EURUSD", trade::OrderSide::buy, trade::OrderType::stop, 1.5, 10));
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "FastBinaryEncoding-Final-Serialize")
{
    // Serialize the account to the FBE stream
    writer.reset();
    size_t serialized = writer.serialize(account);

    context.metrics().AddBytes(serialized);
    context.metrics().SetCustom("Size", (unsigned)serialized);
}

BENCHMARK_MAIN()
