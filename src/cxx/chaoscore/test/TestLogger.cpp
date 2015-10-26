#include "chaoscore/test/TestLogger.hpp"

#include <fstream>
#include <iostream>

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
    m_is_parent           ( false ),
    m_using_stdout        ( false ),
    m_global_unit_passes  ( 0 ),
    m_global_unit_failures( 0 ),
    m_global_success_count( 0 ),
    m_global_failure_count( 0 ),
    m_success_count       ( 0 ),
    m_failure_count       ( 0 )
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
        static_cast< std::ofstream* >( f_s_it->second )->close();
        delete f_s_it->second;
    }
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestLogger::set_global_id( const chaos::str::UTF8String& id )
{
    // set global id and meta path
    m_global_id = id;
    m_meta_path = id + ".metadata";
}

void TestLogger::set_as_parent( bool state )
{
    m_is_parent = state;
}

void TestLogger::add_stdout( chaos::uint16 verbosity, OutFormat format )
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
    create_formatter( &std::cout, verbosity, format, true );

}

void TestLogger::add_file_output(
        const chaos::str::UTF8String& path,
              chaos::uint16           verbosity,
              OutFormat               format )
{
    // the path should be validated at this point..
    chaos::io::file::validate_path( path );

    // open a file stream
    std::ofstream* file_stream = new std::ofstream( path.to_cstring() );
    // did the stream open ok?
    if ( !file_stream->good() )
    {
        file_stream->close();
        chaos::str::UTF8String error_message;
        error_message << "Failed to open path for logging: " << path;
        throw chaos::test::ex::TestRuntimeError( error_message );
    }

    // store the file name and stream
    m_file_streams[ path ] = file_stream;

    // create a formatter
    create_formatter( file_stream, verbosity, format );
}

void TestLogger::open_log()
{
    // only handled by the parent logger
    if ( !m_is_parent )
    {
        return;
    }

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
        ( *it )->close_log( m_global_success_count, m_global_failure_count );
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

    // look for open sub files and append them into the main files
    CHAOS_FOR_EACH( f_it, m_file_streams )
    {
        // add the id as to the filename
        chaos::str::UTF8String sub_name( f_it->first + "." + id );
        // does the sub file exist?
        if ( chaos::io::file::exists ( sub_name ) &&
             chaos::io::file::is_file( sub_name )    )
        {
            // open the file and read the contents into the matching stream
            std::ifstream in_file( sub_name.to_cstring() );
            if ( in_file.is_open() )
            {
                std::string line;
                while( getline( in_file, line ) )
                {
                    ( *f_it->second ) << line << std::endl;
                }
            }
            // close stream
            in_file.close();
            // delete the file
            remove( sub_name.to_cstring() );
        }
    }

    // send the close to formatters
    CHAOS_FOR_EACH( it, m_formatters )
    {
        ( *it )->close_test();
    }

    // read in metadata file
    // does the sub file exist?
    if ( chaos::io::file::exists ( m_meta_path ) &&
         chaos::io::file::is_file( m_meta_path )    )
    {
        std::ifstream metadata( m_meta_path.to_cstring() );
        std::string line;
        if( getline( metadata, line ) )
        {
            bool unit_pass = chaos::str::UTF8String( line.c_str() ).to_bool();
            if ( unit_pass )
            {
                ++m_global_unit_passes;
            }
            else
            {
                ++m_global_unit_failures;
            }
            // TODO: REMOVE ME
            std::cout << "__CCT__: UPDATE GLOBAL UNIT PASSES: "
                      << m_global_unit_passes << std::endl;
            std::cout << "__CCT__: UPDATE GLOBAL UNIT FAILURES: "
                      << m_global_unit_failures << std::endl;
        }
        if( getline( metadata, line ) )
        {
            m_global_success_count +=
                    chaos::str::UTF8String( line.c_str() ).to_uint64();
            // TODO: REMOVE ME
            std::cout << "__CCT__: UPDATE GLOBAL SUCCESS COUNT: "
                      << m_global_success_count << std::endl;
        }
        if( getline( metadata, line ) )
        {
            m_global_failure_count +=
                    chaos::str::UTF8String( line.c_str() ).to_uint64();
            // TODO: REMOVE ME
            std::cout << "__CCT__: UPDATE GLOBAL FAILURE COUNT: "
                      << m_global_failure_count << std::endl;
        }
    }

    // clean up metadata
    remove( m_meta_path.to_cstring() );
}

void TestLogger::report_success(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line )
{
    // record success
    ++m_success_count;
    // send to formatters
    CHAOS_FOR_EACH( it, m_formatters )
    {
        ( *it )->report_success( type, file, line );
    }
}

void TestLogger::report_failure(
        const chaos::str::UTF8String& type,
        const chaos::str::UTF8String& file,
              chaos::int32            line,
        const chaos::str::UTF8String& message )
{
    // record failure
    ++m_failure_count;
    // send to formatters
    CHAOS_FOR_EACH( it, m_formatters )
    {
        ( *it )->report_failure( type, file, line, message );
    }
}

void TestLogger::finialise_test_report()
{
    // send to formatters
    CHAOS_FOR_EACH( it, m_formatters )
    {
        ( *it )->finialise_test_report( m_success_count, m_failure_count );
    }
    // write to meta-data
    chaos::str::UTF8String contents;
    contents << ( m_failure_count == 0 ) << "\n" << m_success_count << "\n"
             << m_failure_count << "\n";
    std::ofstream metadata( m_meta_path.to_cstring() );
    metadata << contents.to_cstring() << std::endl;
    metadata.close();
    // clear
    m_success_count = 0;
    m_failure_count = 0;
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestLogger::create_formatter(
        std::ostream* stream,
        chaos::uint8  verbosity,
        OutFormat     format,
        bool          is_stdout )
{
    // create a new log formatter based on the output type
    log_formatter::AbstractTestLogFormatter* formatter;
    switch( format )
    {
        case OUT_PLAIN_TEXT:
        {
            formatter = new log_formatter::PlainTestLogFormatter(
                    verbosity, stream );
            break;
        }
        case OUT_PRETTY_TEXT:
        {
            formatter = new log_formatter::PrettyTestLogFormatter(
                    verbosity, stream, is_stdout );
            break;
        }
        case OUT_XML:
        {
            formatter = new log_formatter::XMLTestLogFormatter(
                    verbosity, stream );
            break;
        }
        case OUT_HTML:
        {
            formatter = new log_formatter::HTMLTestLogFormatter(
                    verbosity, stream );
            break;
        }
    }
    // store
    m_formatters.push_back( formatter );
}

} // namespace test
} // namespace chaos
