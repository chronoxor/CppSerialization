/*!
    \file serializer.h
    \brief JSON serializer definition
    \author Ivan Shynkarenka
    \date 25.02.2017
    \copyright MIT License
*/

#ifndef CPPSERIALIZATION_JSON_SERIALIZER_H
#define CPPSERIALIZATION_JSON_SERIALIZER_H

#include "json.h"

namespace CppSerialization {
namespace JSON {

//! JSON serializer
/*!
    JSON serializer is parametrized with an output stream and
    is used to serialize objects into JSON format.
*/
template <class OutputStream>
class Serializer : public Writer<OutputStream>
{
public:
    Serializer() = default;
    explicit Serializer(OutputStream& stream) : Writer<OutputStream>(stream) {}
    Serializer(const Serializer&) = delete;
    Serializer(Serializer&&) noexcept = default;
    ~Serializer() = default;

    Serializer& operator=(const Serializer&) = delete;
    Serializer& operator=(Serializer&&) noexcept = default;

    //! Start new object
    void StartObject();
    //! End the current object
    void EndObject();

    //! Start new array
    void StartArray();
    //! End the current array
    void EndArray();

    //! Put the C-string key
    void Key(const char* key);
    //! Put the C-string key with a given size
    void Key(const char* key, size_t size);
    //! Put the string key
    void Key(const std::string& key);
    //! Put the fixed string array key
    template <std::size_t N>
    void Key(const char (&key)[N]);

    //! Put the null value
    void Value(std::nullptr_t value);
    //! Put the boolean value
    void Value(bool value);
    //! Put the integer value
    void Value(int value);
    //! Put the unsigned integer value
    void Value(unsigned value);
    //! Put the 64-bit integer value
    void Value(int64_t value);
    //! Put the 64-bit unsigned integer value
    void Value(uint64_t value);
    //! Put the double value
    void Value(double value);
    //! Put the C-string value
    void Value(const char* value);
    //! Put the C-string value with a given size
    void Value(const char* value, size_t size);
    //! Put the string value
    void Value(const std::string& value);
    //! Put the fixed string array value
    template <std::size_t N>
    void Value(const char (&value)[N]);

    //! Put the null key/value pair
    void Pair(const char* key, std::nullptr_t value)
    { Key(key); Value(value); }
    //! Put the boolean key/value pair
    void Pair(const char* key, bool value)
    { Key(key); Value(value); }
    //! Put the integer key/value pair
    void Pair(const char* key, int value)
    { Key(key); Value(value); }
    //! Put the unsigned integer key/value pair
    void Pair(const char* key, unsigned value)
    { Key(key); Value(value); }
    //! Put the 64-bit integer key/value pair
    void Pair(const char* key, int64_t value)
    { Key(key); Value(value); }
    //! Put the 64-bit unsigned integer key/value pair
    void Pair(const char* key, uint64_t value)
    { Key(key); Value(value); }
    //! Put the double key/value pair
    void Pair(const char* key, double value)
    { Key(key); Value(value); }
    //! Put the C-string key/value pair
    void Pair(const char* key, const char* value)
    { Key(key); Value(value); }
    //! Put the C-string key/value pair with a given size
    void Pair(const char* key, const char* value, size_t size)
    { Key(key); Value(value, size); }
    //! Put the string key/value pair
    void Pair(const char* key, const std::string& value)
    { Key(key); Value(value); }
    //! Put the fixed string array key/value pair
    template <std::size_t N>
    void Pair(const char* key, const char (&value)[N])
    { Key(key); Value(value); }
};

} // namespace JSON
} // namespace CppSerialization

#include "serializer.inl"

#endif // CPPSERIALIZATION_JSON_SERIALIZER_H
