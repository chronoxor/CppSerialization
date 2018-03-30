/*!
    \file domain.h
    \brief Domain model example
    \author Ivan Shynkarenka
    \date 24.02.2017
    \copyright MIT License
*/

#ifndef CPPSERIALIZATION_DOMAIN_DOMAIN_H
#define CPPSERIALIZATION_DOMAIN_DOMAIN_H

#include "flatbuffers/domain_generated.h"
#include "protobuf/domain.pb.h"

#include "serialization/json/serializer.h"
#include "serialization/json/deserializer.h"

#include <algorithm>
#include <map>
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
    char Symbol[32];
    OrderSide Side;
    OrderType Type;
    double Price;
    double Volume;

    Order() : Order(0, "<unknown>", OrderSide::BUY, OrderType::MARKET, 0.0, 0.0) {}
    Order(int id, const std::string& symbol, OrderSide side, OrderType type, double price, double volume)
    {
        Id = id;
        std::strncpy(Symbol, symbol.c_str(), std::min(symbol.size() + 1, sizeof(Symbol)));
        Side = side;
        Type = type;
        Price = price;
        Volume = volume;
    }

    // FlatBuffers serialization

    flatbuffers::Offset<flatbuf::Order> Serialize(flatbuffers::FlatBufferBuilder& builder)
    {
        return flatbuf::CreateOrderDirect(builder, Id, Symbol, (flatbuf::OrderSide)Side, (flatbuf::OrderType)Type, Price, Volume);
    }

    void Deserialize(const flatbuf::Order& value)
    {
        Id = value.Id();
        std::strncpy(Symbol, value.Symbol()->c_str(), std::min((size_t)value.Symbol()->Length() + 1, sizeof(Symbol)));
        Side = (OrderSide)value.Side();
        Type = (OrderType)value.Type();
        Price = value.Price();
        Volume = value.Volume();
    }

    // Protobuf serialization

	protobuf::Order& Serialize(protobuf::Order& value)
    {
		value.set_id(Id);
		value.set_symbol(Symbol);
		value.set_side((MyDomain::protobuf::OrderSide)Side);
		value.set_type((MyDomain::protobuf::OrderType)Type);
		value.set_price(Price);
		value.set_volume(Volume);
		return value;
    }

    void Deserialize(const protobuf::Order& value)
    {
        Id = value.id();
        std::strncpy(Symbol, value.symbol().c_str(), std::min((size_t)value.symbol().size() + 1, sizeof(Symbol)));
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
    char Currency[12];
    double Amount;

    Balance() : Balance("<?>", 0.0) {}
    Balance(const std::string& currency, double amount)
    {
        std::strncpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
        Amount = amount;
    }

    // FlatBuffers serialization

    flatbuffers::Offset<flatbuf::Balance> Serialize(flatbuffers::FlatBufferBuilder& builder)
    {
        return flatbuf::CreateBalanceDirect(builder, Currency, Amount);
    }

    void Deserialize(const flatbuf::Balance& value)
    {
        std::strncpy(Currency, value.Currency()->c_str(), std::min((size_t)value.Currency()->Length() + 1, sizeof(Currency)));
        Amount = value.Amount();
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
		std::strncpy(Currency, value.currency().c_str(), std::min((size_t)value.currency().size() + 1, sizeof(Currency)));
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
    std::map<int, Order> Orders;

    Account() : Account(0, "<unknown>", "<unknown>", 0.0) {}
    Account(int id, const char* name, const char* currency, double amount) : Wallet(currency, amount)
    {
        Id = id;
        Name = name;
    }

    // FlatBuffers serialization

    flatbuffers::Offset<flatbuf::Account> Serialize(flatbuffers::FlatBufferBuilder& builder)
    {
        auto wallet = Wallet.Serialize(builder);
        std::vector<flatbuffers::Offset<flatbuf::Order>> orders;
        for (auto& order : Orders)
            orders.emplace_back(order.second.Serialize(builder));
        return flatbuf::CreateAccountDirect(builder, Id, Name.c_str(), wallet, &orders);
    }

    void Deserialize(const flatbuf::Account& value)
    {
        Id = value.Id();
        Name = value.Name()->str();
        Wallet.Deserialize(*value.Wallet());
        for (auto item : *value.Orders())
        {
            Order order;
            order.Deserialize(*item);
            AddOrder(order);
        }
    }

	// Protobuf serialization

	protobuf::Account& Serialize(protobuf::Account& value)
	{
		value.set_id(Id);
		value.set_name(Name);
		value.set_allocated_wallet(&Wallet.Serialize(*value.wallet().New(value.GetArena())));
		for (auto& order : Orders)
			order.second.Serialize(*value.add_orders());
		return value;
	}

	void Deserialize(const protobuf::Account& value)
	{
		Id = value.id();
		Name = value.name();
		Wallet.Deserialize(value.wallet());
		for (int i = 0; i < value.orders_size(); ++i)
		{
			Order order;
			order.Deserialize(value.orders(i));
			AddOrder(order);
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
            order.second.Serialize(serializer);
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
        Deserializer::FindArray(json, "orders", [this](const Value& item)
        {
            Order order;
            order.Deserialize(item);
            AddOrder(order);
        });
    }

    void AddOrder(const Order& order)
    {
        Orders[order.Id] = order;
    }
};

} // namespace MyDomain

#endif // CPPSERIALIZATION_DOMAIN_DOMAIN_H
