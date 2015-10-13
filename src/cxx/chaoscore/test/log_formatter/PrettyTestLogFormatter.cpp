#include "chaoscore/test/log_formatter/PrettyTestLogFormatter.hpp"

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

PrettyTestLogFormatter::PrettyTestLogFormatter( std::ostream* stream )
    :
    AbstractTestLogFormatter( stream )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void PrettyTestLogFormatter::openLog()
{
    ( *m_stream ) << "ChaosCore Tests" << std::endl;
}

void PrettyTestLogFormatter::closeLog()
{
    // TODO:
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
