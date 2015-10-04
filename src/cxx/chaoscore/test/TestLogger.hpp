/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_LOGGER_HPP_
#define CHAOSCORE_TEST_LOGGER_HPP_

#include "chaoscore/base/Preproc.hpp"
#include "chaoscore/base/string/UTF8String.hpp"

namespace chaos
{
namespace test
{

/*!
 * \brief TODO: DOC
 *
 * TODO: DOC
 */
class TestLogger
{
private:

    CHAOS_DISALLOW_COPY_AND_ASSIGN( TestLogger );

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new TestLogger instance.
     */
    TestLogger();

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~TestLogger();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Initialises this TestLogger instance.
     *
     * This function should only be called once, before an other calls to the
     * logger are made.
     *
     * \param output The output file to write test logs to. If output is set to
     *               "stdout" the logger will write to std::cout rather than to
     *               disk.
     */
    void init( const chaos::str::UTF8String& output );

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    // the output stream being used by the logger
    std::ostream* m_stream;
    // whether stdout is being used or not
    bool m_stdout;
};

} // namespace test
} // namespace chaos

#endif
