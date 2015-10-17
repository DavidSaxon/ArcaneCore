#include "chaoscore/test/TestLogger.hpp"

#include <iostream>
#include <fstream>

#include "chaoscore/io/file/FileUtil.hpp"
#include "chaoscore/test/TestExceptions.hpp"
#include "chaoscore/test/log_formatter/HTMLTestLogFormatter.hpp"
#include "chaoscore/test/log_formatter/PlainTestLogFormatter.hpp"
#include "chaoscore/test/log_formatter/PrettyTestLogFormatter.hpp"
#include "chaoscore/test/log_formatter/XMLTestLogFormatter.hpp"

namespace chaos
{
namespace test
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TestLogger::TestLogger()
    :
    m_isParent   ( false ),
    m_usingStdout( false )
{
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

TestLogger::~TestLogger()
{
    // delete the formatters
    CHAOS_FOR_EACH( ftIt, m_formatters )
    {
        delete *ftIt;
    }
    // close and delete the file streams
    CHAOS_FOR_EACH( fsIt, m_fileStreams )
    {
        static_cast< std::ofstream* >( *fsIt )->close();
        delete *fsIt;
    }
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestLogger::setAsParent( bool state )
{
    m_isParent = state;
}

void TestLogger::addStdOut( OutFormat format )
{
    // safety to ensure two std outs are not defined
    if ( m_usingStdout )
    {
        throw chaos::test::ex::TestRuntimeError(
                "A standard out test logger has already been defined. "
                "Currently only one standard out test logger is supported."
        );
    }

    m_usingStdout = true;

    // create formatter
    createFormatter( &std::cout, format );

}

void TestLogger::addFileOutput(
        const chaos::str::UTF8String& path,
              OutFormat               format )
{
    // the path should be validated at this point..
    chaos::io::file::validatePath( path );

    // open a file stream
    std::ofstream* fileStream = new std::ofstream( path.getCString() );
    // did the stream open ok?
    if ( !fileStream->good() )
    {
        fileStream->close();
        chaos::str::UTF8String errorMessage( "Failed to open path for " );
        errorMessage += "logging: ";
        errorMessage += path;
        throw chaos::test::ex::TestRuntimeError( errorMessage );
    }

    // store the file stream
    m_fileStreams.push_back( fileStream );

    // create a formatter
    createFormatter( fileStream, format );
}

void TestLogger::openLog()
{
    // only handled by the parent logger
    if ( !m_isParent )
    {
        return;
    }

    std::cout << "OPENING LOGGER" << std::endl;

    CHAOS_FOR_EACH( it, m_formatters )
    {
        ( *it )->openLog();
    }
}

void TestLogger::closeLog()
{
    // only handled by the parent logger
    if ( !m_isParent )
    {
        return;
    }

    CHAOS_FOR_EACH( it, m_formatters )
    {
        ( *it )->openLog();
    }
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestLogger::createFormatter( std::ostream* stream, OutFormat format )
{
    // create a new log formatter based on the output type
    log_formatter::AbstractTestLogFormatter* formatter;
    switch( format )
    {
        case OUT_PLAIN_TEXT:
        {
            formatter = new log_formatter::PlainTestLogFormatter( stream );
            break;
        }
        case OUT_PRETTY_TEXT:
        {
            formatter = new log_formatter::PrettyTestLogFormatter( stream );
            break;
        }
        case OUT_XML:
        {
            formatter = new log_formatter::XMLTestLogFormatter( stream );
            break;
        }
        case OUT_HTML:
        {
            formatter = new log_formatter::HTMLTestLogFormatter( stream );
            break;
        }
    }
    // store
    m_formatters.push_back( formatter );
}

} // namespace test
} // namespace chaos
