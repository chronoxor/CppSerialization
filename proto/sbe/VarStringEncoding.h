/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _SBE_VARSTRINGENCODING_H_
#define _SBE_VARSTRINGENCODING_H_

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

class VarStringEncoding
{
private:
    char *m_buffer;
    std::uint64_t m_bufferLength;
    std::uint64_t m_offset;
    std::uint64_t m_actingVersion;

    inline void reset(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        if (SBE_BOUNDS_CHECK_EXPECT(((offset + -1) > bufferLength), false))
        {
            throw std::runtime_error("buffer too short for flyweight [E107]");
        }

        m_buffer = buffer;
        m_bufferLength = bufferLength;
        m_offset = offset;
        m_actingVersion = actingVersion;
    }

public:
    VarStringEncoding() : m_buffer(nullptr), m_offset(0) {}

    VarStringEncoding(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingVersion);
    }

    VarStringEncoding(const VarStringEncoding& codec) :
        m_buffer(codec.m_buffer),
        m_bufferLength(codec.m_bufferLength),
        m_offset(codec.m_offset),
        m_actingVersion(codec.m_actingVersion){}

#if __cplusplus >= 201103L
    VarStringEncoding(VarStringEncoding&& codec) :
        m_buffer(codec.m_buffer),
        m_bufferLength(codec.m_bufferLength),
        m_offset(codec.m_offset),
        m_actingVersion(codec.m_actingVersion){}

    VarStringEncoding& operator=(VarStringEncoding&& codec) SBE_NOEXCEPT
    {
        m_buffer = codec.m_buffer;
        m_bufferLength = codec.m_bufferLength;
        m_offset = codec.m_offset;
        m_actingVersion = codec.m_actingVersion;
        return *this;
    }

#endif

    VarStringEncoding& operator=(const VarStringEncoding& codec) SBE_NOEXCEPT
    {
        m_buffer = codec.m_buffer;
        m_bufferLength = codec.m_bufferLength;
        m_offset = codec.m_offset;
        m_actingVersion = codec.m_actingVersion;
        return *this;
    }

    VarStringEncoding &wrap(char *buffer, const std::uint64_t offset, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, actingVersion);
        return *this;
    }

    static SBE_CONSTEXPR std::uint64_t encodedLength() SBE_NOEXCEPT
    {
        return -1;
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

    static const char * lengthMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t lengthId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t lengthSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool lengthInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= lengthSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t lengthEncodingOffset() SBE_NOEXCEPT
    {
         return 0;
    }

    static SBE_CONSTEXPR std::uint32_t lengthNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t lengthMinValue() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint32_t lengthMaxValue() SBE_NOEXCEPT
    {
        return 1073741824;
    }

    static SBE_CONSTEXPR std::size_t lengthEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t length() const
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset + 0, sizeof(std::uint32_t));
        return SBE_LITTLE_ENDIAN_ENCODE_32(val);
    }

    VarStringEncoding &length(const std::uint32_t value)
    {
        std::uint32_t val = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        std::memcpy(m_buffer + m_offset + 0, &val, sizeof(std::uint32_t));
        return *this;
    }

    static const char * varDataMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t varDataId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t varDataSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool varDataInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= varDataSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t varDataEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }

    static SBE_CONSTEXPR std::uint8_t varDataNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t varDataMinValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)0;
    }

    static SBE_CONSTEXPR std::uint8_t varDataMaxValue() SBE_NOEXCEPT
    {
        return (std::uint8_t)254;
    }

    static SBE_CONSTEXPR std::size_t varDataEncodingLength() SBE_NOEXCEPT
    {
        return -1;
    }
};
}
#endif
