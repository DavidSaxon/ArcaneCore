#include "chaoscore/test/TestLogger.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>

namespace chaos
{
namespace test
{

// TODO: COLOUR!

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TestLogger::TestLogger()
    :
    m_stream( nullptr ),
    m_stdout( false )
{
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

TestLogger::~TestLogger()
{
    if ( m_stream != nullptr )
    {
        // close the file stream if it's being used
        if ( !m_stdout )
        {
            static_cast< std::ofstream* >( m_stream )->close();
        }
        delete m_stream;
    }
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestLogger::init( const chaos::str::UTF8String& output )
{
    if ( output == "stdout" )
    {
        // use std::cout
        m_stdout = true;
        m_stream = &std::cout;
    }
    else
    {
        // open a file stream
        std::ofstream* fileStream = new std::ofstream( output.getCString() );
        // TODO: check if the file is open
        m_stream = fileStream;
    }
}

} // namespace test
} // namespace chaos
