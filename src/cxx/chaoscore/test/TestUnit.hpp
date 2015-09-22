/*!
 * \file
 *
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_TESTUNIT_HPP_
#define CHAOSCORE_TEST_TESTUNIT_HPP_

#include "chaoscore/base/Preproc.hpp"

#include <string>

namespace chaos
{
namespace test
{

/*!
 * \brief TODO: DOC
 *
 * TODO: DOC
 */
class TestUnit
{
private:

    CHAOS_DISALLOW_COPY_AND_ASSIGN( TestUnit );

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * TODO: DOC
     */
    TestUnit( const std::string& name );

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~TestUnit()
    {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    //----------------------------VIRTUAL FUNCTIONS-----------------------------

    /*!
     * \brief Member function intended to be overridden to setup the fixture
     *        for this particular unit test.
     *
     * This function will be called just before the run member function is
     * called.
     *
     * TODO: how to deal with failure, through function or through exception?
     */
    virtual void setup();

    /*!
     * \brief Member function intended to be overridden to clean up the fixture
     *        set up by this unit test.
     *
     * The function will be called after the run member function has been
     * executed, whether or not it completed successfully.
     *
     * TODO: how to deal with error
     */
    virtual void teardown();

    /*!
     * \brief Member function intended to be overridden in order to run this
     *        unit test.
     *
     * This function must be implemented in derived classes and is where you
     * should do the actual testing. From here test results will be recorded
     * to disk. A critical failure (such as a segmentation fault) in this
     * function will not interfere with the test process as a whole, however it
     * will cause this function to abort, therefore some test may not run.
     */
    virtual void run() = 0;

    //--------------------------------------------------------------------------

    /*!
     * \return The name of the unit test.
     */
    const std::string& getName() const;

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    std::string m_name;
};

} // namespace test
} // namespace chaos

#endif
