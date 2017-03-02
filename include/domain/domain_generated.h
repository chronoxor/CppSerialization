// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_DOMAIN_MYDOMAIN_FLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_DOMAIN_MYDOMAIN_FLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"

namespace MyDomain {
namespace FlatBuffers {

struct Order;

struct Balance;

struct Account;

enum class OrderSide : int8_t {
  BUY = 0,
  SELL = 1,
  MIN = BUY,
  MAX = SELL
};

inline const char **EnumNamesOrderSide() {
  static const char *names[] = {
    "BUY",
    "SELL",
    nullptr
  };
  return names;
}

inline const char *EnumNameOrderSide(OrderSide e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesOrderSide()[index];
}

enum class OrderType : int8_t {
  MARKET = 0,
  LIMIT = 1,
  STOP = 2,
  MIN = MARKET,
  MAX = STOP
};

inline const char **EnumNamesOrderType() {
  static const char *names[] = {
    "MARKET",
    "LIMIT",
    "STOP",
    nullptr
  };
  return names;
}

inline const char *EnumNameOrderType(OrderType e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesOrderType()[index];
}

struct Order FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_ID = 4,
    VT_SYMBOL = 6,
    VT_SIDE = 8,
    VT_TYPE = 10,
    VT_PRICE = 12,
    VT_VOLUME = 14
  };
  int32_t Id() const {
    return GetField<int32_t>(VT_ID, 0);
  }
  const flatbuffers::String *Symbol() const {
    return GetPointer<const flatbuffers::String *>(VT_SYMBOL);
  }
  OrderSide Side() const {
    return static_cast<OrderSide>(GetField<int8_t>(VT_SIDE, 0));
  }
  OrderType Type() const {
    return static_cast<OrderType>(GetField<int8_t>(VT_TYPE, 0));
  }
  double Price() const {
    return GetField<double>(VT_PRICE, 0.0);
  }
  double Volume() const {
    return GetField<double>(VT_VOLUME, 0.0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_ID) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_SYMBOL) &&
           verifier.Verify(Symbol()) &&
           VerifyField<int8_t>(verifier, VT_SIDE) &&
           VerifyField<int8_t>(verifier, VT_TYPE) &&
           VerifyField<double>(verifier, VT_PRICE) &&
           VerifyField<double>(verifier, VT_VOLUME) &&
           verifier.EndTable();
  }
};

struct OrderBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_Id(int32_t Id) {
    fbb_.AddElement<int32_t>(Order::VT_ID, Id, 0);
  }
  void add_Symbol(flatbuffers::Offset<flatbuffers::String> Symbol) {
    fbb_.AddOffset(Order::VT_SYMBOL, Symbol);
  }
  void add_Side(OrderSide Side) {
    fbb_.AddElement<int8_t>(Order::VT_SIDE, static_cast<int8_t>(Side), 0);
  }
  void add_Type(OrderType Type) {
    fbb_.AddElement<int8_t>(Order::VT_TYPE, static_cast<int8_t>(Type), 0);
  }
  void add_Price(double Price) {
    fbb_.AddElement<double>(Order::VT_PRICE, Price, 0.0);
  }
  void add_Volume(double Volume) {
    fbb_.AddElement<double>(Order::VT_VOLUME, Volume, 0.0);
  }
  OrderBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  OrderBuilder &operator=(const OrderBuilder &);
  flatbuffers::Offset<Order> Finish() {
    const auto end = fbb_.EndTable(start_, 6);
    auto o = flatbuffers::Offset<Order>(end);
    return o;
  }
};

inline flatbuffers::Offset<Order> CreateOrder(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t Id = 0,
    flatbuffers::Offset<flatbuffers::String> Symbol = 0,
    OrderSide Side = OrderSide::BUY,
    OrderType Type = OrderType::MARKET,
    double Price = 0.0,
    double Volume = 0.0) {
  OrderBuilder builder_(_fbb);
  builder_.add_Volume(Volume);
  builder_.add_Price(Price);
  builder_.add_Symbol(Symbol);
  builder_.add_Id(Id);
  builder_.add_Type(Type);
  builder_.add_Side(Side);
  return builder_.Finish();
}

inline flatbuffers::Offset<Order> CreateOrderDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t Id = 0,
    const char *Symbol = nullptr,
    OrderSide Side = OrderSide::BUY,
    OrderType Type = OrderType::MARKET,
    double Price = 0.0,
    double Volume = 0.0) {
  return MyDomain::FlatBuffers::CreateOrder(
      _fbb,
      Id,
      Symbol ? _fbb.CreateString(Symbol) : 0,
      Side,
      Type,
      Price,
      Volume);
}

