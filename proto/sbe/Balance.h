/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _SBE_BALANCE_H_
#define _SBE_BALANCE_H_

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

class Balance
{
private:
    char *m_buffer;
    std::uint64_t m_bufferLength;
    std::uint64_t m_offset;
    std::uint64_t m_actingVersion;

    inline void reset(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        if (SBE_BOUNDS_CHECK_EXPECT(((offset + 18) > bufferLength), false))
        {
            throw std::runtime_error("buffer too short for flyweight [E107]");
        }

        m_buffer = buffer;
        m_bufferLength = bufferLength;
        m_offset = offset;
        m_actingVersion = actingVersion;
    }

public:
    Balance() : m_buffer(nullptr), m_offset(0) {}

    Balance(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingVersion);
    }

    Balance(const Balance& codec) :
        m_buffer(codec.m_buffer),
        m_bufferLength(codec.m_bufferLength),
        m_offset(codec.m_offset),
        m_actingVersion(codec.m_actingVersion){}

#if __cplusplus >= 201103L
    Balance(Balance&& codec) :
        m_buffer(codec.m_buffer),
        m_bufferLength(codec.m_bufferLength),
        m_offset(codec.m_offset),
        m_actingVersion(codec.m_actingVersion){}

    Balance& operator=(Balance&& codec) SBE_NOEXCEPT
    {
        m_buffer = codec.m_buffer;
        m_bufferLength = codec.m_bufferLength;
        m_offset = codec.m_offset;
        m_actingVersion = codec.m_actingVersion;
        return *this;
    }

#endif

    Balance& operator=(const Balance& codec) SBE_NOEXCEPT
    {
        m_buffer = codec.m_buffer;
        m_bufferLength = codec.m_bufferLength;
        m_offset = codec.m_offset;
        m_actingVersion = codec.m_actingVersion;
        return *this;
    }

    Balance &wrap(char *buffer, const std::uint64_t offset, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, actingVersion);
        return *this;
    }

    static SBE_CONSTEXPR std::uint64_t encodedLength() SBE_NOEXCEPT
    {
        return 18;
    }

    std::uint64_t offset() const SBE_NOEXCEPT
    {
        return m_offset;
    }

    const char * buffer() const SBE_NOEXCEPT
    {
        return m_buffer;
    }

    char * buffer() SBE_NOEXCEPT
    {
        return m_buffer;
    }

    std::uint64_t bufferLength() const SBE_NOEXCEPT
    {
        return m_bufferLength;
    }

    static SBE_CONSTEXPR std::uint16_t sbeSchemaId() SBE_NOEXCEPT
    {
        return (std::uint16_t)1;
    }

    static SBE_CONSTEXPR std::uint16_t sbeSchemaVersion() SBE_NOEXCEPT
    {
        return (std::uint16_t)1;
    }

    static const char * currencyMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case ::sbe::MetaAttribute::EPOCH: return "";
            case ::sbe::MetaAttribute::TIME_UNIT: return "";
            case ::sbe::MetaAttribute::SEMANTIC_TYPE: return "";
            case ::sbe::MetaAttribute::PRESENCE: return "required";
        }

        return "";
    }

    static SBE_CONSTEXPR std::uint16_t currencyId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t currencySinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool currencyInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= currencySinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t currencyEncodingOffset() SBE_NOEXCEPT
    {
         return 0;
    }

    static SBE_CONSTEXPR char currencyNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char currencyMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char currencyMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t currencyEncodingLength() SBE_NOEXCEPT
    {
        return 10;
    }

    static SBE_CONSTEXPR std::uint64_t currencyLength() SBE_NOEXCEPT
    {
        return 10;
    }

    const char *currency() const
    {
        return (m_buffer + m_offset + 0);
    }

    char currency(const std::uint64_t index) const
    {
        if (index >= 10)
        {
            throw std::runtime_error("index out of range for currency [E104]");
        }

        char val;
        std::memcpy(&val, m_buffer + m_offset + 0 + (index * 1), sizeof(char));
        return (val);
    }

    void currency(const std::uint64_t index, const char value)
    {
        if (index >= 10)
        {
            throw std::runtime_error("index out of range for currency [E105]");
        }

        char val = (value);
        std::memcpy(m_buffer + m_offset + 0 + (index * 1), &val, sizeof(char));
    }

    std::uint64_t getCurrency(char *dst, const std::uint64_t length) const
    {
        if (length > 10)
        {
             throw std::runtime_error("length too large for getCurrency [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 0, sizeof(char) * length);
        return length;
    }

    Balance &putCurrency(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 0, src, sizeof(char) * 10);
        return *this;
    }

    std::string getCurrencyAsString() const
    {
        std::string result(m_buffer + m_offset + 0, 10);
        return result;
    }

    Balance &putCurrency(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 0, str.c_str(), 10);
        return *this;
    }

    static const char * amountMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case ::sbe::MetaAttribute::EPOCH: return "";
            case ::sbe::MetaAttribute::TIME_UNIT: return "";
            case ::sbe::MetaAttribute::SEMANTIC_TYPE: return "";
            case ::sbe::MetaAttribute::PRESENCE: return "required";
        }

        return "";
    }

    static SBE_CONSTEXPR std::uint16_t amountId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t amountSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool amountInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= amountSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t amountEncodingOffset() SBE_NOEXCEPT
    {
         return 10;
    }

    static SBE_CONSTEXPR double amountNullValue() SBE_NOEXCEPT
    {
        return SBE_DOUBLE_NAN;
    }

    static SBE_CONSTEXPR double amountMinValue() SBE_NOEXCEPT
    {
        return 4.9E-324;
    }

    static SBE_CONSTEXPR double amountMaxValue() SBE_NOEXCEPT
    {
        return 1.7976931348623157E308;
    }

    static SBE_CONSTEXPR std::size_t amountEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    double amount() const
    {
        ::sbe::sbe_double_as_uint_t val;
        std::memcpy(&val, m_buffer + m_offset + 10, sizeof(double));
        val.uint_value = SBE_LITTLE_ENDIAN_ENCODE_64(val.uint_value);
        return val.fp_value;
    }

    Balance &amount(const double value)
    {
        ::sbe::sbe_double_as_uint_t val;
        val.fp_value = value;
        val.uint_value = SBE_LITTLE_ENDIAN_ENCODE_64(val.uint_value);
        std::memcpy(m_buffer + m_offset + 10, &val, sizeof(double));
        return *this;
    }
};
}
#endif
