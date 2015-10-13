/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_LOGFORMATTER_ABSTRACTTESTLOGFORMATTER_HPP_
#define CHAOSCORE_TEST_LOGFORMATTER_ABSTRACTTESTLOGFORMATTER_HPP_

#include <iosfwd>
#include <vector>

namespace chaos
{
namespace test
{
namespace log_formatter
{

/*!
 * \brief Abstract base class that all other Test Log Formatters will inherit
 *        from.
 *
 * Test Log Formatters provided functions for formatting data to log and then
 * writing it to it's output stream.
 */
class AbstractTestLogFormatter
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Super constructor for Test Log Formatters.
     *
     * \param stream the stream to write logs to.
     */
    AbstractTestLogFormatter( std::ostream* stream )
        :
        m_stream( stream )
    {
    }

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~AbstractTestLogFormatter()
    {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void openLog() = 0;

    virtual void closeLog() = 0;

protected:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The stream this logger is writing to.
     */
    std::ostream* m_stream;
};

} // namespace log_formatter
} // namespace test
} // namespace chaos

#endif
