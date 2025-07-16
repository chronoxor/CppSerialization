//
// Created by Ivan Shynkarenka on 16.07.2025
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class DeserializationFixture
{
protected:
    std::array<std::byte, 0x1000> buffer;
    TradeProto::Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        TradeProto::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

        // Serialize the account to the zpp::bits buffer
        (void) zpp::bits::out{buffer}(account);
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "zpp::bits-Deserialize")
{
    // Deserialize the account from the zpp::bits buffer
    zpp::bits::in in{buffer};
    (void) in(deserialized);

    context.metrics().AddBytes(in.position());
    context.metrics().SetCustom("MessageSize", (unsigned)in.position());
    context.metrics().SetCustom("OriginalSize", (unsigned)deserialized.size());
}

BENCHMARK_MAIN()
