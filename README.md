# CppSerialization

[![Linux build status](https://img.shields.io/travis/chronoxor/CppSerialization/master.svg?label=Linux)](https://travis-ci.org/chronoxor/CppSerialization)
[![OSX build status](https://img.shields.io/travis/chronoxor/CppSerialization/master.svg?label=OSX)](https://travis-ci.org/chronoxor/CppSerialization)
[![Cygwin build status](https://img.shields.io/appveyor/ci/chronoxor/CppSerialization/master.svg?label=Cygwin)](https://ci.appveyor.com/project/chronoxor/CppSerialization)
[![MinGW build status](https://img.shields.io/appveyor/ci/chronoxor/CppSerialization/master.svg?label=MinGW)](https://ci.appveyor.com/project/chronoxor/CppSerialization)
[![Windows build status](https://img.shields.io/appveyor/ci/chronoxor/CppSerialization/master.svg?label=Windows)](https://ci.appveyor.com/project/chronoxor/CppSerialization)

C++ Serialization Library provides functionality to serialize/deserialize
objects in/from different formats such as Flatbuffers, JSON.

[CppSerialization API reference](http://chronoxor.github.io/CppSerialization/index.html)

# Contents
  * [Features](#features)
  * [Requirements](#requirements)
  * [How to build?](#how-to-build)
    * [Clone repository with submodules](#clone-repository-with-submodules)
    * [Linux](#linux)
    * [OSX](#osx)
    * [Windows (Cygwin)](#windows-cygwin)
    * [Windows (MinGW)](#windows-mingw)
    * [Windows (MinGW with MSYS)](#windows-mingw-with-msys)
    * [Windows (Visaul Studio 2015)](#windows-visaul-studio-2015)
  * [Domain model](#domain-model)
  * [FlatBuffers serialization](#flatbuffers-serialization)
    * [FlatBuffers schema](#flatbuffers-schema)
    * [FlatBuffers schema compilation](#flatbuffers-schema-compilation)
    * [FlatBuffers serialization methods](#flatbuffers-serialization-methods)
    * [FlatBuffers example](#flatbuffers-example)
    * [FlatBuffers performance](#flatbuffers-performance)
  * [JSON serialization](#json-serialization)
    * [JSON serialization methods](#json-serialization-methods)
    * [JSON example](#json-example)
    * [JSON performance](#json-performance)

# Features
* Cross platform (Linux, OSX, Windows)
* Fast binary serialization using [FlatBuffers library](https://google.github.io/flatbuffers)
* Fast JSON serialization using [RapidJSON library](http://rapidjson.org)

# Requirements
* Linux
* OSX
* Windows 7 / Windows 10
* [CMake](http://www.cmake.org)
* [GIT](https://git-scm.com)
* [GCC](https://gcc.gnu.org)

Optional:
* [Clang](http://clang.llvm.org)
* [Clion](https://www.jetbrains.com/clion)
* [MinGW](http://mingw-w64.org/doku.php)
* [Visual Studio 2015](https://www.visualstudio.com)

# How to build?

## Clone repository with submodules
```
git clone https://github.com/chronoxor/CppSerialization.git CppSerialization
cd CppSerialization
git submodule update --init --recursive --remote
```

## Linux
```
cd build
./unix.sh
```

## OSX
```
cd build
./unix.sh
```

## Windows (Cygwin)
```
cd build
cygwin.bat
```

## Windows (MinGW)
```
cd build
mingw.bat
```

## Windows (Visaul Studio 2015)
```
cd build
vs.bat
```

# Domain model
The first step you should perform to use CppSerialization library is to provide
a domain model (aka business objects). Domain model is a set of structures or
classes that related to each other and might be aggregated in some hierarchy.

There is an example domain model which describes Account-Wallet-Orders relation
of some abstract trading platform:

```C++
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

    void AddOrder(const Order& order)
    {
        Orders[order.Id] = order;
    }
};

} // namespace MyDomain
```

The next step you should provide serialization methods for the domain model.

# FlatBuffers serialization
FlatBuffers serialization is based on [FlatBuffers library](https://google.github.io/flatbuffers).

## FlatBuffers schema
FlatBuffers serialization starts with describing a model schema. For our domain
model the schema will be the following:

```
namespace MyDomain.flat;

enum OrderSide : byte
{
    BUY,
    SELL
}

enum OrderType : byte
{
    MARKET,
    LIMIT,
    STOP
}

table Order
{
    Id : int;
    Symbol : string;
    Side : OrderSide;
    Type : OrderType;
    Price : double = 0.0;
    Volume : double = 0.0;
}

table Balance
{
    Currency : string;
    Amount : double = 0.0;
}

table Account
{
    Id : int;
    Name : string;
    Wallet : Balance;
    Orders:[Order];
}

root_type Account;
```

## FlatBuffers schema compilation
The next step is a schema compilation using 'flatc' utility which will create
a generated code for required programming language.

The following command will create a C++ generated code:
```
flatc --cpp --scoped-enums -o . domain.fbs
```

It is possible to use add_custom_command() in CMakeLists.txt to generate code
using 'cmake' utility:
```
add_custom_command(TARGET example POST_BUILD COMMAND flatc --cpp --scoped-enums -o . domain.fbs)
```

As the result 'domain_generated.h' file will be created.

## FlatBuffers serialization methods
Finally you should extend your domain model with a FlatBuffers serialization
methods:

```C++
#include "domain_generated.h"

#include <algorithm>

namespace MyDomain {

struct Order
{
    ...

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

    ...
};

struct Balance
{
    ...

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

    ...
};

struct Account
{
    ...

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

    ...
};

} // namespace MyDomain
```

## FlatBuffers example
Here comes the usage example of FlatBuffers serialize/deserialize functionality:

```C++
#include "../domain/domain.h"

#include <iostream>

int main(int argc, char** argv)
{
    // Create a new account with some orders
    MyDomain::Account account(1, "Test", "USD", 1000);
    account.AddOrder(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
    account.AddOrder(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
    account.AddOrder(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

    // Serialize the account to the FlatBuffer stream
    flatbuffers::FlatBufferBuilder builder;
    builder.Finish(account.SerializeFlatBuffer(builder));

    // Show the serialized FlatBuffer size
    std::cout << "FlatBuffer size: " << builder.GetSize() << std::endl;

    // Deserialize the account from the FlatBuffer stream
    auto root = MyDomain::flat::GetAccount(builder.GetBufferPointer());
    MyDomain::Account deserialized;
    deserialized.DeserializeFlatBuffer(*root);

    // Show account content
    std::cout << std::endl;
    std::cout << "Account.Id = " << deserialized.Id << std::endl;
    std::cout << "Account.Name = " << deserialized.Name << std::endl;
    std::cout << "Account.Wallet.Currency = " << deserialized.Wallet.Currency << std::endl;
    std::cout << "Account.Wallet.Amount = " << deserialized.Wallet.Amount << std::endl;
    for (auto& order : deserialized.Orders)
    {
        std::cout << "Account.Order => Id: " << order.second.Id
            << ", Symbol: " << order.second.Symbol
            << ", Side: " << (int)order.second.Side
            << ", Type: " << (int)order.second.Type
            << ", Price: " << order.second.Price
            << ", Volume: " << order.second.Volume
            << std::endl;
    }

    return 0;
}
```

Output of the example is the following:
```
FlatBuffer size: 280

Account.Id = 1
Account.Name = Test
Account.Wallet.Currency = USD
Account.Wallet.Amount = 1000
Account.Order => Id: 1, Symbol: EURUSD, Side: 0, Type: 0, Price: 1.23456, Volume: 1000
Account.Order => Id: 2, Symbol: EURUSD, Side: 1, Type: 1, Price: 1, Volume: 100
Account.Order => Id: 3, Symbol: EURUSD, Side: 0, Type: 2, Price: 1.5, Volume: 10
```

## FlatBuffers performance
FlatBuffers serialization performance of the provided domain model is the
following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 4.008 GHz
CPU Hyper-Threading: enabled
RAM total: 31.903 GiB
RAM free: 16.1011 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Fri Mar  3 17:30:24 2017
UTC timestamp: Fri Mar  3 14:30:24 2017
===============================================================================
Benchmark: FlatBuffers-Serialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: FlatBuffers-Serialize
Average time: 785 ns / iteration
Minimal time: 785 ns / iteration
Maximal time: 789 ns / iteration
Total time: 785.804 ms
Total iterations: 1000000
Iterations throughput: 1272580 / second
===============================================================================
```

FlatBuffers deserialization performance of the provided domain model is the
following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 4.008 GHz
CPU Hyper-Threading: enabled
RAM total: 31.903 GiB
RAM free: 16.938 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Fri Mar  3 17:31:26 2017
UTC timestamp: Fri Mar  3 14:31:26 2017
===============================================================================
Benchmark: FlatBuffers-Deserialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: FlatBuffers-Deserialize
Average time: 397 ns / iteration
Minimal time: 397 ns / iteration
Maximal time: 399 ns / iteration
Total time: 397.788 ms
Total iterations: 1000000
Iterations throughput: 2513901 / second
===============================================================================
```

# JSON serialization
JSON serialization is based on [RapidJSON library](http://rapidjson.org).

## JSON serialization methods
Finally you should extend your domain model with a JSON serialization
methods:

```C++
#include "serialization/json/serializer.h"
#include "serialization/json/deserializer.h"

namespace MyDomain {

struct Order
{
    ...

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

    ...
};

struct Balance
{
    ...

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

    ...
};

struct Account
{
    ...

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

    ...
};

} // namespace MyDomain
```

## JSON example
Here comes the usage example of JSON serialize/deserialize functionality:

```C++
#include "../domain/domain.h"

#include "serialization/json/parser.h"

#include <iostream>

int main(int argc, char** argv)
{
    // Create a new account with some orders
    MyDomain::Account account(1, "Test", "USD", 1000);
    account.AddOrder(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
    account.AddOrder(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
    account.AddOrder(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

    // Serialize the account to the JSON stream
    CppSerialization::JSON::StringBuffer buffer;
    CppSerialization::JSON::Serializer<CppSerialization::JSON::StringBuffer> serializer(buffer);
    account.SerializeJSON(serializer);

    // Show the serialized JSON
    std::cout << "JSON: " << buffer.GetString() << std::endl;

    // Parse JSON string
    CppSerialization::JSON::Document json = CppSerialization::JSON::Parser::Parse(buffer.GetString());

    // Deserialize the account from the JSON stream
    MyDomain::Account deserialized;
    deserialized.DeserializeJSON(json);

    // Show account content
    std::cout << std::endl;
    std::cout << "Account.Id = " << deserialized.Id << std::endl;
    std::cout << "Account.Name = " << deserialized.Name << std::endl;
    std::cout << "Account.Wallet.Currency = " << deserialized.Wallet.Currency << std::endl;
    std::cout << "Account.Wallet.Amount = " << deserialized.Wallet.Amount << std::endl;
    for (auto& order : deserialized.Orders)
    {
        std::cout << "Account.Order => Id: " << order.second.Id
            << ", Symbol: " << order.second.Symbol
            << ", Side: " << (int)order.second.Side
            << ", Type: " << (int)order.second.Type
            << ", Price: " << order.second.Price
            << ", Volume: " << order.second.Volume
            << std::endl;
    }

    return 0;
}
```

Output of the example is the following:
```
JSON: {"id":1,"name":"Test","wallet":{"currency":"USD","amount":1000.0},"orders":[{"id":1,"symbol":"EURUSD","side":0,"type":0,"price":1.23456,"volume":1000.0},{"id":2,"symbol":"EURUSD","side":1,"type":1,"price":1.0,"volume":100.0},{"id":3,"symbol":"EURUSD","side":0,"type":2,"price":1.5,"volume":10.0}]}

Account.Id = 1
Account.Name = Test
Account.Wallet.Currency = USD
Account.Wallet.Amount = 1000
Account.Order => Id: 1, Symbol: EURUSD, Side: 0, Type: 0, Price: 1.23456, Volume: 1000
Account.Order => Id: 2, Symbol: EURUSD, Side: 1, Type: 1, Price: 1, Volume: 100
Account.Order => Id: 3, Symbol: EURUSD, Side: 0, Type: 2, Price: 1.5, Volume: 10
```

## JSON performance
JSON serialization performance of the provided domain model is the following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 4.008 GHz
CPU Hyper-Threading: enabled
RAM total: 31.903 GiB
RAM free: 17.049 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Fri Mar  3 17:42:32 2017
UTC timestamp: Fri Mar  3 14:42:32 2017
===============================================================================
Benchmark: JSON-Serialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: JSON-Serialize
Average time: 1.051 mcs / iteration
Minimal time: 1.051 mcs / iteration
Maximal time: 1.057 mcs / iteration
Total time: 1.051 s
Total iterations: 1000000
Total bytes: 283.247 MiB
Iterations throughput: 950673 / second
Bytes throughput: 269.276 MiB / second
===============================================================================
```

JSON document parsing performance of the provided domain model is the following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 4.008 GHz
CPU Hyper-Threading: enabled
RAM total: 31.903 GiB
RAM free: 17.050 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Fri Mar  3 17:42:56 2017
UTC timestamp: Fri Mar  3 14:42:56 2017
===============================================================================
Benchmark: JSON-Parse
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: JSON-Parse
Average time: 2.609 mcs / iteration
Minimal time: 2.609 mcs / iteration
Maximal time: 2.624 mcs / iteration
Total time: 2.609 s
Total iterations: 1000000
Total bytes: 283.247 MiB
Iterations throughput: 383266 / second
Bytes throughput: 108.570 MiB / second
===============================================================================
```

JSON deserialization performance of the provided domain model is the following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 4.008 GHz
CPU Hyper-Threading: enabled
RAM total: 31.903 GiB
RAM free: 16.953 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Fri Mar  3 17:43:11 2017
UTC timestamp: Fri Mar  3 14:43:11 2017
===============================================================================
Benchmark: JSON-Deserialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: JSON-Deserialize
Average time: 709 ns / iteration
Minimal time: 709 ns / iteration
Maximal time: 747 ns / iteration
Total time: 709.339 ms
Total iterations: 1000000
Iterations throughput: 1409762 / second
===============================================================================
```
