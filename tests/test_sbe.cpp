//
// Created by Ivan Shynkarenka on 02.01.2019
//

#include "test.h"

#include "../proto/trade.h"

using namespace CppCommon;
using namespace CppSerialization;

TEST_CASE("SimpleBinaryEncoding", "[CppSerialization]")
{
    // Create a new account with some orders
    TradeProto::Account account(1, "Test", "USD", 1000);
    account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

    // Serialize the account to the SBE stream
    char buffer[1024];
    sbe::MessageHeader header;
    header.wrap(buffer, 0, 1, sizeof(buffer))
       .blockLength(sbe::Account::sbeBlockLength())
       .templateId(sbe::Account::sbeTemplateId())
       .schemaId(sbe::Account::sbeSchemaId())
       .version(sbe::Account::sbeSchemaVersion());
    sbe::Account message;
    message.wrapForEncode(buffer, header.encodedLength(), sizeof(buffer));
    account.Serialize(message);
    size_t serialized = header.encodedLength() + message.encodedLength();

    REQUIRE(serialized > 0);

    // Deserialize the account from the SBE stream
    header.wrap(buffer, 0, 1, sizeof(buffer));
    int actingVersion = header.version();
    int actingBlockLength = header.blockLength();
    message.wrapForDecode(buffer, header.encodedLength(), actingBlockLength, actingVersion, sizeof(buffer));
    TradeProto::Account deserialized;
    deserialized.Deserialize(message);

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
