/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _SBE_ORDER_H_
#define _SBE_ORDER_H_

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

#include "OrderSide.h"
#include "OrderType.h"

namespace sbe {

class Order
{
private:
    char *m_buffer;
    std::uint64_t m_bufferLength;
    std::uint64_t m_offset;
    std::uint64_t m_actingVersion;

    inline void reset(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        if (SBE_BOUNDS_CHECK_EXPECT(((offset + 32) > bufferLength), false))
        {
            throw std::runtime_error("buffer too short for flyweight [E107]");
        }

        m_buffer = buffer;
        m_bufferLength = bufferLength;
        m_offset = offset;
        m_actingVersion = actingVersion;
    }

public:
    Order() : m_buffer(nullptr), m_offset(0) {}

    Order(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingVersion);
    }

    Order(const Order& codec) :
        m_buffer(codec.m_buffer),
        m_bufferLength(codec.m_bufferLength),
        m_offset(codec.m_offset),
        m_actingVersion(codec.m_actingVersion){}

#if __cplusplus >= 201103L
    Order(Order&& codec) :
        m_buffer(codec.m_buffer),
        m_bufferLength(codec.m_bufferLength),
        m_offset(codec.m_offset),
        m_actingVersion(codec.m_actingVersion){}

    Order& operator=(Order&& codec) SBE_NOEXCEPT
    {
        m_buffer = codec.m_buffer;
        m_bufferLength = codec.m_bufferLength;
        m_offset = codec.m_offset;
        m_actingVersion = codec.m_actingVersion;
        return *this;
    }

#endif

    Order& operator=(const Order& codec) SBE_NOEXCEPT
    {
        m_buffer = codec.m_buffer;
        m_bufferLength = codec.m_bufferLength;
        m_offset = codec.m_offset;
        m_actingVersion = codec.m_actingVersion;
        return *this;
    }

