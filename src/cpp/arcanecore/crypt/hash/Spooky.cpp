#include "arcanecore/crypt/hash/Spooky.hpp"

#include <cstring>


namespace arc
{
namespace crypt
{
namespace hash
{

//------------------------------------------------------------------------------
//                                    GLOBALS
//------------------------------------------------------------------------------

namespace
{

// the number of unsigned 64-bit ints in the internal state
static const std::size_t SPOOKY_NUMBER_OF_VARS = 12;
// the size of the internal state
static const std::size_t SPOOKY_BLOCK_SIZE  = SPOOKY_NUMBER_OF_VARS * 8;
// the size of the buffer of unhashed data, in bytes
static const std::size_t SPOOKY_BUFFER_SIZE = 2 * SPOOKY_BLOCK_SIZE;

// a value which is not zero, is odd, and is not very regular mix of 1s and 0s.
static const arc::uint64 SPOOKY_CONSTANT = 0xDEADBEEFDEADBEEFUL;

} // namespace anonymous

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

bool spooky_force_aligned_reads = false;

//------------------------------------------------------------------------------
//                                     UNION
//------------------------------------------------------------------------------

// used for changing the type the data is accessed via
union Access
{
    const arc::uint8* p8;
    const arc::uint32* p32;
    const arc::uint64* p64;
    std::size_t i;
};

//------------------------------------------------------------------------------
//                                   PROTOTYPES
//------------------------------------------------------------------------------

// left rotates a 64-bit value by k-bytes
static ARC_FORCE_INLINE arc::uint64 spooky_rot_64(arc::uint64 x, int k);

static ARC_FORCE_INLINE void spooky_mix(
        const arc::uint64* data,
        arc::uint64& s0,
        arc::uint64& s1,
        arc::uint64& s2,
        arc::uint64& s3,
        arc::uint64& s4,
        arc::uint64& s5,
        arc::uint64& s6,
        arc::uint64& s7,
        arc::uint64& s8,
        arc::uint64& s9,
        arc::uint64& s10,
        arc::uint64& s11);

static ARC_FORCE_INLINE void spooky_end(
        const arc::uint64* data,
        arc::uint64& h0,
        arc::uint64& h1,
        arc::uint64& h2,
        arc::uint64& h3,
        arc::uint64& h4,
        arc::uint64& h5,
        arc::uint64& h6,
        arc::uint64& h7,
        arc::uint64& h8,
        arc::uint64& h9,
        arc::uint64& h10,
        arc::uint64& h11);

static ARC_FORCE_INLINE void spooky_end_partial(
        arc::uint64& h0,
        arc::uint64& h1,
        arc::uint64& h2,
        arc::uint64& h3,
        arc::uint64& h4,
        arc::uint64& h5,
        arc::uint64& h6,
        arc::uint64& h7,
        arc::uint64& h8,
        arc::uint64& h9,
        arc::uint64& h10,
        arc::uint64& h11);

// hashes short data
static void spooky_short(
        const void* data,
        std::size_t length,
        arc::uint64& out_hash1,
        arc::uint64& out_hash2,
        arc::uint64 initial1,
        arc::uint64 initial2);

// the goal is for each bit of the input to expand into 128 bits of apparent
// entropy before it is full overwritten
static ARC_FORCE_INLINE void spooky_short_mix(
        arc::uint64& h0,
        arc::uint64& h1,
        arc::uint64& h2,
        arc::uint64& h3);

// mix all 4 inputs together so that h0, and h1 are a hash of them all.
static ARC_FORCE_INLINE void spooky_short_end(
        arc::uint64& h0,
        arc::uint64& h1,
        arc::uint64& h2,
        arc::uint64& h3);

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

void spooky_128(
        const void* data,
        std::size_t length,
        arc::uint64& out_hash1,
        arc::uint64& out_hash2,
        arc::uint64 initial1,
        arc::uint64 initial2)
{
    // short message?
    if(length < SPOOKY_BUFFER_SIZE)
    {
        spooky_short(data, length, out_hash1, out_hash2, initial1, initial2);
        return;
    }

    arc::uint64 h0  = initial1;
    arc::uint64 h1  = initial2;
    arc::uint64 h2  = SPOOKY_CONSTANT;
    arc::uint64 h3  = initial1;
    arc::uint64 h4  = initial2;
    arc::uint64 h5  = SPOOKY_CONSTANT;
    arc::uint64 h6  = initial1;
    arc::uint64 h7  = initial2;
    arc::uint64 h8  = SPOOKY_CONSTANT;
    arc::uint64 h9  = initial1;
    arc::uint64 h10 = initial2;
    arc::uint64 h11 = SPOOKY_CONSTANT;

    Access access;
    access.p8 = static_cast<const arc::uint8*>(data);

    const arc::uint64* end =
        access.p64 + ((length / SPOOKY_BLOCK_SIZE) * SPOOKY_NUMBER_OF_VARS);

    arc::uint64 buffer[SPOOKY_NUMBER_OF_VARS];

    // handle all whole block size blocks of data
    if(!spooky_force_aligned_reads || ((access.i & 0x7) == 0))
    {
        while(access.p64 < end)
        {
            spooky_mix(
                access.p64,
                h0,
                h1,
                h2,
                h3,
                h4,
                h5,
                h6,
                h7,
                h8,
                h9,
                h10,
                h11
            );
            access.p64 += SPOOKY_NUMBER_OF_VARS;
        }
    }
    else
    {
        std::memcpy(buffer, access.p64, SPOOKY_BLOCK_SIZE);
        spooky_mix(
            buffer,
            h0,
            h1,
            h2,
            h3,
            h4,
            h5,
            h6,
            h7,
            h8,
            h9,
            h10,
            h11
        );
        access.p64 += SPOOKY_NUMBER_OF_VARS;
    }

    // handle the last partial block of SPOOKY_BLOCK_SIZE bytes
    std::size_t remain =
        length -
        (reinterpret_cast<const arc::uint8*>(end) -
         reinterpret_cast<const arc::uint8*>(data));
    std::memcpy(buffer, end, remain);
    std::memset(
        reinterpret_cast<arc::uint8*>(buffer) + remain,
        0,
        SPOOKY_BLOCK_SIZE - remain
    );
    reinterpret_cast<arc::uint8*>(buffer)[SPOOKY_BLOCK_SIZE - 1] =
        static_cast<arc::uint8>(remain);

    // do some final mixing
    spooky_end(buffer, h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    // return
    out_hash1 = h0;
    out_hash2 = h1;
}

arc::uint64 spooky_64(
        const void* data,
        std::size_t length,
        arc::uint64 initial)
{
    arc::uint64 out_hash1 = 0;
    arc::uint64 out_hash2 = 0;
    spooky_128(data, length, out_hash1, out_hash2, initial, initial);
    return out_hash1;
}

arc::uint32 spooky_32(
        const void* data,
        std::size_t length,
        arc::uint32 initial)
{
    arc::uint64 out_hash1 = 0;
    arc::uint64 out_hash2 = 0;
    spooky_128(
        data,
        length,
        out_hash1,
        out_hash2,
        static_cast<arc::int32>(initial),
        static_cast<arc::int32>(initial)
    );
    return static_cast<arc::int32>(out_hash1);
}

static ARC_FORCE_INLINE arc::uint64 spooky_rot_64(arc::uint64 x, int k)
{
    return (x << k) | (x >> (64 - k));
}

static ARC_FORCE_INLINE void spooky_mix(
        const arc::uint64* data,
        arc::uint64& s0,
        arc::uint64& s1,
        arc::uint64& s2,
        arc::uint64& s3,
        arc::uint64& s4,
        arc::uint64& s5,
        arc::uint64& s6,
        arc::uint64& s7,
        arc::uint64& s8,
        arc::uint64& s9,
        arc::uint64& s10,
        arc::uint64& s11)
{
    s0  += data[0];
    s2  ^= s10;
    s11 ^= s0;
    s0  = spooky_rot_64(s0, 11);
    s11 += s1;
    s1  += data[1];
    s3  ^= s11;
    s0  ^= s1;
    s1  = spooky_rot_64(s1, 32);
    s0  += s2;
    s2  += data[2];
    s4  ^= s0;
    s1  ^= s2;
    s2  = spooky_rot_64(s2, 43);
    s1  += s3;
    s3  += data[3];
    s5  ^= s1;
    s2  ^= s3;
    s3  = spooky_rot_64(s3, 31);
    s2  += s4;
    s4  += data[4];
    s6  ^= s2;
    s3  ^= s4;
    s4  = spooky_rot_64(s4, 17);
    s3  += s5;
    s5  += data[5];
    s7  ^= s3;
    s4  ^= s5;
    s5  = spooky_rot_64(s5, 28);
    s4  += s6;
    s6  += data[6];
    s8  ^= s4;
    s5  ^= s6;
    s6  = spooky_rot_64(s6, 39);
    s5  += s7;
    s7  += data[7];
    s9  ^= s5;
    s6  ^= s7;
    s7  = spooky_rot_64(s7, 57);
    s6  += s8;
    s8  += data[8];
    s10 ^= s6;
    s7  ^= s8;
    s8  = spooky_rot_64(s8, 55);
    s7  += s9;
    s9  += data[9];
    s11 ^= s7;
    s8  ^= s9;
    s9  = spooky_rot_64(s9, 54);
    s8  += s10;
    s10 += data[10];
    s0  ^= s8;
    s9  ^= s10;
    s10 = spooky_rot_64(s10 ,22);
    s9  += s11;
    s11 += data[11];
    s1  ^= s9;
    s10 ^= s11;
    s11 = spooky_rot_64(s11 ,46);
    s10 += s0;
}

static ARC_FORCE_INLINE void spooky_end(
        const arc::uint64* data,
        arc::uint64& h0,
        arc::uint64& h1,
        arc::uint64& h2,
        arc::uint64& h3,
        arc::uint64& h4,
        arc::uint64& h5,
        arc::uint64& h6,
        arc::uint64& h7,
        arc::uint64& h8,
        arc::uint64& h9,
        arc::uint64& h10,
        arc::uint64& h11)
{
    h0 += data[0];
    h1 += data[1];
    h2 += data[2];
    h3 += data[3];
    h4 += data[4];
    h5 += data[5];
    h6 += data[6];
    h7 += data[7];
    h8 += data[8];
    h9 += data[9];
    h10 += data[10];
    h11 += data[11];
    spooky_end_partial(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    spooky_end_partial(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    spooky_end_partial(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
}

static ARC_FORCE_INLINE void spooky_end_partial(
        arc::uint64& h0,
        arc::uint64& h1,
        arc::uint64& h2,
        arc::uint64& h3,
        arc::uint64& h4,
        arc::uint64& h5,
        arc::uint64& h6,
        arc::uint64& h7,
        arc::uint64& h8,
        arc::uint64& h9,
        arc::uint64& h10,
        arc::uint64& h11)
{
    h11 += h1;
    h2  ^= h11;
    h1  = spooky_rot_64(h1, 44);
    h0  += h2;
    h3  ^= h0;
    h2  = spooky_rot_64(h2, 15);
    h1  += h3;
    h4  ^= h1;
    h3  = spooky_rot_64(h3, 34);
    h2  += h4;
    h5  ^= h2;
    h4  = spooky_rot_64(h4, 21);
    h3  += h5;
    h6  ^= h3;
    h5  = spooky_rot_64(h5, 38);
    h4  += h6;
    h7  ^= h4;
    h6  = spooky_rot_64(h6, 33);
    h5  += h7;
    h8  ^= h5;
    h7  = spooky_rot_64(h7, 10);
    h6  += h8;
    h9  ^= h6;
    h8  = spooky_rot_64(h8, 13);
    h7  += h9;
    h10 ^= h7;
    h9  = spooky_rot_64(h9, 38);
    h8  += h10;
    h11 ^= h8;
    h10 = spooky_rot_64(h10, 53);
    h9  += h11;
    h0  ^= h9;
    h11 = spooky_rot_64(h11, 42);
    h10 += h0;
    h1  ^= h10;
    h0  = spooky_rot_64(h0, 54);
}

static void spooky_short(
        const void* data,
        std::size_t length,
        arc::uint64& out_hash1,
        arc::uint64& out_hash2,
        arc::uint64 initial1,
        arc::uint64 initial2)
{
    Access access;
    access.p8 = static_cast<const arc::uint8*>(data);

    // do we need to align the input data?
    arc::uint64 align_buffer[2 * SPOOKY_NUMBER_OF_VARS];
    if(!spooky_force_aligned_reads && (access.i & 0x7))
    {
        std::memcpy(align_buffer, data, length);
        access.p64 = align_buffer;
    }

    std::size_t remain = length % 32;
    arc::uint64 a = initial1;
    arc::uint64 b = initial2;
    arc::uint64 c = SPOOKY_CONSTANT;
    arc::uint64 d = SPOOKY_CONSTANT;

    if(length > 15)
    {
        const arc::uint64* end = access.p64 + (length / 32) * 4;

        // handle all complete sets of 32 bytes
        for(; access.p64 < end; access.p64 += 4)
        {
            c += access.p64[0];
            d += access.p64[1];
            spooky_short_mix(a, b, c, d);
            a += access.p64[2];
            b += access.p64[3];
        }

        // handle the case of 16+ remaining bytes
        if(remain >= 16)
        {
            c += access.p64[0];
            d += access.p64[1];
            spooky_short_mix(a, b, c, d);
            access.p64 += 2;
            remain -= 16;
        }
    }

    // handle the last 0-15 bytes
    d += static_cast<arc::uint64>(length) << 56;
    switch(remain)
    {
        case 15:
            d += static_cast<arc::uint64>(access.p8[14]) << 48;
        case 14:
            d += static_cast<arc::uint64>(access.p8[13]) << 40;
        case 13:
            d += static_cast<arc::uint64>(access.p8[12]) << 32;
        case 12:
            d += access.p32[2];
            c += access.p64[0];
            break;
        case 11:
            d += static_cast<arc::uint64>(access.p8[10]) << 16;
        case 10:
            d += static_cast<arc::uint64>(access.p8[9]) << 8;
        case 9:
            d += static_cast<arc::uint64>(access.p8[8]);
        case 8:
            c += access.p64[0];
            break;
        case 7:
            c += static_cast<arc::uint64>(access.p8[6]) << 48;
        case 6:
            c += static_cast<arc::uint64>(access.p8[5]) << 40;
        case 5:
            c += static_cast<arc::uint64>(access.p8[4]) << 32;
        case 4:
            c += access.p32[0];
            break;
        case 3:
            c += static_cast<arc::uint64>(access.p8[2]) << 16;
        case 2:
            c += static_cast<arc::uint64>(access.p8[1]) << 8;
        case 1:
            c += static_cast<arc::uint64>(access.p8[0]);
            break;
        case 0:
            c += SPOOKY_CONSTANT;
            d += SPOOKY_CONSTANT;
    }
    spooky_short_end(a, b, c, d);
    out_hash1 = a;
    out_hash2 = b;
}

static ARC_FORCE_INLINE void spooky_short_mix(
        arc::uint64& h0,
        arc::uint64& h1,
        arc::uint64& h2,
        arc::uint64& h3)
{
    h2 = spooky_rot_64(h2, 50);
    h2 += h3;
    h0 ^= h2;
    h3 = spooky_rot_64(h3, 52);
    h3 += h0;
    h1 ^= h3;
    h0 = spooky_rot_64(h0, 30);
    h0 += h1;
    h2 ^= h0;
    h1 = spooky_rot_64(h1, 41);
    h1 += h2;
    h3 ^= h1;
    h2 = spooky_rot_64(h2, 54);
    h2 += h3;
    h0 ^= h2;
    h3 = spooky_rot_64(h3, 48);
    h3 += h0;
    h1 ^= h3;
    h0 = spooky_rot_64(h0, 38);
    h0 += h1;
    h2 ^= h0;
    h1 = spooky_rot_64(h1, 37);
    h1 += h2;
    h3 ^= h1;
    h2 = spooky_rot_64(h2, 62);
    h2 += h3;
    h0 ^= h2;
    h3 = spooky_rot_64(h3, 34);
    h3 += h0;
    h1 ^= h3;
    h0 = spooky_rot_64(h0, 5);
    h0 += h1;
    h2 ^= h0;
    h1 = spooky_rot_64(h1, 36);
    h1 += h2;
    h3 ^= h1;
}

static ARC_FORCE_INLINE void spooky_short_end(
        arc::uint64& h0,
        arc::uint64& h1,
        arc::uint64& h2,
        arc::uint64& h3)
{
    h3 ^= h2;
    h2 = spooky_rot_64(h2, 15);
    h3 += h2;
    h0 ^= h3;
    h3 = spooky_rot_64(h3, 52);
    h0 += h3;
    h1 ^= h0;
    h0 = spooky_rot_64(h0, 26);
    h1 += h0;
    h2 ^= h1;
    h1 = spooky_rot_64(h1, 51);
    h2 += h1;
    h3 ^= h2;
    h2 = spooky_rot_64(h2, 28);
    h3 += h2;
    h0 ^= h3;
    h3 = spooky_rot_64(h3, 9);
    h0 += h3;
    h1 ^= h0;
    h0 = spooky_rot_64(h0, 47);
    h1 += h0;
    h2 ^= h1;
    h1 = spooky_rot_64(h1, 54);
    h2 += h1;
    h3 ^= h2;
    h2 = spooky_rot_64(h2, 32);
    h3 += h2;
    h0 ^= h3;
    h3 = spooky_rot_64(h3, 25);
    h0 += h3;
    h1 ^= h0;
    h0 = spooky_rot_64(h0, 63);
    h1 += h0;
}

} // namespace hash
} // namespace crypt
} // namespace arc
