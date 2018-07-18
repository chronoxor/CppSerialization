//
// Created by Ivan Shynkarenka on 08.05.2018
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class DeserializationFixture
{
protected:
    FBE::trade::AccountModel<FBE::WriteBuffer> writer;
    FBE::trade::AccountModel<FBE::ReadBuffer> reader;
    TradeProto::Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        TradeProto::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

        // Serialize the account to the FBE stream
        size_t model_begin = writer.create_begin();
        account.Serialize(writer.model);
        writer.create_end(model_begin);
        assert(writer.verify() && "Model is broken!");
        reader.attach(writer.buffer());
        assert(reader.verify() && "Model is broken!");
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "FastBinaryEncoding-Deserialize")
{
    context.metrics().AddBytes(reader.buffer().size());
    context.metrics().SetCustom("Size", (unsigned)reader.buffer().size());

    // Deserialize the account from the FBE stream
    deserialized.Deserialize(reader.model);
}

BENCHMARK_MAIN()
