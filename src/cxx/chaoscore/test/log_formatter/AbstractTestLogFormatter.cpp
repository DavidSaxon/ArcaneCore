#include "chaoscore/test/log_formatter/AbstractTestLogFormatter.hpp"

namespace chaos
{
namespace test
{
namespace log_formatter
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

AbstractTestLogFormatter::AbstractTestLogFormatter(
        chaos::uint16  verbosity,
        std::ostream* stream )
    :
    m_verbosity( verbosity ),
    m_stream   ( stream )
{
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void AbstractTestLogFormatter::add_occurrence(
        const chaos::str::UTF8String& entry )
{
    // is there no occurrence yet?
    if ( m_occurrence_map.find( entry ) == m_occurrence_map.end() )
    {
        m_occurrence_map[ entry ] = 1;
    }
    else
    {
        ++m_occurrence_map[ entry ];
    }
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
