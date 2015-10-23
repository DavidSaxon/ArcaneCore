#include "chaoscore/test/log_formatter/PrettyTestLogFormatter.hpp"

#include <ostream>

#include "chaoscore/io/format/ANSI.hpp"

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
        chaos::uint16 verbosity,
        std::ostream* stream,
        bool          is_stdout )
    :
    AbstractTestLogFormatter( verbosity, stream ),
    m_use_ansi              ( false )
{
    // should we use ANSI escape sequences or not?
    #ifdef CHAOS_OS_UNIX
        m_use_ansi = is_stdout;
    #endif
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void PrettyTestLogFormatter::open_log()
{
    // verbosity 2+
    if ( m_verbosity < 2 )
    {
        return;
    }

    chaos::str::UTF8String divider( "=" );
    divider *= 79;

    chaos::str::UTF8String message( "\n" );
    message << divider << "\n   ________                     ______            "
            << "     ______          __\n  / ____/ /_  ____ _____  _____/ ____/"
            << "___  ________   /_  __/__  _____/ /______\n / /   / __ \\/ __ `"
            << "/ __ \\/ ___/ /   / __ \\/ ___/ _ \\   / / / _ \\/ ___/ __/ ___"
            << "/\n/ /___/ / / / /_/ / /_/ (__  ) /___/ /_/ / /  /  __/  / / / "
            << " __(__  ) /_(__  )\n\\____/_/ /_/\\__,_/\\____/____/\\____/\\__"
            << "__/_/   \\___/  /_/  \\___/____/\\__/____/\n" << divider;

    // colourise
    if ( m_use_ansi )
    {
        message = chaos::io::format::apply_escape_sequence(
                message,
                chaos::io::format::ANSI_FG_LIGHT_CYAN,
                chaos::io::format::ANSI_ATTR_BOLD );
    }
    // write to stream
    ( *m_stream ) << message << std::endl;
}

void PrettyTestLogFormatter::close_log()
{

}

void PrettyTestLogFormatter::open_test(
        const chaos::str::UTF8String& path,
        const chaos::str::UTF8String& id )
{
    // verbosity 2+
    if ( m_verbosity < 2 )
    {
        return;
    }

    chaos::str::UTF8String divider( "=" );
    divider *= 79;
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

void PrettyTestLogFormatter::finialise_test_report(
        chaos::uint64 success_count,
        chaos::uint64 failure_count )
{
    // TODO:
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
