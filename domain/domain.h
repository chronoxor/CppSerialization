/*!
    \file domain.h
    \brief Domain model example
    \author Ivan Shynkarenka
    \date 24.02.2017
    \copyright MIT License
*/

#include "domain_generated.h"

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

    flatbuffers::Offset<flat::Order> SerializeFlatbuffer(flatbuffers::FlatBufferBuilder& builder)
    {
        return flat::CreateOrderDirect(builder, Id, Symbol, (flat::OrderSide)Side, (flat::OrderType)Type, Price, Volume);
    }

    void DeserializeFlatbuffer(const MyDomain::flat::Order& value)
    {
        Id = value.Id();
        std::strncpy(Symbol, value.Symbol()->c_str(), std::min((size_t)value.Symbol()->Length() + 1, sizeof(Symbol)));
        Side = (OrderSide)value.Side();
        Type = (OrderType)value.Type();
        Price = value.Price();
        Volume = value.Volume();
    }

    // JSON serialization

    template<typename OutputStream>
    void SerializeJSON(CppSerialization::JSON::Serializer<OutputStream>& serializer)
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
    void DeserializeJSON(const JSON& json)
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

    flatbuffers::Offset<flat::Balance> SerializeFlatBuffer(flatbuffers::FlatBufferBuilder& builder)
    {
        return flat::CreateBalanceDirect(builder, Currency, Amount);
    }

    void DeserializeFlatBuffer(const MyDomain::flat::Balance& value)
    {
        std::strncpy(Currency, value.Currency()->c_str(), std::min((size_t)value.Currency()->Length() + 1, sizeof(Currency)));
        Amount = value.Amount();
    }

    // JSON serialization

    template<typename OutputStream>
    void SerializeJSON(CppSerialization::JSON::Serializer<OutputStream>& serializer)
    {
        serializer.StartObject();
        serializer.Pair("currency", Currency);
        serializer.Pair("amount", Amount);
        serializer.EndObject();
    }

    template<typename JSON>
    void DeserializeJSON(const JSON& json)
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

    flatbuffers::Offset<flat::Account> SerializeFlatBuffer(flatbuffers::FlatBufferBuilder& builder)
    {
        auto wallet = Wallet.SerializeFlatBuffer(builder);
        std::vector<flatbuffers::Offset<flat::Order>> orders;
        for (auto order : Orders)
            orders.emplace_back(order.second.SerializeFlatbuffer(builder));
        return flat::CreateAccountDirect(builder, Id, Name.c_str(), wallet, &orders);
    }

    void DeserializeFlatBuffer(const MyDomain::flat::Account& value)
    {
        Id = value.Id();
        Name = value.Name()->str();
        Wallet.DeserializeFlatBuffer(*value.Wallet());
        for (auto item : *value.Orders())
        {
            Order order;
            order.DeserializeFlatbuffer(*item);
            AddOrder(order);
        }
    }

    // JSON serialization

    template<typename OutputStream>
    void SerializeJSON(CppSerialization::JSON::Serializer<OutputStream>& serializer)
    {
        serializer.StartObject();
        serializer.Pair("id", Id);
        serializer.Pair("name", Name);
        serializer.Key("wallet");
        Wallet.SerializeJSON(serializer);
        serializer.Key("orders");
        serializer.StartArray();
        for (auto order : Orders)
            order.second.SerializeJSON(serializer);
        serializer.EndArray();
        serializer.EndObject();
    }

    template<typename JSON>
    void DeserializeJSON(const JSON& json)
    {
        using namespace CppSerialization::JSON;

        Deserializer::Find(json, "id", Id);
        Deserializer::Find(json, "name", Name);
        Deserializer::FindObject(json, "wallet", [this](const Value::ConstObject& object)
        {
            Wallet.DeserializeJSON(object);
        });
        Deserializer::FindArray(json, "orders", [this](const Value& item)
        {
            Order order;
            order.DeserializeJSON(item);
            AddOrder(order);
        });
    }

    void AddOrder(const Order& order)
    {
        Orders[order.Id] = order;
    }
};

} // namespace MyDomain
