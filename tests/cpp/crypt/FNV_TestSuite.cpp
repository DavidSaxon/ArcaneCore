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
            arc::crypt::fnv1a_32(bytes.get_raw(), bytes.get_byte_length()),
            3731475286U
        );
    }
    {
        arc ::str::UTF8String bytes("");
        ARC_CHECK_EQUAL(
            arc::crypt::fnv1a_32(bytes.get_raw(), bytes.get_byte_length()),
            84696351U
        );
    }
    {
        arc ::str::UTF8String bytes("1438956");
        ARC_CHECK_EQUAL(
            arc::crypt::fnv1a_32(bytes.get_raw(), bytes.get_byte_length()),
            3954456103U
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
            arc::crypt::fnv1a_64(bytes.get_raw(), bytes.get_byte_length()),
            2782959106579962582UL
        );
    }
    {
        arc ::str::UTF8String bytes("");
        ARC_CHECK_EQUAL(
            arc::crypt::fnv1a_64(bytes.get_raw(), bytes.get_byte_length()),
            12638153115695167455UL
        );
    }
    {
        arc ::str::UTF8String bytes("1438956");
        ARC_CHECK_EQUAL(
            arc::crypt::fnv1a_64(bytes.get_raw(), bytes.get_byte_length()),
            16537246913123215463UL
        );
    }
}

} // namespace anonymous
