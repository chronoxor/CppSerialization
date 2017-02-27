/*!
    \file parser.cpp
    \brief JSON parser implementation
    \author Ivan Shynkarenka
    \date 27.02.2017
    \copyright MIT License
*/

#include "serialization/json/parser.h"

namespace CppSerialization {
namespace JSON {

Document Parser::Parse(const char* str)
{
    Document result;
    return std::move(result.Parse(str));
}

Document Parser::Parse(const char* str, size_t size)
{
    Document result;
    return std::move(result.Parse(str, size));
}

Document Parser::Parse(const std::string& str)
{
    Document result;
    return std::move(result.Parse(str));
}

Document Parser::ParseInPlace(char* str)
{
    Document result;
    return std::move(result.ParseInsitu(str));
}

} // namespace JSON
} // namespace CppSerialization
