/*!
    \file capnproto.cpp
    \brief Cap'n'Proto serialization example
    \author Ivan Shynkarenka
    \date 31.03.2018
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

    // Serialize the account to the Cap'n'Proto stream
    capnp::MallocMessageBuilder output;
    MyDomain::capnproto::Account::Builder builder = output.initRoot<MyDomain::capnproto::Account>();
    account.Serialize(builder);
    kj::VectorOutputStream buffer;
    writeMessage(buffer, output);

    // Show the serialized Cap'n'Proto size
    std::cout << "Protobuf size: " << buffer.getArray().size() << std::endl;

    // Deserialize the account from the Cap'n'Proto stream
    kj::ArrayInputStream array(buffer.getArray());
    capnp::InputStreamMessageReader input(array);
    MyDomain::Account deserialized;
    deserialized.Deserialize(input.getRoot<MyDomain::capnproto::Account>());

    // Show account content
    std::cout << std::endl;
    std::cout << "Account.Id = " << deserialized.Id << std::endl;
    std::cout << "Account.Name = " << deserialized.Name << std::endl;
    std::cout << "Account.Wallet.Currency = " << deserialized.Wallet.Currency << std::endl;
    std::cout << "Account.Wallet.Amount = " << deserialized.Wallet.Amount << std::endl;
    for (auto& order : deserialized.Orders)
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
