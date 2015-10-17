#include "chaoscore/test/log_formatter/PlainTestLogFormatter.hpp"

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

PlainTestLogFormatter::PlainTestLogFormatter( std::ostream* stream )
    :
    AbstractTestLogFormatter( stream )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void PlainTestLogFormatter::openLog()
{
    // do nothing for plain text
}

void PlainTestLogFormatter::closeLog()
{
    // do nothing for plain text
}

void PlainTestLogFormatter::open_test(
        const chaos::str::UTF8String& path,
        const chaos::str::UTF8String& id )
{
    // TODO:
}

void PlainTestLogFormatter::close_test()
{
    // TODO:
}

} // namespace log_formatter
} // namespace test
} // namespace chaos
