#include "chaoscore/test/log_formatter/PrettyTestLogFormatter.hpp"

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

PrettyTestLogFormatter::PrettyTestLogFormatter(
        chaos::uint8 verbosity, std::ostream* stream )
    :
    AbstractTestLogFormatter( verbosity, stream )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void PrettyTestLogFormatter::open_log()
{
    ( *m_stream ) << "ChaosCore Tests" << std::endl;
}

void PrettyTestLogFormatter::close_log()
{
    // TODO:
}

void PrettyTestLogFormatter::open_test(
        const chaos::str::UTF8String& path,
        const chaos::str::UTF8String& id )
{
    // TODO:
}

void PrettyTestLogFormatter::close_test()
{
    // TODO:
}

void PrettyTestLogFormatter::report_success(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line )
{
    // TODO:
}

void PrettyTestLogFormatter::report_failure(
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
