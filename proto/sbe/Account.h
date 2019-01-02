/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _SBE_ACCOUNT_H_
#define _SBE_ACCOUNT_H_

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

#include "Order.h"
#include "OrderType.h"
#include "MessageHeader.h"
#include "GroupSizeEncoding.h"
#include "VarStringEncoding.h"
#include "Balance.h"
#include "OrderSide.h"

namespace sbe {

class Account
{
private:
    char *m_buffer;
    std::uint64_t m_bufferLength;
    std::uint64_t *m_positionPtr;
    std::uint64_t m_offset;
    std::uint64_t m_position;
    std::uint64_t m_actingBlockLength;
    std::uint64_t m_actingVersion;

    inline void reset(
        char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength,
        const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        m_buffer = buffer;
        m_offset = offset;
        m_bufferLength = bufferLength;
        m_actingBlockLength = actingBlockLength;
        m_actingVersion = actingVersion;
        m_positionPtr = &m_position;
        sbePosition(offset + m_actingBlockLength);
    }

    inline void reset(const Account& codec)
    {
        m_buffer = codec.m_buffer;
        m_offset = codec.m_offset;
        m_bufferLength = codec.m_bufferLength;
        m_actingBlockLength = codec.m_actingBlockLength;
        m_actingVersion = codec.m_actingVersion;
        m_positionPtr = &m_position;
        m_position = codec.m_position;
    }

public:

    Account() : m_buffer(nullptr), m_bufferLength(0), m_offset(0) {}

    Account(char *buffer, const std::uint64_t bufferLength)
    {
        reset(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    Account(char *buffer, const std::uint64_t bufferLength, const std::uint64_t actingBlockLength, const std::uint64_t actingVersion)
    {
        reset(buffer, 0, bufferLength, actingBlockLength, actingVersion);
    }

    Account(const Account& codec)
    {
        reset(codec);
    }

#if __cplusplus >= 201103L
    Account(Account&& codec)
    {
        reset(codec);
    }

    Account& operator=(Account&& codec)
    {
        reset(codec);
        return *this;
    }

#endif

    Account& operator=(const Account& codec)
    {
        reset(codec);
        return *this;
    }

    static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return (std::uint16_t)22;
    }

    static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return (std::uint16_t)1;
    }

    static SBE_CONSTEXPR std::uint16_t sbeSchemaId() SBE_NOEXCEPT
    {
        return (std::uint16_t)1;
    }

    static SBE_CONSTEXPR std::uint16_t sbeSchemaVersion() SBE_NOEXCEPT
    {
        return (std::uint16_t)1;
    }

    static SBE_CONSTEXPR const char * sbeSemanticType() SBE_NOEXCEPT
    {
        return "";
    }

    std::uint64_t offset() const SBE_NOEXCEPT
    {
        return m_offset;
    }

    Account &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
        return *this;
    }

    Account &wrapForDecode(
         char *buffer, const std::uint64_t offset, const std::uint64_t actingBlockLength,
         const std::uint64_t actingVersion, const std::uint64_t bufferLength)
    {
        reset(buffer, offset, bufferLength, actingBlockLength, actingVersion);
        return *this;
    }

    std::uint64_t sbePosition() const SBE_NOEXCEPT
    {
        return m_position;
    }

    void sbePosition(const std::uint64_t position)
    {
        if (SBE_BOUNDS_CHECK_EXPECT((position > m_bufferLength), false))
        {
            throw std::runtime_error("buffer too short [E100]");
        }
        m_position = position;
    }

