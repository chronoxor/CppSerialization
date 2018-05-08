/*!
    \file domain.h
    \brief Domain model example
    \author Ivan Shynkarenka
    \date 24.02.2017
    \copyright MIT License
*/

#ifndef CPPSERIALIZATION_DOMAIN_DOMAIN_H
#define CPPSERIALIZATION_DOMAIN_DOMAIN_H

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4244) // C4244: conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable: 4245) // C4244: conversion' : conversion from 'type1' to 'type2', signed/unsigned mismatch
#pragma warning(disable: 4267) // C4267: var' : conversion from 'size_t' to 'type', possible loss of data
#endif
#include "capnp/serialize.h"
#include "capnproto/domain.capnp.h"
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
#include "fbe/domain.h"
#include "flatbuffers/domain_generated.h"
#include "protobuf/domain.pb.h"

#include "serialization/json/serializer.h"
#include "serialization/json/deserializer.h"

#include <algorithm>
#include <string>
#include <vector>

namespace MyDomain {

enum class OrderSide : uint8_t
{
    BUY,
    SELL
};

enum class OrderType : uint8_t
{
    MARKET,
    LIMIT,
    STOP
};

struct Order
{
    int Id;
    char Symbol[10];
    OrderSide Side;
    OrderType Type;
    double Price;
    double Volume;

    Order() : Order(0, "<\?\?\?>", OrderSide::BUY, OrderType::MARKET, 0.0, 0.0) {}
    Order(int id, const std::string& symbol, OrderSide side, OrderType type, double price, double volume)
    {
        Id = id;
        std::strncpy(Symbol, symbol.c_str(), std::min(symbol.size() + 1, sizeof(Symbol)));
        Side = side;
        Type = type;
        Price = price;
        Volume = volume;
    }

    // Cap'n'Proto serialization

    void Serialize(capnproto::Order::Builder& builder)
    {
        builder.setId(Id);
        builder.setSymbol(Symbol);
        builder.setSide((capnproto::OrderSide)Side);
        builder.setType((capnproto::OrderType)Type);
        builder.setPrice(Price);
        builder.setVolume(Volume);
    }

    void Deserialize(const capnproto::Order::Reader& reader)
    {
        Id = reader.getId();
        std::string symbol = reader.getSymbol();
        std::strncpy(Symbol, symbol.c_str(), std::min(symbol.size() + 1, sizeof(Symbol)));
        Side = (OrderSide)reader.getSide();
        Type = (OrderType)reader.getType();
        Price = reader.getPrice();
        Volume = reader.getVolume();
    }

    // Fast Binary Encoding serialization

    template <class TBuffer>
    void Serialize(FBE::FieldModel<TBuffer, domain::Order>& model)
    {
        size_t model_begin = model.set_begin();
        model.id.set(Id);
        model.symbol.set(Symbol);
        model.side.set((domain::OrderSide)Side);
        model.type.set((domain::OrderType)Type);
        model.price.set(Price);
        model.volume.set(Volume);
        model.set_end(model_begin);
    }

    template <class TBuffer>
    void Deserialize(const FBE::FieldModel<TBuffer, domain::Order>& model)
    {
        size_t model_begin = model.get_begin();
        model.id.get(Id);
        model.symbol.get(Symbol);
        domain::OrderSide side;
        model.side.get(side);
        Side = (OrderSide)side;
        domain::OrderType type;
        model.type.get(type);
        Type = (OrderType)type;
        model.price.get(Price);
        model.volume.get(Volume);
        model.get_end(model_begin);
    }

    // FlatBuffers serialization

    flatbuffers::Offset<flatbuf::Order> Serialize(flatbuffers::FlatBufferBuilder& builder)
    {
        return flatbuf::CreateOrderDirect(builder, Id, Symbol, (flatbuf::OrderSide)Side, (flatbuf::OrderType)Type, Price, Volume);
    }

    void Deserialize(const flatbuf::Order& value)
    {
        Id = value.id();
        std::string symbol = value.symbol()->str();
        std::strncpy(Symbol, symbol.c_str(), std::min(symbol.size() + 1, sizeof(Symbol)));
        Side = (OrderSide)value.side();
        Type = (OrderType)value.type();
        Price = value.price();
        Volume = value.volume();
    }

    // Protobuf serialization

