#include "chaoscore/test/TestLogger.hpp"

#include <iostream>
#include <fstream>

#include "chaoscore/base/file/FileSystem.hpp"
#include "chaoscore/test/TestExceptions.hpp"

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
    // delete the file streams
    CHAOS_FOR_EACH( fsIt, m_fileStreams )
    {
        delete ( *fsIt )->stream;
    }
    // delete all stream info structures
    CHAOS_FOR_EACH( sIt, m_allStreams )
    {
        delete *sIt;
    }
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestLogger::addStdOut( OutFormat format )
{
    m_usingStdout = true;
    m_stdoutFormat = format;

    // create and store a stream object
    StreamInfo* streamInfo = new StreamInfo( &std::cout, format );
    m_allStreams.push_back( streamInfo );
}

void TestLogger::addFileOutput(
        const chaos::str::UTF8String& path,
              OutFormat               format )
{
    // the path should be validated at this point..
    chaos::file::validatePath( path );

    // open a file stream
    std::ofstream* fileStream = new std::ofstream( path.getCString() );
    // did the stream open ok?
    if ( ! fileStream->good() )
    {
        fileStream->close();
        chaos::str::UTF8String errorMessage( "Failed to open path for " );
        errorMessage += "logging: ";
        errorMessage += path;
        throw chaos::test::ex::TestRuntimeError( errorMessage );
    }

    // store the open file handler and the format
    StreamInfo* fileStreamInfo =
            new StreamInfo( fileStream, format );
    m_fileStreams.push_back( fileStreamInfo );
    m_allStreams.push_back( fileStreamInfo );
}

void TestLogger::openLog()
{
    CHAOS_FOR_EACH( it, m_allStreams )
    {
        std::ostream& stream = *( *it )->stream;

        switch( ( *it )->format )
        {
            case OUT_PLAIN_TEXT:
                // do nothing for plain text
                break;
            case OUT_PRETTY_TEXT:
                stream << "Chaos Tests!" << std::endl;
                break;
            case OUT_XML:
                stream << "<chaos_test>" << std::endl;
                break;
            case OUT_HTML:
                // TODO:
                break;
        }
    }
}

} // namespace test
} // namespace chaos
