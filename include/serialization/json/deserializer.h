/*!
    \file deserializer.h
    \brief JSON deserializer definition
    \author Ivan Shynkarenka
    \date 27.02.2017
    \copyright MIT License
*/

#ifndef CPPSERIALIZATION_JSON_DESERIALIZER_H
#define CPPSERIALIZATION_JSON_DESERIALIZER_H

#include "json.h"

#include <algorithm>
#include <cassert>
#include <functional>

namespace CppSerialization {
namespace JSON {

//! JSON deserializer
/*!
    JSON deserializer is used to deserialize objects from the JSON document.
*/
class Deserializer
{
public:
    Deserializer() = delete;
    Deserializer(const Deserializer&) = delete;
    Deserializer(Deserializer&&) = delete;
    ~Deserializer() = delete;

    Deserializer& operator=(const Deserializer&) = delete;
    Deserializer& operator=(Deserializer&&) = delete;

    //! Try to get the boolean key/value pair
    template<typename JSON>
    static bool Find(const JSON& json, const char* key, bool& value);
    //! Try to get the integer key/value pair
    template<typename JSON>
    static bool Find(const JSON& json, const char* key, int& value);
    //! Try to get the unsigned key/value pair
    template<typename JSON>
    static bool Find(const JSON& json, const char* key, unsigned& value);
    //! Try to get the 64-bit integer key/value pair
    template<typename JSON>
    static bool Find(const JSON& json, const char* key, int64_t& value);
    //! Try to get the 64-bit unsigned key/value pair
    template<typename JSON>
    static bool Find(const JSON& json, const char* key, uint64_t& value);
    //! Try to get the double key/value pair
    template<typename JSON>
    static bool Find(const JSON& json, const char* key, double& value);
    //! Try to get the C-string key/value pair with a given size
    template<typename JSON>
    static bool Find(const JSON& json, const char* key, char* value, size_t size);
    //! Try to get the string key/value pair
    template<typename JSON>
    static bool Find(const JSON& json, const char* key, std::string& value);
    //! Try to get the fixed string array key/value pair
    template <typename JSON, std::size_t N>
    static bool Find(const JSON& json, const char* key, char (&value)[N]);

    //! Try to get the array key/value pair
    template<typename JSON>
    static bool FindArray(const JSON& json, const char* key, const std::function<void(const Value&)>& handler);
    //! Try to get the array key/value pair with array initialize handler
    template<typename JSON>
    static bool FindArray(const JSON& json, const char* key, const std::function<void(size_t)>& initialize, const std::function<void(const Value&)>& handler);

    //! Try to get the object key/value pair
    template<typename JSON>
    static bool FindObject(const JSON& json, const char* key, const std::function<void(const Value::ConstObject&)>& handler);
};

} // namespace JSON
} // namespace CppSerialization

#include "deserializer.inl"

#endif // CPPSERIALIZATION_JSON_DESERIALIZER_H
