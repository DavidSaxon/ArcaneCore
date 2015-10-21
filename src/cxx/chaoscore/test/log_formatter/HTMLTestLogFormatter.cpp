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
        chaos::uint8 verbosity, std::ostream* stream )
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

void HTMLTestLogFormatter::close_log()
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

void HTMLTestLogFormatter::report_success(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line )
{
    // TODO:
}

void HTMLTestLogFormatter::report_failure(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line,
        const chaos::str::UTF8String& message )
{
    // TODO:
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
