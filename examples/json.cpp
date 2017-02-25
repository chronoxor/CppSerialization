/*!
    \file json.cpp
    \brief JSON serialization example
    \author Ivan Shynkarenka
    \date 24.02.2017
    \copyright MIT License
*/

#include "domain.h"

#include <iostream>

int main(int argc, char** argv)
{
    // Create a new account with some orders
    Account account(1, "Test", 1000);
    account.AddOrder(Order(1, "EURUSD", OrderSide::BUY, OrderType::MARKET, 1.23456, 1000));
    account.AddOrder(Order(2, "EURUSD", OrderSide::SELL, OrderType::LIMIT, 1.0, 100));
    account.AddOrder(Order(3, "EURUSD", OrderSide::BUY, OrderType::STOP, 1.5, 10));

    // Serialize the account to the JSON file stream
    CppSerialization::JSON::StringBuffer buffer;
    CppSerialization::JSON::Serializer<CppSerialization::JSON::StringBuffer> serializer(buffer);
    JSONSerialize(serializer, account);

    // Show the serialized JSON
    std::cerr << "JSON: " << buffer.GetString() << std::endl;

    return 0;
}
