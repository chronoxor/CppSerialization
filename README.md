# CppSerialization

[![Linux build status](https://img.shields.io/travis/chronoxor/CppSerialization/master.svg?label=Linux)](https://travis-ci.org/chronoxor/CppSerialization)
[![OSX build status](https://img.shields.io/travis/chronoxor/CppSerialization/master.svg?label=OSX)](https://travis-ci.org/chronoxor/CppSerialization)
[![Cygwin build status](https://img.shields.io/appveyor/ci/chronoxor/CppSerialization/master.svg?label=Cygwin)](https://ci.appveyor.com/project/chronoxor/CppSerialization)
[![MinGW build status](https://img.shields.io/appveyor/ci/chronoxor/CppSerialization/master.svg?label=MinGW)](https://ci.appveyor.com/project/chronoxor/CppSerialization)
[![Windows build status](https://img.shields.io/appveyor/ci/chronoxor/CppSerialization/master.svg?label=Windows)](https://ci.appveyor.com/project/chronoxor/CppSerialization)

C++ Serialization Library provides functionality to serialize/deserialize
objects in/from different formats such as Cap'n'Proto, FastBinaryEncoding,
Flatbuffers, Protobuf, JSON.

Performance comparison based on the [Domain model](#domain-model):

| Format             | Message size | Serialization time | Deserialization time |
| ------------------ | ------------ | ------------------ | -------------------- |
| Cap'n'Proto        | 208 bytes    | 678 ns             | 480 ns               |
| FastBinaryEncoding | 234 bytes    | 116 ns             | 119 ns               |
| FlatBuffers        | 280 bytes    | 1024 ns            | 385 ns               |
| Protobuf           | 120 bytes    | 836 ns             | 1024 ns              |
| JSON               | 297 bytes    | 845 ns             | 2560 ns              |

[CppSerialization API reference](https://chronoxor.github.io/CppSerialization/index.html)

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
  * [Cap'n'Proto serialization](#capnproto-serialization)
    * [Cap'n'Proto schema](#capnproto-schema)
    * [Cap'n'Proto schema compilation](#capnproto-schema-compilation)
    * [Cap'n'Proto serialization methods](#capnproto-serialization-methods)
    * [Cap'n'Proto example](#capnproto-example)
    * [Cap'n'Proto performance](#capnproto-performance)
  * [FastBinaryEncoding serialization](#fastbinaryencoding-serialization)
    * [FastBinaryEncoding schema](#fastbinaryencoding-schema)
    * [FastBinaryEncoding schema compilation](#fastbinaryencoding-schema-compilation)
    * [FastBinaryEncoding serialization methods](#fastbinaryencoding-serialization-methods)
    * [FastBinaryEncoding example](#fastbinaryencoding-example)
    * [FastBinaryEncoding performance](#fastbinaryencoding-performance)
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
* Binary serialization using [Cap'n'Proto library](https://capnproto.org)
* Binary serialization using [FastBinaryEncoding library](https://github.com/chronoxor/FastBinaryEncoding)
* Binary serialization using [FlatBuffers library](https://google.github.io/flatbuffers)
* Binary serialization using [Protobuf library](https://developers.google.com/protocol-buffers)
* JSON serialization using [RapidJSON library](http://rapidjson.org)

# Requirements
* Linux
* OSX
* Windows 7 / Windows 10
* [CMake](https://www.cmake.org)
* [GIT](https://git-scm.com)
* [GCC](https://gcc.gnu.org)

Optional:
* [Clang](https://clang.llvm.org)
* [Clion](https://www.jetbrains.com/clion)
* [Cygwin](https://cygwin.com)
* [MinGW](https://mingw-w64.org/doku.php)
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
};

struct Account
{
    int Id;
    std::string Name;
    Balance Wallet;
    std::vector<Order> Orders;

    Account() : Account(0, "<\?\?\?>", "<\?\?\?>", 0.0) {}
    Account(int id, const char* name, const char* currency, double amount) : Wallet(currency, amount)
    {
        Id = id;
        Name = name;
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
        std::string symbol = reader.getSymbol();
        std::strncpy(Symbol, symbol.c_str(), std::min(symbol.size() + 1, sizeof(Symbol)));
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
        std::string currency = reader.getCurrency();
        std::strncpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
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
    account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

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
        std::cout << "Account.Order => Id: " << order.Id
            << ", Symbol: " << order.Symbol
            << ", Side: " << (int)order.Side
            << ", Type: " << (int)order.Type
            << ", Price: " << order.Price
            << ", Volume: " << order.Volume
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
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.485 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed May  9 00:18:42 2018
UTC timestamp: Tue May  8 21:18:42 2018
===============================================================================
Benchmark: Cap'n'Proto-Serialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: Cap'n'Proto-Serialize
Average time: 678 ns / iteration
Minimal time: 678 ns / iteration
Maximal time: 704 ns / iteration
Total time: 678.918 ms
Total iterations: 1000000
Total bytes: 198.373 MiB
Iterations throughput: 1472930 / second
Bytes throughput: 292.180 MiB / second
Custom values:
        Size: 208
===============================================================================
```

Cap'n'Proto deserialization performance of the provided domain model is the
following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.483 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed May  9 00:19:20 2018
UTC timestamp: Tue May  8 21:19:20 2018
===============================================================================
Benchmark: Cap'n'Proto-Deserialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: Cap'n'Proto-Deserialize
Average time: 480 ns / iteration
Minimal time: 480 ns / iteration
Maximal time: 519 ns / iteration
Total time: 480.625 ms
Total iterations: 1000000
Total bytes: 198.373 MiB
Iterations throughput: 2080620 / second
Bytes throughput: 412.738 MiB / second
Custom values:
        Size: 208
===============================================================================
```

# FastBinaryEncoding serialization
FastBinaryEncoding serialization is based on [FastBinaryEncoding library](https://github.com/chronoxor/FastBinaryEncoding).

## FastBinaryEncoding schema
FastBinaryEncoding serialization starts with describing a model schema. For our
domain model the schema will be the following:

```
package domain

enum OrderSide : byte
{
    buy;
    sell;
}

enum OrderType : byte
{
    market;
    limit;
    stop;
}

struct Order
{
    [key] int32 id;
    string symbol;
    OrderSide side;
    OrderType type;
    double price = 0.0;
    double volume = 0.0;
}

struct Balance
{
    [key] string currency;
    double amount = 0.0;
}

struct Account
{
    [key] int32 id;
    string name;
    Balance wallet;
    Order[] orders;
}
```

## FastBinaryEncoding schema compilation
The next step is a schema compilation using 'fbec' utility which will create
a generated code for required programming language.

The following command will create a C++ generated code:
```
fbec --c++ --input=domain.fbe --output=.
```

It is possible to use add_custom_command() in CMakeLists.txt to generate code
using 'cmake' utility:
```
add_custom_command(TARGET example POST_BUILD COMMAND fbec --c++ --input=domain.fbe --output=.)
```

As the result 'common.h' and 'domain.h' files will be generated.

## FastBinaryEncoding serialization methods
Finally you should extend your domain model with a FastBinaryEncoding serialization
methods:

```C++
#include "fbe/domain.h"

#include <algorithm>

namespace MyDomain {

struct Order
{
    ...

    // FastBinaryEncoding serialization

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

    ...
};

struct Balance
{
    ...

    // FastBinaryEncoding serialization

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

    ...
};

struct Account
{
    ...

    // FastBinaryEncoding serialization

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

    ...
};

} // namespace MyDomain
```

## FastBinaryEncoding example
Here comes the usage example of FastBinaryEncoding serialize/deserialize functionality:

```C++
#include "../domain/domain.h"

#include <iostream>

int main(int argc, char** argv)
{
    // Create a new account with some orders
    MyDomain::Account account(1, "Test", "USD", 1000);
    account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

    // Serialize the account to the FBE stream
    FBE::AccountModel<FBE::WriteBuffer> writer;
    size_t model_begin = writer.create_begin();
    account.Serialize(writer.model);
    size_t serialized = writer.create_end(model_begin);
    assert(writer.verify() && "Model is broken!");

    // Show the serialized FBE size
    std::cout << "FBE size: " << serialized << std::endl;

    // Deserialize the account from the FBE stream
    MyDomain::Account deserialized;
    FBE::AccountModel<FBE::ReadBuffer> reader;
    reader.attach(writer.buffer());
    assert(reader.verify() && "Model is broken!");
    deserialized.Deserialize(reader.model);

    // Show account content
    std::cout << std::endl;
    std::cout << "Account.Id = " << deserialized.Id << std::endl;
    std::cout << "Account.Name = " << deserialized.Name << std::endl;
    std::cout << "Account.Wallet.Currency = " << deserialized.Wallet.Currency << std::endl;
    std::cout << "Account.Wallet.Amount = " << deserialized.Wallet.Amount << std::endl;
    for (auto& order : deserialized.Orders)
    {
        std::cout << "Account.Order => Id: " << order.Id
            << ", Symbol: " << order.Symbol
            << ", Side: " << (int)order.Side
            << ", Type: " << (int)order.Type
            << ", Price: " << order.Price
            << ", Volume: " << order.Volume
            << std::endl;
    }

    return 0;
}
```

Output of the example is the following:
```
FBE size: 234

Account.Id = 1
Account.Name = Test
Account.Wallet.Currency = USD
Account.Wallet.Amount = 1000
Account.Order => Id: 1, Symbol: EURUSD, Side: 0, Type: 0, Price: 1.23456, Volume: 1000
Account.Order => Id: 2, Symbol: EURUSD, Side: 1, Type: 1, Price: 1, Volume: 100
Account.Order => Id: 3, Symbol: EURUSD, Side: 0, Type: 2, Price: 1.5, Volume: 10
```

## FastBinaryEncoding performance
FastBinaryEncoding serialization performance of the provided domain model is the
following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.341 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed May  9 02:34:50 2018
UTC timestamp: Tue May  8 23:34:50 2018
===============================================================================
Benchmark: FastBinaryEncoding-Serialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: FastBinaryEncoding-Serialize
Average time: 116 ns / iteration
Minimal time: 116 ns / iteration
Maximal time: 118 ns / iteration
Total time: 116.975 ms
Total iterations: 1000000
Total bytes: 223.163 MiB
Iterations throughput: 8548766 / second
Bytes throughput: 1.883 GiB / second
Custom values:
        Size: 234
===============================================================================
```

FastBinaryEncoding deserialization performance of the provided domain model is the
following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.339 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed May  9 02:35:06 2018
UTC timestamp: Tue May  8 23:35:06 2018
===============================================================================
Benchmark: FastBinaryEncoding-Deserialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: FastBinaryEncoding-Deserialize
Average time: 119 ns / iteration
Minimal time: 119 ns / iteration
Maximal time: 129 ns / iteration
Total time: 119.236 ms
Total iterations: 1000000
Total bytes: 223.163 MiB
Iterations throughput: 8386715 / second
Bytes throughput: 1.847 GiB / second
Custom values:
        Size: 234
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
        std::string symbol = value.symbol()->str();
        std::strncpy(Symbol, symbol.c_str(), std::min(symbol.size() + 1, sizeof(Symbol)));
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
        std::string currency = value.currency()->str();
        std::strncpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
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
    account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

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
        std::cout << "Account.Order => Id: " << order.Id
            << ", Symbol: " << order.Symbol
            << ", Side: " << (int)order.Side
            << ", Type: " << (int)order.Type
            << ", Price: " << order.Price
            << ", Volume: " << order.Volume
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
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.493 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed May  9 00:21:43 2018
UTC timestamp: Tue May  8 21:21:43 2018
===============================================================================
Benchmark: FlatBuffers-Serialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: FlatBuffers-Serialize
Average time: 1.024 mcs / iteration
Minimal time: 1.024 mcs / iteration
Maximal time: 1.094 mcs / iteration
Total time: 1.024 s
Total iterations: 1000000
Total bytes: 267.029 MiB
Iterations throughput: 976463 / second
Bytes throughput: 260.761 MiB / second
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
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.495 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed May  9 00:21:58 2018
UTC timestamp: Tue May  8 21:21:58 2018
===============================================================================
Benchmark: FlatBuffers-Deserialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: FlatBuffers-Deserialize
Average time: 385 ns / iteration
Minimal time: 385 ns / iteration
Maximal time: 390 ns / iteration
Total time: 385.867 ms
Total iterations: 1000000
Total bytes: 267.029 MiB
Iterations throughput: 2591566 / second
Bytes throughput: 692.023 MiB / second
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
        std::string symbol = value.symbol();
        std::strncpy(Symbol, symbol.c_str(), std::min(symbol.size() + 1, sizeof(Symbol)));
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
        std::string currency = value.currency();
        std::strncpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
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
    account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

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
        std::cout << "Account.Order => Id: " << order.Id
            << ", Symbol: " << order.Symbol
            << ", Side: " << (int)order.Side
            << ", Type: " << (int)order.Type
            << ", Price: " << order.Price
            << ", Volume: " << order.Volume
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
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.488 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed May  9 00:23:37 2018
UTC timestamp: Tue May  8 21:23:37 2018
===============================================================================
Benchmark: Protobuf-Serialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: Protobuf-Serialize
Average time: 836 ns / iteration
Minimal time: 836 ns / iteration
Maximal time: 866 ns / iteration
Total time: 836.492 ms
Total iterations: 1000000
Total bytes: 114.451 MiB
Iterations throughput: 1195467 / second
Bytes throughput: 136.829 MiB / second
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
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.482 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed May  9 00:24:13 2018
UTC timestamp: Tue May  8 21:24:13 2018
===============================================================================
Benchmark: Protobuf-Deserialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: Protobuf-Deserialize
Average time: 1.024 mcs / iteration
Minimal time: 1.024 mcs / iteration
Maximal time: 1.091 mcs / iteration
Total time: 1.024 s
Total iterations: 1000000
Total bytes: 114.451 MiB
Iterations throughput: 976142 / second
Bytes throughput: 111.727 MiB / second
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
        Deserializer::FindArray(json, "orders", [this](const Value& item)
        {
            Order order;
            order.Deserialize(item);
            Orders.emplace_back(order);
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
    account.Orders.emplace_back(MyDomain::Order(1, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(MyDomain::Order(2, "EURUSD", MyDomain::OrderSide::SELL, MyDomain::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(MyDomain::Order(3, "EURUSD", MyDomain::OrderSide::BUY, MyDomain::OrderType::STOP, 1.5, 10));

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
        std::cout << "Account.Order => Id: " << order.Id
            << ", Symbol: " << order.Symbol
            << ", Side: " << (int)order.Side
            << ", Type: " << (int)order.Type
            << ", Price: " << order.Price
            << ", Volume: " << order.Volume
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
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.475 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed May  9 00:25:12 2018
UTC timestamp: Tue May  8 21:25:12 2018
===============================================================================
Benchmark: JSON-Serialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: JSON-Serialize
Average time: 845 ns / iteration
Minimal time: 845 ns / iteration
Maximal time: 871 ns / iteration
Total time: 845.313 ms
Total iterations: 1000000
Total bytes: 283.247 MiB
Iterations throughput: 1182993 / second
Bytes throughput: 335.074 MiB / second
Custom values:
        Size: 297
===============================================================================
```

JSON document parsing performance of the provided domain model is the following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.484 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed May  9 00:25:44 2018
UTC timestamp: Tue May  8 21:25:44 2018
===============================================================================
Benchmark: JSON-Parse
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: JSON-Parse
Average time: 2.560 mcs / iteration
Minimal time: 2.560 mcs / iteration
Maximal time: 2.600 mcs / iteration
Total time: 2.560 s
Total iterations: 1000000
Total bytes: 283.247 MiB
Iterations throughput: 390564 / second
Bytes throughput: 110.639 MiB / second
Custom values:
        Size: 297
===============================================================================
```

JSON deserialization performance of the provided domain model is the following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.489 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed May  9 00:26:05 2018
UTC timestamp: Tue May  8 21:26:05 2018
===============================================================================
Benchmark: JSON-Deserialize
Attempts: 5
Iterations: 1000000
-------------------------------------------------------------------------------
Phase: JSON-Deserialize
Average time: 638 ns / iteration
Minimal time: 638 ns / iteration
Maximal time: 674 ns / iteration
Total time: 638.172 ms
Total iterations: 1000000
Total bytes: 3.834 MiB
Iterations throughput: 1566975 / second
Bytes throughput: 5.1000 MiB / second
Custom values:
        Size: 297
===============================================================================
```
