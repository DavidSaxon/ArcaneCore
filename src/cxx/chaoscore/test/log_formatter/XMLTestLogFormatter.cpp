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
        chaos::uint8 verbosity, std::ostream* stream )
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

void XMLTestLogFormatter::close_log()
{
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

void XMLTestLogFormatter::report_success(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line )
{
    ( *m_stream ) << "    <Success type=" << type << " file=" << file
                  << " line=" << line << "/>" << std::endl;
}

void XMLTestLogFormatter::report_failure(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line,
        const chaos::str::UTF8String& message )
{


    ( *m_stream ) << "    <Failure type=" << type << " file=" << file
                  << " line=" << line;
    if ( !message.is_empty() )
    {
        ( *m_stream ) << " message=" << message;
    }
    ( *m_stream ) << "/>" << std::endl;
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
