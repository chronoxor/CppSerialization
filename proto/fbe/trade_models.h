// Automatically generated by the Fast Binary Encoding compiler, do not modify!
// https://github.com/chronoxor/FastBinaryEncoding
// Source: trade.fbe
// Version: 1.6.0.0

#pragma once

#if defined(__clang__)
#pragma clang system_header
#elif defined(__GNUC__)
#pragma GCC system_header
#elif defined(_MSC_VER)
#pragma system_header
#endif

#include "fbe_models.h"

#include "trade.h"

namespace FBE {

// Fast Binary Encoding ::trade::OrderSide field model
template <>
class FieldModel<::trade::OrderSide> : public FieldModelBase<::trade::OrderSide, uint8_t>
{
public:
    using FieldModelBase<::trade::OrderSide, uint8_t>::FieldModelBase;
};

// Fast Binary Encoding ::trade::OrderType field model
template <>
class FieldModel<::trade::OrderType> : public FieldModelBase<::trade::OrderType, uint8_t>
{
public:
    using FieldModelBase<::trade::OrderType, uint8_t>::FieldModelBase;
};

// Fast Binary Encoding ::trade::Order field model
template <>
class FieldModel<::trade::Order>
{
public:
    FieldModel(FBEBuffer& buffer, size_t offset) noexcept;

    // Get the field offset
    size_t fbe_offset() const noexcept { return _offset; }
    // Get the field size
    size_t fbe_size() const noexcept { return 4; }
    // Get the field body size
    size_t fbe_body() const noexcept;
    // Get the field extra size
    size_t fbe_extra() const noexcept;
    // Get the field type
    static constexpr size_t fbe_type() noexcept { return 1; }

    // Shift the current field offset
    void fbe_shift(size_t size) noexcept { _offset += size; }
    // Unshift the current field offset
    void fbe_unshift(size_t size) noexcept { _offset -= size; }

    // Check if the struct value is valid
    bool verify(bool fbe_verify_type = true) const noexcept;
    // Check if the struct fields are valid
    bool verify_fields(size_t fbe_struct_size) const noexcept;

    // Get the struct value (begin phase)
    size_t get_begin() const noexcept;
    // Get the struct value (end phase)
    void get_end(size_t fbe_begin) const noexcept;

    // Get the struct value
    void get(::trade::Order& fbe_value) const noexcept;
    // Get the struct fields values
    void get_fields(::trade::Order& fbe_value, size_t fbe_struct_size) const noexcept;

    // Set the struct value (begin phase)
    size_t set_begin();
    // Set the struct value (end phase)
    void set_end(size_t fbe_begin);

    // Set the struct value
    void set(const ::trade::Order& fbe_value) noexcept;
    // Set the struct fields values
    void set_fields(const ::trade::Order& fbe_value) noexcept;

private:
    FBEBuffer& _buffer;
    size_t _offset;

public:
    FieldModel<int32_t> id;
    FieldModel<std::string> symbol;
    FieldModel<::trade::OrderSide> side;
    FieldModel<::trade::OrderType> type;
    FieldModel<double> price;
    FieldModel<double> volume;
};

namespace trade {

// Fast Binary Encoding Order model
class OrderModel : public FBE::Model
{
public:
    OrderModel() : model(this->buffer(), 4) {}
    OrderModel(const std::shared_ptr<FBEBuffer>& buffer) : FBE::Model(buffer), model(this->buffer(), 4) {}

    // Get the model size
    size_t fbe_size() const noexcept { return model.fbe_size() + model.fbe_extra(); }
    // Get the model type
    static constexpr size_t fbe_type() noexcept { return FieldModel<::trade::Order>::fbe_type(); }

    // Check if the struct value is valid
    bool verify();

    // Create a new model (begin phase)
    size_t create_begin();
    // Create a new model (end phase)
    size_t create_end(size_t fbe_begin);

    // Serialize the struct value
    size_t serialize(const ::trade::Order& value);
    // Deserialize the struct value
    size_t deserialize(::trade::Order& value) const noexcept;

    // Move to the next struct value
    void next(size_t prev) noexcept { model.fbe_shift(prev); }

public:
    FieldModel<::trade::Order> model;
};

} // namespace trade

// Fast Binary Encoding ::trade::Balance field model
template <>
class FieldModel<::trade::Balance>
{
public:
    FieldModel(FBEBuffer& buffer, size_t offset) noexcept;

    // Get the field offset
    size_t fbe_offset() const noexcept { return _offset; }
    // Get the field size
    size_t fbe_size() const noexcept { return 4; }
    // Get the field body size
    size_t fbe_body() const noexcept;
    // Get the field extra size
    size_t fbe_extra() const noexcept;
    // Get the field type
    static constexpr size_t fbe_type() noexcept { return 2; }

    // Shift the current field offset
    void fbe_shift(size_t size) noexcept { _offset += size; }
    // Unshift the current field offset
    void fbe_unshift(size_t size) noexcept { _offset -= size; }

    // Check if the struct value is valid
    bool verify(bool fbe_verify_type = true) const noexcept;
    // Check if the struct fields are valid
    bool verify_fields(size_t fbe_struct_size) const noexcept;

