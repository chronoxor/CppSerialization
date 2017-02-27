/*!
    \file parser.inl
    \brief JSON parser inline implementation
    \author Ivan Shynkarenka
    \date 27.02.2017
    \copyright MIT License
*/

namespace CppSerialization {
namespace JSON {

template <typename InputStream>
inline Document Parser::ParseStream(InputStream& stream)
{
    Document result;
    return std::move(result.ParseStream(stream));
}

inline Document Parser::Parse(const char* str)
{
    Document result;
    return std::move(result.Parse(str));
}

inline Document Parser::Parse(const char* str, size_t size)
{
    Document result;
    return std::move(result.Parse(str, size));
}

inline Document Parser::Parse(const std::string& str)
{
    Document result;
    return std::move(result.Parse(str));
}

inline Document Parser::ParseInPlace(char* str)
{
    Document result;
    return std::move(result.ParseInsitu(str));
}

} // namespace JSON
} // namespace CppSerialization
