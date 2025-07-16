//
// Created by Ivan Shynkarenka on 02.01.2019
//

#include "benchmark/cppbenchmark.h"

#include "../proto/trade.h"

class DeserializationFixture
{
protected:
    char buffer[1024];
    sbe::MessageHeader header;
    sbe::Account message;
    size_t serialized;
    TradeProto::Account deserialized;

    DeserializationFixture()
    {
        // Create a new account with some orders
        TradeProto::Account account(1, "Test", "USD", 1000);
        account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
        account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
        account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

        // Serialize the account to the SBE buffer
        header.wrap(buffer, 0, 1, sizeof(buffer))
           .blockLength(sbe::Account::sbeBlockLength())
           .templateId(sbe::Account::sbeTemplateId())
           .schemaId(sbe::Account::sbeSchemaId())
           .version(sbe::Account::sbeSchemaVersion());
        message.wrapForEncode(buffer, header.encodedLength(), sizeof(buffer));
        account.Serialize(message);
        serialized = header.encodedLength() + message.encodedLength();
    }
};

BENCHMARK_FIXTURE(DeserializationFixture, "SimpleBinaryEncoding-Deserialize")
{
    context.metrics().AddBytes(serialized);
    context.metrics().SetCustom("MessageSize", (unsigned)serialized);

    // Deserialize the account from the SBE buffer
    header.wrap(buffer, 0, 1, sizeof(buffer));
    int actingVersion = header.version();
    int actingBlockLength = header.blockLength();
    message.wrapForDecode(buffer, header.encodedLength(), actingBlockLength, actingVersion, sizeof(buffer));
    deserialized.Deserialize(message);

    context.metrics().SetCustom("OriginalSize", (unsigned)deserialized.size());
}

BENCHMARK_MAIN()
