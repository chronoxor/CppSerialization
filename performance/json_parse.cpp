//
// Created by Ivan Shynkarenka on 28.02.2017
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

#include "serialization/json/parser.h"

using namespace CppSerialization::JSON;

class ParserFixture
{
protected:
    StringBuffer buffer;

    ParserFixture()
    {
        // Create a new account with some orders
        TradeProto::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

        // Serialize the account to the JSON stream
        Serializer<StringBuffer> serializer(buffer);
        account.Serialize(serializer);
    }
};

BENCHMARK_FIXTURE(ParserFixture, "JSON-Parse")
{
    context.metrics().AddBytes(buffer.GetSize());
    context.metrics().SetCustom("MessageSize", (unsigned)buffer.GetSize());

    // Parse JSON document from the JSON stream
    Document json = Parser::Parse(buffer.GetString());
}

BENCHMARK_MAIN()
