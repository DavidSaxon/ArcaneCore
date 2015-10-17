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

void HTMLTestLogFormatter::open_test(
        const chaos::str::UTF8String& path,
        const chaos::str::UTF8String& id )
{
    // TODO:
}

void HTMLTestLogFormatter::close_test()
{
    // TODO:
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
