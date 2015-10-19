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

void PrettyTestLogFormatter::open_log()
{
    ( *m_stream ) << "ChaosCore Tests" << std::endl;
}

void PrettyTestLogFormatter::close_log()
{
    // TODO:
}

void PrettyTestLogFormatter::open_test(
        const chaos::str::UTF8String& path,
        const chaos::str::UTF8String& id )
{
    // TODO:
}

void PrettyTestLogFormatter::close_test()
{
    // TODO:
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
