/*!
    \file parser.h
    \brief JSON parser definition
    \author Ivan Shynkarenka
    \date 27.02.2017
    \copyright MIT License
*/

#ifndef CPPSERIALIZATION_JSON_PARSER_H
#define CPPSERIALIZATION_JSON_PARSER_H

#include "json.h"

namespace CppSerialization {
namespace JSON {

//! JSON parser
/*!
    JSON parser is used to parse JSON from the given source (stream, string)
    and create a corresponding DOM document.
*/
class Parser
{
public:
    Parser() = delete;
    Parser(const Parser&) = delete;
    Parser(Parser&&) = delete;
    ~Parser() = delete;

    Parser& operator=(const Parser&) = delete;
    Parser& operator=(Parser&&) = delete;

    //! Parse the input stream
    template <typename InputStream>
    static Document ParseStream(InputStream& stream);

    //! Parse the C-string
    static Document Parse(const char* source);
    //! Parse the C-string with a given size
    static Document Parse(const char* source, size_t size);
    //! Parse the string
    static Document Parse(const std::string& source);

    //! Parse the in-place C-string in mutable mode
    static Document ParseInPlace(char* source);
};

} // namespace JSON
} // namespace CppSerialization

#include "parser.inl"

#endif // CPPSERIALIZATION_JSON_PARSER_H
