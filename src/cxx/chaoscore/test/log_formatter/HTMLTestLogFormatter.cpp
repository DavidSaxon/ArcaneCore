#include "chaoscore/test/log_formatter/HTMLTestLogFormatter.hpp"

#include <ostream>

namespace chaos
{
namespace test
{
namespace log_formatter
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

HTMLTestLogFormatter::HTMLTestLogFormatter(
        chaos::uint16 verbosity, std::ostream* stream )
    :
    AbstractTestLogFormatter( verbosity, stream )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void HTMLTestLogFormatter::open_log()
{
    // TODO:
}

void HTMLTestLogFormatter::close_log(
        chaos::int32  units_passed,
        chaos::int32  units_failed,
        chaos::int32  units_errored,
        chaos::uint64 checks_passed,
        chaos::uint64 checks_failed )
{
    // TODO:
}

void HTMLTestLogFormatter::open_test(
        const chaos::str::UTF8String& path,
        const chaos::str::UTF8String& id )
{
    // TODO:
}

void HTMLTestLogFormatter::close_test()
{
    // TODO:
}

void HTMLTestLogFormatter::report_check_pass(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line )
{
    // TODO:
}

void HTMLTestLogFormatter::report_check_fail(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line,
        const chaos::str::UTF8String& message )
{
    // TODO:
}

void HTMLTestLogFormatter::finialise_test_report(
        chaos::uint64 checks_passed,
        chaos::uint64 checks_failed )
{
    // TODO:
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
