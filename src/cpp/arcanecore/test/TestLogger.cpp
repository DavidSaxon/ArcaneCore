#include "arcanecore/test/TestLogger.hpp"

#include <fstream>
#include <iostream>

#include "arcanecore/io/sys/FileSystemOperations.hpp"
#include "arcanecore/test/TestExceptions.hpp"
#include "arcanecore/test/log_formatter/HTMLTestLogFormatter.hpp"
#include "arcanecore/test/log_formatter/PlainTestLogFormatter.hpp"
#include "arcanecore/test/log_formatter/PrettyTestLogFormatter.hpp"
#include "arcanecore/test/log_formatter/XMLTestLogFormatter.hpp"

namespace arc
{
namespace test
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TestLogger::TestLogger()
    :
    m_is_parent              (false),
    m_using_stdout           (false),
    m_unit_passes            (0),
    m_unit_failures          (0),
    m_unit_errors            (0),
    m_global_check_pass_count(0),
    m_global_check_fail_count(0),
    m_check_pass_count       (0),
    m_check_fail_count       (0)
{
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

TestLogger::~TestLogger()
{
    // delete the formatters
    ARC_FOR_EACH(f_it, m_formatters)
    {
        delete *f_it;
    }
    // close and delete the file streams
    ARC_FOR_EACH(f_s_it, m_file_streams)
    {
        static_cast<std::ofstream*>(f_s_it->second)->close();
        delete f_s_it->second;
    }
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestLogger::set_global_id(const arc::str::UTF8String& id)
{
    // set global id and meta path
    m_global_id = id;
    m_meta_path = arc::io::sys::Path(id + ".metadata");
}

void TestLogger::set_as_parent(bool state)
{
    m_is_parent = state;
}

void TestLogger::add_stdout(arc::uint16 verbosity, OutFormat format)
{
    // safety to ensure two std outs are not defined
    if(m_using_stdout)
    {
        throw arc::test::ex::TestRuntimeError(
                "A standard out test logger has already been defined. "
                "Currently only one standard out test logger is supported."
        );
    }

    m_using_stdout = true;

    // create formatter
    create_formatter(&std::cout, verbosity, format, true);

}

void TestLogger::add_file_output(
        const arc::str::UTF8String& path,
        arc::uint16 verbosity,
        OutFormat format)
{
    // open a file stream
    std::ofstream* file_stream = new std::ofstream(path.get_raw());
    // did the stream open ok?
    if(!file_stream->good())
    {
        file_stream->close();
        arc::str::UTF8String error_message;
        error_message << "Failed to open path for logging: " << path;
        throw arc::test::ex::TestRuntimeError(error_message);
    }

    // store the file name and stream
    m_file_streams[path] = file_stream;

    // create a formatter
    create_formatter(file_stream, verbosity, format);
}

void TestLogger::open_log()
{
    // only handled by the parent logger
    if(!m_is_parent)
    {
        return;
    }

    ARC_FOR_EACH(it, m_formatters)
    {
        (*it)->open_log();
    }
}

void TestLogger::close_log()
{
    // only handled by the parent logger
    if(!m_is_parent)
    {
        return;
    }

    ARC_FOR_EACH(it, m_formatters)
    {
        (*it)->close_log(
                m_unit_passes,
                m_unit_failures,
                m_unit_errors,
                m_global_check_pass_count,
                m_global_check_fail_count);
    }
}

void TestLogger::open_test(
        const arc::str::UTF8String& path,
        const arc::str::UTF8String& id)
{
    // only handled by the parent logger
    if(!m_is_parent)
    {
        return;
    }

    ARC_FOR_EACH(it, m_formatters)
    {
        (*it)->open_test(path, id);
    }
}

void TestLogger::close_test(const arc::str::UTF8String& id)
{
    // only handled by the parent logger
    if(!m_is_parent)
    {
        return;
    }

    // look for open sub files and append them into the main files
    ARC_FOR_EACH(f_it, m_file_streams)
    {
        // add the id as to the filename
        arc::io::sys::Path sub_path(f_it->first + "." + id);
        // does the sub file exist?
        if(arc::io::sys::exists (sub_path) &&
             arc::io::sys::is_file(sub_path)   )
        {
            // TODO: this doesn't support windows utf-16 encoded paths
            // open the file and read the contents into the matching stream
            std::ifstream in_file(sub_path.to_native().get_raw());
            if(in_file.is_open())
            {
                std::string line;
                while(getline(in_file, line))
                {
                    (*f_it->second) << line << std::endl;
                }
            }
            // close stream
            in_file.close();
            // delete the file
            try
            {
                arc::io::sys::delete_path(sub_path);
            }
            catch(...) {}
        }
    }

    // send the close to formatters
    ARC_FOR_EACH(it, m_formatters)
    {
        (*it)->close_test();
    }

    // read in metadata file
    if(arc::io::sys::exists (m_meta_path) &&
       arc::io::sys::is_file(m_meta_path)   )
    {
        // TODO: this doesn't support Windows UTF-16 encoded file paths
        std::ifstream metadata(m_meta_path.to_native().get_raw());
        std::string line;
        if(getline(metadata, line))
        {
            bool unit_pass = arc::str::UTF8String(line.c_str()).to_bool();
            if(unit_pass)
            {
                ++m_unit_passes;
            }
            else
            {
                ++m_unit_failures;
            }
        }
        if(getline(metadata, line))
        {
            m_global_check_pass_count +=
                    arc::str::UTF8String(line.c_str()).to_uint64();
        }
        if(getline(metadata, line))
        {
            m_global_check_fail_count +=
                    arc::str::UTF8String(line.c_str()).to_uint64();
        }

        // clean up metadata
        metadata.close();
        try
        {
            arc::io::sys::delete_path(m_meta_path);
        }
        catch(...) {}
    }
}

void TestLogger::report_crash(
        const arc::str::UTF8String& id,
        const arc::str::UTF8String& info)
{
    // clean up the sub files and metadata -- there's no point reading as they're
    // likely incomplete or corrupted
    ARC_FOR_EACH(f_it, m_file_streams)
    {
        // add the id as to the filename
        arc::io::sys::Path sub_path(f_it->first + "." + id);
        if(arc::io::sys::exists (sub_path) &&
             arc::io::sys::is_file(sub_path)   )
        {
            try
            {
                arc::io::sys::delete_path(sub_path);
            }
            catch(...) {}
        }
    }
    if(arc::io::sys::exists (m_meta_path) &&
         arc::io::sys::is_file(m_meta_path)   )
    {
        try
        {
            arc::io::sys::delete_path(m_meta_path);
        }
        catch(...) {}
    }

    // increment errored tests
    ++m_unit_errors;

    // send to formatters
    ARC_FOR_EACH(it, m_formatters)
    {
        (*it)->report_crash(info);
    }
}

void TestLogger::report_check_pass(
        const arc::str::UTF8String& type,
        const arc::str::UTF8String& file,
        arc::int32 line)
{
    // record success
    ++m_check_pass_count;
    // send to formatters
    ARC_FOR_EACH(it, m_formatters)
    {
        (*it)->report_check_pass(type, file, line);
    }
}

void TestLogger::report_check_fail(
        const arc::str::UTF8String& type,
        const arc::str::UTF8String& file,
        arc::int32 line,
        const arc::str::UTF8String& message)
{
    // record failure
    ++m_check_fail_count;
    // send to formatters
    ARC_FOR_EACH(it, m_formatters)
    {
        (*it)->report_check_fail(type, file, line, message);
    }
}

void TestLogger::write_message(const arc::str::UTF8String& message)
{
    // send to formatters
    ARC_FOR_EACH(it, m_formatters)
    {
        (*it)->write_message(message);
    }
}

void TestLogger::finialise_test_report()
{
    // send to formatters
    ARC_FOR_EACH(it, m_formatters)
    {
        (*it)->finialise_test_report(
                m_check_pass_count, m_check_fail_count);
    }
    // write to meta-data
    arc::str::UTF8String contents;
    contents << (m_check_fail_count == 0) << "\n" << m_check_pass_count
             << "\n" << m_check_fail_count << "\n";
    // TODO: this doesn't support Windows UTF-16 encoded data
    std::ofstream metadata(m_meta_path.to_native().get_raw());
    metadata << contents.get_raw() << std::endl;
    metadata.close();
    // clear
    m_check_pass_count = 0;
    m_check_fail_count = 0;
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestLogger::create_formatter(
        std::ostream* stream,
        arc::uint16 verbosity,
        OutFormat format,
        bool is_stdout)
{
    // create a new log formatter based on the output type
    log_formatter::AbstractTestLogFormatter* formatter;
    switch(format)
    {
        case OUT_PLAIN_TEXT:
        {
            formatter = new log_formatter::PlainTestLogFormatter(
                    verbosity, stream);
            break;
        }
        case OUT_PRETTY_TEXT:
        {
            formatter = new log_formatter::PrettyTestLogFormatter(
                    verbosity, stream, is_stdout);
            break;
        }
        case OUT_XML:
        {
            formatter = new log_formatter::XMLTestLogFormatter(
                    verbosity, stream);
            break;
        }
        case OUT_HTML:
        {
            formatter = new log_formatter::HTMLTestLogFormatter(
                    verbosity, stream);
            break;
        }
    }
    // store
    m_formatters.push_back(formatter);
}

} // namespace test
} // namespace arc
