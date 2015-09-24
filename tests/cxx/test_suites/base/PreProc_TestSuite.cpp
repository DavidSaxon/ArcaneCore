#include "chaoscore/test/ChaosTest.hpp"

//------------------------------------------------------------------------------
//                                   UNIT TESTS
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT(  )
{
    std::cout << "RUN DISALLOW CONSTRUCTION" << std::endl;
}

CHAOS_TEST_UNIT( base.preproc.disallow_copy_and_assign )
{
    std::cout << "RUN DISALLOW COPY AND ASSIGN" << std::endl;
}

