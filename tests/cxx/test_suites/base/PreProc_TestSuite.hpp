#ifndef CHAOSCORE_TESTS_SUITES_BASE_PREPROC_HPP_
#define CHAOSCORE_TESTS_SUITES_BASE_PREPROC_HPP_

#include "chaoscore/test/TestSuite.hpp"

class PreProc_TestSuite : public chaos::test::TestSuite
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    PreProc_TestSuite();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void registerTestUnits();
};

#endif