struct Balance FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CURRENCY = 4,
    VT_AMOUNT = 6
  };
  const flatbuffers::String *Currency() const {
    return GetPointer<const flatbuffers::String *>(VT_CURRENCY);
  }
  double Amount() const {
    return GetField<double>(VT_AMOUNT, 0.0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_CURRENCY) &&
           verifier.Verify(Currency()) &&
           VerifyField<double>(verifier, VT_AMOUNT) &&
           verifier.EndTable();
  }
};

struct BalanceBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_Currency(flatbuffers::Offset<flatbuffers::String> Currency) {
    fbb_.AddOffset(Balance::VT_CURRENCY, Currency);
  }
  void add_Amount(double Amount) {
    fbb_.AddElement<double>(Balance::VT_AMOUNT, Amount, 0.0);
  }
  BalanceBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  BalanceBuilder &operator=(const BalanceBuilder &);
  flatbuffers::Offset<Balance> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<Balance>(end);
    return o;
  }
};

inline flatbuffers::Offset<Balance> CreateBalance(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> Currency = 0,
    double Amount = 0.0) {
  BalanceBuilder builder_(_fbb);
  builder_.add_Amount(Amount);
  builder_.add_Currency(Currency);
  return builder_.Finish();
}

inline flatbuffers::Offset<Balance> CreateBalanceDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *Currency = nullptr,
    double Amount = 0.0) {
  return MyDomain::FlatBuffers::CreateBalance(
      _fbb,
      Currency ? _fbb.CreateString(Currency) : 0,
      Amount);
}

struct Account FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_ID = 4,
    VT_NAME = 6,
    VT_WALLET = 8,
    VT_ORDERS = 10
  };
  int32_t Id() const {
    return GetField<int32_t>(VT_ID, 0);
  }
  const flatbuffers::String *Name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  const Balance *Wallet() const {
    return GetPointer<const Balance *>(VT_WALLET);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Order>> *Orders() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Order>> *>(VT_ORDERS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_ID) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_NAME) &&
           verifier.Verify(Name()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_WALLET) &&
           verifier.VerifyTable(Wallet()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_ORDERS) &&
           verifier.Verify(Orders()) &&
           verifier.VerifyVectorOfTables(Orders()) &&
           verifier.EndTable();
  }
};

struct AccountBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_Id(int32_t Id) {
    fbb_.AddElement<int32_t>(Account::VT_ID, Id, 0);
  }
  void add_Name(flatbuffers::Offset<flatbuffers::String> Name) {
    fbb_.AddOffset(Account::VT_NAME, Name);
  }
  void add_Wallet(flatbuffers::Offset<Balance> Wallet) {
    fbb_.AddOffset(Account::VT_WALLET, Wallet);
  }
  void add_Orders(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Order>>> Orders) {
    fbb_.AddOffset(Account::VT_ORDERS, Orders);
  }
  AccountBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  AccountBuilder &operator=(const AccountBuilder &);
  flatbuffers::Offset<Account> Finish() {
    const auto end = fbb_.EndTable(start_, 4);
    auto o = flatbuffers::Offset<Account>(end);
    return o;
  }
};

inline flatbuffers::Offset<Account> CreateAccount(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t Id = 0,
    flatbuffers::Offset<flatbuffers::String> Name = 0,
    flatbuffers::Offset<Balance> Wallet = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Order>>> Orders = 0) {
  AccountBuilder builder_(_fbb);
  builder_.add_Orders(Orders);
  builder_.add_Wallet(Wallet);
  builder_.add_Name(Name);
  builder_.add_Id(Id);
  return builder_.Finish();
}

inline flatbuffers::Offset<Account> CreateAccountDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t Id = 0,
    const char *Name = nullptr,
    flatbuffers::Offset<Balance> Wallet = 0,
    const std::vector<flatbuffers::Offset<Order>> *Orders = nullptr) {
  return MyDomain::FlatBuffers::CreateAccount(
      _fbb,
      Id,
      Name ? _fbb.CreateString(Name) : 0,
      Wallet,
      Orders ? _fbb.CreateVector<flatbuffers::Offset<Order>>(*Orders) : 0);
}

inline const MyDomain::FlatBuffers::Account *GetAccount(const void *buf) {
  return flatbuffers::GetRoot<MyDomain::FlatBuffers::Account>(buf);
}

inline bool VerifyAccountBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<MyDomain::FlatBuffers::Account>(nullptr);
}

inline void FinishAccountBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<MyDomain::FlatBuffers::Account> root) {
  fbb.Finish(root);
}

}  // namespace FlatBuffers
}  // namespace MyDomain

#endif  // FLATBUFFERS_GENERATED_DOMAIN_MYDOMAIN_FLATBUFFERS_H_
