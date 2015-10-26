#include "chaoscore/test/log_formatter/PlainTestLogFormatter.hpp"

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

PlainTestLogFormatter::PlainTestLogFormatter(
        chaos::uint16 verbosity, std::ostream* stream )
    :
    AbstractTestLogFormatter( verbosity, stream )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void PlainTestLogFormatter::open_log()
{
    // do nothing for plain text
}

void PlainTestLogFormatter::close_log(
        chaos::uint64 success_count,
        chaos::uint64 failure_count )
{
    // do nothing for plain text
}

void PlainTestLogFormatter::open_test(
        const chaos::str::UTF8String& path,
        const chaos::str::UTF8String& id )
{
    // TODO:
}

void PlainTestLogFormatter::close_test()
{
    // TODO:
}

void PlainTestLogFormatter::report_success(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line )
{
    // TODO:
}

void PlainTestLogFormatter::report_failure(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line,
        const chaos::str::UTF8String& message )
{
    // TODO:
}

void PlainTestLogFormatter::finialise_test_report(
        chaos::uint64 success_count,
        chaos::uint64 failure_count )
{
    // TODO:
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
