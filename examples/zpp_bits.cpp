/*!
    \file zpp_bits.cpp
    \brief zpp_bits serialization example
    \author Ivan Shynkarenka
    \date 30.03.2017
    \copyright MIT License
*/

#include "../proto/trade.h"
#include "zpp_bits/zpp_bits.h"

#include <iostream>

namespace TradeProto
{
auto serialize(const Order &) -> zpp::bits::members<6>;
auto serialize(const Account &) -> zpp::bits::members<4>;
auto serialize(const Balance &) -> zpp::bits::members<2>;
}

int main(int argc, char** argv)
{
    // Create a new account with some orders
    TradeProto::Account account(1, "Test", "USD", 1000);
    account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

    // Serialize the account to bytes.
    auto [data, out] = zpp::bits::data_out();
    (void) out(account);

    // Show the serialized size
    std::cout << "zpp_bits data size: " << data.size() << std::endl;

    TradeProto::Account deserialized;
    (void) zpp::bits::in{data}(deserialized);

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
