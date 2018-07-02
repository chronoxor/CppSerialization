/*!
    \file protobuf.cpp
    \brief Protobuf serialization example
    \author Ivan Shynkarenka
    \date 30.03.2017
    \copyright MIT License
*/

#include "../domain/domain.h"

#include <iostream>

int main(int argc, char** argv)
{
    // Create a new account with some orders
    MyDomain::Account account(1, "Test", "USD", 1000);
    account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

    // Serialize the account to the Protobuf stream
    MyDomain::protobuf::Account output;
    account.Serialize(output);
    auto buffer = output.SerializeAsString();

    // Show the serialized Protobuf size
    std::cout << "Protobuf size: " << buffer.size() << std::endl;

    // Deserialize the account from the Protobuf stream
    MyDomain::protobuf::Account input;
    input.ParseFromString(buffer);
    MyDomain::Account deserialized;
    deserialized.Deserialize(input);

    // Show account content
    std::cout << std::endl;
    std::cout << "Account.Uid = " << deserialized.Uid << std::endl;
    std::cout << "Account.Name = " << deserialized.Name << std::endl;
    std::cout << "Account.Wallet.Currency = " << deserialized.Wallet.Currency << std::endl;
    std::cout << "Account.Wallet.Amount = " << deserialized.Wallet.Amount << std::endl;
    for (auto& order : deserialized.Orders)
    {
        std::cout << "Account.Order => Uid: " << order.Uid
            << ", Symbol: " << order.Symbol
            << ", Side: " << (int)order.Side
            << ", Type: " << (int)order.Type
            << ", Price: " << order.Price
            << ", Volume: " << order.Volume
            << std::endl;
    }

    // Delete all global objects allocated by Protobuf
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