    // Get the struct value (begin phase)
    size_t get_begin() const noexcept;
    // Get the struct value (end phase)
    void get_end(size_t fbe_begin) const noexcept;

    // Get the struct value
    void get(::trade::Balance& fbe_value) const noexcept;
    // Get the struct fields values
    void get_fields(::trade::Balance& fbe_value, size_t fbe_struct_size) const noexcept;

    // Set the struct value (begin phase)
    size_t set_begin();
    // Set the struct value (end phase)
    void set_end(size_t fbe_begin);

    // Set the struct value
    void set(const ::trade::Balance& fbe_value) noexcept;
    // Set the struct fields values
    void set_fields(const ::trade::Balance& fbe_value) noexcept;

private:
    FBEBuffer& _buffer;
    size_t _offset;

public:
    FieldModel<std::string> currency;
    FieldModel<double> amount;
};

namespace trade {

// Fast Binary Encoding Balance model
class BalanceModel : public FBE::Model
{
public:
    BalanceModel() : model(this->buffer(), 4) {}
    BalanceModel(const std::shared_ptr<FBEBuffer>& buffer) : FBE::Model(buffer), model(this->buffer(), 4) {}

    // Get the model size
    size_t fbe_size() const noexcept { return model.fbe_size() + model.fbe_extra(); }
    // Get the model type
    static constexpr size_t fbe_type() noexcept { return FieldModel<::trade::Balance>::fbe_type(); }

    // Check if the struct value is valid
    bool verify();

    // Create a new model (begin phase)
    size_t create_begin();
    // Create a new model (end phase)
    size_t create_end(size_t fbe_begin);

    // Serialize the struct value
    size_t serialize(const ::trade::Balance& value);
    // Deserialize the struct value
    size_t deserialize(::trade::Balance& value) const noexcept;

    // Move to the next struct value
    void next(size_t prev) noexcept { model.fbe_shift(prev); }

public:
    FieldModel<::trade::Balance> model;
};

} // namespace trade

// Fast Binary Encoding ::trade::Account field model
template <>
class FieldModel<::trade::Account>
{
public:
    FieldModel(FBEBuffer& buffer, size_t offset) noexcept;

    // Get the field offset
    size_t fbe_offset() const noexcept { return _offset; }
    // Get the field size
    size_t fbe_size() const noexcept { return 4; }
    // Get the field body size
    size_t fbe_body() const noexcept;
    // Get the field extra size
    size_t fbe_extra() const noexcept;
    // Get the field type
    static constexpr size_t fbe_type() noexcept { return 3; }

    // Shift the current field offset
    void fbe_shift(size_t size) noexcept { _offset += size; }
    // Unshift the current field offset
    void fbe_unshift(size_t size) noexcept { _offset -= size; }

    // Check if the struct value is valid
    bool verify(bool fbe_verify_type = true) const noexcept;
    // Check if the struct fields are valid
    bool verify_fields(size_t fbe_struct_size) const noexcept;

    // Get the struct value (begin phase)
    size_t get_begin() const noexcept;
    // Get the struct value (end phase)
    void get_end(size_t fbe_begin) const noexcept;

    // Get the struct value
    void get(::trade::Account& fbe_value) const noexcept;
    // Get the struct fields values
    void get_fields(::trade::Account& fbe_value, size_t fbe_struct_size) const noexcept;

    // Set the struct value (begin phase)
    size_t set_begin();
    // Set the struct value (end phase)
    void set_end(size_t fbe_begin);

    // Set the struct value
    void set(const ::trade::Account& fbe_value) noexcept;
    // Set the struct fields values
    void set_fields(const ::trade::Account& fbe_value) noexcept;

private:
    FBEBuffer& _buffer;
    size_t _offset;

public:
    FieldModel<int32_t> id;
    FieldModel<std::string> name;
    FieldModel<::trade::Balance> wallet;
    FieldModelVector<::trade::Order> orders;
};

namespace trade {

// Fast Binary Encoding Account model
class AccountModel : public FBE::Model
{
public:
    AccountModel() : model(this->buffer(), 4) {}
    AccountModel(const std::shared_ptr<FBEBuffer>& buffer) : FBE::Model(buffer), model(this->buffer(), 4) {}

    // Get the model size
    size_t fbe_size() const noexcept { return model.fbe_size() + model.fbe_extra(); }
    // Get the model type
    static constexpr size_t fbe_type() noexcept { return FieldModel<::trade::Account>::fbe_type(); }

    // Check if the struct value is valid
    bool verify();

    // Create a new model (begin phase)
    size_t create_begin();
    // Create a new model (end phase)
    size_t create_end(size_t fbe_begin);

    // Serialize the struct value
    size_t serialize(const ::trade::Account& value);
    // Deserialize the struct value
    size_t deserialize(::trade::Account& value) const noexcept;

    // Move to the next struct value
    void next(size_t prev) noexcept { model.fbe_shift(prev); }

public:
    FieldModel<::trade::Account> model;
};

} // namespace trade

} // namespace FBE
