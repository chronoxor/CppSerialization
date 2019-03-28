/*!
    \file sbe.cpp
    \brief SimpleBinaryEncoding serialization example
    \author Ivan Shynkarenka
    \date 02.01.2019
    \copyright MIT License
*/

#include "../proto/trade.h"

#include <iostream>

int main(int argc, char** argv)
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

    // Show the serialized SBE size
    std::cout << "SBE size: " << header.encodedLength() + message.encodedLength() << std::endl;

    // Deserialize the account from the SBE stream
    header.wrap(buffer, 0, 1, sizeof(buffer));
    int actingVersion = header.version();
    int actingBlockLength = header.blockLength();
    message.wrapForDecode(buffer, header.encodedLength(), actingBlockLength, actingVersion, sizeof(buffer));
    TradeProto::Account deserialized;
    deserialized.Deserialize(message);

    // Show account content
    std::cout << std::endl;
    std::cout << "Account.Id = " << deserialized.Id << std::endl;
    std::cout << "Account.Name = " << deserialized.Name << std::endl;
    std::cout << "Account.Wallet.Currency = " << deserialized.Wallet.Currency << std::endl;
    std::cout << "Account.Wallet.Amount = " << deserialized.Wallet.Amount << std::endl;
    for (const auto& order : deserialized.Orders)
    {
        std::cout << "Account.Order => Id: " << order.Id
            << ", Symbol: " << order.Symbol
            << ", Side: " << (int)order.Side
            << ", Type: " << (int)order.Type
            << ", Price: " << order.Price
            << ", Volume: " << order.Volume
            << std::endl;
    }

    return 0;
}
