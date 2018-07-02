//
// Created by Ivan Shynkarenka on 28.02.2017
//

#include "test.h"

#include "../domain/domain.h"

#include "serialization/json/parser.h"

using namespace CppCommon;
using namespace CppSerialization::JSON;

TEST_CASE("JSON", "[CppSerialization]")
{
    // Create a new account with some orders
    MyDomain::Account account(1, "Test", "USD", 1000);
    account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

    // Serialize the account to the JSON file stream
    StringBuffer buffer;
    Serializer<StringBuffer> serializer(buffer);
    account.Serialize(serializer);

    REQUIRE(buffer.GetLength() > 0);
    REQUIRE(buffer.GetString() != nullptr);

    // Parse JSON string
    Document json = Parser::Parse(buffer.GetString());

    // Deserialize the account from the JSON file stream
    MyDomain::Account deserialized;
    deserialized.Deserialize(json);

    REQUIRE(deserialized.Uid == 1);
    REQUIRE(deserialized.Name == "Test");
    REQUIRE(std::string(deserialized.Wallet.Currency) == "USD");
    REQUIRE(deserialized.Wallet.Amount == 1000);
    REQUIRE(deserialized.Orders.size() == 3);
    REQUIRE(deserialized.Orders[0].Uid == 1);
    REQUIRE(std::string(deserialized.Orders[0].Symbol) == "EURUSD");
    REQUIRE(deserialized.Orders[0].Side == MyDomain::OrderSide::BUY);
    REQUIRE(deserialized.Orders[0].Type == MyDomain::OrderType::MARKET);
    REQUIRE(deserialized.Orders[0].Price == 1.23456);
    REQUIRE(deserialized.Orders[0].Volume == 1000);
    REQUIRE(deserialized.Orders[1].Uid == 2);
    REQUIRE(std::string(deserialized.Orders[1].Symbol) == "EURUSD");
    REQUIRE(deserialized.Orders[1].Side == MyDomain::OrderSide::SELL);
    REQUIRE(deserialized.Orders[1].Type == MyDomain::OrderType::LIMIT);
    REQUIRE(deserialized.Orders[1].Price == 1.0);
    REQUIRE(deserialized.Orders[1].Volume == 100);
    REQUIRE(deserialized.Orders[2].Uid == 3);
    REQUIRE(std::string(deserialized.Orders[2].Symbol) == "EURUSD");
    REQUIRE(deserialized.Orders[2].Side == MyDomain::OrderSide::BUY);
    REQUIRE(deserialized.Orders[2].Type == MyDomain::OrderType::STOP);
    REQUIRE(deserialized.Orders[2].Price == 1.5);
    REQUIRE(deserialized.Orders[2].Volume == 10);
}
