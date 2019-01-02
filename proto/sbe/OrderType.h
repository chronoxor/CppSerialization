/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _SBE_ORDERTYPE_H_
#define _SBE_ORDERTYPE_H_

#if defined(SBE_HAVE_CMATH)
/* cmath needed for std::numeric_limits<double>::quiet_NaN() */
#  include <cmath>
#  define SBE_FLOAT_NAN std::numeric_limits<float>::quiet_NaN()
#  define SBE_DOUBLE_NAN std::numeric_limits<double>::quiet_NaN()
#else
/* math.h needed for NAN */
#  include <math.h>
#  define SBE_FLOAT_NAN NAN
#  define SBE_DOUBLE_NAN NAN
#endif

#if __cplusplus >= 201103L
#  include <cstdint>
#  include <string>
#  include <cstring>
#endif

#if __cplusplus >= 201103L
#  define SBE_CONSTEXPR constexpr
#  define SBE_NOEXCEPT noexcept
#else
#  define SBE_CONSTEXPR
#  define SBE_NOEXCEPT
#endif

#include <sbe/sbe.h>

namespace sbe {

class OrderType
{
public:

    enum Value 
    {
        market = (std::uint8_t)0,
        limit = (std::uint8_t)1,
        stop = (std::uint8_t)2,
        NULL_VALUE = (std::uint8_t)255
    };

    static OrderType::Value get(const std::uint8_t value)
    {
        switch (value)
        {
            case 0: return market;
            case 1: return limit;
            case 2: return stop;
            case 255: return NULL_VALUE;
        }

        throw std::runtime_error("unknown value for enum OrderType [E103]");
    }
};
}
#endif
