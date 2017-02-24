/*!
    \file domain.cpp
    \brief Domain model example
    \author Ivan Shynkarenka
    \date 24.02.2017
    \copyright MIT License
*/

#include "serialization/json/rapidjson.h"

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
    std::string Symbol;
    OrderSide Side;
    OrderType Type;
    double Price;
    double Volume;

    Order() {}
    Order(int id, const std::string& symbol, OrderSide side, OrderType type, double price, double volume)
    {
        Id = id;
        Symbol = symbol;
        Side = side;
        Type = type;
        Price = price;
        Volume = volume;
    }

    template<typename OutputStream>
    bool SerializeJSON(CppSerialization::JSON::Writer<OutputStream>& writer) const
    {
        if (!writer.StartObject()) return false;
        if (!writer.Key("id")) return false;
        if (!writer.Int(Id)) return false;
        if (!writer.Key("symbol")) return false;
        if (!writer.String(Symbol)) return false;
        if (!writer.Key("side")) return false;
        if (!writer.Int((int)Side)) return false;
        if (!writer.Key("type")) return false;
        if (!writer.Int((int)Type)) return false;
        if (!writer.Key("price")) return false;
        if (!writer.Double(Price)) return false;
        if (!writer.Key("volume")) return false;
        if (!writer.Double(Volume)) return false;
        if (!writer.EndObject()) return false;
        return true;
    }

    bool DeserializeJSON(CppSerialization::JSON::Value& value)
    {
        CppSerialization::JSON::Value::MemberIterator id = value.FindMember("id");
        if ((id == value.MemberEnd()) || !id->value.IsInt()) return false;
        Id = id->value.GetInt();
        CppSerialization::JSON::Value::MemberIterator symbol = value.FindMember("symbol");
        if ((symbol == value.MemberEnd()) || !symbol->value.IsString()) return false;
        Symbol = symbol->value.GetString();
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
    bool SerializeJSON(CppSerialization::JSON::Writer<OutputStream>& writer) const
    {
        if (!writer.StartObject()) return false;
        if (!writer.Key("id")) return false;
        if (!writer.Int(Id)) return false;
        if (!writer.Key("name")) return false;
        if (!writer.String(Name)) return false;
        if (!writer.Key("balance")) return false;
        if (!writer.Double(Balance)) return false;
        if (!writer.StartArray()) return false;
        for (auto& order : Orders)
            if (!order.second.SerializeJSON(writer)) return false;
        if (!writer.EndArray()) return false;
        if (!writer.EndObject()) return false;
        return true;
    }

    bool DeserializeJSON(CppSerialization::JSON::Value& value)
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
            if (!order.DeserializeJSON(ord)) return false;
            AddOrder(order);
        }
        return true;
    }
};
