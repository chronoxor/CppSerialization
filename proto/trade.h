/*!
    \file trade.h
    \brief Trade proto
    \author Ivan Shynkarenka
    \date 24.02.2017
    \copyright MIT License
*/

#ifndef CPPSERIALIZATION_PROTO_TRADE_H
#define CPPSERIALIZATION_PROTO_TRADE_H

#if defined(__clang__)
#pragma clang system_header
#elif defined(__GNUC__)
#pragma GCC system_header
#elif defined(_MSC_VER)
#pragma system_header
#endif

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4127) // C4127: conditional expression is constant
#pragma warning(disable: 4244) // C4244: 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable: 4245) // C4244: 'conversion' : conversion from 'type1' to 'type2', signed/unsigned mismatch
#pragma warning(disable: 4251) // C4251: 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable: 4267) // C4267: 'var' : conversion from 'size_t' to 'type', possible loss of data
#pragma warning(disable: 4505) // C4505: 'var': unreferenced local function has been removed
#pragma warning(disable: 5054) // C5054: operator 'operator-name': deprecated between enumerations of different types
#endif
#include "capnp/serialize.h"
#include "capnproto/trade.capnp.h"
#include "fbe/trade_models.h"
#include "fbe/trade_final_models.h"
#include "flatbuffers/trade_generated.h"
#include "protobuf/trade.pb.h"
#include "sbe/Account.h"
#include "sbe/MessageHeader.h"
#include "zpp_bits/zpp_bits.h"
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include "serialization/json/serializer.h"
#include "serialization/json/deserializer.h"

#include <algorithm>
#include <string>
#include <vector>