    std::uint64_t encodedLength() const SBE_NOEXCEPT
    {
        return sbePosition() - m_offset;
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

    std::uint64_t actingVersion() const SBE_NOEXCEPT
    {
        return m_actingVersion;
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
        return 1;
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

    Account &id(const std::int32_t value)
    {
        std::int32_t val = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        std::memcpy(m_buffer + m_offset + 0, &val, sizeof(std::int32_t));
        return *this;
    }

    static const char * walletMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

    static SBE_CONSTEXPR std::uint16_t walletId() SBE_NOEXCEPT
    {
        return 2;
    }

    static SBE_CONSTEXPR std::uint64_t walletSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool walletInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= walletSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::size_t walletEncodingOffset() SBE_NOEXCEPT
    {
         return 4;
    }

private:
    Balance m_wallet;

public:

    Balance &wallet()
    {
        m_wallet.wrap(m_buffer, m_offset + 4, m_actingVersion, m_bufferLength);
        return m_wallet;
    }

    class Orders
    {
    private:
        char *m_buffer;
        std::uint64_t m_bufferLength;
        std::uint64_t *m_positionPtr;
        std::uint64_t m_blockLength;
        std::uint64_t m_count;
        std::uint64_t m_index;
        std::uint64_t m_offset;
        std::uint64_t m_actingVersion;
        GroupSizeEncoding m_dimensions;

    public:

        inline void wrapForDecode(char *buffer, std::uint64_t *pos, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
        {
            m_buffer = buffer;
            m_bufferLength = bufferLength;
            m_dimensions.wrap(m_buffer, *pos, actingVersion, bufferLength);
            m_blockLength = m_dimensions.blockLength();
            m_count = m_dimensions.numInGroup();
            m_index = -1;
            m_actingVersion = actingVersion;
            m_positionPtr = pos;
            *m_positionPtr = *m_positionPtr + 4;
        }

        inline void wrapForEncode(char *buffer, const std::uint16_t count, std::uint64_t *pos, const std::uint64_t actingVersion, const std::uint64_t bufferLength)
        {
    #if defined(__GNUG__) && !defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wtype-limits"
    #endif
            if (count < 0 || count > 65534)
            {
                throw std::runtime_error("count outside of allowed range [E110]");
            }
    #if defined(__GNUG__) && !defined(__clang__)
    #pragma GCC diagnostic pop
    #endif
            m_buffer = buffer;
            m_bufferLength = bufferLength;
            m_dimensions.wrap(m_buffer, *pos, actingVersion, bufferLength);
            m_dimensions.blockLength((std::uint16_t)32);
            m_dimensions.numInGroup((std::uint16_t)count);
            m_index = -1;
            m_count = count;
            m_blockLength = 32;
            m_actingVersion = actingVersion;
            m_positionPtr = pos;
            *m_positionPtr = *m_positionPtr + 4;
        }

        static SBE_CONSTEXPR std::uint64_t sbeHeaderSize() SBE_NOEXCEPT
        {
            return 4;
        }

        static SBE_CONSTEXPR std::uint64_t sbeBlockLength() SBE_NOEXCEPT
        {
            return 32;
        }

        std::uint64_t sbePosition() const
        {
            return *m_positionPtr;
        }

        void sbePosition(const std::uint64_t position)
        {
            if (SBE_BOUNDS_CHECK_EXPECT((position > m_bufferLength), false))
            {
                 throw std::runtime_error("buffer too short [E100]");
            }
            *m_positionPtr = position;
        }

        inline std::uint64_t count() const SBE_NOEXCEPT
        {
            return m_count;
        }

        inline bool hasNext() const SBE_NOEXCEPT
        {
            return m_index + 1 < m_count;
        }

        inline Orders &next()
        {
            m_offset = *m_positionPtr;
            if (SBE_BOUNDS_CHECK_EXPECT(( (m_offset + m_blockLength) > m_bufferLength ), false))
            {
                throw std::runtime_error("buffer too short to support next group index [E108]");
            }
            *m_positionPtr = m_offset + m_blockLength;
            ++m_index;

            return *this;
        }

    #if __cplusplus < 201103L
        template<class Func> inline void forEach(Func& func)
        {
            while (hasNext())
            {
                next(); func(*this);
            }
        }

    #else
        template<class Func> inline void forEach(Func&& func)
        {
            while (hasNext())
            {
                next(); func(*this);
            }
        }

    #endif


        static const char * orderMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
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

        static SBE_CONSTEXPR std::uint16_t orderId() SBE_NOEXCEPT
        {
            return 4;
        }

        static SBE_CONSTEXPR std::uint64_t orderSinceVersion() SBE_NOEXCEPT
        {
             return 0;
        }

        bool orderInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= orderSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        static SBE_CONSTEXPR std::size_t orderEncodingOffset() SBE_NOEXCEPT
        {
             return 0;
        }

private:
        Order m_order;

public:

        Order &order()
        {
            m_order.wrap(m_buffer, m_offset + 0, m_actingVersion, m_bufferLength);
            return m_order;
        }
    };

private:
    Orders m_orders;

public:

    static SBE_CONSTEXPR std::uint16_t ordersId() SBE_NOEXCEPT
    {
        return 3;
    }


    inline Orders &orders()
    {
        m_orders.wrapForDecode(m_buffer, m_positionPtr, m_actingVersion, m_bufferLength);
        return m_orders;
    }

    Orders &ordersCount(const std::uint16_t count)
    {
        m_orders.wrapForEncode(m_buffer, count, m_positionPtr, m_actingVersion, m_bufferLength);
        return m_orders;
    }

    static SBE_CONSTEXPR std::uint64_t ordersSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool ordersInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= ordersSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static const char * nameMetaAttribute(const ::sbe::MetaAttribute::Attribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case ::sbe::MetaAttribute::EPOCH: return "unix";
            case ::sbe::MetaAttribute::TIME_UNIT: return "nanosecond";
            case ::sbe::MetaAttribute::SEMANTIC_TYPE: return "";
            case ::sbe::MetaAttribute::PRESENCE: return "required";
        }

        return "";
    }

    static const char *nameCharacterEncoding() SBE_NOEXCEPT
    {
        return "UTF-8";
    }

    static SBE_CONSTEXPR std::uint64_t nameSinceVersion() SBE_NOEXCEPT
    {
         return 0;
    }

    bool nameInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= nameSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::uint16_t nameId() SBE_NOEXCEPT
    {
        return 5;
    }


    static SBE_CONSTEXPR std::uint64_t nameHeaderLength() SBE_NOEXCEPT
    {
        return 4;
    }

    std::uint32_t nameLength() const
    {
        std::uint32_t length;
        std::memcpy(&length, m_buffer + sbePosition(), sizeof(std::uint32_t));
        return SBE_LITTLE_ENDIAN_ENCODE_32(length);
    }


    const char *name()
    {
         std::uint32_t lengthFieldValue;
         std::memcpy(&lengthFieldValue, m_buffer + sbePosition(), sizeof(std::uint32_t));
         const char *fieldPtr = (m_buffer + sbePosition() + 4);
         sbePosition(sbePosition() + 4 + SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue));
         return fieldPtr;
    }

    std::uint64_t getName(char *dst, const std::uint64_t length)
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        sbePosition(lengthPosition + lengthOfLengthField);
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        std::uint64_t bytesToCopy = (length < dataLength) ? length : dataLength;
        std::uint64_t pos = sbePosition();
        sbePosition(sbePosition() + dataLength);
        std::memcpy(dst, m_buffer + pos, bytesToCopy);
        return bytesToCopy;
    }

