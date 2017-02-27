/*!
    \file domain.cpp
    \brief Domain model example
    \author Ivan Shynkarenka
    \date 24.02.2017
    \copyright MIT License
*/

#include "serialization/json/serializer.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

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

    Order() {}
    Order(int id, const std::string& symbol, OrderSide side, OrderType type, double price, double volume)
    {
        Id = id;
        std::memcpy(Symbol, symbol.data(), std::min(symbol.size(), sizeof(Symbol)));
        Side = side;
        Type = type;
        Price = price;
        Volume = volume;
    }

    template<typename OutputStream>
    friend void JSONSerialize(CppSerialization::JSON::Serializer<OutputStream>& serializer, const Order order)
    {
        serializer.StartObject();
        serializer.Pair("id", order.Id);
        serializer.Pair("symbol", order.Symbol);
        serializer.Pair("side", (int)order.Side);
        serializer.Pair("type", (int)order.Type);
        serializer.Pair("price", order.Price);
        serializer.Pair("volume", order.Volume);
        serializer.EndObject();
    }

    bool JSONDeserialize(CppSerialization::JSON::Value& value)
    {
        CppSerialization::JSON::Value::MemberIterator id = value.FindMember("id");
        if ((id == value.MemberEnd()) || !id->value.IsInt()) return false;
        Id = id->value.GetInt();
        CppSerialization::JSON::Value::MemberIterator symbol = value.FindMember("symbol");
        if ((symbol == value.MemberEnd()) || !symbol->value.IsString()) return false;
        std::memcpy(Symbol, symbol->value.GetString(), std::min((size_t)symbol->value.GetStringLength(), sizeof(Symbol)));
        CppSerialization::JSON::Value::MemberIterator side = value.FindMember("side");
        if ((side == value.MemberEnd()) || !side->value.IsInt()) return false;
        Side = (OrderSide)side->value.GetInt();
        CppSerialization::JSON::Value::MemberIterator type = value.FindMember("type");
        if ((type == value.MemberEnd()) || !type->value.IsInt()) return false;
        Type = (OrderType)type->value.GetInt();
        CppSerialization::JSON::Value::MemberIterator price = value.FindMember("price");
        if ((price == value.MemberEnd()) || !price->value.IsDouble()) return false;
        Price = price->value.GetDouble();
        CppSerialization::JSON::Value::MemberIterator volume = value.FindMember("volume");
        if ((volume == value.MemberEnd()) || !volume->value.IsDouble()) return false;
        Volume = volume->value.GetDouble();
        return true;
    }
};

struct Account
{
    int Id;
    std::string Name;
    double Balance;
    std::map<int, Order> Orders;

    Account() {}
    Account(int id, const std::string& name, double balance)
    {
        Id = id;
        Name = name;
        Balance = balance;
    }

    void AddOrder(const Order& order)
    {
        Orders[order.Id] = order;
    }

    template<typename OutputStream>
    friend void JSONSerialize(CppSerialization::JSON::Serializer<OutputStream>& serializer, const Account account)
    {
        serializer.StartObject();
        serializer.Pair("id", account.Id);
        serializer.Pair("name", account.Name);
        serializer.Pair("balance", account.Balance);
        serializer.StartArray();
        for (auto& order : account.Orders)
            JSONSerialize(serializer, order.second);
        serializer.EndArray();
        serializer.EndObject();
    }

    bool JSONDeserialize(CppSerialization::JSON::Value& value)
    {
        CppSerialization::JSON::Value::MemberIterator id = value.FindMember("id");
        if ((id == value.MemberEnd()) || !id->value.IsInt()) return false;
        Id = id->value.GetInt();
        CppSerialization::JSON::Value::MemberIterator name = value.FindMember("name");
        if ((name == value.MemberEnd()) || !name->value.IsString()) return false;
        Name = name->value.GetString();
        CppSerialization::JSON::Value::MemberIterator balance = value.FindMember("balance");
        if ((balance == value.MemberEnd()) || !balance->value.IsDouble()) return false;
        Balance = balance->value.GetDouble();
        CppSerialization::JSON::Value::MemberIterator orders = value.FindMember("orders");
        if ((orders == value.MemberEnd()) || !orders->value.IsArray()) return false;
        Orders.clear();
        for (auto& ord : orders->value.GetArray())
        {
            Order order;
            if (!order.JSONDeserialize(ord)) return false;
            AddOrder(order);
        }
        return true;
    }
};
