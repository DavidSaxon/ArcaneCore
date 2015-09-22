/**
  * \file
  *
  * \author David Saxon
  */
#ifndef CHAOSCORE_TEST_TESTSUITE_HPP_
#define CHAOSCORE_TEST_TESTSUITE_HPP_

#include "chaoscore/base/Preproc.hpp"
#include "chaoscore/base/string/UTF8String.hpp"

#include <vector>

namespace chaos
{
namespace test
{

//------------------------------------------------------------------------------
//                             FORWARD DECELERATIONS
//------------------------------------------------------------------------------

class TestUnit;

/**
  * \brief TODO: DOC
  *
  * TODO: DOC
  */
class TestSuite
{
private:

    CHAOS_DISALLOW_COPY_AND_ASSIGN( TestSuite );

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /**
      * TODO: DOC
      */
    TestSuite( const chaos::str::UTF8String& name );

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~TestSuite()
    {
        // TODO:
        // delete the unit test registered under this suite
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    //----------------------------VIRTUAL FUNCTIONS-----------------------------

    /**
      * \brief Member function intended to be overridden to register unit tests
      *        within this suite.
      *
      * This function will be called once the LaunchPad has constructed an
      * instance of this object. This process should not perform an actions that
      * can fail, simply register subsequent TestUnit objects.
      *
      * \attention This function is abstract so must be overridden.
      */
    virtual void registerTestUnits() = 0;

    /**
      * \brief Member function intended to be overridden to setup the fixture
      *        for this suite.
      *
      * This function will be called just before the TestUnit objects registered
      * by this suite are run. This function should not perform actions that can
      * suffer from critical failure, but may fail to setup the environment.
      *
      * TODO: how to deal with failure? Exception or function call, bool return
      */
    virtual void setup();

    /**
      * \brief Member function intended to be overridden to clean up the fixture
      *        setup by this suite.
      *
      * This function will be called after execution of all TestUnit objects
      * registered by this suite have finished execution, whether or not they
      * have executed successfully. This function should not risk critical
      * failure, but may fail to clean up the environment.
      *
      * TODO: how to deal with failure?
      */
    virtual void teardown();

    //--------------------------------------------------------------------------

    /**
      * \return The name of this test suite
      */
    const chaos::str::UTF8String& getName() const;

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /**
      * TODO: DOC
      */
    void registerTestUnit( TestUnit* unit );

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    // he name of this this test suite
    chaos::str::UTF8String m_name;
    // the list of test units registered under this suite
    std::vector< TestUnit* > m_units;
};

} // namespace test
} // namespace chaos

#endif