    protobuf::Order& Serialize(protobuf::Order& value)
    {
        value.set_id(Id);
        value.set_symbol(Symbol);
        value.set_side((protobuf::OrderSide)Side);
        value.set_type((protobuf::OrderType)Type);
        value.set_price(Price);
        value.set_volume(Volume);
        return value;
    }

    void Deserialize(const protobuf::Order& value)
    {
        Id = value.id();
        std::string symbol = value.symbol();
        std::strncpy(Symbol, symbol.c_str(), std::min(symbol.size() + 1, sizeof(Symbol)));
        Side = (OrderSide)value.side();
        Type = (OrderType)value.type();
        Price = value.price();
        Volume = value.volume();
    }

    // JSON serialization

    template<typename OutputStream>
    void Serialize(CppSerialization::JSON::Serializer<OutputStream>& serializer)
    {
        serializer.StartObject();
        serializer.Pair("id", Id);
        serializer.Pair("symbol", Symbol);
        serializer.Pair("side", (int)Side);
        serializer.Pair("type", (int)Type);
        serializer.Pair("price", Price);
        serializer.Pair("volume", Volume);
        serializer.EndObject();
    }

    template<typename JSON>
    void Deserialize(const JSON& json)
    {
        using namespace CppSerialization::JSON;

        Deserializer::Find(json, "id", Id);
        Deserializer::Find(json, "symbol", Symbol);
        int side = 0; Deserializer::Find(json, "side", side); Side = (OrderSide)side;
        int type = 0; Deserializer::Find(json, "type", type); Type = (OrderType)type;
        Deserializer::Find(json, "price", Price);
        Deserializer::Find(json, "volume", Volume);
    }
};

struct Balance
{
    char Currency[10];
    double Amount;

    Balance() : Balance("<\?\?\?>", 0.0) {}
    Balance(const std::string& currency, double amount)
    {
        std::strncpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
        Amount = amount;
    }

    // Cap'n'Proto serialization

    void Serialize(capnproto::Balance::Builder& builder)
    {
        builder.setCurrency(Currency);
        builder.setAmount(Amount);
    }

    void Deserialize(const capnproto::Balance::Reader& reader)
    {
        std::string currency = reader.getCurrency();
        std::strncpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
        Amount = reader.getAmount();
    }

    // Fast Binary Encoding serialization

    template <class TBuffer>
    void Serialize(FBE::FieldModel<TBuffer, domain::Balance>& model)
    {
        size_t model_begin = model.set_begin();
        model.currency.set(Currency);
        model.amount.set(Amount);
        model.set_end(model_begin);
    }

    template <class TBuffer>
    void Deserialize(const FBE::FieldModel<TBuffer, domain::Balance>& model)
    {
        size_t model_begin = model.get_begin();
        model.currency.get(Currency);
        model.amount.get(Amount);
        model.get_end(model_begin);
    }

    // FlatBuffers serialization

    flatbuffers::Offset<flatbuf::Balance> Serialize(flatbuffers::FlatBufferBuilder& builder)
    {
        return flatbuf::CreateBalanceDirect(builder, Currency, Amount);
    }

    void Deserialize(const flatbuf::Balance& value)
    {
        std::string currency = value.currency()->str();
        std::strncpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
        Amount = value.amount();
    }

    // Protobuf serialization

    protobuf::Balance& Serialize(protobuf::Balance& value)
    {
        value.set_currency(Currency);
        value.set_amount(Amount);
        return value;
    }

    void Deserialize(const protobuf::Balance& value)
    {
        std::string currency = value.currency();
        std::strncpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
        Amount = value.amount();
    }

    // JSON serialization

    template<typename OutputStream>
    void Serialize(CppSerialization::JSON::Serializer<OutputStream>& serializer)
    {
        serializer.StartObject();
        serializer.Pair("currency", Currency);
        serializer.Pair("amount", Amount);
        serializer.EndObject();
    }

    template<typename JSON>
    void Deserialize(const JSON& json)
    {
        using namespace CppSerialization::JSON;

        Deserializer::Find(json, "currency", Currency);
        Deserializer::Find(json, "amount", Amount);
    }
};

struct Account
{
    int Id;
    std::string Name;
    Balance Wallet;
    std::vector<Order> Orders;

    Account() : Account(0, "<<\?\?\?>>", "<<\?\?\?>>", 0.0) {}
    Account(int id, const char* name, const char* currency, double amount) : Wallet(currency, amount)
    {
        Id = id;
        Name = name;
    }

    // Cap'n'Proto serialization

