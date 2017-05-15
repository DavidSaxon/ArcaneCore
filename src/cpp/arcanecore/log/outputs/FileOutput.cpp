#include "arcanecore/log/outputs/FileOutput.hpp"

#include <arcanecore/io/sys/FileSystemOperations.hpp>


namespace arc
{
namespace log
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

FileOutput::FileOutput(
        arc::io::sys::Path& path,
        bool open_now,
        arc::log::Verbosity verbosity_level)
    :
    AbstractOutput(verbosity_level),
    m_path        (path),
    m_opened_once (false)
{
    m_enabled = false;
    if(open_now)
    {
        set_enabled(true);
    }
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void FileOutput::set_enabled(bool enabled)
{
    // open?
    if(enabled && !m_writer.is_open())
    {
        // does the file handle need to be opened for the first time?
        if(!m_opened_once)
        {
            // validate the path first
            arc::io::sys::validate(m_path);

            // set up the writer
            m_writer.set_path(m_path);
            m_writer.set_encoding(arc::io::sys::FileHandle::ENCODING_UTF8);
            m_writer.set_open_mode(arc::io::sys::FileWriter::OPEN_TRUNCATE);
            m_writer.open();

            m_opened_once = true;
        }
        else
        {
            // open in append mode
            m_writer.set_open_mode(arc::io::sys::FileWriter::OPEN_APPEND);
            m_writer.open();
        }
    }
    // close?
    else if(!enabled && m_writer.is_open())
    {
        m_writer.close();
    }

    // super call
    AbstractOutput::set_enabled(enabled);
}

void FileOutput::write(
        arc::log::Verbosity verbosity,
        const arc::log::Profile& profile,
        const arc::str::UTF8String& message)
{
    // should writing be skipped?
    if(!m_enabled || verbosity > m_verbosity_level)
    {
        return;
    }

    arc::str::UTF8String formatted;
    // add the app name and version to the prefix (if required)
    if(!profile.app_name.is_empty())
    {
        formatted = profile.app_name;
    }
    if(!profile.app_version.is_empty())
    {
        if(!formatted.is_empty())
        {
            formatted += "-";
        }
        formatted += profile.app_version;
    }
    if(!formatted.is_empty())
    {
        formatted = arc::str::UTF8String("{") + formatted + "} - ";
    }
    // add the verbosity level to the prefix
    switch(verbosity)
    {
        case arc::log::VERBOSITY_CRITICAL:
        {
            formatted += "[CRITICAL]: ";
            break;
        }
        case arc::log::VERBOSITY_ERROR:
        {
            formatted += "[ERROR]: ";
            break;
        }
        case arc::log::VERBOSITY_WARNING:
        {
            formatted += "[WARNING]: ";
            break;
        }
        case arc::log::VERBOSITY_NOTICE:
        {
            formatted += "[NOTICE]: ";
            break;
        }
        case arc::log::VERBOSITY_INFO:
        {
            formatted += "[INFO]: ";
            break;
        }
        case arc::log::VERBOSITY_DEBUG:
        {
            formatted += "[DEBUG]: ";
            break;
        }
    }

    // add the message to formatted string
    formatted += message;

    // write to the file
    m_writer.write(formatted, true);
}

} // namespace log
} // namespace arc
