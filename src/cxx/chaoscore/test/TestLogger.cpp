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
    m_is_parent   ( false ),
    m_using_stdout( false )
{
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

TestLogger::~TestLogger()
{
    // delete the formatters
    CHAOS_FOR_EACH( f_it, m_formatters )
    {
        delete *f_it;
    }
    // close and delete the file streams
    CHAOS_FOR_EACH( f_s_it, m_file_streams )
    {
        static_cast< std::ofstream* >( *f_s_it )->close();
        delete *f_s_it;
    }
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestLogger::set_as_parent( bool state )
{
    m_is_parent = state;
}

void TestLogger::add_stdout( OutFormat format )
{
    // safety to ensure two std outs are not defined
    if ( m_using_stdout )
    {
        throw chaos::test::ex::TestRuntimeError(
                "A standard out test logger has already been defined. "
                "Currently only one standard out test logger is supported."
        );
    }

    m_using_stdout = true;

    // create formatter
    create_formatter( &std::cout, format );

}

void TestLogger::add_file_output(
        const chaos::str::UTF8String& path,
        OutFormat format )
{
    // the path should be validated at this point..
    chaos::io::file::validate_path( path );

    // open a file stream
    std::ofstream* file_stream = new std::ofstream( path.get_cstring() );
    // did the stream open ok?
    if ( !file_stream->good() )
    {
        file_stream->close();
        chaos::str::UTF8String error_message;
        error_message << "Failed to open path for logging: " << path;
        throw chaos::test::ex::TestRuntimeError( error_message );
    }

    // store the file stream
    m_file_streams.push_back( file_stream );

    // create a formatter
    create_formatter( file_stream, format );
}

void TestLogger::open_log()
{
    // only handled by the parent logger
    if ( !m_is_parent )
    {
        return;
    }

    std::cout << "OPENING LOGGER" << std::endl;

    CHAOS_FOR_EACH( it, m_formatters )
    {
        ( *it )->open_log();
    }
}

void TestLogger::close_log()
{
    // only handled by the parent logger
    if ( !m_is_parent )
    {
        return;
    }

    CHAOS_FOR_EACH( it, m_formatters )
    {
        ( *it )->close_log();
    }
}

void TestLogger::open_test(
        const chaos::str::UTF8String& path,
        const chaos::str::UTF8String& id )
{
    // only handled by the parent logger
    if ( !m_is_parent )
    {
        return;
    }

    CHAOS_FOR_EACH( it, m_formatters )
    {
        ( *it )->open_test( path, id );
    }
}

void TestLogger::close_test( const chaos::str::UTF8String& id )
{
    // only handled by the parent logger
    if ( !m_is_parent )
    {
        return;
    }

    CHAOS_FOR_EACH( it, m_formatters )
    {
        ( *it )->close_test();
    }
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestLogger::create_formatter( std::ostream* stream, OutFormat format )
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
