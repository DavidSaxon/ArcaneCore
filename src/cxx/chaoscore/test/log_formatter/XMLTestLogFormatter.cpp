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
    ( *m_stream ) << "<chaoscore::tests>" << std::endl;;
}

void XMLTestLogFormatter::closeLog()
{
    // TODO:
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
