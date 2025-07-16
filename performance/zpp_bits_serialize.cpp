//
// Created by Ivan Shynkarenka on 16.07.2025
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class SerializationFixture
{
protected:
    std::array<std::byte, 0x1000> buffer;
    TradeProto::Account account;

    SerializationFixture() : account(1, "Test", "USD", 1000)
    {
        // Create a new account with some orders
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "zpp::bits-Serialize")
{
    // Serialize the account to the zpp::bits buffer
    zpp::bits::out out{buffer};
    (void) out(account);

    context.metrics().AddBytes(out.position());
    context.metrics().SetCustom("OriginalSize", (unsigned)account.size());
    context.metrics().SetCustom("MessageSize", (unsigned)out.position());
}

BENCHMARK_MAIN()