    Order &wrap(char *buffer, const std::uint64_t offset, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, actingVersion);
        return *this;
    }

    static SBE_CONSTEXPR std::uint64_t encodedLength() SBE_NOEXCEPT
    {
        return 32;
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

    static const char * idMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t idId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t idSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool idInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= idSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t idEncodingOffset() SBE_NOEXCEPT
    {
         return 0;
    }

    static SBE_CONSTEXPR std::int32_t idNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_INT32;
    }

    static SBE_CONSTEXPR std::int32_t idMinValue() SBE_NOEXCEPT
    {
        return -2147483647;
    }

    static SBE_CONSTEXPR std::int32_t idMaxValue() SBE_NOEXCEPT
    {
        return 2147483647;
    }

    static SBE_CONSTEXPR std::size_t idEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::int32_t id() const
    {
        std::int32_t val;
        std::memcpy(&val, m_buffer + m_offset + 0, sizeof(std::int32_t));
        return SBE_LITTLE_ENDIAN_ENCODE_32(val);
    }

    Order &id(const std::int32_t value)
    {
        std::int32_t val = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        std::memcpy(m_buffer + m_offset + 0, &val, sizeof(std::int32_t));
        return *this;
    }

    static const char * symbolMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t symbolId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t symbolSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool symbolInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= symbolSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t symbolEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }

    static SBE_CONSTEXPR char symbolNullValue() SBE_NOEXCEPT
    {
        return (char)0;
    }

    static SBE_CONSTEXPR char symbolMinValue() SBE_NOEXCEPT
    {
        return (char)32;
    }

    static SBE_CONSTEXPR char symbolMaxValue() SBE_NOEXCEPT
    {
        return (char)126;
    }

    static SBE_CONSTEXPR std::size_t symbolEncodingLength() SBE_NOEXCEPT
    {
        return 10;
    }

    static SBE_CONSTEXPR std::uint64_t symbolLength() SBE_NOEXCEPT
    {
        return 10;
    }

    const char *symbol() const
    {
        return (m_buffer + m_offset + 4);
    }

    char symbol(const std::uint64_t index) const
    {
        if (index >= 10)
        {
            throw std::runtime_error("index out of range for symbol [E104]");
        }

        char val;
        std::memcpy(&val, m_buffer + m_offset + 4 + (index * 1), sizeof(char));
        return (val);
    }

    void symbol(const std::uint64_t index, const char value)
    {
        if (index >= 10)
        {
            throw std::runtime_error("index out of range for symbol [E105]");
        }

        char val = (value);
        std::memcpy(m_buffer + m_offset + 4 + (index * 1), &val, sizeof(char));
    }

    std::uint64_t getSymbol(char *dst, const std::uint64_t length) const
    {
        if (length > 10)
        {
             throw std::runtime_error("length too large for getSymbol [E106]");
        }

        std::memcpy(dst, m_buffer + m_offset + 4, sizeof(char) * length);
        return length;
    }

    Order &putSymbol(const char *src)
    {
        std::memcpy(m_buffer + m_offset + 4, src, sizeof(char) * 10);
        return *this;
    }

    std::string getSymbolAsString() const
    {
        std::string result(m_buffer + m_offset + 4, 10);
        return result;
    }

    Order &putSymbol(const std::string& str)
    {
        std::memcpy(m_buffer + m_offset + 4, str.c_str(), 10);
        return *this;
    }

    static const char * sideMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t sideId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t sideSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool sideInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= sideSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t sideEncodingOffset() SBE_NOEXCEPT
    {
         return 14;
    }

    static SBE_CONSTEXPR std::size_t sideEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    OrderSide::Value side() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset + 14, sizeof(std::uint8_t));
        return OrderSide::get((val));
    }

    Order &side(const OrderSide::Value value)
    {
        std::uint8_t val = (value);
        std::memcpy(m_buffer + m_offset + 14, &val, sizeof(std::uint8_t));
        return *this;
    }

    static const char * typeMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t typeId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t typeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool typeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= typeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t typeEncodingOffset() SBE_NOEXCEPT
    {
         return 15;
    }

    static SBE_CONSTEXPR std::size_t typeEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    OrderType::Value type() const
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset + 15, sizeof(std::uint8_t));
        return OrderType::get((val));
    }

    Order &type(const OrderType::Value value)
    {
        std::uint8_t val = (value);
        std::memcpy(m_buffer + m_offset + 15, &val, sizeof(std::uint8_t));
        return *this;
    }

    static const char * priceMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t priceId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t priceSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool priceInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= priceSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t priceEncodingOffset() SBE_NOEXCEPT
    {
         return 16;
    }

    static SBE_CONSTEXPR double priceNullValue() SBE_NOEXCEPT
    {
        return SBE_DOUBLE_NAN;
    }

    static SBE_CONSTEXPR double priceMinValue() SBE_NOEXCEPT
    {
        return 4.9E-324;
    }

    static SBE_CONSTEXPR double priceMaxValue() SBE_NOEXCEPT
    {
        return 1.7976931348623157E308;
    }

    static SBE_CONSTEXPR std::size_t priceEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    double price() const
    {
        ::sbe::sbe_double_as_uint_t val;
        std::memcpy(&val, m_buffer + m_offset + 16, sizeof(double));
        val.uint_value = SBE_LITTLE_ENDIAN_ENCODE_64(val.uint_value);
        return val.fp_value;
    }

    Order &price(const double value)
    {
        ::sbe::sbe_double_as_uint_t val;
        val.fp_value = value;
        val.uint_value = SBE_LITTLE_ENDIAN_ENCODE_64(val.uint_value);
        std::memcpy(m_buffer + m_offset + 16, &val, sizeof(double));
        return *this;
    }

    static const char * volumeMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t volumeId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t volumeSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool volumeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= volumeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t volumeEncodingOffset() SBE_NOEXCEPT
    {
         return 24;
    }

    static SBE_CONSTEXPR double volumeNullValue() SBE_NOEXCEPT
    {
        return SBE_DOUBLE_NAN;
    }

    static SBE_CONSTEXPR double volumeMinValue() SBE_NOEXCEPT
    {
        return 4.9E-324;
    }

    static SBE_CONSTEXPR double volumeMaxValue() SBE_NOEXCEPT
    {
        return 1.7976931348623157E308;
    }

    static SBE_CONSTEXPR std::size_t volumeEncodingLength() SBE_NOEXCEPT
    {
        return 8;
    }

    double volume() const
    {
        ::sbe::sbe_double_as_uint_t val;
        std::memcpy(&val, m_buffer + m_offset + 24, sizeof(double));
        val.uint_value = SBE_LITTLE_ENDIAN_ENCODE_64(val.uint_value);
        return val.fp_value;
    }

    Order &volume(const double value)
    {
        ::sbe::sbe_double_as_uint_t val;
        val.fp_value = value;
        val.uint_value = SBE_LITTLE_ENDIAN_ENCODE_64(val.uint_value);
        std::memcpy(m_buffer + m_offset + 24, &val, sizeof(double));
        return *this;
    }
};
}
#endif
