#include "chaoscore/test/TestLogger.hpp"

#include <iostream>

namespace chaos
{
namespace test
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TestLogger::TestLogger()
    :
    m_usingStdout( false )
{
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

TestLogger::~TestLogger()
{
    CHAOS_FOR_EACH( it, m_fileStreams )
    {
        delete *it;
    }
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestLogger::addStdOut( OutFormat format )
{
    m_usingStdout = true;
    m_stdoutFormat = format;

    // TODO: REMOVE ME
    std::cout << "ADDED STDOUT: " << format << std::endl;
}

void TestLogger::addFileOutput(
        const chaos::str::UTF8String& path,
              OutFormat               format )
{
    // TODO:
}

} // namespace test
} // namespace chaos
