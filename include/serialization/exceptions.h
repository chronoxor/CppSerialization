/*!
    \file serialization/exceptions.h
    \brief Serialization exceptions definition
    \author Ivan Shynkarenka
    \date 25.02.2017
    \copyright MIT License
*/

#ifndef CPPSERIALIZATION_EXCEPTIONS_H
#define CPPSERIALIZATION_EXCEPTIONS_H

#include "errors/exceptions.h"

namespace CppSerialization {

//! Serialization exception
class SerializationException : public CppCommon::Exception
{
public:
    using Exception::Exception;
};

} // namespace CppSerialization

#endif // CPPSERIALIZATION_EXCEPTIONS_H
