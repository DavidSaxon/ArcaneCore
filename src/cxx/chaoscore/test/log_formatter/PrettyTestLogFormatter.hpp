/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_LOGFORMATTER_PRETTYTESTLOGFORMATTER_HPP_
#define CHAOSCORE_TEST_LOGFORMATTER_PRETTYTESTLOGFORMATTER_HPP_

#include "chaoscore/test/log_formatter/AbstractTestLogFormatter.hpp"

namespace chaos
{
namespace test
{
namespace log_formatter
{

/*!
 * \brief Test Log Formatter that writes logs in pretty formatted text.
 */
class PrettyTestLogFormatter : public AbstractTestLogFormatter
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new Pretty Test Log Formatter.
     */
    PrettyTestLogFormatter(
            chaos::uint16 verbosity,
            std::ostream* stream,
            bool          is_stdout = false );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void open_log();

    virtual void close_log(
            chaos::uint64 success_count,
            chaos::uint64 failure_count );

    virtual void open_test(
            const chaos::str::UTF8String& path,
            const chaos::str::UTF8String& id );

    virtual void close_test();

    virtual void report_success(
            const chaos::str::UTF8String& type,
            const chaos::str::UTF8String& file,
                  chaos::int32            line );

    virtual void report_failure(
            const chaos::str::UTF8String& type,
            const chaos::str::UTF8String& file,
                  chaos::int32            line,
            const chaos::str::UTF8String& message );

    virtual void finialise_test_report(
            chaos::uint64 success_count,
            chaos::uint64 failure_count );

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    bool m_use_ansi;
};

} // namespace log_formatter
} // namespace test
} // namespace chaos

#endif
