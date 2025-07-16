//
// Created by Ivan Shynkarenka on 03.03.2017
//

#include "test.h"

#include "../proto/trade.h"

using namespace CppCommon;
using namespace CppSerialization;

TEST_CASE("FlatBuffers", "[CppSerialization]")
{
    // Create a new account with some orders
    TradeProto::Account account(1, "Test", "USD", 1000);
    account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

    // Serialize the account to the FlatBuffer buffer
    flatbuffers::FlatBufferBuilder builder;
    builder.Finish(account.Serialize(builder));

    REQUIRE(builder.GetSize() > 0);
    REQUIRE(builder.GetBufferPointer() != nullptr);

    // Deserialize the account from the FlatBuffer buffer
    TradeProto::Account deserialized;
    deserialized.Deserialize(*Trade::flatbuf::GetAccount(builder.GetBufferPointer()));

    REQUIRE(deserialized.Id == 1);
    REQUIRE(deserialized.Name == "Test");
    REQUIRE(std::string(deserialized.Wallet.Currency) == "USD");
    REQUIRE(deserialized.Wallet.Amount == 1000);
    REQUIRE(deserialized.Orders.size() == 3);
    REQUIRE(deserialized.Orders[0].Id == 1);
    REQUIRE(std::string(deserialized.Orders[0].Symbol) == "EURUSD");
    REQUIRE(deserialized.Orders[0].Side == TradeProto::OrderSide::BUY);
    REQUIRE(deserialized.Orders[0].Type == TradeProto::OrderType::MARKET);
    REQUIRE(deserialized.Orders[0].Price == 1.23456);
    REQUIRE(deserialized.Orders[0].Volume == 1000);
    REQUIRE(deserialized.Orders[1].Id == 2);
    REQUIRE(std::string(deserialized.Orders[1].Symbol) == "EURUSD");
    REQUIRE(deserialized.Orders[1].Side == TradeProto::OrderSide::SELL);
    REQUIRE(deserialized.Orders[1].Type == TradeProto::OrderType::LIMIT);
    REQUIRE(deserialized.Orders[1].Price == 1.0);
    REQUIRE(deserialized.Orders[1].Volume == 100);
    REQUIRE(deserialized.Orders[2].Id == 3);
    REQUIRE(std::string(deserialized.Orders[2].Symbol) == "EURUSD");
    REQUIRE(deserialized.Orders[2].Side == TradeProto::OrderSide::BUY);
    REQUIRE(deserialized.Orders[2].Type == TradeProto::OrderType::STOP);
    REQUIRE(deserialized.Orders[2].Price == 1.5);
    REQUIRE(deserialized.Orders[2].Volume == 10);
}
