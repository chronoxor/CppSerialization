/*!
    \file serializer.inl
    \brief JSON serializer inline implementation
    \author Ivan Shynkarenka
    \date 25.02.2017
    \copyright MIT License
*/

namespace CppSerialization {
namespace JSON {

template <class OutputStream>
inline void Serializer<OutputStream>::StartObject()
{
    if (!Writer<OutputStream>::StartObject())
        throwex SerializationException("Cannot start to serialize JSON object!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::EndObject()
{
    if (!Writer<OutputStream>::EndObject())
        throwex SerializationException("Cannot end to serialize JSON object!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::StartArray()
{
    if (!Writer<OutputStream>::StartArray())
        throwex SerializationException("Cannot start to serialize JSON array!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::EndArray()
{
    if (!Writer<OutputStream>::EndArray())
        throwex SerializationException("Cannot end to serialize JSON array!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Key(const char* key)
{
    if (!Writer<OutputStream>::Key(key))
        throwex SerializationException("Cannot serialize JSON key!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Key(const char* key, size_t size)
{
    if (!Writer<OutputStream>::Key(key, size))
        throwex SerializationException("Cannot serialize JSON key!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Key(const std::string& key)
{
    if (!Writer<OutputStream>::Key(key))
        throwex SerializationException("Cannot serialize JSON key!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Value(std::nullptr_t value)
{
    if (!Writer<OutputStream>::Null())
        throwex SerializationException("Cannot serialize JSON null value!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Value(bool value)
{
    if (!Writer<OutputStream>::Bool(value))
        throwex SerializationException("Cannot serialize JSON bool value!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Value(int value)
{
    if (!Writer<OutputStream>::Int(value))
        throwex SerializationException("Cannot serialize JSON integer value!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Value(unsigned value)
{
    if (!Writer<OutputStream>::UInt(value))
        throwex SerializationException("Cannot serialize JSON unsigned value!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Value(int64_t value)
{
    if (!Writer<OutputStream>::Int64(value))
        throwex SerializationException("Cannot serialize JSON 64-bit integer value!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Value(uint64_t value)
{
    if (!Writer<OutputStream>::UInt64(value))
        throwex SerializationException("Cannot serialize JSON 64-bit unsigned value!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Value(double value)
{
    if (!Writer<OutputStream>::Double(value))
        throwex SerializationException("Cannot serialize JSON double value!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Value(const char* value)
{
    if (!Writer<OutputStream>::String(value))
        throwex SerializationException("Cannot serialize JSON C-string value!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Value(const char* value, size_t size)
{
    if (!Writer<OutputStream>::String(value, size))
        throwex SerializationException("Cannot serialize JSON C-string value!");
}

template <class OutputStream>
inline void Serializer<OutputStream>::Value(const std::string& value)
{
    if (!Writer<OutputStream>::String(value))
        throwex SerializationException("Cannot serialize JSON string value!");
}

} // namespace JSON
} // namespace CppSerialization
