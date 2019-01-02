/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _SBE_MESSAGEHEADER_H_
#define _SBE_MESSAGEHEADER_H_

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

class MessageHeader
{
private:
    char *m_buffer;
    std::uint64_t m_bufferLength;
    std::uint64_t m_offset;
    std::uint64_t m_actingVersion;

    inline void reset(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        if (SBE_BOUNDS_CHECK_EXPECT(((offset + 8) > bufferLength), false))
        {
            throw std::runtime_error("buffer too short for flyweight [E107]");
        }

        m_buffer = buffer;
        m_bufferLength = bufferLength;
        m_offset = offset;
        m_actingVersion = actingVersion;
    }

public:
    MessageHeader() : m_buffer(nullptr), m_offset(0) {}

    MessageHeader(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingVersion);
    }

    MessageHeader(const MessageHeader& codec) :
        m_buffer(codec.m_buffer),
        m_bufferLength(codec.m_bufferLength),
        m_offset(codec.m_offset),
        m_actingVersion(codec.m_actingVersion){}

#if __cplusplus >= 201103L
    MessageHeader(MessageHeader&& codec) :
        m_buffer(codec.m_buffer),
        m_bufferLength(codec.m_bufferLength),
        m_offset(codec.m_offset),
        m_actingVersion(codec.m_actingVersion){}

    MessageHeader& operator=(MessageHeader&& codec) SBE_NOEXCEPT
    {
        m_buffer = codec.m_buffer;
        m_bufferLength = codec.m_bufferLength;
        m_offset = codec.m_offset;
        m_actingVersion = codec.m_actingVersion;
        return *this;
    }

#endif

    MessageHeader& operator=(const MessageHeader& codec) SBE_NOEXCEPT
    {
        m_buffer = codec.m_buffer;
        m_bufferLength = codec.m_bufferLength;
        m_offset = codec.m_offset;
        m_actingVersion = codec.m_actingVersion;
        return *this;
    }

    MessageHeader &wrap(char *buffer, const std::uint64_t offset, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, actingVersion);
        return *this;
    }

    static SBE_CONSTEXPR std::uint64_t encodedLength() SBE_NOEXCEPT
    {
        return 8;
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

    static const char * blockLengthMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t blockLengthId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t blockLengthSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool blockLengthInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= blockLengthSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t blockLengthEncodingOffset() SBE_NOEXCEPT
    {
         return 0;
    }

    static SBE_CONSTEXPR std::uint16_t blockLengthNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t blockLengthMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t blockLengthMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t blockLengthEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t blockLength() const
    {
        std::uint16_t val;
        std::memcpy(&val, m_buffer + m_offset + 0, sizeof(std::uint16_t));
        return SBE_LITTLE_ENDIAN_ENCODE_16(val);
    }

    MessageHeader &blockLength(const std::uint16_t value)
    {
        std::uint16_t val = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        std::memcpy(m_buffer + m_offset + 0, &val, sizeof(std::uint16_t));
        return *this;
    }

    static const char * templateIdMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t templateIdId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t templateIdSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool templateIdInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= templateIdSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t templateIdEncodingOffset() SBE_NOEXCEPT
    {
         return 2;
    }

    static SBE_CONSTEXPR std::uint16_t templateIdNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t templateIdMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t templateIdMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t templateIdEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t templateId() const
    {
        std::uint16_t val;
        std::memcpy(&val, m_buffer + m_offset + 2, sizeof(std::uint16_t));
        return SBE_LITTLE_ENDIAN_ENCODE_16(val);
    }

    MessageHeader &templateId(const std::uint16_t value)
    {
        std::uint16_t val = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        std::memcpy(m_buffer + m_offset + 2, &val, sizeof(std::uint16_t));
        return *this;
    }

    static const char * schemaIdMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t schemaIdId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t schemaIdSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool schemaIdInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= schemaIdSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t schemaIdEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }

    static SBE_CONSTEXPR std::uint16_t schemaIdNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t schemaIdMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t schemaIdMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t schemaIdEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t schemaId() const
    {
        std::uint16_t val;
        std::memcpy(&val, m_buffer + m_offset + 4, sizeof(std::uint16_t));
        return SBE_LITTLE_ENDIAN_ENCODE_16(val);
    }

    MessageHeader &schemaId(const std::uint16_t value)
    {
        std::uint16_t val = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        std::memcpy(m_buffer + m_offset + 4, &val, sizeof(std::uint16_t));
        return *this;
    }

    static const char * versionMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t versionId() SBE_NOEXCEPT
    {
        return -1;
    }

    static SBE_CONSTEXPR std::uint64_t versionSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool versionInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= versionSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t versionEncodingOffset() SBE_NOEXCEPT
    {
         return 6;
    }

    static SBE_CONSTEXPR std::uint16_t versionNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT16;
    }

    static SBE_CONSTEXPR std::uint16_t versionMinValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)0;
    }

    static SBE_CONSTEXPR std::uint16_t versionMaxValue() SBE_NOEXCEPT
    {
        return (std::uint16_t)65534;
    }

    static SBE_CONSTEXPR std::size_t versionEncodingLength() SBE_NOEXCEPT
    {
        return 2;
    }

    std::uint16_t version() const
    {
        std::uint16_t val;
        std::memcpy(&val, m_buffer + m_offset + 6, sizeof(std::uint16_t));
        return SBE_LITTLE_ENDIAN_ENCODE_16(val);
    }

    MessageHeader &version(const std::uint16_t value)
    {
        std::uint16_t val = SBE_LITTLE_ENDIAN_ENCODE_16(value);
        std::memcpy(m_buffer + m_offset + 6, &val, sizeof(std::uint16_t));
        return *this;
    }
};
}
#endif