    void Serialize(capnproto::Account::Builder& builder)
    {
        builder.setId(Id);
        builder.setName(Name);
        auto wallet = builder.initWallet();
        Wallet.Serialize(wallet);
        auto orders = builder.initOrders((unsigned)Orders.size());
        unsigned index = 0;
        for (auto& order : Orders)
        {
            auto o = orders[index++];
            order.Serialize(o);
        }
    }

    void Deserialize(const capnproto::Account::Reader& reader)
    {
        Id = reader.getId();
        Name = reader.getName().cStr();
        Wallet.Deserialize(reader.getWallet());
        Orders.clear();
        for (auto o : reader.getOrders())
        {
            Order order;
            order.Deserialize(o);
            Orders.emplace_back(order);
        }
    }

    // Fast Binary Encoding serialization

    template <class TBuffer>
    void Serialize(FBE::FieldModel<TBuffer, domain::Account>& model)
    {
        size_t model_begin = model.set_begin();
        model.id.set(Id);
        model.name.set(Name);
        Wallet.Serialize(model.wallet);
        auto order_model = model.orders.resize(Orders.size());
        for (auto& order : Orders)
        {
            order.Serialize(order_model);
            order_model.fbe_shift(order_model.fbe_size());
        }
        model.set_end(model_begin);
    }

    template <class TBuffer>
    void Deserialize(const FBE::FieldModel<TBuffer, domain::Account>& model)
    {
        size_t model_begin = model.get_begin();
        model.id.get(Id);
        model.name.get(Name);
        Wallet.Deserialize(model.wallet);
        Orders.clear();
        for (size_t i = 0; i < model.orders.size(); ++i)
        {
            Order order;
            order.Deserialize(model.orders[i]);
            Orders.emplace_back(order);
        }
        model.get_end(model_begin);
    }

    // FlatBuffers serialization

    flatbuffers::Offset<flatbuf::Account> Serialize(flatbuffers::FlatBufferBuilder& builder)
    {
        auto wallet = Wallet.Serialize(builder);
        std::vector<flatbuffers::Offset<flatbuf::Order>> orders;
        for (auto& order : Orders)
            orders.emplace_back(order.Serialize(builder));
        return flatbuf::CreateAccountDirect(builder, Id, Name.c_str(), wallet, &orders);
    }

    void Deserialize(const flatbuf::Account& value)
    {
        Id = value.id();
        Name = value.name()->str();
        Wallet.Deserialize(*value.wallet());
        Orders.clear();
        for (auto o : *value.orders())
        {
            Order order;
            order.Deserialize(*o);
            Orders.emplace_back(order);
        }
    }

    // Protobuf serialization

    protobuf::Account& Serialize(protobuf::Account& value)
    {
        value.set_id(Id);
        value.set_name(Name);
        value.set_allocated_wallet(&Wallet.Serialize(*value.wallet().New(value.GetArena())));
        for (auto& order : Orders)
            order.Serialize(*value.add_orders());
        return value;
    }

    void Deserialize(const protobuf::Account& value)
    {
        Id = value.id();
        Name = value.name();
        Wallet.Deserialize(value.wallet());
        Orders.clear();
        for (int i = 0; i < value.orders_size(); ++i)
        {
            Order order;
            order.Deserialize(value.orders(i));
            Orders.emplace_back(order);
        }
    }

    // JSON serialization

    template<typename OutputStream>
    void Serialize(CppSerialization::JSON::Serializer<OutputStream>& serializer)
    {
        serializer.StartObject();
        serializer.Pair("id", Id);
        serializer.Pair("name", Name);
        serializer.Key("wallet");
        Wallet.Serialize(serializer);
        serializer.Key("orders");
        serializer.StartArray();
        for (auto& order : Orders)
            order.Serialize(serializer);
        serializer.EndArray();
        serializer.EndObject();
    }

    template<typename JSON>
    void Deserialize(const JSON& json)
    {
        using namespace CppSerialization::JSON;

        Deserializer::Find(json, "id", Id);
        Deserializer::Find(json, "name", Name);
        Deserializer::FindObject(json, "wallet", [this](const Value::ConstObject& object)
        {
            Wallet.Deserialize(object);
        });
        Orders.clear();
        Deserializer::FindArray(json, "orders", [this](const Value& item)
        {
            Order order;
            order.Deserialize(item);
            Orders.emplace_back(order);
        });
    }
};

} // namespace MyDomain

#endif // CPPSERIALIZATION_DOMAIN_DOMAIN_H
