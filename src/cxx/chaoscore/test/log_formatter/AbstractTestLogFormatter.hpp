/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_LOGFORMATTER_ABSTRACTTESTLOGFORMATTER_HPP_
#define CHAOSCORE_TEST_LOGFORMATTER_ABSTRACTTESTLOGFORMATTER_HPP_

#include <iosfwd>
#include <map>
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
    AbstractTestLogFormatter( chaos::uint16 verbosity, std::ostream* stream );

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

    virtual void close_log(
            chaos::int32  units_passed,
            chaos::int32  units_failed,
            chaos::int32  units_errored,
            chaos::uint64 checks_passed,
            chaos::uint64 checks_failed ) = 0;

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

    virtual void finialise_test_report(
            chaos::uint64 checks_passed,
            chaos::uint64 checks_failed ) = 0;

protected:

    //--------------------------------------------------------------------------
    //                            PROTECTED ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The verbosity level of the formatter.
     */
    chaos::uint16 m_verbosity;
    /*!
     * \brief The stream this logger is writing to.
     */
    std::ostream* m_stream;
    /*!
     * \brief mapping from log message to the number of times they've occurred.
     */
    std::map< chaos::str::UTF8String, chaos::uint64 > m_occurrence_map;

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Adds an occurrence of a log entry to the occurrence map.
     */
    void add_occurrence( const chaos::str::UTF8String& entry );
};

} // namespace log_formatter
} // namespace test
} // namespace chaos

#endif
