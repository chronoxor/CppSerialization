//
// Created by Ivan Shynkarenka on 02.01.2019
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class SerializationFixture
{
protected:
    char buffer[1024];
    sbe::MessageHeader header;
    sbe::Account message;
    TradeProto::Account account;

    SerializationFixture() : account(1, "Test", "USD", 1000)
    {
        // Create a new account with some orders
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));
    }
};

BENCHMARK_FIXTURE(SerializationFixture, "SimpleBinaryEncoding-Serialize")
{
    // Serialize the account to the SBE stream
    header.wrap(buffer, 0, 1, sizeof(buffer))
       .blockLength(sbe::Account::sbeBlockLength())
       .templateId(sbe::Account::sbeTemplateId())
       .schemaId(sbe::Account::sbeSchemaId())
       .version(sbe::Account::sbeSchemaVersion());
    message.wrapForEncode(buffer, header.encodedLength(), sizeof(buffer));
    account.Serialize(message);
    size_t serialized = header.encodedLength() + message.encodedLength();

    context.metrics().AddBytes(serialized);
    context.metrics().SetCustom("OriginalSize", (unsigned)account.size());
    context.metrics().SetCustom("MessageSize", (unsigned)serialized);
}

BENCHMARK_MAIN()
