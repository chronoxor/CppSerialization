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

} // namespace JSON
} // namespace CppSerialization
