//
// Created by Ivan Shynkarenka on 30.03.2018
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"
#include "zpp_bits/zpp_bits.h"

namespace TradeProto
{
auto serialize(const Order &) -> zpp::bits::members<6>;
auto serialize(const Account &) -> zpp::bits::members<4>;
auto serialize(const Balance &) -> zpp::bits::members<2>;
}

class SerializationFixture
{
protected:
    TradeProto::Account account;
    std::array<std::byte, 0x1000> buffer;

    SerializationFixture() : account(1, "Test", "USD", 1000)
    {
        // Create a new account with some orders
        account.Orders.emplace_back(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000);
        account.Orders.emplace_back(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100);
        account.Orders.emplace_back(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10);
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "ZppBits-Serialize")
{
    zpp::bits::out out{buffer};
    (void) out(account);
    context.metrics().AddBytes(out.position());
    context.metrics().SetCustom("Size", (unsigned)out.position());
}

BENCHMARK_MAIN()
