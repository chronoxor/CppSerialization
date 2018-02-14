//
// Created by Ivan Shynkarenka on 28.02.2017
//

#include "test.h"

#include "../domain/domain.h"

#include "serialization/json/parser.h"

using namespace CppCommon;
using namespace CppSerialization::JSON;
using namespace MyDomain;

TEST_CASE("JSON", "[CppSerialization]")
{
    // Create a new account with some orders
    Account account(1, "Test", "USD", 1000);
    account.AddOrder(Order(1, "EURUSD", OrderSide::BUY, OrderType::MARKET, 1.23456, 1000));
    account.AddOrder(Order(2, "EURUSD", OrderSide::SELL, OrderType::LIMIT, 1.0, 100));
    account.AddOrder(Order(3, "EURUSD", OrderSide::BUY, OrderType::STOP, 1.5, 10));

    // Serialize the account to the JSON file stream
    StringBuffer buffer;
    Serializer<StringBuffer> serializer(buffer);
    account.SerializeJSON(serializer);

    REQUIRE(buffer.GetLength() > 0);
    REQUIRE(buffer.GetString() != nullptr);

    // Parse JSON string
    Document json = Parser::Parse(buffer.GetString());

    // Deserialize the account from the JSON file stream
    Account deserialized;
    deserialized.DeserializeJSON(json);

    REQUIRE(deserialized.Id == 1);
    REQUIRE(deserialized.Name == "Test");
    REQUIRE(deserialized.Name == "Test");
    REQUIRE(std::string(deserialized.Wallet.Currency) == "USD");
    REQUIRE(deserialized.Wallet.Amount == 1000);
    REQUIRE(deserialized.Orders.size() == 3);
    REQUIRE(deserialized.Orders[1].Id == 1);
    REQUIRE(std::string(deserialized.Orders[1].Symbol) == "EURUSD");
    REQUIRE(deserialized.Orders[1].Side == OrderSide::BUY);
    REQUIRE(deserialized.Orders[1].Type == OrderType::MARKET);
    REQUIRE(deserialized.Orders[1].Price == 1.23456);
    REQUIRE(deserialized.Orders[1].Volume == 1000);
    REQUIRE(deserialized.Orders[2].Id == 2);
    REQUIRE(std::string(deserialized.Orders[2].Symbol) == "EURUSD");
    REQUIRE(deserialized.Orders[2].Side == OrderSide::SELL);
    REQUIRE(deserialized.Orders[2].Type == OrderType::LIMIT);
    REQUIRE(deserialized.Orders[2].Price == 1.0);
    REQUIRE(deserialized.Orders[2].Volume == 100);
    REQUIRE(deserialized.Orders[3].Id == 3);
    REQUIRE(std::string(deserialized.Orders[3].Symbol) == "EURUSD");
    REQUIRE(deserialized.Orders[3].Side == OrderSide::BUY);
    REQUIRE(deserialized.Orders[3].Type == OrderType::STOP);
    REQUIRE(deserialized.Orders[3].Price == 1.5);
    REQUIRE(deserialized.Orders[3].Volume == 10);
}
