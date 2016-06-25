#include "arcanecore/test/log_formatter/HTMLTestLogFormatter.hpp"

#include <ostream>

namespace arc
{
namespace test
{
namespace log_formatter
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

HTMLTestLogFormatter::HTMLTestLogFormatter(
        arc::uint16 verbosity, std::ostream* stream)
    :
    AbstractTestLogFormatter(verbosity, stream)
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
        arc::int32 units_passed,
        arc::int32 units_failed,
        arc::int32 units_errored,
        arc::uint64 checks_passed,
        arc::uint64 checks_failed)
{
    // TODO:
}

void HTMLTestLogFormatter::open_test(
        const arc::str::UTF8String& path,
        const arc::str::UTF8String& id)
{
    // TODO:
}

void HTMLTestLogFormatter::close_test()
{
    // TODO:
}

void HTMLTestLogFormatter::report_crash(const arc::str::UTF8String& info)
{
    // TODO:
}

void HTMLTestLogFormatter::report_check_pass(
        const arc::str::UTF8String& type,
        const arc::str::UTF8String& file,
        arc::int32 line)
{
    // TODO:
}

void HTMLTestLogFormatter::report_check_fail(
        const arc::str::UTF8String& type,
        const arc::str::UTF8String& file,
        arc::int32 line,
        const arc::str::UTF8String& message)
{
    // TODO:
}

void HTMLTestLogFormatter::write_message(
        const arc::str::UTF8String& message)
{
    // TODO:
}

void HTMLTestLogFormatter::finialise_test_report(
        arc::uint64 checks_passed,
        arc::uint64 checks_failed)
{
    // TODO:
}

} // namespace log_formatter
} // namespace test
} // namespace arc
