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

XMLTestLogFormatter::XMLTestLogFormatter( std::ostream* stream )
    :
    AbstractTestLogFormatter( stream )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void XMLTestLogFormatter::openLog()
{
    ( *m_stream ) << "<ChaosCoreTests>" << std::endl;
}

void XMLTestLogFormatter::closeLog()
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

} // namespace log_formatter
} // namespace test
} // namespace chaos
