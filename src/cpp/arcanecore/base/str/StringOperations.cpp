#include "chaoscore/base/Exceptions.hpp"
#include "chaoscore/base/str/StringOperations.hpp"

namespace chaos
{
namespace str
{

bool is_digit(chaos::uint32 code_point)
{
    return code_point >= 48 && code_point <= 57;
}

chaos::str::UTF8String utf16_to_utf8(
        const char* data,
        std::size_t byte_length,
        chaos::data::Endianness endianness)
{
    // ensure data is unsigned
    const unsigned char* d = reinterpret_cast<const unsigned char*>(data);

    std::vector<unsigned char> utf8;
    // iterate over each character
    for(size_t i = 0;
        byte_length == chaos::str::npos || i < byte_length;
        i += 2)
    {
        chaos::uint32 code_point = 0;
        if(endianness == chaos::data::ENDIAN_BIG)
        {
            code_point = (static_cast<chaos::uint32>(d[i]) << 8) |
                          static_cast<chaos::uint32>(d[i + 1]);
        }
        else
        {
            code_point = static_cast<chaos::uint32>(d[i]) |
                         (static_cast<chaos::uint32>(d[i + 1] << 8));
        }

        // is this actually a 4-byte UTF-16 symbol, if so decode the code point
        if(code_point >= chaos::str::UTF16_HIGH_SURROGATE_MIN &&
           code_point <= chaos::str::UTF16_HIGH_SURROGATE_MAX    )
        {
            chaos::uint32 high_surrogate = code_point;
            chaos::uint32 low_surrogate = 0;
            if(endianness == chaos::data::ENDIAN_BIG)
            {
                low_surrogate = (static_cast<chaos::uint32>(d[i + 2]) << 8) |
                                 static_cast<chaos::uint32>(d[i + 3]);
            }
            else
            {
                low_surrogate = static_cast<chaos::uint32>(d[i + 2]) |
                               (static_cast<chaos::uint32>(d[i + 3] << 8));
            }
            // decompose the surrogates
            high_surrogate -= chaos::str::UTF16_HIGH_SURROGATE_MIN;
            low_surrogate  -= chaos::str::UTF16_LOW_SURROGATE_MIN;
            code_point = (high_surrogate << 10) | low_surrogate;
            code_point += chaos::str::UTF16_4BYTE_OFFSET;
            // we passed an extra two bytes
            i += 2;
        }

        // null?
        if(code_point == 0 && byte_length == chaos::str::npos)
        {
            break;
        }
        // one byte UTF-8 character
        else if(code_point < 0x80)
        {
            utf8.push_back(static_cast<unsigned char>(code_point));
        }
        // two byte UTF-8 character
        else if(code_point < 0x800)
        {
            utf8.push_back(static_cast<unsigned char>(
                0xC0 + (code_point >> 6))
            );
            utf8.push_back(static_cast<unsigned char>(
                0x80 + (code_point & 0x3F))
            );
        }
        // three byte UTF-8 character
        else if(code_point < 0x10000)
        {
            utf8.push_back(static_cast<unsigned char>(
                0xE0 + (code_point >> 12))
            );
            utf8.push_back(static_cast<unsigned char>(
                0x80 + ((code_point >> 6) & 0x3F))
            );
            utf8.push_back(static_cast<unsigned char>(
                0x80 + (code_point & 0x3F))
            );
        }
        // four byte UTF-8 character
        else
        {
            // TODO: could check the value is less than the max... utf16
            utf8.push_back(static_cast<unsigned char>(
                0xF0 + ((code_point >> 18) & 0x0F))
            );
            utf8.push_back(static_cast<unsigned char>(
                0x80 + ((code_point >> 12) & 0x3F))
            );
            utf8.push_back(static_cast<unsigned char>(
                0x80 + ((code_point >> 6) & 0x3F))
            );
            utf8.push_back(static_cast<unsigned char>(
                0x80 + (code_point & 0x3F))
            );
        }
    }

    return chaos::str::UTF8String((const char*) &utf8[0], utf8.size());
}

char* utf8_to_utf16(
        const chaos::str::UTF8String& data,
        std::size_t& r_length,
        chaos::data::Endianness endianness,
        bool null_terminated)
{
    std::vector<unsigned char> v_str;
    // convert
    for(std::size_t i = 0; i < data.get_length(); ++i)
    {
        chaos::uint32 code_point = data.get_code_point(i);
        // if this is a 4 byte character apply the surrogate to the code point
        bool is_surrogate_pair = false;
        if(code_point > chaos::str::UTF16_MAX_2BYTE)
        {
            // StringOperations
            is_surrogate_pair = true;
            code_point -= chaos::str::UTF16_4BYTE_OFFSET;
            chaos::uint32 high_surrogate =
                chaos::str::UTF16_HIGH_SURROGATE_MIN +
                ((code_point >> 10) & 0x3FF);
            chaos::uint32 low_surrogate =
                chaos::str::UTF16_LOW_SURROGATE_MIN + (code_point & 0x3FF);
            code_point = (high_surrogate << 16) | low_surrogate;
        }

        if(endianness == chaos::data::ENDIAN_LITTLE)
        {
            if(is_surrogate_pair)
            {
                v_str.push_back(code_point >> 16);
                v_str.push_back(code_point >> 24);
            }
            v_str.push_back(code_point);
            v_str.push_back(code_point >> 8);
        }
        else
        {
            if(is_surrogate_pair)
            {
                v_str.push_back(code_point >> 24);
                v_str.push_back(code_point >> 16);
            }
            v_str.push_back(code_point >> 8);
            v_str.push_back(code_point);
        }
    }
    // add the NULL terminator
    if(null_terminated)
    {
        v_str.push_back(0x00);
        v_str.push_back(0x00);
    }

    r_length = v_str.size();
    // allocate to array and copy
    char* s = new char[r_length];
    for(std::size_t i = 0; i < v_str.size(); ++i)
    {
        s[i] = static_cast<char>(v_str[i]);
    }

    return s;
}

bool is_utf8(const char* data, std::size_t length)
{
    // marks the number of bytes after a primary byte that are required to start
    // with 10xxxxxx
    chaos::uint8 following_bytes = 0;
    // iterate over the data
    for(std::size_t i = 0; i < length; ++i)
    {
        // check for null terminator
        if(length == chaos::str::npos && data[i] == '\0')
        {
            return true;
        }

        // is this a following byte we need to check
        if(following_bytes > 0)
        {
            if((data[i] & 0xC0) == 0x80)
            {
                // valid following byte
                --following_bytes;
                continue;
            }
            else
            {
                // invalid following byte
                return false;
            }
        }

        // since this is not a following byte check against valid primary bytes
        if((data[i] & 0x80) == 0)
        {
            // single byte character
            continue;
        }
        else if((data[i] & 0xE0) == 0xC0)
        {
            // double byte character
            following_bytes = 1;
            continue;
        }
        else if((data[i] & 0xF0) == 0xE0)
        {
            // triple byte character
            following_bytes = 2;
            continue;
        }
        else if((data[i] & 0xF8) == 0xF0)
        {
            // quad byte character
            following_bytes = 3;
            continue;
        }
        else
        {
            // invalid primary character
            return false;
        }
    }

    // we made it through no errors
    return true;
}

chaos::str::UTF8String join(
        const std::vector<chaos::str::UTF8String>& components,
        const chaos::str::UTF8String& seperator)
{
    chaos::str::UTF8String ret;

    for(std::size_t i = 0; i < components.size(); ++i)
    {
        ret << components[i];
        if(i != components.size() - 1)
        {
            ret << seperator;
        }
    }

    return ret;
}

} // namespace str
} // namespace chaos
