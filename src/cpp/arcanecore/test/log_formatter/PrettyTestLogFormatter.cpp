#include "arcanecore/test/log_formatter/PrettyTestLogFormatter.hpp"

#include <ostream>

#include "arcanecore/io/format/ANSI.hpp"
#include "arcanecore/io/format/FormatOperations.hpp"

namespace arc
{
namespace test
{
namespace log_formatter
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

PrettyTestLogFormatter::PrettyTestLogFormatter(
        arc::uint16 verbosity,
        std::ostream* stream,
        bool is_stdout)
    :
    AbstractTestLogFormatter(verbosity, stream),
    m_use_ansi              (false)
{
    // should we use ANSI escape sequences or not?
    #ifdef ARC_OS_UNIX
        m_use_ansi = is_stdout;
    #endif
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void PrettyTestLogFormatter::open_log()
{
    // verbosity 2+
    if(m_verbosity < 2)
    {
        return;
    }

    arc::str::UTF8String divider("=");
    divider *= 79;

    arc::str::UTF8String message("\n");
    message << divider << "\n   ________                     ______            "
            << "     ______          __\n  / ____/ /_  ____ _____  _____/ ____/"
            << "___  ________   /_  __/__  _____/ /______\n / /   / __ \\/ __ `"
            << "/ __ \\/ ___/ /   / __ \\/ ___/ _ \\   / / / _ \\/ ___/ __/ ___"
            << "/\n/ /___/ / / / /_/ / /_/ (__  ) /___/ /_/ / /  /  __/  / / / "
            << " __(__  ) /_(__  )\n\\____/_/ /_/\\__,_/\\____/____/\\____/\\__"
            << "__/_/   \\___/  /_/  \\___/____/\\__/____/\n" << divider
            << "\n";

    // colourise
    if(m_use_ansi)
    {
        arc::io::format::apply_escape_sequence(
                message,
                arc::io::format::ANSI_FG_LIGHT_CYAN,
                arc::io::format::ANSI_ATTR_BOLD
        );
    }
    // write to stream
    (*m_stream) << message << std::endl;
}

void PrettyTestLogFormatter::close_log(
        arc::int32 units_passed,
        arc::int32 units_failed,
        arc::int32 units_errored,
        arc::uint64 checks_passed,
        arc::uint64 checks_failed)
{
    // verbosity 2+
    if(m_verbosity < 2)
    {
        return;
    }

    arc::int32 unit_total = units_passed + units_failed + units_errored;
    arc::uint32 unit_pass_percent = static_cast< arc::uint32 > (
            (static_cast< float >(units_passed) /
              static_cast< float >(unit_total  )  )
            * 100.0F
    );

    arc::uint64 check_total = checks_passed + checks_failed;
    arc::uint32 check_pass_percent = static_cast< arc::uint32 > (
            (static_cast< float >(checks_passed) /
              static_cast< float >(check_total  )  )
            * 100.0F
    );

    arc::str::UTF8String divider("=");
    divider *= 79;
    arc::str::UTF8String message;

    arc::str::UTF8String intro("All Tests Completed");
    arc::io::format::centre_text(intro, 79, true);

    arc::str::UTF8String unit_summary("-- Summary for ");
    unit_summary << unit_total << " Unit Tests --";
    arc::io::format::centre_text(unit_summary, 79, true);

    arc::str::UTF8String unit_count;
    unit_count << "Passed: " << units_passed << " - Failed: " << units_failed
               << " - Errored: " << units_errored;
    arc::io::format::centre_text(unit_count, 79, true);

    arc::str::UTF8String unit_percent;
    unit_percent << unit_pass_percent << "% pass rate";
    arc::io::format::centre_text(unit_percent, 79, true);

    arc::str::UTF8String check_summary("-- Summary for ");
    check_summary << check_total << " Checks --";
    arc::io::format::centre_text(check_summary, 79, true);

    arc::str::UTF8String check_count;
    check_count << "Passed: " << checks_passed << " - Failed: "
                << checks_failed;
    arc::io::format::centre_text(check_count, 79, true);

    arc::str::UTF8String check_percent;
    check_percent << check_pass_percent << "% pass rate";
    arc::io::format::centre_text(check_percent, 79, true);

    // colourise
    if(m_use_ansi)
    {
        arc::io::format::apply_escape_sequence(
                divider,
                arc::io::format::ANSI_FG_LIGHT_CYAN
        );
        arc::io::format::apply_escape_sequence(
                intro,
                arc::io::format::ANSI_FG_LIGHT_CYAN
        );
        arc::io::format::apply_escape_sequence(
                unit_summary,
                arc::io::format::ANSI_FG_LIGHT_BLUE,
                arc::io::format::ANSI_ATTR_BOLD
        );
        arc::io::format::apply_escape_sequence(
                unit_count,
                arc::io::format::ANSI_FG_WHITE
        );
        if(unit_pass_percent <= 25)
        {
            arc::io::format::apply_escape_sequence(
                    unit_percent,
                    arc::io::format::ANSI_FG_RED,
                    arc::io::format::ANSI_ATTR_BLINK
            );
        }
        else if(unit_pass_percent <= 50)
        {
            arc::io::format::apply_escape_sequence(
                    unit_percent,
                    arc::io::format::ANSI_FG_MAGENTA,
                    arc::io::format::ANSI_ATTR_BLINK
            );
        }
        else if(unit_pass_percent < 100)
        {
            arc::io::format::apply_escape_sequence(
                    unit_percent,
                    arc::io::format::ANSI_FG_LIGHT_YELLOW,
                    arc::io::format::ANSI_ATTR_BLINK
            );
        }
        else
        {
            arc::io::format::apply_escape_sequence(
                    unit_percent,
                    arc::io::format::ANSI_FG_GREEN
            );
        }
        arc::io::format::apply_escape_sequence(
                check_summary,
                arc::io::format::ANSI_FG_LIGHT_BLUE,
                arc::io::format::ANSI_ATTR_BOLD
        );
        arc::io::format::apply_escape_sequence(
                check_count,
                arc::io::format::ANSI_FG_WHITE
        );
        if(check_pass_percent <= 25)
        {
            arc::io::format::apply_escape_sequence(
                    check_percent,
                    arc::io::format::ANSI_FG_RED,
                    arc::io::format::ANSI_ATTR_BLINK
            );
        }
        else if(check_pass_percent <= 50)
        {
            arc::io::format::apply_escape_sequence(
                    check_percent,
                    arc::io::format::ANSI_FG_MAGENTA,
                    arc::io::format::ANSI_ATTR_BLINK
            );
        }
        else if(check_pass_percent < 100)
        {
            arc::io::format::apply_escape_sequence(
                    check_percent,
                    arc::io::format::ANSI_FG_LIGHT_YELLOW,
                    arc::io::format::ANSI_ATTR_BLINK
            );
        }
        else
        {
            arc::io::format::apply_escape_sequence(
                    check_percent,
                    arc::io::format::ANSI_FG_GREEN
            );
        }
    }


    message << divider << "\n" << intro << "\n" << divider << "\n"
            << unit_summary << "\n" << unit_count << "\n" << unit_percent
            << "\n" << divider << "\n" << check_summary << "\n" << check_count
            << "\n" << check_percent << "\n" << divider << "\n";

    // colourise
    if(m_use_ansi)
    {
        arc::io::format::apply_escape_sequence(
                message,
                arc::io::format::ANSI_FG_LIGHT_CYAN,
                arc::io::format::ANSI_ATTR_BOLD
        );
    }
    // write to stream
    (*m_stream) << message << std::endl;
}

void PrettyTestLogFormatter::open_test(
        const arc::str::UTF8String& path,
        const arc::str::UTF8String& id)
{
    arc::str::UTF8String divider("-");
    divider *= 79;
    arc::str::UTF8String intro("Running Unit Test:");
    arc::io::format::centre_text(intro, 79, true);
    arc::str::UTF8String divider_2("---");
    arc::io::format::centre_text(divider_2, 79, true);
    arc::str::UTF8String path_f(path);
    arc::io::format::centre_text(path_f, 79, true);

    // colourise
    if(m_use_ansi)
    {
        arc::io::format::apply_escape_sequence(
                divider,
                arc::io::format::ANSI_FG_WHITE
        );
        arc::io::format::apply_escape_sequence(
                intro,
                arc::io::format::ANSI_FG_WHITE
        );
        arc::io::format::apply_escape_sequence(
                divider_2,
                arc::io::format::ANSI_FG_WHITE
        );
        arc::io::format::apply_escape_sequence(
                path_f,
                arc::io::format::ANSI_FG_LIGHT_YELLOW,
                arc::io::format::ANSI_ATTR_BOLD
        );
    }

    // write to stream
    arc::str::UTF8String message;
    message << divider << "\n" << intro << "\n" << divider_2 << "\n" << path_f
            << "\n" << divider << "\n";
    (*m_stream) << message << std::endl;
}

void PrettyTestLogFormatter::close_test()
{
    // verbosity 2+
    if(m_verbosity < 2)
    {
        return;
    }

    arc::str::UTF8String message("...");
    arc::io::format::centre_text(message, 79, true);

    // colourise
    if(m_use_ansi)
    {
        arc::io::format::apply_escape_sequence(
                message,
                arc::io::format::ANSI_FG_WHITE
        );
    }

    // write to stream
    (*m_stream) << message << "\n" << std::endl;
}

void PrettyTestLogFormatter::report_crash(const arc::str::UTF8String& info)
{
    arc::str::UTF8String message;
    message << "CRITICAL ERROR. Test failed with exit code: " << info;

    // colourise
    if(m_use_ansi)
    {
        arc::io::format::apply_escape_sequence(
                message,
                arc::io::format::ANSI_FG_RED,
                arc::io::format::ANSI_ATTR_BLINK
        );
    }
    // write stream
    (*m_stream) << message << std::endl;
}

void PrettyTestLogFormatter::report_check_pass(
        const arc::str::UTF8String& type,
        const arc::str::UTF8String& file,
        arc::int32 line)
{
    // verbosity 3+
    if(m_verbosity >= 3)
    {
        arc::str::UTF8String entry;
        entry << " + Passed: " << type << " at line: " << line;

        // store occurrence
        if(m_verbosity <= 3)
        {
            add_occurrence(entry);
        }
        // or print
        else
        {
            // colourise
            if(m_use_ansi)
            {
                arc::io::format::apply_escape_sequence(
                        entry,
                        arc::io::format::ANSI_FG_LIGHT_GREEN
                );
            }
            // write stream
            (*m_stream) << entry << std::endl;
        }
    }
}

void PrettyTestLogFormatter::report_check_fail(
        const arc::str::UTF8String& type,
        const arc::str::UTF8String& file,
        arc::int32 line,
        const arc::str::UTF8String& message)
{
    arc::str::UTF8String entry;
    entry << " - Failed: " << type << ": " << message << " at line: " << line;

    // store occurrence
    if(m_verbosity <= 3)
    {
        add_occurrence(entry);
    }
    // or print
    else
    {
        // colourise
        if(m_use_ansi)
        {
            arc::io::format::apply_escape_sequence(
                    entry,
                    arc::io::format::ANSI_FG_RED
            );
        }
        // write to stream
        (*m_stream) << entry << std::endl;
    }
}

void PrettyTestLogFormatter::write_message(
        const arc::str::UTF8String& message)
{
    // verbosity 3+
    if(m_verbosity < 3)
    {
        return;
    }

    arc::str::UTF8String entry(" -- ");
    entry << message;

    // store occurrence
    if(m_verbosity <= 3)
    {
        add_occurrence(entry);
    }
    // or print
    else
    {
        // colourise
        if(m_use_ansi)
        {
            arc::io::format::apply_escape_sequence(
                    entry,
                    arc::io::format::ANSI_BG_BLUE
            );
        }
        // write to stream
        (*m_stream) << entry << std::endl;
    }
}

void PrettyTestLogFormatter::finialise_test_report(
        arc::uint64 checks_passed,
        arc::uint64 checks_failed)
{
    // write collected reports
    if(m_verbosity <= 3)
    {
        ARC_FOR_EACH(it, m_occurrences)
        {
            arc::str::UTF8String message(it->entry);
            arc::uint64 occurrences = it->count;

            if(occurrences > 1)
            {
                arc::str::UTF8String occ(" [occurrences: ");
                occ << occurrences << "]";

                if(message.get_length() + occ.get_length() < 79)
                {
                    arc::str::UTF8String space(" ");
                    space *= 79 - (message.get_length() + occ.get_length());
                    message += space;
                }

                message << occ;
            }

            // colourise
            if(m_use_ansi)
            {
                if(message.starts_with(" -- "))
                {
                    arc::io::format::apply_escape_sequence(
                            message,
                            arc::io::format::ANSI_BG_BLUE
                    );
                }
                else if(message.starts_with(" - Failed:"))
                {
                    arc::io::format::apply_escape_sequence(
                            message,
                            arc::io::format::ANSI_FG_RED
                    );
                }
                else
                {
                    arc::io::format::apply_escape_sequence(
                            message,
                            arc::io::format::ANSI_FG_LIGHT_GREEN
                    );

                }
            }
            // write to stream
            (*m_stream) << message << std::endl;

        }
    }

    // verbosity 2+
    if(m_verbosity < 2)
    {
        return;
    }

    arc::uint64 total_count = checks_passed + checks_failed;
    arc::uint32 pass_percent = static_cast<arc::uint32> (
            (static_cast<float>(checks_passed) /
              static_cast<float>(total_count)     )
            * 100.0F
    );

    arc::str::UTF8String divider("+");
    divider *= 79;

    arc::str::UTF8String summary("-- Summary for ");
    summary << total_count << " Checks --";
    arc::io::format::centre_text(summary, 79, true);

    arc::str::UTF8String counts;
    counts << "Passed: " << checks_passed << " - Failed: " << checks_failed;
    arc::io::format::centre_text(counts, 79, true);

    arc::str::UTF8String percent;
    percent << pass_percent << "% pass rate";
    arc::io::format::centre_text(percent, 79, true);

    // colourise
    if(m_use_ansi)
    {
        arc::io::format::apply_escape_sequence(
                divider,
                arc::io::format::ANSI_FG_LIGHT_BLUE
        );
        arc::io::format::apply_escape_sequence(
                summary,
                arc::io::format::ANSI_FG_LIGHT_BLUE,
                arc::io::format::ANSI_ATTR_BOLD
        );
        arc::io::format::apply_escape_sequence(
                counts,
                arc::io::format::ANSI_FG_WHITE
        );
        if(pass_percent <= 25)
        {
            arc::io::format::apply_escape_sequence(
                    percent,
                    arc::io::format::ANSI_FG_RED,
                    arc::io::format::ANSI_ATTR_BLINK
            );
        }
        else if(pass_percent <= 50)
        {
            arc::io::format::apply_escape_sequence(
                    percent,
                    arc::io::format::ANSI_FG_MAGENTA,
                    arc::io::format::ANSI_ATTR_BLINK
            );
        }
        else if(pass_percent < 100)
        {
            arc::io::format::apply_escape_sequence(
                    percent,
                    arc::io::format::ANSI_FG_LIGHT_YELLOW,
                    arc::io::format::ANSI_ATTR_BLINK
            );
        }
        else
        {
            arc::io::format::apply_escape_sequence(
                    percent,
                    arc::io::format::ANSI_FG_GREEN
            );
        }
    }

    // write to stream
    arc::str::UTF8String message;
    message << "\n" << divider << "\n" << summary << "\n" << counts << "\n"
            << percent << "\n" << divider << "\n";
    (*m_stream) << message << std::endl;
}

} // namespace log_formatter
} // namespace test
} // namespace arc
