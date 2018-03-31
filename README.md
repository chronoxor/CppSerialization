# CppSerialization

[![Linux build status](https://img.shields.io/travis/chronoxor/CppSerialization/master.svg?label=Linux)](https://travis-ci.org/chronoxor/CppSerialization)
[![OSX build status](https://img.shields.io/travis/chronoxor/CppSerialization/master.svg?label=OSX)](https://travis-ci.org/chronoxor/CppSerialization)
[![Cygwin build status](https://img.shields.io/appveyor/ci/chronoxor/CppSerialization/master.svg?label=Cygwin)](https://ci.appveyor.com/project/chronoxor/CppSerialization)
[![MinGW build status](https://img.shields.io/appveyor/ci/chronoxor/CppSerialization/master.svg?label=MinGW)](https://ci.appveyor.com/project/chronoxor/CppSerialization)
[![Windows build status](https://img.shields.io/appveyor/ci/chronoxor/CppSerialization/master.svg?label=Windows)](https://ci.appveyor.com/project/chronoxor/CppSerialization)

C++ Serialization Library provides functionality to serialize/deserialize
objects in/from different formats such as Flatbuffers, Protobuf, JSON.

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
    * [Windows (Visual Studio)](#windows-visual-studio)
  * [Domain model](#domain-model)
  * [Cap'n'Proto serialization](#cap-n-proto-serialization)
    * [Cap'n'Proto schema](#cap-n-proto-schema)
    * [Cap'n'Proto schema compilation](#cap-n-proto-schema-compilation)
    * [Cap'n'Proto serialization methods](#cap-n-proto-serialization-methods)
    * [Cap'n'Proto example](#cap-n-proto-example)
    * [Cap'n'Proto performance](#cap-n-proto-performance)
  * [FlatBuffers serialization](#flatbuffers-serialization)
    * [FlatBuffers schema](#flatbuffers-schema)
    * [FlatBuffers schema compilation](#flatbuffers-schema-compilation)
    * [FlatBuffers serialization methods](#flatbuffers-serialization-methods)
    * [FlatBuffers example](#flatbuffers-example)
    * [FlatBuffers performance](#flatbuffers-performance)
  * [Protobuf serialization](#protobuf-serialization)
    * [Protobuf schema](#protobuf-schema)
    * [Protobuf schema compilation](#protobuf-schema-compilation)
    * [Protobuf serialization methods](#protobuf-serialization-methods)
    * [Protobuf example](#protobuf-example)
    * [Protobuf performance](#protobuf-performance)
  * [JSON serialization](#json-serialization)
    * [JSON serialization methods](#json-serialization-methods)
    * [JSON example](#json-example)
    * [JSON performance](#json-performance)

# Features
* Cross platform (Linux, OSX, Windows)
* Fast binary serialization using [Cap'n'Proto library](https://capnproto.org)
* Fast binary serialization using [FlatBuffers library](https://google.github.io/flatbuffers)
* Fast binary serialization using [Protobuf library](https://developers.google.com/protocol-buffers)
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
* [Visual Studio](https://www.visualstudio.com)

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

## Windows (Visual Studio)
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

# Cap'n'Proto serialization
Cap'n'Proto serialization is based on [Cap'n'Proto library](https://capnproto.org).

## Cap'n'Proto schema
Cap'n'Proto serialization starts with describing a model schema. For our domain
model the schema will be the following:

```
# Unique file ID, generated by 'capnp id'
@0xd4b6e00623bed170;

using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("MyDomain::capnproto");

enum OrderSide
{
    buy @0;
    sell @1;
}

enum OrderType
{
    market @0;
    limit @1;
    stop @2;
}

struct Order
{
    id @0 : Int32;
    symbol @1 : Text;
    side @2 : OrderSide;
    type @3 : OrderType;
    price @4 : Float64 = 0.0;
    volume @5 : Float64 = 0.0;
}

struct Balance
{
    currency @0 : Text;
    amount @1 : Float64 = 0.0;
}

struct Account
{
    id @0 : Int32;
    name @1 : Text;
    wallet @2 : Balance;
    orders @3 : List(Order);
}
```

## Cap'n'Proto schema compilation
The next step is a schema compilation using 'capnpc' utility which will create
a generated code for required programming language.

The following command will create a C++ generated code:
```
capnp compile -I capnproto/c++/src -oc++ domain.capnp
```

It is possible to use capnp_generate_cpp() in CMakeLists.txt to generate code
using 'cmake' utility:
```
capnp_generate_cpp(CAPNP_HEADERS CAPNP_SOURCES domain.capnp)
```

As the result 'domain.capnp.h' and 'domain.capnp.c++' files will be generated.

## Cap'n'Proto serialization methods
Finally you should extend your domain model with a Cap'n'Proto serialization
methods:

```C++
#include "capnp/serialize.h"
#include "capnproto/domain.capnp.h"

#include <algorithm>

namespace MyDomain {

struct Order
{
    ...

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
        std::strncpy(Symbol, reader.getSymbol().cStr(), std::min((size_t)reader.getSymbol().size() + 1, sizeof(Symbol)));
        Side = (OrderSide)reader.getSide();
        Type = (OrderType)reader.getType();
        Price = reader.getPrice();
        Volume = reader.getVolume();
    }

    ...
};

struct Balance
{
    ...

    // Cap'n'Proto serialization

    void Serialize(capnproto::Balance::Builder& builder)
    {
        builder.setCurrency(Currency);
        builder.setAmount(Amount);
    }

    void Deserialize(const capnproto::Balance::Reader& reader)
    {
        std::strncpy(Currency, reader.getCurrency().cStr(), std::min((size_t)reader.getCurrency().size() + 1, sizeof(Currency)));
        Amount = reader.getAmount();
    }

    ...
};

struct Account
{
    ...

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
            order.second.Serialize(o);
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
            AddOrder(order);
        }
    }

    ...
};

} // namespace MyDomain
```

## Cap'n'Proto example
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

    // Serialize the account to the Cap'n'Proto stream
    capnp::MallocMessageBuilder output;
    MyDomain::capnproto::Account::Builder builder = output.initRoot<MyDomain::capnproto::Account>();
    account.Serialize(builder);
    kj::VectorOutputStream buffer;
    writeMessage(buffer, output);

    // Show the serialized Cap'n'Proto size
    std::cout << "Protobuf size: " << buffer.getArray().size() << std::endl;

    // Deserialize the account from the Cap'n'Proto stream
    kj::ArrayInputStream array(buffer.getArray());
    capnp::InputStreamMessageReader input(array);
    MyDomain::Account deserialized;
    deserialized.Deserialize(input.getRoot<MyDomain::capnproto::Account>());

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
Protobuf size: 208

Account.Id = 1
Account.Name = Test
Account.Wallet.Currency = USD
Account.Wallet.Amount = 1000
Account.Order => Id: 1, Symbol: EURUSD, Side: 0, Type: 0, Price: 1.23456, Volume: 1000
Account.Order => Id: 2, Symbol: EURUSD, Side: 1, Type: 1, Price: 1, Volume: 100
Account.Order => Id: 3, Symbol: EURUSD, Side: 0, Type: 2, Price: 1.5, Volume: 10
```

## Cap'n'Proto performance
Cap'n'Proto serialization performance of the provided domain model is the
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
Average time: 995 ns / iteration
Minimal time: 995 ns / iteration
Maximal time: 996 ns / iteration
Total time: 995.554 ms
Total iterations: 1000000
Total bytes: 267.029 MiB
Iterations throughput: 1004465 / second
Bytes throughput: 268.226 MiB / second
Custom values:
        Size: 280
===============================================================================
```

Cap'n'Proto deserialization performance of the provided domain model is the
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
Average time: 586 ns / iteration
Minimal time: 586 ns / iteration
Maximal time: 609 ns / iteration
Total time: 586.430 ms
Total iterations: 1000000
Total bytes: 267.029 MiB
Iterations throughput: 1705232 / second
Bytes throughput: 455.354 MiB / second
Custom values:
        Size: 280
===============================================================================
```

# FlatBuffers serialization
FlatBuffers serialization is based on [FlatBuffers library](https://google.github.io/flatbuffers).

## FlatBuffers schema
FlatBuffers serialization starts with describing a model schema. For our domain
model the schema will be the following:

```
namespace MyDomain.flatbuf;

enum OrderSide : byte
{
    buy,
    sell
}

enum OrderType : byte
{
    market,
    limit,
    stop
}

table Order
{
    id : int;
    symbol : string;
    side : OrderSide;
    type : OrderType;
    price : double = 0.0;
    volume : double = 0.0;
}

table Balance
{
    currency : string;
    amount : double = 0.0;
}

table Account
{
    id : int;
    name : string;
    wallet : Balance;
    orders : [Order];
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

As the result 'domain_generated.h' file will be generated.

## FlatBuffers serialization methods
Finally you should extend your domain model with a FlatBuffers serialization
methods:

```C++
#include "flatbuffers/domain_generated.h"

#include <algorithm>

namespace MyDomain {

struct Order
{
    ...

    // FlatBuffers serialization

    flatbuffers::Offset<flatbuf::Order> Serialize(flatbuffers::FlatBufferBuilder& builder)
    {
        return flatbuf::CreateOrderDirect(builder, Id, Symbol, (flatbuf::OrderSide)Side, (flatbuf::OrderType)Type, Price, Volume);
    }

    void Deserialize(const flatbuf::Order& value)
    {
        Id = value.id();
        std::strncpy(Symbol, value.symbol()->c_str(), std::min((size_t)value.symbol()->Length() + 1, sizeof(Symbol)));
        Side = (OrderSide)value.side();
        Type = (OrderType)value.type();
        Price = value.price();
        Volume = value.volume();
    }

    ...
};

struct Balance
{
    ...

    // FlatBuffers serialization

    flatbuffers::Offset<flatbuf::Balance> Serialize(flatbuffers::FlatBufferBuilder& builder)
    {
        return flatbuf::CreateBalanceDirect(builder, Currency, Amount);
    }

    void Deserialize(const flatbuf::Balance& value)
    {
        std::strncpy(Currency, value.currency()->c_str(), std::min((size_t)value.currency()->Length() + 1, sizeof(Currency)));
        Amount = value.amount();
    }

    ...
};

struct Account
{
    ...

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
        Id = value.id();
        Name = value.name()->str();
        Wallet.Deserialize(*value.wallet());
        Orders.clear();
        for (auto o : *value.orders())
        {
            Order order;
            order.Deserialize(*o);
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
    builder.Finish(account.Serialize(builder));

    // Show the serialized FlatBuffer size
    std::cout << "FlatBuffer size: " << builder.GetSize() << std::endl;

    // Deserialize the account from the FlatBuffer stream
    MyDomain::Account deserialized;
    deserialized.Deserialize(*MyDomain::flatbuf::GetAccount(builder.GetBufferPointer()));

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
Average time: 995 ns / iteration
Minimal time: 995 ns / iteration
Maximal time: 996 ns / iteration
Total time: 995.554 ms
Total iterations: 1000000
Total bytes: 267.029 MiB
Iterations throughput: 1004465 / second
Bytes throughput: 268.226 MiB / second
Custom values:
        Size: 280
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
Average time: 586 ns / iteration
Minimal time: 586 ns / iteration
Maximal time: 609 ns / iteration
Total time: 586.430 ms
Total iterations: 1000000
Total bytes: 267.029 MiB
Iterations throughput: 1705232 / second
Bytes throughput: 455.354 MiB / second
Custom values:
        Size: 280
===============================================================================
```

# Protobuf serialization
Protobuf serialization is based on [Protobuf library](https://developers.google.com/protocol-buffers).

## Protobuf schema
Protobuf serialization starts with describing a model schema. For our domain
model the schema will be the following:

```
syntax = "proto3";
package MyDomain.protobuf;

enum OrderSide
{
    buy = 0;
    sell = 1;
}

enum OrderType
{
    market = 0;
    limit = 1;
    stop = 2;
}

message Order
{
    int32 id = 1;
    string symbol = 2;
    OrderSide side = 3;
    OrderType type = 4;
    double price = 5;
    double volume = 6;
}

message Balance
{
    string currency = 1;
    double amount = 2;
}

message Account
{
    int32 id = 1;
    string name = 2;
    Balance wallet = 3;
    repeated Order orders = 4;
}
```

## Protobuf schema compilation
The next step is a schema compilation using 'protoc' utility which will create
a generated code for required programming language.

The following command will create a C++ generated code:
```
protoc --proto_path=. --cpp_out=. domain.proto
```

It is possible to use add_custom_command() in CMakeLists.txt to generate code
using 'cmake' utility:
```
add_custom_command(TARGET example POST_BUILD COMMAND protoc --proto_path=. --cpp_out=. domain.proto)
```

As the result 'domain.pb.h' and 'domain.pb.cc' files will be generated.

## Protobuf serialization methods
Finally you should extend your domain model with a FlatBuffers serialization
methods:

```C++
#include "protobuf/domain.pb.h"

#include <algorithm>

namespace MyDomain {

struct Order
{
    ...

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

    ...
};

struct Balance
{
    ...

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

    ...
};

struct Account
{
    ...

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
        Orders.clear();
        for (int i = 0; i < value.orders_size(); ++i)
        {
            Order order;
            order.Deserialize(value.orders(i));
            AddOrder(order);
        }
    }

    ...
};

} // namespace MyDomain
```

## Protobuf example
Here comes the usage example of Protobuf serialize/deserialize functionality:

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

    // Serialize the account to the Protobuf stream
    MyDomain::protobuf::Account ouput;
    account.Serialize(ouput);
    auto buffer = ouput.SerializeAsString();

    // Show the serialized Protobuf size
    std::cout << "Protobuf size: " << buffer.size() << std::endl;

    // Deserialize the account from the Protobuf stream
    MyDomain::protobuf::Account input;
    input.ParseFromString(buffer);
    MyDomain::Account deserialized;
    deserialized.Deserialize(input);

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

    // Delete all global objects allocated by Protobuf
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
```

Output of the example is the following:
```
Protobuf size: 120

Account.Id = 1
Account.Name = Test
Account.Wallet.Currency = USD
Account.Wallet.Amount = 1000
Account.Order => Id: 1, Symbol: EURUSD, Side: 0, Type: 0, Price: 1.23456, Volume: 1000
Account.Order => Id: 2, Symbol: EURUSD, Side: 1, Type: 1, Price: 1, Volume: 100
Account.Order => Id: 3, Symbol: EURUSD, Side: 0, Type: 2, Price: 1.5, Volume: 10
```

## Protobuf performance
Protobuf serialization performance of the provided domain model is the
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
RAM free: 20.224 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Fri Mar 30 14:29:43 2018
UTC timestamp: Fri Mar 30 11:29:43 2018
===============================================================================
Benchmark: Protobuf-Serialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: Protobuf-Serialize
Average time: 731 ns / iteration
Minimal time: 731 ns / iteration
Maximal time: 737 ns / iteration
Total time: 731.319 ms
Total iterations: 1000000
Total bytes: 114.451 MiB
Iterations throughput: 1367392 / second
Bytes throughput: 156.497 MiB / second
Custom values:
        Size: 120
===============================================================================
```

Protobuf deserialization performance of the provided domain model is the
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
RAM free: 20.189 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Fri Mar 30 14:30:12 2018
UTC timestamp: Fri Mar 30 11:30:12 2018
===============================================================================
Phase: Protobuf-Deserialize
Average time: 1.151 mcs / iteration
Minimal time: 1.151 mcs / iteration
Maximal time: 1.179 mcs / iteration
Total time: 1.151 s
Total iterations: 1000000
Total bytes: 114.451 MiB
Iterations throughput: 868654 / second
Bytes throughput: 99.419 MiB / second
Custom values:
        Size: 120
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

    ...
};

struct Balance
{
    ...

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

    ...
};

struct Account
{
    ...

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
    account.Serialize(serializer);

    // Show the serialized JSON
    std::cout << "JSON: " << buffer.GetString() << std::endl;

    // Parse JSON string
    CppSerialization::JSON::Document json = CppSerialization::JSON::Parser::Parse(buffer.GetString());

    // Deserialize the account from the JSON stream
    MyDomain::Account deserialized;
    deserialized.Deserialize(json);

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
JSON content: {"id":1,"name":"Test","wallet":{"currency":"USD","amount":1000.0},"orders":[{"id":1,"symbol":"EURUSD","side":0,"type":0,"price":1.23456,"volume":1000.0},{"id":2,"symbol":"EURUSD","side":1,"type":1,"price":1.0,"volume":100.0},{"id":3,"symbol":"EURUSD","side":0,"type":2,"price":1.5,"volume":10.0}]}
JSON size: 297

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
Average time: 922 ns / iteration
Minimal time: 922 ns / iteration
Maximal time: 931 ns / iteration
Total time: 922.530 ms
Total iterations: 1000000
Total bytes: 283.247 MiB
Iterations throughput: 1083974 / second
Bytes throughput: 307.027 MiB / second
Custom values:
        Size: 297
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
Average time: 2.479 mcs / iteration
Minimal time: 2.479 mcs / iteration
Maximal time: 2.483 mcs / iteration
Total time: 2.479 s
Total iterations: 1000000
Total bytes: 283.247 MiB
Iterations throughput: 403366 / second
Bytes throughput: 114.255 MiB / second
Custom values:
        Size: 297
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
Average time: 918 ns / iteration
Minimal time: 918 ns / iteration
Maximal time: 975 ns / iteration
Total time: 918.357 ms
Total iterations: 1000000
Total bytes: 3.834 MiB
Iterations throughput: 1088900 / second
Bytes throughput: 4.157 MiB / second
Custom values:
        Size: 297               ..
===============================================================================
```
                                                                                ..