namespace TradeProto {

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
        std::memcpy(Symbol, symbol.c_str(), std::min(symbol.size() + 1, sizeof(Symbol)));
        Side = side;
        Type = type;
        Price = price;
        Volume = volume;
    }

    constexpr size_t size() const { return sizeof(Order); }

    // Cap'n'Proto serialization

    void Serialize(Trade::capnproto::Order::Builder& builder) const
    {
        builder.setId(Id);
        builder.setSymbol(Symbol);
        builder.setSide((Trade::capnproto::OrderSide)Side);
        builder.setType((Trade::capnproto::OrderType)Type);
        builder.setPrice(Price);
        builder.setVolume(Volume);
    }

    void Deserialize(const Trade::capnproto::Order::Reader& reader)
    {
        Id = reader.getId();
        std::string symbol = reader.getSymbol();
        std::memcpy(Symbol, symbol.c_str(), std::min(symbol.size() + 1, sizeof(Symbol)));
        Side = (OrderSide)reader.getSide();
        Type = (OrderType)reader.getType();
        Price = reader.getPrice();
        Volume = reader.getVolume();
    }

    // FastBinaryEncoding serialization

    void Serialize(FBE::FieldModel<trade::Order>& model) const
    {
        size_t model_begin = model.set_begin();
        model.id.set(Id);
        model.symbol.set(Symbol);
        model.side.set((trade::OrderSide)Side);
        model.type.set((trade::OrderType)Type);
        model.price.set(Price);
        model.volume.set(Volume);
        model.set_end(model_begin);
    }

    void Deserialize(const FBE::FieldModel<trade::Order>& model)
    {
        size_t model_begin = model.get_begin();
        model.id.get(Id);
        model.symbol.get(Symbol);
        trade::OrderSide side;
        model.side.get(side);
        Side = (OrderSide)side;
        trade::OrderType type;
        model.type.get(type);
        Type = (OrderType)type;
        model.price.get(Price);
        model.volume.get(Volume);
        model.get_end(model_begin);
    }

    // FlatBuffers serialization

    flatbuffers::Offset<Trade::flatbuf::Order> Serialize(flatbuffers::FlatBufferBuilder& builder) const
    {
        return Trade::flatbuf::CreateOrderDirect(builder, Id, Symbol, (Trade::flatbuf::OrderSide)Side, (Trade::flatbuf::OrderType)Type, Price, Volume);
    }

    void Deserialize(const Trade::flatbuf::Order& value)
    {
        Id = value.id();
        std::string symbol = value.symbol()->str();
        std::memcpy(Symbol, symbol.c_str(), std::min(symbol.size() + 1, sizeof(Symbol)));
        Side = (OrderSide)value.side();
        Type = (OrderType)value.type();
        Price = value.price();
        Volume = value.volume();
    }

    // Protobuf serialization

    Trade::protobuf::Order& Serialize(Trade::protobuf::Order& value) const
    {
        value.set_id(Id);
        value.set_symbol(Symbol);
        value.set_side((Trade::protobuf::OrderSide)Side);
        value.set_type((Trade::protobuf::OrderType)Type);
        value.set_price(Price);
        value.set_volume(Volume);
        return value;
    }

    void Deserialize(const Trade::protobuf::Order& value)
    {
        Id = value.id();
        std::string symbol = value.symbol();
        std::memcpy(Symbol, symbol.c_str(), std::min(symbol.size() + 1, sizeof(Symbol)));
        Side = (OrderSide)value.side();
        Type = (OrderType)value.type();
        Price = value.price();
        Volume = value.volume();
    }

    // SimpleBinaryEncoding serialization

    void Serialize(sbe::Order& model) const
    {
        model.id(Id);
        model.putSymbol(Symbol);
        model.side((sbe::OrderSide::Value)Side);
        model.type((sbe::OrderType::Value)Type);
        model.price(Price);
        model.volume(Volume);
    }

    void Deserialize(sbe::Order& model)
    {
        Id = model.id();
        model.getSymbol(Symbol, sizeof(Symbol));
        Side = (OrderSide)model.side();
        Type = (OrderType)model.type();
        Price = model.price();
        Volume = model.volume();
    }

    // zpp::bits serialization

    using serialize = zpp::bits::members<6>;

    // JSON serialization

    template<typename OutputStream>
    void Serialize(CppSerialization::JSON::Serializer<OutputStream>& serializer) const
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
        std::memcpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
        Amount = amount;
    }

    constexpr size_t size() const { return sizeof(Balance); }

    // Cap'n'Proto serialization

    void Serialize(Trade::capnproto::Balance::Builder& builder) const
    {
        builder.setCurrency(Currency);
        builder.setAmount(Amount);
    }

    void Deserialize(const Trade::capnproto::Balance::Reader& reader)
    {
        std::string currency = reader.getCurrency();
        std::memcpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
        Amount = reader.getAmount();
    }

    // FastBinaryEncoding serialization

    void Serialize(FBE::FieldModel<trade::Balance>& model) const
    {
        size_t model_begin = model.set_begin();
        model.currency.set(Currency);
        model.amount.set(Amount);
        model.set_end(model_begin);
    }

    void Deserialize(const FBE::FieldModel<trade::Balance>& model)
    {
        size_t model_begin = model.get_begin();
        model.currency.get(Currency);
        model.amount.get(Amount);
        model.get_end(model_begin);
    }

    // FlatBuffers serialization

    flatbuffers::Offset<Trade::flatbuf::Balance> Serialize(flatbuffers::FlatBufferBuilder& builder) const
    {
        return Trade::flatbuf::CreateBalanceDirect(builder, Currency, Amount);
    }

    void Deserialize(const Trade::flatbuf::Balance& value)
    {
        std::string currency = value.currency()->str();
        std::memcpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
        Amount = value.amount();
    }

    // Protobuf serialization

    Trade::protobuf::Balance& Serialize(Trade::protobuf::Balance& value) const
    {
        value.set_currency(Currency);
        value.set_amount(Amount);
        return value;
    }

    void Deserialize(const Trade::protobuf::Balance& value)
    {
        std::string currency = value.currency();
        std::memcpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
        Amount = value.amount();
    }

    // SimpleBinaryEncoding serialization

    void Serialize(sbe::Balance& model) const
    {
        model.putCurrency(Currency);
        model.amount(Amount);
    }

    void Deserialize(sbe::Balance& model)
    {
        model.getCurrency(Currency, sizeof(Currency));
        Amount = model.amount();
    }

    // zpp::bits serialization

    using serialize = zpp::bits::members<2>;

    // JSON serialization

    template<typename OutputStream>
    void Serialize(CppSerialization::JSON::Serializer<OutputStream>& serializer) const
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

    size_t size() const { return sizeof(int) + Name.size() + Wallet.size() + std::accumulate(Orders.begin(), Orders.end(), 0, [](size_t sum, const Order& order) { return sum + order.size(); }); }

    // Cap'n'Proto serialization

    void Serialize(Trade::capnproto::Account::Builder& builder) const
    {
        builder.setId(Id);
        builder.setName(Name);
        auto wallet = builder.initWallet();
        Wallet.Serialize(wallet);
        auto orders = builder.initOrders((unsigned)Orders.size());
        unsigned index = 0;
        for (const auto& order : Orders)
        {
            auto o = orders[index++];
            order.Serialize(o);
        }
    }

    void Deserialize(const Trade::capnproto::Account::Reader& reader)
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

    // FastBinaryEncoding serialization

    void Serialize(FBE::FieldModel<trade::Account>& model) const
    {
        size_t model_begin = model.set_begin();
        model.id.set(Id);
        model.name.set(Name);
        Wallet.Serialize(model.wallet);
        auto order_model = model.orders.resize(Orders.size());
        for (const auto& order : Orders)
        {
            order.Serialize(order_model);
            order_model.fbe_shift(order_model.fbe_size());
        }
        model.set_end(model_begin);
    }

    void Deserialize(const FBE::FieldModel<trade::Account>& model)
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

    flatbuffers::Offset<Trade::flatbuf::Account> Serialize(flatbuffers::FlatBufferBuilder& builder) const
    {
        auto wallet = Wallet.Serialize(builder);
        std::vector<flatbuffers::Offset<Trade::flatbuf::Order>> orders;
        for (const auto& order : Orders)
            orders.emplace_back(order.Serialize(builder));
        return Trade::flatbuf::CreateAccountDirect(builder, Id, Name.c_str(), wallet, &orders);
    }

    void Deserialize(const Trade::flatbuf::Account& value)
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

    Trade::protobuf::Account& Serialize(Trade::protobuf::Account& value) const
    {
        value.set_id(Id);
        value.set_name(Name);
        value.set_allocated_wallet(&Wallet.Serialize(*value.wallet().New(value.GetArena())));
        for (const auto& order : Orders)
            order.Serialize(*value.add_orders());
        return value;
    }

    void Deserialize(const Trade::protobuf::Account& value)
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

    // SimpleBinaryEncoding serialization

    void Serialize(sbe::Account& model) const
    {
        model.id(Id);
        model.putName(Name);
        Wallet.Serialize(model.wallet());
        auto orders = model.ordersCount((uint16_t)Orders.size());
        for (const auto& order : Orders)
            order.Serialize(orders.next().order());
    }

    void Deserialize(sbe::Account& model)
    {
        Id = model.id();
        Name = model.getNameAsString();
        Wallet.Deserialize(model.wallet());
        Orders.clear();
        auto orders = model.orders();
        for (int i = 0; i < orders.count(); ++i)
        {
            Order order;
            order.Deserialize(orders.next().order());
            Orders.emplace_back(order);
        }
    }

    // zpp::bits serialization

    using serialize = zpp::bits::members<4>;

    // JSON serialization

    template<typename OutputStream>
    void Serialize(CppSerialization::JSON::Serializer<OutputStream>& serializer) const
    {
        serializer.StartObject();
        serializer.Pair("id", Id);
        serializer.Pair("name", Name);
        serializer.Key("wallet");
        Wallet.Serialize(serializer);
        serializer.Key("orders");
        serializer.StartArray();
        for (const auto& order : Orders)
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

} // namespace Trade

#endif // CPPSERIALIZATION_PROTO_TRADE_H
