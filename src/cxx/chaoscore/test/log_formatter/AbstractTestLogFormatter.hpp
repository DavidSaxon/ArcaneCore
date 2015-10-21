/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_LOGFORMATTER_ABSTRACTTESTLOGFORMATTER_HPP_
#define CHAOSCORE_TEST_LOGFORMATTER_ABSTRACTTESTLOGFORMATTER_HPP_

#include <iosfwd>
#include <vector>

#include "chaoscore/base/string/UTF8String.hpp"

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
     * \param verbosity The level of verbosity of the formatter.
     * \param stream The stream to write logs to.
     */
    AbstractTestLogFormatter( chaos::uint8 verbosity, std::ostream* stream )
        :
        m_verbosity( verbosity ),
        m_stream   ( stream )
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

    virtual void open_log() = 0;

    virtual void close_log() = 0;

    virtual void open_test(
            const chaos::str::UTF8String& path,
            const chaos::str::UTF8String& id ) = 0;

    virtual void close_test() = 0;

    virtual void report_success(
            const chaos::str::UTF8String& type,
            const chaos::str::UTF8String& file,
                  chaos::int32            line ) = 0;

    virtual void report_failure(
            const chaos::str::UTF8String& type,
            const chaos::str::UTF8String& file,
                  chaos::int32            line,
            const chaos::str::UTF8String& message ) = 0;

protected:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The verbosity level of the formatter.
     */
    chaos::uint8 m_verbosity;
    /*!
     * \brief The stream this logger is writing to.
     */
    std::ostream* m_stream;
};

} // namespace log_formatter
} // namespace test
} // namespace chaos

#endif
