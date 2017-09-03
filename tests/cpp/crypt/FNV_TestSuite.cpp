#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(crypt.FNV)

#include <arcanecore/crypt/FNV.hpp>

namespace
{

//------------------------------------------------------------------------------
//                                 FNV-1A 32-BITS
//------------------------------------------------------------------------------

ARC_TEST_UNIT(fnv1a_32)
{
    {
        arc ::str::UTF8String bytes("Hello world!");
        ARC_CHECK_EQUAL(
            arc::crypt::fnv1a_32(bytes.get_raw(), bytes.get_byte_length() - 1),
            2054747410U
        );
    }
    {
        arc ::str::UTF8String bytes("");
        ARC_CHECK_EQUAL(
            arc::crypt::fnv1a_32(bytes.get_raw(), bytes.get_byte_length() - 1),
            2166136261U
        );
    }
    {
        arc ::str::UTF8String bytes("1438956");
        ARC_CHECK_EQUAL(
            arc::crypt::fnv1a_32(bytes.get_raw(), bytes.get_byte_length() - 1),
            2806195613U
        );
    }

    {
        arc ::str::UTF8String part1("this is the start of the string ");
        arc ::str::UTF8String part2("while this is the end 325832");
        arc ::str::UTF8String combined = part1 + part2;

        arc::uint32 accumlated_hash =
            arc::crypt::fnv1a_32(part1.get_raw(), part1.get_byte_length() - 1);
        accumlated_hash = arc::crypt::fnv1a_32(
            part2.get_raw(),
            part2.get_byte_length() - 1,
            accumlated_hash
        );

        ARC_CHECK_EQUAL(
            accumlated_hash,
            arc::crypt::fnv1a_32(
                combined.get_raw(),
                combined.get_byte_length() - 1
            )
        );
    }
}

//------------------------------------------------------------------------------
//                                 FNV-1A 64-BITS
//------------------------------------------------------------------------------

ARC_TEST_UNIT(fnv1a_64)
{
    {
        arc ::str::UTF8String bytes("Hello world!");
        ARC_CHECK_EQUAL(
            arc::crypt::fnv1a_64(bytes.get_raw(), bytes.get_byte_length() - 1),
            11408319431909077714UL
        );
    }
    {
        arc ::str::UTF8String bytes("");
        ARC_CHECK_EQUAL(
            arc::crypt::fnv1a_64(bytes.get_raw(), bytes.get_byte_length() - 1),
            14695981039346656037UL
        );
    }
    {
        arc ::str::UTF8String bytes("1438956");
        ARC_CHECK_EQUAL(
            arc::crypt::fnv1a_64(bytes.get_raw(), bytes.get_byte_length() - 1),
            12006184821643943037UL
        );
    }

    {
        arc ::str::UTF8String part1("this is the start of the string ");
        arc ::str::UTF8String part2("while this is the end 325832");
        arc ::str::UTF8String combined = part1 + part2;

        arc::uint64 accumlated_hash =
            arc::crypt::fnv1a_32(part1.get_raw(), part1.get_byte_length() - 1);
        accumlated_hash = arc::crypt::fnv1a_32(
            part2.get_raw(),
            part2.get_byte_length() - 1,
            accumlated_hash
        );

        ARC_CHECK_EQUAL(
            accumlated_hash,
            arc::crypt::fnv1a_32(
                combined.get_raw(),
                combined.get_byte_length() - 1
            )
        );
    }
}

} // namespace anonymous
