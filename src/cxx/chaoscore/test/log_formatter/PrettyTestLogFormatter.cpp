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

void PrettyTestLogFormatter::close_log(
        chaos::int32  units_passed,
        chaos::int32  units_failed,
        chaos::int32  units_errored,
        chaos::uint64 checks_passed,
        chaos::uint64 checks_failed )
{
    // verbosity 2+
    if ( m_verbosity < 2 )
    {
        return;
    }

    chaos::int32 unit_total = units_passed + units_failed + units_errored;
    chaos::uint32 unit_pass_percent = static_cast< chaos::uint32 > (
            ( static_cast< float >( units_passed ) /
              static_cast< float >( unit_total   )   )
            * 100.0F
    );

    chaos::uint64 check_total = checks_passed + checks_failed;
    chaos::uint32 check_pass_percent = static_cast< chaos::uint32 > (
            ( static_cast< float >( checks_passed ) /
              static_cast< float >( check_total   )   )
            * 100.0F
    );

    chaos::str::UTF8String divider( "=" );
    divider *= 79;
    chaos::str::UTF8String message;

    chaos::str::UTF8String intro( "All Tests Completed" );
    chaos::io::format::centre_text( intro, 79, true );

    chaos::str::UTF8String unit_summary( "-- Summary for " );
    unit_summary << unit_total << " Unit Tests --";
    chaos::io::format::centre_text( unit_summary, 79, true );

    chaos::str::UTF8String unit_count;
    unit_count << "Passed: " << units_passed << " Failed: " << units_failed;
    chaos::io::format::centre_text( unit_count, 79, true );

    chaos::str::UTF8String unit_percent;
    unit_percent << unit_pass_percent << "% pass rate";
    chaos::io::format::centre_text( unit_percent, 79, true );

    chaos::str::UTF8String check_summary( "-- Summary for " );
    check_summary << check_total << " Checks --";
    chaos::io::format::centre_text( check_summary, 79, true );

    chaos::str::UTF8String check_count;
    check_count << "Passed: " << checks_passed << " Failed: " << checks_failed;
    chaos::io::format::centre_text( check_count, 79, true );

    chaos::str::UTF8String check_percent;
    check_percent << check_pass_percent << "% pass rate";
    chaos::io::format::centre_text( check_percent, 79, true );

    message << divider << "\n" << intro << "\n" << divider << "\n"
            << unit_summary << "\n" << unit_count << "\n" << unit_percent
            << "\n" << divider << "\n" << check_summary << "\n" << check_count
            << "\n" << check_percent << "\n" << divider << "\n";

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
    // verbosity 2+
    if ( m_verbosity < 2 )
    {
        return;
    }

    chaos::str::UTF8String message( "..." );
    chaos::io::format::centre_text( message, 79, true );

    // colourise
    if ( m_use_ansi )
    {
        chaos::io::format::apply_escape_sequence(
                message,
                chaos::io::format::ANSI_FG_WHITE
        );
    }

    // write to stream
    ( *m_stream ) << message << "\n" << std::endl;
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
            // write stream
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
        // write to stream
        ( *m_stream ) << entry << std::endl;
    }
}

void PrettyTestLogFormatter::finialise_test_report(
        chaos::uint64 checks_passed,
        chaos::uint64 checks_failed )
{
    // write collected reports
    if ( m_verbosity <= 3 )
    {
        CHAOS_FOR_EACH( it, m_occurrence_map )
        {
            chaos::str::UTF8String message( it->first.substring( 0 , 10 ) );
            message << " [ occurrences: " << it->second << " ]";
            message << it->first.substring( 10 , it->first.get_length() );

            // colourise
            if ( m_use_ansi )
            {
                if ( message.starts_with( " - Failed:" ) )
                {
                    chaos::io::format::apply_escape_sequence(
                            message,
                            chaos::io::format::ANSI_FG_RED
                    );
                }
                else
                {
                    chaos::io::format::apply_escape_sequence(
                            message,
                            chaos::io::format::ANSI_FG_LIGHT_GREEN
                    );

                }
            }
            // write to stream
            ( *m_stream ) << message << std::endl;

        }
    }

    // verbosity 2+
    if ( m_verbosity < 2 )
    {
        return;
    }

    chaos::uint64 total_count = checks_passed + checks_failed;
    chaos::uint32 pass_percent = static_cast< chaos::uint32 > (
            ( static_cast< float >( checks_passed ) /
              static_cast< float >( total_count )      )
            * 100.0F
    );

    chaos::str::UTF8String divider( "+" );
    divider *= 79;

    chaos::str::UTF8String summary( "-- Summary for " );
    summary << total_count << " Checks --";
    chaos::io::format::centre_text( summary, 79, true );

    chaos::str::UTF8String counts;
    counts << "Passed: " << checks_passed << " Failed: " << checks_failed;
    chaos::io::format::centre_text( counts, 79, true );

    chaos::str::UTF8String percent;
    percent << pass_percent << "% pass rate";
    chaos::io::format::centre_text( percent, 79, true );

    // colourise
    if ( m_use_ansi )
    {
        chaos::io::format::apply_escape_sequence(
                divider,
                chaos::io::format::ANSI_FG_LIGHT_BLUE
        );
        chaos::io::format::apply_escape_sequence(
                summary,
                chaos::io::format::ANSI_FG_LIGHT_BLUE,
                chaos::io::format::ANSI_ATTR_BOLD
        );
        chaos::io::format::apply_escape_sequence(
                counts,
                chaos::io::format::ANSI_FG_WHITE
        );
        if ( pass_percent <= 25 )
        {
            chaos::io::format::apply_escape_sequence(
                    percent,
                    chaos::io::format::ANSI_FG_RED
            );
        }
        else if ( pass_percent <= 50 )
        {
            chaos::io::format::apply_escape_sequence(
                    percent,
                    chaos::io::format::ANSI_FG_MAGENTA
            );
        }
        else if ( pass_percent <= 75 )
        {
            chaos::io::format::apply_escape_sequence(
                    percent,
                    chaos::io::format::ANSI_FG_LIGHT_YELLOW
            );
        }
        else
        {
            chaos::io::format::apply_escape_sequence(
                    percent,
                    chaos::io::format::ANSI_FG_GREEN
            );
        }
    }

    // write to stream
    chaos::str::UTF8String message;
    message << "\n" << divider << "\n" << summary << "\n" << counts << "\n"
            << percent << "\n" << divider << "\n";
    ( *m_stream ) << message << std::endl;
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
