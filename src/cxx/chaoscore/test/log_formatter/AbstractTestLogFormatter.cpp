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
        const chaos::uni::UTF8String& entry )
{
    // is there no occurrence yet?
    if ( m_occurrence_map.find( entry ) == m_occurrence_map.end() )
    {
        m_occurrence_map[ entry ] = 1;
        m_occurrence_order.push_back( entry );
    }
    else
    {
        ++m_occurrence_map[ entry ];
    }

    // check against the previous occurrence
    if ( !m_occurrences.empty() && m_occurrences.back().entry == entry )
    {
        // update the current occurrence
        ++m_occurrences.back().count;
    }
    else
    {
        m_occurrences.push_back( LogOccurence() );
        m_occurrences.back().entry = entry;
        m_occurrences.back().count = 1;
    }
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
