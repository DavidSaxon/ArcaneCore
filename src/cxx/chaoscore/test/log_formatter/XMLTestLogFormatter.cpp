#include "chaoscore/test/log_formatter/XMLTestLogFormatter.hpp"

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

XMLTestLogFormatter::XMLTestLogFormatter(
        chaos::uint16 verbosity, std::ostream* stream )
    :
    AbstractTestLogFormatter( verbosity, stream )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void XMLTestLogFormatter::open_log()
{
    ( *m_stream ) << "<ChaosCoreTests>" << std::endl;
}

void XMLTestLogFormatter::close_log(
        chaos::int32  units_passed,
        chaos::int32  units_failed,
        chaos::int32  units_errored,
        chaos::uint64 checks_passed,
        chaos::uint64 checks_failed )
{
    // verbosity 2+
    if ( m_verbosity >= 2 )
    {
        // write summary
        ( *m_stream ) << "  <FinalSummary UnitsPassed=" << units_passed
                      << " UnitsFailed=" << units_failed << " UnitsErrored="
                      << units_errored << " ChecksPassed=" << checks_passed
                      << " ChecksFailed=" << checks_failed << "/>" << std::endl;
    }

    ( *m_stream ) << "</ChaosCoreTests>" << std::endl;
}

void XMLTestLogFormatter::open_test(
        const chaos::str::UTF8String& path,
        const chaos::str::UTF8String& id )
{
    ( *m_stream ) << "  <UnitTest path=\"" << path << "\" id=\""
                  << id << "\">" << std::endl;
}

void XMLTestLogFormatter::close_test()
{
    ( *m_stream ) << "  </UnitTest>" << std::endl;
}

void XMLTestLogFormatter::report_check_pass(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line )
{
    // verbosity 3+
    if ( m_verbosity >= 3 )
    {
        // build the start of the entry
        chaos::str::UTF8String entry;
        entry <<  "    <Success type=" << type << " file=" << file << " line="
              << line;

        // store occurrence
        if ( m_verbosity <= 3 )
        {
            add_occurrence( entry );
        }
        // or print
        else
        {
            ( *m_stream ) << entry << "/>" << std::endl;
        }
    }
}

void XMLTestLogFormatter::report_check_fail(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line,
        const chaos::str::UTF8String& message )
{
    // build the start of the entry
    chaos::str::UTF8String entry;
    entry << "    <Failure type=" << type << " file=" << file << " line="
          << line;
    if ( !message.is_empty() )
    {
        entry << " message=" << message;
    }

    // store occurrence
    if ( m_verbosity <= 3 )
    {
        add_occurrence( entry );
    }
    // or print
    else
    {
        ( *m_stream ) << entry << "/>" << std::endl;
    }
}

void XMLTestLogFormatter::finialise_test_report(
        chaos::uint64 checks_passed,
        chaos::uint64 checks_failed )
{
    // write collected reports
    if ( m_verbosity <= 3 )
    {
        CHAOS_FOR_EACH( it, m_occurrence_map )
        {
            chaos::str::UTF8String message( it->first );
            message << " occurrences=" << it->second;
            ( *m_stream ) << message << "/>" << std::endl;
        }
    }

    // verbosity 2+
    if ( m_verbosity < 2 )
    {
        return;
    }

    ( *m_stream ) << "    <UnitSummary ChecksPassed=" << checks_passed
                  << " ChecksFailed=" << checks_failed << "/>"
                  << std::endl;
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
