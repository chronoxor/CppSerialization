/*!
    \file deserializer.inl
    \brief JSON deserializer inline implementation
    \author Ivan Shynkarenka
    \date 27.02.2017
    \copyright MIT License
*/

namespace CppSerialization {
namespace JSON {

template<typename JSON>
inline bool Deserializer::Find(const JSON& json, const char* key, bool& value)
{
    // Try to find a member with the given key
    Value::ConstMemberIterator member = json.FindMember(key);
    if ((member == json.MemberEnd()) || member->value.IsNull())
        return false;

    // Schema validation
    if (!member->value.IsBool())
        throwex SerializationException("Cannot deserialize JSON bool value!");

    // Save the member value
    value = member->value.GetBool();
    return true;
}

template<typename JSON>
inline bool Deserializer::Find(const JSON& json, const char* key, int& value)
{
    // Try to find a member with the given key
    Value::ConstMemberIterator member = json.FindMember(key);
    if ((member == json.MemberEnd()) || member->value.IsNull())
        return false;

    // Schema validation
    if (!member->value.IsInt())
        throwex SerializationException("Cannot deserialize JSON integer value!");

    // Save the member value
    value = member->value.GetInt();
    return true;
}

template<typename JSON>
inline bool Deserializer::Find(const JSON& json, const char* key, unsigned& value)
{
    // Try to find a member with the given key
    Value::ConstMemberIterator member = json.FindMember(key);
    if ((member == json.MemberEnd()) || member->value.IsNull())
        return false;

    // Schema validation
    if (!member->value.IsUint())
        throwex SerializationException("Cannot deserialize JSON unsigned value!");

    // Save the member value
    value = member->value.GetUint();
    return true;
}

template<typename JSON>
inline bool Deserializer::Find(const JSON& json, const char* key, int64_t& value)
{
    // Try to find a member with the given key
    Value::ConstMemberIterator member = json.FindMember(key);
    if ((member == json.MemberEnd()) || member->value.IsNull())
        return false;

    // Schema validation
    if (!member->value.IsInt64())
        throwex SerializationException("Cannot deserialize JSON 64-bit integer value!");

    // Save the member value
    value = member->value.GetInt64();
    return true;
}

template<typename JSON>
inline bool Deserializer::Find(const JSON& json, const char* key, uint64_t& value)
{
    // Try to find a member with the given key
    Value::ConstMemberIterator member = json.FindMember(key);
    if ((member == json.MemberEnd()) || member->value.IsNull())
        return false;

    // Schema validation
    if (!member->value.IsUint64())
        throwex SerializationException("Cannot deserialize JSON 64-bit unsigned value!");

    // Save the member value
    value = member->value.GetUint64();
    return true;
}

template<typename JSON>
inline bool Deserializer::Find(const JSON& json, const char* key, double& value)
{
    // Try to find a member with the given key
    Value::ConstMemberIterator member = json.FindMember(key);
    if ((member == json.MemberEnd()) || member->value.IsNull())
        return false;

    // Schema validation
    if (!member->value.IsDouble())
        throwex SerializationException("Cannot deserialize JSON double value!");

    // Save the member value
    value = member->value.GetDouble();
    return true;
}

template<typename JSON>
inline bool Deserializer::Find(const JSON& json, const char* key, char* value, size_t size)
{
    // Try to find a member with the given key
    Value::ConstMemberIterator member = json.FindMember(key);
    if ((member == json.MemberEnd()) || member->value.IsNull())
        return false;

    // Schema validation
    if (!member->value.IsString())
        throwex SerializationException("Cannot deserialize JSON C-string value with a given size!");

    // Save the member value
    size_t length = std::min((size_t)member->value.GetStringLength(), size);
    std::memcpy(value, member->value.GetString(), length);
    // Write the end of string character if possible
    if (length < size)
        value[length] = '\0';
    return true;
}

template<typename JSON>
inline bool Deserializer::Find(const JSON& json, const char* key, std::string& value)
{
    // Try to find a member with the given key
    Value::ConstMemberIterator member = json.FindMember(key);
    if ((member == json.MemberEnd()) || member->value.IsNull())
        return false;

    // Schema validation
    if (!member->value.IsString())
        throwex SerializationException("Cannot deserialize JSON string value!");

    // Save the member value
    value.assign(member->value.GetString(), (size_t)member->value.GetStringLength());
    return true;
}

template <typename JSON, std::size_t N>
inline bool Deserializer::Find(const JSON& json, const char* key, char (&value)[N])
{
    // Try to find a member with the given key
    Value::ConstMemberIterator member = json.FindMember(key);
    if ((member == json.MemberEnd()) || member->value.IsNull())
        return false;

    // Schema validation
    if (!member->value.IsString())
        throwex SerializationException("Cannot deserialize JSON string array value!");

    // Save the member value
    size_t length = std::min((size_t)member->value.GetStringLength(), N);
    std::memcpy(value, member->value.GetString(), length);
    // Write the end of string character if possible
    if (length < N)
        value[length] = '\0';
    return true;
}

template<typename JSON>
inline bool Deserializer::FindArray(const JSON& json, const char* key, const std::function<void(const Value&)>& handler)
{
    return FindArray(json, key, [](size_t){}, handler);
}


template<typename JSON>
inline bool Deserializer::FindArray(const JSON& json, const char* key, const std::function<void(size_t)>& initialize, const std::function<void(const Value&)>& handler)
{
    // Try to find a member with the given key
    Value::ConstMemberIterator member = json.FindMember(key);
    if ((member == json.MemberEnd()) || member->value.IsNull())
        return false;

    // Schema validation
    if (!member->value.IsArray())
        throwex SerializationException("Cannot deserialize JSON array!");

    // Handle array items
    initialize(member->value.GetArray().Size());
    for (auto& item : member->value.GetArray())
        handler(item);
    return true;
}

template<typename JSON>
inline bool Deserializer::FindObject(const JSON& json, const char* key, const std::function<void(const Value::ConstObject&)>& handler)
{
    // Try to find a member with the given key
    Value::ConstMemberIterator member = json.FindMember(key);
    if ((member == json.MemberEnd()) || member->value.IsNull())
        return false;

    // Schema validation
    if (!member->value.IsObject())
        throwex SerializationException("Cannot deserialize JSON object!");

    // Handle object
    handler(member->value.GetObject());
    return true;
}

} // namespace JSON
} // namespace CppSerialization
