//
// Created by Ivan Shynkarenka on 05.01.2019
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class DeserializationFixture
{
protected:
    FBE::trade::AccountFinalModel writer;
    FBE::trade::AccountFinalModel reader;
    trade::Account account;

    DeserializationFixture()
    {
        // Create a new account with some orders
        account.id = 1;
        account.name = "Test";
        account.wallet.currency = "USD";
        account.wallet.amount = 1000;
        account.orders.emplace_back(trade::Order(1, "EURUSD", trade::OrderSide::buy, trade::OrderType::market, 1.23456, 1000));
        account.orders.emplace_back(trade::Order(2, "EURUSD", trade::OrderSide::sell, trade::OrderType::limit, 1.0, 100));
        account.orders.emplace_back(trade::Order(3, "EURUSD", trade::OrderSide::buy, trade::OrderType::stop, 1.5, 10));

        // Serialize the account to the FBE stream
        writer.serialize(account);
        assert(writer.verify() && "Model is broken!");
        reader.attach(writer.buffer());
        assert(reader.verify() && "Model is broken!");
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "FastBinaryEncoding-Final-Deserialize")
{
    // Deserialize the account from the FBE stream
    size_t deserialized = reader.deserialize(account);

    context.metrics().AddBytes(deserialized);
    context.metrics().SetCustom("MessageSize", (unsigned)deserialized);
}

BENCHMARK_MAIN()
