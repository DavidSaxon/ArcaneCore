#include "chaoscore/test/log_formatter/HTMLTestLogFormatter.hpp"

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

HTMLTestLogFormatter::HTMLTestLogFormatter( std::ostream* stream )
    :
    AbstractTestLogFormatter( stream )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void HTMLTestLogFormatter::openLog()
{
    // TODO:
}

void HTMLTestLogFormatter::closeLog()
{
    // TODO:
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
