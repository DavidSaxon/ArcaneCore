#include "chaoscore/test/log_formatter/PrettyTestLogFormatter.hpp"

#include <ostream>

#include "chaoscore/io/format/ANSI.hpp"
#include "chaoscore/io/format/FormatUtil.hpp"

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
            << "__/_/   \\___/  /_/  \\___/____/\\__/____/\n" << divider
            << "\n";

    // colourise
    if ( m_use_ansi )
    {
        chaos::io::format::apply_escape_sequence(
                message,
                chaos::io::format::ANSI_FG_LIGHT_CYAN,
                chaos::io::format::ANSI_ATTR_BOLD
        );
    }
    // write to stream
    ( *m_stream ) << message << std::endl;
}

void PrettyTestLogFormatter::close_log()
{
    // verbosity 2+
    if ( m_verbosity < 2 )
    {
        return;
    }

    chaos::str::UTF8String divider( "=" );
    divider *= 79;
    chaos::str::UTF8String message;

    chaos::str::UTF8String t( "All Tests Completed" );
    chaos::io::format::centre_text( t, 79, true );

    message << divider << "\n" << t << "\n" << divider;
    // colourise
    if ( m_use_ansi )
    {
        chaos::io::format::apply_escape_sequence(
                message,
                chaos::io::format::ANSI_FG_LIGHT_CYAN,
                chaos::io::format::ANSI_ATTR_BOLD
        );
    }
    // write to stream
    ( *m_stream ) << message << std::endl;
}

void PrettyTestLogFormatter::open_test(
        const chaos::str::UTF8String& path,
        const chaos::str::UTF8String& id )
{
    chaos::str::UTF8String divider( "-" );
    divider *= 79;
    chaos::str::UTF8String intro( "Running Unit Test:" );
    chaos::io::format::centre_text( intro, 79, true );
    chaos::str::UTF8String divider_2( "---" );
    chaos::io::format::centre_text( divider_2, 79, true );
    chaos::str::UTF8String path_f( path );
    chaos::io::format::centre_text( path_f, 79, true );

    // colourise
    if ( m_use_ansi )
    {
        chaos::io::format::apply_escape_sequence(
                divider,
                chaos::io::format::ANSI_FG_WHITE
        );
        chaos::io::format::apply_escape_sequence(
                intro,
                chaos::io::format::ANSI_FG_WHITE
        );
        chaos::io::format::apply_escape_sequence(
                divider_2,
                chaos::io::format::ANSI_FG_WHITE
        );
        chaos::io::format::apply_escape_sequence(
                path_f,
                chaos::io::format::ANSI_FG_LIGHT_YELLOW,
                chaos::io::format::ANSI_ATTR_BOLD
        );
    }

    // write to stream
    chaos::str::UTF8String message;
    message << divider << "\n" << intro << "\n" << divider_2 << "\n" << path_f
            << "\n" << divider << "\n";
    ( *m_stream ) << message << std::endl;
}

void PrettyTestLogFormatter::close_test()
{
    // do nothing
}

void PrettyTestLogFormatter::report_success(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line )
{
    // verbosity 3+
    if ( m_verbosity >= 3 )
    {
        chaos::str::UTF8String entry;
        entry << " + Passed: " << type << " at line: " << line;

        // store occurrence
        if ( m_verbosity <= 3 )
        {
            add_occurrence( entry );
        }
        // or print
        else
        {
            // colourise
            if ( m_use_ansi )
            {
                chaos::io::format::apply_escape_sequence(
                        entry,
                        chaos::io::format::ANSI_FG_LIGHT_GREEN
                );
            }
            ( *m_stream ) << entry << std::endl;
        }
    }
}

void PrettyTestLogFormatter::report_failure(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line,
        const chaos::str::UTF8String& message )
{
    chaos::str::UTF8String entry;
    entry << " - Failed: " << type << ": " << message << " at line: " << line;

    // store occurrence
    if ( m_verbosity <= 3 )
    {
        add_occurrence( entry );
    }
    // or print
    else
    {
        // colourise
        if ( m_use_ansi )
        {
            chaos::io::format::apply_escape_sequence(
                    entry,
                    chaos::io::format::ANSI_FG_RED
            );
        }
        ( *m_stream ) << entry << std::endl;
    }
}

void PrettyTestLogFormatter::finialise_test_report(
        chaos::uint64 success_count,
        chaos::uint64 failure_count )
{
    // TODO: collected entries

    // verbosity 2+
    if ( m_verbosity < 2 )
    {
        return;
    }

    chaos::uint64 total_count = success_count + failure_count;
    chaos::uint32 percent =
            ( static_cast< float >( success_count ) /
              static_cast< float >( total_count )      )
            * 100;

    chaos::str::UTF8String divider( "+" );
    divider *= 79;
    chaos::str::UTF8String intro( "Unit Test Summary:" );
    chaos::io::format::centre_text( intro, 79, true );
    chaos::str::UTF8String total( "Total Tests : " );
    total << ( success_count + failure_count );
    chaos::io::format::centre_text( total, 79, true );
    chaos::str::UTF8String passes( "Passed      : " );
    passes << success_count;
    chaos::io::format::centre_text( passes, 79, true );
    chaos::str::UTF8String failures( "Failed      : " );
    failures << failure_count;
    chaos::io::format::centre_text( failures, 79, true );
    chaos::str::UTF8String pass_percent;
    pass_percent << percent << "% pass rate.";
    chaos::io::format::centre_text( pass_percent, 79, true );

    // colourise
    if ( m_use_ansi )
    {
        chaos::io::format::apply_escape_sequence(
                divider,
                chaos::io::format::ANSI_FG_LIGHT_BLUE
        );
        chaos::io::format::apply_escape_sequence(
                intro,
                chaos::io::format::ANSI_FG_LIGHT_BLUE,
                chaos::io::format::ANSI_ATTR_BOLD
        );
        chaos::io::format::apply_escape_sequence(
                total,
                chaos::io::format::ANSI_FG_WHITE
        );
        chaos::io::format::apply_escape_sequence(
                passes,
                chaos::io::format::ANSI_FG_WHITE
        );
        chaos::io::format::apply_escape_sequence(
                failures,
                chaos::io::format::ANSI_FG_WHITE
        );
        if ( percent <= 25 )
        {
            chaos::io::format::apply_escape_sequence(
                    pass_percent,
                    chaos::io::format::ANSI_FG_RED
            );
        }
        else if ( percent <= 50 )
        {
            chaos::io::format::apply_escape_sequence(
                    pass_percent,
                    chaos::io::format::ANSI_FG_MAGENTA
            );
        }
        else if ( percent <= 75 )
        {
            chaos::io::format::apply_escape_sequence(
                    pass_percent,
                    chaos::io::format::ANSI_FG_LIGHT_YELLOW
            );
        }
        else
        {
            chaos::io::format::apply_escape_sequence(
                    pass_percent,
                    chaos::io::format::ANSI_FG_GREEN
            );
        }
    }

    // write to stream
    chaos::str::UTF8String message;
    message << "\n" << divider << "\n" << intro << "\n" << total << "\n"
            << passes << "\n" << failures << "\n" << pass_percent << "\n"
            << divider << "\n";
    ( *m_stream ) << message << std::endl;
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
