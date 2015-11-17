#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( io.file.path )

#include "chaoscore/io/file/Path.hpp"

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( default_constructor )
{
    chaos::io::file::Path empty;
    // CHAOS_CHECK_TRUE( empty.to_string().is_empty() );
}
