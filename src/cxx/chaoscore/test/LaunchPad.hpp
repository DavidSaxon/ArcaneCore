/**
  * \file
  *
  * \author David Saxon
  */
#ifndef CHAOSCORE_TEST_LAUNCHPAD_HPP_
#define CHAOSCORE_TEST_LAUNCHPAD_HPP_

#include <map>

#include "chaoscore/base/Types.hpp"
#include "chaoscore/base/string/UTF8String.hpp"

namespace chaos
{
namespace test
{

//------------------------------------------------------------------------------
//                             FORWARD DECELERATIONS
//------------------------------------------------------------------------------

class TestSuite;

/**
  * \brief TODO: DOC
  *
  * TODO: DOC
  *
  * \attention This object is disallows copying or assignment.
  */
class LaunchPad
{
private:

    CHAOS_DISALLOW_COPY_AND_ASSIGN( LaunchPad );

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /**
      * TODO: DOC
      */
    LaunchPad( chaos::uint64 options = 0UL );

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~LaunchPad();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /**
      * TODO: DOC
      */
    void registerTestSuite( TestSuite* suite );

    /**
      * TODO: DOC
      */
    // TODO: RENAME
    void init( int argc, char* argv[] );

    /**
      * TODO: DOC
      */
    int execute();

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    // the list of test suites registered by this launch pad
    std::map< chaos::str::UTF8String, TestSuite* > m_registeredSuites;

};

} // namespace test
} // namespace chaos

#endif
