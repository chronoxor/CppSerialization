# CppSerialization

[![Linux (clang)](https://github.com/chronoxor/CppSerialization/actions/workflows/build-linux-clang.yml/badge.svg)](https://github.com/chronoxor/CppSerialization/actions/workflows/build-linux-clang.yml)
[![Linux (gcc)](https://github.com/chronoxor/CppSerialization/actions/workflows/build-linux-gcc.yml/badge.svg)](https://github.com/chronoxor/CppSerialization/actions/workflows/build-linux-gcc.yml)
<br/>
[![MacOS](https://github.com/chronoxor/CppSerialization/actions/workflows/build-macos.yml/badge.svg)](https://github.com/chronoxor/CppSerialization/actions/workflows/build-macos.yml)
<br/>
[![Windows (MSYS2)](https://github.com/chronoxor/CppSerialization/actions/workflows/build-windows-msys2.yml/badge.svg)](https://github.com/chronoxor/CppSerialization/actions/workflows/build-windows-msys2.yml)
[![Windows (MinGW)](https://github.com/chronoxor/CppSerialization/actions/workflows/build-windows-mingw.yml/badge.svg)](https://github.com/chronoxor/CppSerialization/actions/workflows/build-windows-mingw.yml)
[![Windows (Visual Studio)](https://github.com/chronoxor/CppSerialization/actions/workflows/build-windows-vs.yml/badge.svg)](https://github.com/chronoxor/CppSerialization/actions/workflows/build-windows-vs.yml)

C++ Serialization Library provides functionality to serialize/deserialize
objects using different protocols such as Cap'n'Proto, FastBinaryEncoding,
Flatbuffers, Protobuf, SimpleBinaryEncoding, JSON.

Performance comparison based on the [Domain model](#domain-model):

| Protocol                                                                     | Message size | Serialization time | Deserialization time |
| :--------------------------------------------------------------------------: | -----------: | -----------------: | -------------------: |
| [Cap'n'Proto](https://capnproto.org)                                         |    208 bytes |             558 ns |               359 ns |
| [FastBinaryEncoding](https://github.com/chronoxor/FastBinaryEncoding)        |    234 bytes |              66 ns |                82 ns |
| [FlatBuffers](https://google.github.io/flatbuffers)                          |    280 bytes |             830 ns |               290 ns |
| [Protobuf](https://developers.google.com/protocol-buffers)                   |    120 bytes |             628 ns |               759 ns |
| [SimpleBinaryEncoding](https://github.com/real-logic/simple-binary-encoding) |    138 bytes |              35 ns |                85 ns |
| [JSON](http://rapidjson.org)                                                 |    301 bytes |             740 ns |               500 ns |

[CppSerialization API reference](https://chronoxor.github.io/CppSerialization/index.html)

# Contents
  * [Features](#features)
  * [Requirements](#requirements)
  * [How to build?](#how-to-build)
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
  * [SimpleBinaryEncoding serialization](#simplebinaryencoding-serialization)
    * [SimpleBinaryEncoding schema](#simplebinaryencoding-schema)
    * [SimpleBinaryEncoding schema compilation](#simplebinaryencoding-schema-compilation)
    * [SimpleBinaryEncoding serialization methods](#simplebinaryencoding-serialization-methods)
    * [SimpleBinaryEncoding example](#simplebinaryencoding-example)
    * [SimpleBinaryEncoding performance](#simplebinaryencoding-performance)
  * [JSON serialization](#json-serialization)
    * [JSON serialization methods](#json-serialization-methods)
    * [JSON example](#json-example)
    * [JSON performance](#json-performance)

# Features
* Cross platform (Linux, MacOS, Windows)
* Binary serialization using [Cap'n'Proto library](https://capnproto.org)
* Binary serialization using [FastBinaryEncoding library](https://github.com/chronoxor/FastBinaryEncoding)
* Binary serialization using [FlatBuffers library](https://google.github.io/flatbuffers)
* Binary serialization using [Protobuf library](https://developers.google.com/protocol-buffers)
* Binary serialization using [SimpleBinaryEncoding library](https://github.com/real-logic/simple-binary-encoding)
* JSON serialization using [RapidJSON library](http://rapidjson.org)

# Requirements
* Linux
* MacOS
* Windows
* [cmake](https://www.cmake.org)
* [gcc](https://gcc.gnu.org)
* [git](https://git-scm.com)
* [gil](https://github.com/chronoxor/gil.git)
* [python3](https://www.python.org)

Optional:
* [clang](https://clang.llvm.org)
* [CLion](https://www.jetbrains.com/clion)
* [MSYS2](https://www.msys2.org)
* [MinGW](https://mingw-w64.org/doku.php)
* [Visual Studio](https://www.visualstudio.com)

# How to build?

### Linux: install required packages
```shell
sudo apt-get install -y binutils-dev uuid-dev
```

### Install [gil (git links) tool](https://github.com/chronoxor/gil)
```shell
pip3 install gil
```

### Setup repository
```shell
git clone https://github.com/chronoxor/CppSerialization.git
cd CppSerialization
gil update
```

### Linux
```shell
cd build
./unix.sh
```

### MacOS
```shell
cd build
./unix.sh
```

### Windows (MSYS2)
```shell
cd build
unix.bat
```

### Windows (MinGW)
```shell
cd build
mingw.bat
```

### Windows (Visual Studio)
```shell
cd build
vs.bat
```

# Domain model
The first step you should perform to use CppSerialization library is to provide
a domain model (aka business objects). Domain model is a set of structures or
classes that related to each other and might be aggregated in some hierarchy.

There is an example domain model which describes Account-Balance-Orders
relation of some abstract trading platform:

```c++
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

} // namespace TradeProto
```

The next step you should provide serialization methods for the domain model.

# Cap'n'Proto serialization
Cap'n'Proto serialization is based on [Cap'n'Proto library](https://capnproto.org).

## Cap'n'Proto schema
Cap'n'Proto serialization starts with describing a model schema. For our domain
model the schema will be the following:

```proto
# Unique file ID, generated by 'capnp id'
@0xd4b6e00623bed170;

using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("Trade::capnproto");

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
```shell
capnp compile -I capnproto/c++/src -oc++ trade.capnp
```

It is possible to use capnp_generate_cpp() in CMakeLists.txt to generate code
using 'cmake' utility:
```cmake
capnp_generate_cpp(CAPNP_HEADERS CAPNP_SOURCES trade.capnp)
```

As the result 'trade.capnp.h' and 'trade.capnp.c++' files will be generated.

## Cap'n'Proto serialization methods
Finally you should extend your domain model with a Cap'n'Proto serialization
methods:

```c++
#include "capnp/serialize.h"
#include "capnproto/trade.capnp.h"

#include <algorithm>

namespace TradeProto {

struct Order
{
    ...

    // Cap'n'Proto serialization

    void Serialize(Trade::capnproto::Order::Builder& builder)
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

    ...
};

struct Balance
{
    ...

    // Cap'n'Proto serialization

    void Serialize(Trade::capnproto::Balance::Builder& builder)
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

    ...
};

struct Account
{
    ...

    // Cap'n'Proto serialization

    void Serialize(Trade::capnproto::Account::Builder& builder)
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

    ...
};

} // namespace TradeProto
```

## Cap'n'Proto example
Here comes the usage example of FlatBuffers serialize/deserialize functionality:

```c++
#include "../proto/trade.h"

#include <iostream>

int main(int argc, char** argv)
{
    // Create a new account with some orders
    TradeProto::Account account(1, "Test", "USD", 1000);
    account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

    // Serialize the account to the Cap'n'Proto stream
    capnp::MallocMessageBuilder output;
    Trade::capnproto::Account::Builder builder = output.initRoot<Trade::capnproto::Account>();
    account.Serialize(builder);
    kj::VectorOutputStream buffer;
    writeMessage(buffer, output);

    // Show the serialized Cap'n'Proto size
    std::cout << "Protobuf size: " << buffer.getArray().size() << std::endl;

    // Deserialize the account from the Cap'n'Proto stream
    kj::ArrayInputStream array(buffer.getArray());
    capnp::InputStreamMessageReader input(array);
    TradeProto::Account deserialized;
    deserialized.Deserialize(input.getRoot<Trade::capnproto::Account>());

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
CPU architecutre: Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 4.008 GHz
CPU Hyper-Threading: enabled
RAM total: 31.903 GiB
RAM free: 20.431 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jul 18 13:21:25 2018
UTC timestamp: Wed Jul 18 10:21:25 2018
===============================================================================
Benchmark: Cap'n'Proto-Serialize
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: Cap'n'Proto-Serialize
Average time: 558 ns/op
Minimal time: 558 ns/op
Maximal time: 568 ns/op
Total time: 4.783 s
Total operations: 8562741
Total bytes: 1.674 GiB
Operations throughput: 1789911 ops/s
Bytes throughput: 355.055 MiB/s
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
CPU architecutre: Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 4.008 GHz
CPU Hyper-Threading: enabled
RAM total: 31.903 GiB
RAM free: 20.631 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jul 18 13:22:27 2018
UTC timestamp: Wed Jul 18 10:22:27 2018
===============================================================================
Benchmark: Cap'n'Proto-Deserialize
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: Cap'n'Proto-Deserialize
Average time: 359 ns/op
Minimal time: 359 ns/op
Maximal time: 361 ns/op
Total time: 4.828 s
Total operations: 13440063
Total bytes: 2.618 GiB
Operations throughput: 2783738 ops/s
Bytes throughput: 552.198 MiB/s
Custom values:
        Size: 208
===============================================================================
```

# FastBinaryEncoding serialization
FastBinaryEncoding serialization is based on [FastBinaryEncoding library](https://github.com/chronoxor/FastBinaryEncoding).

## FastBinaryEncoding schema
FastBinaryEncoding serialization starts with describing a model schema. For our
domain model the schema will be the following:

```proto
package trade

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
```shell
fbec --cpp --input=trade.fbe --output=.
```

It is possible to use add_custom_command() in CMakeLists.txt to generate code
using 'cmake' utility:
```cmake
add_custom_command(TARGET example POST_BUILD COMMAND fbec --cpp --input=trade.fbe --output=.)
```

As the result 'fbe.h' and 'trade.h' files will be generated.

## FastBinaryEncoding serialization methods
Finally you should extend your domain model with a FastBinaryEncoding serialization
methods:

```c++
#include "fbe/trade_models.h"

#include <algorithm>

namespace TradeProto {

struct Order
{
    ...

    // FastBinaryEncoding serialization

    template <class TBuffer>
    void Serialize(FBE::FieldModel<TBuffer, trade::Order>& model)
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

    template <class TBuffer>
    void Deserialize(const FBE::FieldModel<TBuffer, trade::Order>& model)
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

    ...
};

struct Balance
{
    ...

    // FastBinaryEncoding serialization

    template <class TBuffer>
    void Serialize(FBE::FieldModel<TBuffer, trade::Balance>& model)
    {
        size_t model_begin = model.set_begin();
        model.currency.set(Currency);
        model.amount.set(Amount);
        model.set_end(model_begin);
    }

    template <class TBuffer>
    void Deserialize(const FBE::FieldModel<TBuffer, trade::Balance>& model)
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
    void Serialize(FBE::FieldModel<TBuffer, trade::Account>& model)
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
    void Deserialize(const FBE::FieldModel<TBuffer, trade::Account>& model)
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

} // namespace TradeProto
```

## FastBinaryEncoding example
Here comes the usage example of FastBinaryEncoding serialize/deserialize functionality:

```c++
#include "../proto/trade.h"

#include <iostream>

int main(int argc, char** argv)
{
    // Create a new account with some orders
    TradeProto::Account account(1, "Test", "USD", 1000);
    account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

    // Serialize the account to the FBE stream
    FBE::trade::AccountModel<FBE::WriteBuffer> writer;
    size_t model_begin = writer.create_begin();
    account.Serialize(writer.model);
    size_t serialized = writer.create_end(model_begin);
    assert(writer.verify() && "Model is broken!");

    // Show the serialized FBE size
    std::cout << "FBE size: " << serialized << std::endl;

    // Deserialize the account from the FBE stream
    TradeProto::Account deserialized;
    FBE::trade::AccountModel<FBE::ReadBuffer> reader;
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
CPU architecutre: Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 4.008 GHz
CPU Hyper-Threading: enabled
RAM total: 31.903 GiB
RAM free: 20.644 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jul 18 13:23:18 2018
UTC timestamp: Wed Jul 18 10:23:18 2018
===============================================================================
Benchmark: FastBinaryEncoding-Serialize
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: FastBinaryEncoding-Serialize
Average time: 66 ns/op
Minimal time: 66 ns/op
Maximal time: 67 ns/op
Total time: 3.598 s
Total operations: 54301046
Total bytes: 11.853 GiB
Operations throughput: 15090301 ops/s
Bytes throughput: 3.295 GiB/s
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
CPU architecutre: Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 4.008 GHz
CPU Hyper-Threading: enabled
RAM total: 31.903 GiB
RAM free: 20.520 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jul 18 13:24:03 2018
UTC timestamp: Wed Jul 18 10:24:03 2018
===============================================================================
Benchmark: FastBinaryEncoding-Deserialize
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: FastBinaryEncoding-Deserialize
Average time: 82 ns/op
Minimal time: 82 ns/op
Maximal time: 85 ns/op
Total time: 3.302 s
Total operations: 40260567
Total bytes: 8.792 GiB
Operations throughput: 12190362 ops/s
Bytes throughput: 2.672 GiB/s
Custom values:
        Size: 234
===============================================================================
```

# FlatBuffers serialization
FlatBuffers serialization is based on [FlatBuffers library](https://google.github.io/flatbuffers).

## FlatBuffers schema
FlatBuffers serialization starts with describing a model schema. For our domain
model the schema will be the following:

```proto
namespace Trade.flatbuf;

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
```shell
flatc --cpp --scoped-enums -o . trade.fbs
```

It is possible to use add_custom_command() in CMakeLists.txt to generate code
using 'cmake' utility:
```cmake
add_custom_command(TARGET example POST_BUILD COMMAND flatc --cpp --scoped-enums -o . trade.fbs)
```

As the result 'domain_generated.h' file will be generated.

## FlatBuffers serialization methods
Finally you should extend your domain model with a FlatBuffers serialization
methods:

```c++
#include "flatbuffers/trade_generated.h"

#include <algorithm>

namespace TradeProto {

struct Order
{
    ...

    // FlatBuffers serialization

    flatbuffers::Offset<Trade::flatbuf::Order> Serialize(flatbuffers::FlatBufferBuilder& builder)
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

    ...
};

struct Balance
{
    ...

    // FlatBuffers serialization

    flatbuffers::Offset<Trade::flatbuf::Balance> Serialize(flatbuffers::FlatBufferBuilder& builder)
    {
        return Trade::flatbuf::CreateBalanceDirect(builder, Currency, Amount);
    }

    void Deserialize(const Trade::flatbuf::Balance& value)
    {
        std::string currency = value.currency()->str();
        std::memcpy(Currency, currency.c_str(), std::min(currency.size() + 1, sizeof(Currency)));
        Amount = value.amount();
    }

    ...
};

struct Account
{
    ...

    // FlatBuffers serialization

    flatbuffers::Offset<Trade::flatbuf::Account> Serialize(flatbuffers::FlatBufferBuilder& builder)
    {
        auto wallet = Wallet.Serialize(builder);
        std::vector<flatbuffers::Offset<Trade::flatbuf::Order>> orders;
        for (auto& order : Orders)
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

    ...
};

} // namespace TradeProto
```

## FlatBuffers example
Here comes the usage example of FlatBuffers serialize/deserialize functionality:

```c++
#include "../proto/trade.h"

#include <iostream>

int main(int argc, char** argv)
{
    // Create a new account with some orders
    TradeProto::Account account(1, "Test", "USD", 1000);
    account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

    // Serialize the account to the FlatBuffer stream
    flatbuffers::FlatBufferBuilder builder;
    builder.Finish(account.Serialize(builder));

    // Show the serialized FlatBuffer size
    std::cout << "FlatBuffer size: " << builder.GetSize() << std::endl;

    // Deserialize the account from the FlatBuffer stream
    TradeProto::Account deserialized;
    deserialized.Deserialize(*Trade::flatbuf::GetAccount(builder.GetBufferPointer()));

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
CPU architecutre: Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 4.008 GHz
CPU Hyper-Threading: enabled
RAM total: 31.903 GiB
RAM free: 20.624 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jul 18 13:24:57 2018
UTC timestamp: Wed Jul 18 10:24:57 2018
===============================================================================
Benchmark: FlatBuffers-Serialize
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: FlatBuffers-Serialize
Average time: 830 ns/op
Minimal time: 830 ns/op
Maximal time: 840 ns/op
Total time: 4.830 s
Total operations: 5816587
Total bytes: 1.529 GiB
Operations throughput: 1204142 ops/s
Bytes throughput: 321.553 MiB/s
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
RAM free: 20.631 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jul 18 13:25:45 2018
UTC timestamp: Wed Jul 18 10:25:45 2018
===============================================================================
Benchmark: FlatBuffers-Deserialize
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: FlatBuffers-Deserialize
Average time: 290 ns/op
Minimal time: 290 ns/op
Maximal time: 293 ns/op
Total time: 4.690 s
Total operations: 16143136
Total bytes: 4.214 GiB
Operations throughput: 3441995 ops/s
Bytes throughput: 919.114 MiB/s
Custom values:
        Size: 280
===============================================================================
```

# Protobuf serialization
Protobuf serialization is based on [Protobuf library](https://developers.google.com/protocol-buffers).

## Protobuf schema
Protobuf serialization starts with describing a model schema. For our domain
model the schema will be the following:

```proto
syntax = "proto3";
package Trade.protobuf;

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
```shell
protoc --proto_path=. --cpp_out=. trade.proto
```

It is possible to use add_custom_command() in CMakeLists.txt to generate code
using 'cmake' utility:
```cmake
add_custom_command(TARGET example POST_BUILD COMMAND protoc --proto_path=. --cpp_out=. trade.proto)
```

As the result 'trade.pb.h' and 'trade.pb.cc' files will be generated.

## Protobuf serialization methods
Finally you should extend your domain model with a FlatBuffers serialization
methods:

```c++
#include "protobuf/trade.pb.h"

#include <algorithm>

namespace TradeProto {

struct Order
{
    ...

    // Protobuf serialization

    Trade::protobuf::Order& Serialize(Trade::protobuf::Order& value)
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

    ...
};

struct Balance
{
    ...

    // Protobuf serialization

    Trade::protobuf::Balance& Serialize(Trade::protobuf::Balance& value)
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

    ...
};

struct Account
{
    ...

    // Protobuf serialization

    Trade::protobuf::Account& Serialize(Trade::protobuf::Account& value)
    {
        value.set_id(id);
        value.set_name(Name);
        value.set_allocated_wallet(&Wallet.Serialize(*value.wallet().New(value.GetArena())));
        for (auto& order : Orders)
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

    ...
};

} // namespace TradeProto
```

## Protobuf example
Here comes the usage example of Protobuf serialize/deserialize functionality:

```c++
#include "../proto/trade.h"

#include <iostream>

int main(int argc, char** argv)
{
    // Create a new account with some orders
    TradeProto::Account account(1, "Test", "USD", 1000);
    account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

    // Serialize the account to the Protobuf stream
    Trade::protobuf::Account output;
    account.Serialize(output);
    auto buffer = output.SerializeAsString();

    // Show the serialized Protobuf size
    std::cout << "Protobuf size: " << buffer.size() << std::endl;

    // Deserialize the account from the Protobuf stream
    Trade::protobuf::Account input;
    input.ParseFromString(buffer);
    TradeProto::Account deserialized;
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
CPU architecutre: Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 4.008 GHz
CPU Hyper-Threading: enabled
RAM total: 31.903 GiB
RAM free: 20.676 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jul 18 13:26:34 2018
UTC timestamp: Wed Jul 18 10:26:34 2018
===============================================================================
Benchmark: Protobuf-Serialize
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: Protobuf-Serialize
Average time: 628 ns/op
Minimal time: 628 ns/op
Maximal time: 658 ns/op
Total time: 4.552 s
Total operations: 7240754
Total bytes: 828.653 MiB
Operations throughput: 1590357 ops/s
Bytes throughput: 182.002 MiB/s
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
RAM free: 20.676 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jul 18 13:27:18 2018
UTC timestamp: Wed Jul 18 10:27:18 2018
===============================================================================
Benchmark: Protobuf-Deserialize
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: Protobuf-Deserialize
Average time: 759 ns/op
Minimal time: 759 ns/op
Maximal time: 776 ns/op
Total time: 4.757 s
Total operations: 6267474
Total bytes: 717.261 MiB
Operations throughput: 1317322 ops/s
Bytes throughput: 150.773 MiB/s
Custom values:
        Size: 120
===============================================================================
```

# SimpleBinaryEncoding serialization
SimpleBinaryEncoding serialization is based on [SimpleBinaryEncoding library](https://github.com/real-logic/simple-binary-encoding).

## SimpleBinaryEncoding schema
SimpleBinaryEncoding serialization starts with describing a model schema. For our
domain model the schema will be the following:

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<sbe:messageSchema xmlns:sbe="http://fixprotocol.io/2016/sbe" package="sbe" id="1" version="1" semanticVersion="5.2" description="Trade schema" byteOrder="littleEndian">
    <types>
        <composite name="messageHeader" description="Message identifiers and length of message root">
            <type name="blockLength" primitiveType="uint16"/>
            <type name="templateId" primitiveType="uint16"/>
            <type name="schemaId" primitiveType="uint16"/>
            <type name="version" primitiveType="uint16"/>
        </composite>
        <composite name="groupSizeEncoding" description="Repeating group dimensions">
            <type name="blockLength" primitiveType="uint16"/>
            <type name="numInGroup" primitiveType="uint16"/>
        </composite>
        <composite name="varStringEncoding">
            <type name="length" primitiveType="uint32" maxValue="1073741824"/>
            <type name="varData" primitiveType="uint8" length="0" characterEncoding="UTF-8"/>
        </composite>
    </types>
    <types>
        <enum name="OrderSide" encodingType="uint8">
            <validValue name="buy">0</validValue>
            <validValue name="sell">1</validValue>
        </enum>
        <enum name="OrderType" encodingType="uint8">
            <validValue name="market">0</validValue>
            <validValue name="limit">1</validValue>
            <validValue name="stop">2</validValue>
        </enum>
        <composite name="Order">
            <type name="id" primitiveType="int32"/>
            <type name="symbol" primitiveType="char" length="10" characterEncoding="UTF-8"/>
            <ref name="side" type="OrderSide"/>
            <ref name="type" type="OrderType"/>
            <type name="price" primitiveType="double"/>
            <type name="volume" primitiveType="double"/>
        </composite>
        <composite name="Balance">
            <type name="currency" primitiveType="char" length="10" characterEncoding="UTF-8"/>
            <type name="amount" primitiveType="double"/>
        </composite>
        <type name="AccountId" primitiveType="int32"/>
    </types>
    <sbe:message name="Account" id="1">
        <field name="id" id="1" type="AccountId"/>
        <field name="wallet" id="2" type="Balance"/>
        <group name="orders" id="3" dimensionType="groupSizeEncoding">
            <field name="order" id="4" type="Order"/>
        </group>
        <data name="name" id="5" type="varStringEncoding"/>
    </sbe:message>
</sbe:messageSchema>
```

## SimpleBinaryEncoding schema compilation
The next step is a schema compilation using 'sbe' utility which will create
a generated code for required programming language.

The following command will create a C++ generated code:
```shell
java -Dsbe.target.language=cpp -jar sbe-all-1.27.0.jar trade.sbe.xml
```

As the result required C++ header files will be generated.

## SimpleBinaryEncoding serialization methods
Finally you should extend your domain model with a SimpleBinaryEncoding serialization
methods:

```c++
#include "fbe/trade_models.h"

#include <algorithm>

namespace TradeProto {

struct Order
{
    ...

    // SimpleBinaryEncoding serialization

    void Serialize(sbe::Order& model)
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

    ...
};

struct Balance
{
    ...

    // SimpleBinaryEncoding serialization

    void Serialize(sbe::Balance& model)
    {
        model.putCurrency(Currency);
        model.amount(Amount);
    }

    void Deserialize(sbe::Balance& model)
    {
        model.getCurrency(Currency, sizeof(Currency));
        Amount = model.amount();
    }

    ...
};

struct Account
{
    ...

    // SimpleBinaryEncoding serialization

    void Serialize(sbe::Account& model)
    {
        model.id(Id);
        model.putName(Name);
        Wallet.Serialize(model.wallet());
        auto orders = model.ordersCount((uint16_t)Orders.size());
        for (auto& order : Orders)
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

    ...
};

} // namespace TradeProto
```

## SimpleBinaryEncoding example
Here comes the usage example of SimpleBinaryEncoding serialize/deserialize functionality:

```c++
#include "../proto/trade.h"

#include <iostream>

int main(int argc, char** argv)
{
    // Create a new account with some orders
    TradeProto::Account account(1, "Test", "USD", 1000);
    account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

    // Serialize the account to the SBE stream
    char buffer[1024];
    sbe::MessageHeader header;
    header.wrap(buffer, 0, 1, sizeof(buffer))
       .blockLength(sbe::Account::sbeBlockLength())
       .templateId(sbe::Account::sbeTemplateId())
       .schemaId(sbe::Account::sbeSchemaId())
       .version(sbe::Account::sbeSchemaVersion());
    sbe::Account message;
    message.wrapForEncode(buffer, header.encodedLength(), sizeof(buffer));
    account.Serialize(message);

    // Show the serialized SBE size
    std::cout << "SBE size: " << header.encodedLength() + message.encodedLength() << std::endl;

    // Deserialize the account from the SBE stream
    header.wrap(buffer, 0, 1, sizeof(buffer));
    int actingVersion = header.version();
    int actingBlockLength = header.blockLength();
    message.wrapForDecode(buffer, header.encodedLength(), actingBlockLength, actingVersion, sizeof(buffer));
    TradeProto::Account deserialized;
    deserialized.Deserialize(message);

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
SBE size: 138

Account.Id = 1
Account.Name = Test
Account.Wallet.Currency = USD
Account.Wallet.Amount = 1000
Account.Order => Id: 1, Symbol: EURUSD, Side: 0, Type: 0, Price: 1.23456, Volume: 1000
Account.Order => Id: 2, Symbol: EURUSD, Side: 1, Type: 1, Price: 1, Volume: 100
Account.Order => Id: 3, Symbol: EURUSD, Side: 0, Type: 2, Price: 1.5, Volume: 10
```

## SimpleBinaryEncoding performance
SimpleBinaryEncoding serialization performance of the provided domain model is the
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
RAM free: 16.910 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jan  2 05:34:26 2019
UTC timestamp: Wed Jan  2 02:34:26 2019
===============================================================================
Benchmark: SimpleBinaryEncoding-Serialize
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: SimpleBinaryEncoding-Serialize
Average time: 35 ns/op
Minimal time: 35 ns/op
Maximal time: 38 ns/op
Total time: 2.398 s
Total operations: 67877907
Total bytes: 8.741 GiB
Operations throughput: 28296533 ops/s
Bytes throughput: 3.652 GiB/s
Custom values:
        Size: 138
===============================================================================
```

SimpleBinaryEncoding deserialization performance of the provided domain model is the
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
RAM free: 16.884 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jan  2 05:35:26 2019
UTC timestamp: Wed Jan  2 02:35:26 2019
===============================================================================
Benchmark: SimpleBinaryEncoding-Deserialize
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: SimpleBinaryEncoding-Deserialize
Average time: 85 ns/op
Minimal time: 85 ns/op
Maximal time: 88 ns/op
Total time: 3.629 s
Total operations: 42653547
Total bytes: 5.493 GiB
Operations throughput: 11750351 ops/s
Bytes throughput: 1.522 GiB/s
Custom values:
        Size: 138
===============================================================================
```

# JSON serialization
JSON serialization is based on [RapidJSON library](http://rapidjson.org).

## JSON serialization methods
Finally you should extend your domain model with a JSON serialization
methods:

```c++
#include "serialization/json/serializer.h"
#include "serialization/json/deserializer.h"

namespace TradeProto {

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
        Orders.clear();
        Deserializer::FindArray(json, "orders", [this](const Value& item)
        {
            Order order;
            order.Deserialize(item);
            Orders.emplace_back(order);
        });
    }

    ...
};

} // namespace TradeProto
```

## JSON example
Here comes the usage example of JSON serialize/deserialize functionality:

```c++
#include "../proto/trade.h"

#include "serialization/json/parser.h"

#include <iostream>

int main(int argc, char** argv)
{
    // Create a new account with some orders
    TradeProto::Account account(1, "Test", "USD", 1000);
    account.Orders.emplace_back(TradeProto::Order(1, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::MARKET, 1.23456, 1000));
    account.Orders.emplace_back(TradeProto::Order(2, "EURUSD", TradeProto::OrderSide::SELL, TradeProto::OrderType::LIMIT, 1.0, 100));
    account.Orders.emplace_back(TradeProto::Order(3, "EURUSD", TradeProto::OrderSide::BUY, TradeProto::OrderType::STOP, 1.5, 10));

    // Serialize the account to the JSON stream
    CppSerialization::JSON::StringBuffer buffer;
    CppSerialization::JSON::Serializer<CppSerialization::JSON::StringBuffer> serializer(buffer);
    account.Serialize(serializer);

    // Show the serialized JSON content
    std::cout << "JSON content: " << buffer.GetString() << std::endl;
    // Show the serialized JSON size
    std::cout << "JSON size: " << buffer.GetSize() << std::endl;

    // Parse JSON string
    CppSerialization::JSON::Document json = CppSerialization::JSON::Parser::Parse(buffer.GetString());

    // Deserialize the account from the JSON stream
    TradeProto::Account deserialized;
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
JSON size: 301

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
RAM free: 20.683 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jul 18 13:28:06 2018
UTC timestamp: Wed Jul 18 10:28:06 2018
===============================================================================
Benchmark: JSON-Serialize
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: JSON-Serialize
Average time: 740 ns/op
Minimal time: 740 ns/op
Maximal time: 746 ns/op
Total time: 4.851 s
Total operations: 6552815
Total bytes: 1.857 GiB
Operations throughput: 1350543 ops/s
Bytes throughput: 387.697 MiB/s
Custom values:
        Size: 301
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
RAM free: 20.698 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jul 18 13:29:53 2018
UTC timestamp: Wed Jul 18 10:29:53 2018
===============================================================================
Benchmark: JSON-Parse
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: JSON-Parse
Average time: 2.063 mcs/op
Minimal time: 2.063 mcs/op
Maximal time: 2.090 mcs/op
Total time: 4.928 s
Total operations: 2388728
Total bytes: 685.715 MiB
Operations throughput: 484713 ops/s
Bytes throughput: 139.143 MiB/s
Custom values:
        Size: 301
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
RAM free: 20.706 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jul 18 13:30:43 2018
UTC timestamp: Wed Jul 18 10:30:43 2018
===============================================================================
Benchmark: JSON-Deserialize
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: JSON-Deserialize
Average time: 500 ns/op
Minimal time: 500 ns/op
Maximal time: 510 ns/op
Total time: 4.749 s
Total operations: 9487106
Total bytes: 36.195 MiB
Operations throughput: 1997556 ops/s
Bytes throughput: 7.634 MiB/s
Custom values:
        Size: 301
===============================================================================
```