    Account &putName(const char *src, const std::uint32_t length)
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        std::uint32_t lengthFieldValue = SBE_LITTLE_ENDIAN_ENCODE_32(length);
        sbePosition(lengthPosition + lengthOfLengthField);
        std::memcpy(m_buffer + lengthPosition, &lengthFieldValue, sizeof(std::uint32_t));
        std::uint64_t pos = sbePosition();
        sbePosition(sbePosition() + length);
        std::memcpy(m_buffer + pos, src, length);
        return *this;
    }

    const std::string getNameAsString()
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        sbePosition(lengthPosition + lengthOfLengthField);
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        std::uint64_t pos = sbePosition();
        const std::string result(m_buffer + pos, dataLength);
        sbePosition(sbePosition() + dataLength);
        return result;
    }

    Account &putName(const std::string& str)
    {
        if (str.length() > 1073741824)
        {
             throw std::runtime_error("std::string too long for length type [E109]");
        }
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        std::uint32_t lengthFieldValue = SBE_LITTLE_ENDIAN_ENCODE_32(static_cast<std::uint32_t>(str.length()));
        sbePosition(lengthPosition + lengthOfLengthField);
        std::memcpy(m_buffer + lengthPosition, &lengthFieldValue, sizeof(std::uint32_t));
        std::uint64_t pos = sbePosition();
        sbePosition(sbePosition() + str.length());
        std::memcpy(m_buffer + pos, str.c_str(), str.length());
        return *this;
    }
};
}
#endif
