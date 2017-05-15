/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_LOG_OUTPUTS_FILEOUTPUT_HPP_
#define ARCANECORE_LOG_OUTPUTS_FILEOUTPUT_HPP_

#include <arcanecore/io/sys/FileWriter.hpp>

#include "arcanecore/log/AbstractOutput.hpp"


namespace arc
{
namespace log
{

/*!
 * \brief Implementation of arc::log::AbstractOutput that writes logging message
 *        to the file system.
 *
 * The file handle is only opened when the output is first enabled (which by
 * default happens at construction time). If the output is later disabled the
 * file handle will be closed, and reopened the next time the output is enabled.
 */
class FileOutput : public arc::log::AbstractOutput
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new opened FileOutput.
     *
     * If the ```open_now``` is set to ```false``` the file handle will not be
     * opened immediately, instead the FileOutput will initially be disabled,
     * and opened for the first time when the output is enabled.
     *
     * \param path The file path to write the log to.
     * \param open_now Whether this output will initially be enabled and the
     *                 file handle will be opened on construction.
     * \param verbosity_level The initial level of verbosity of this output.
     *
     * \throws arc::ex::IOError If the path cannot be opened for writing.
     */
    FileOutput(
            arc::io::sys::Path& path,
            bool open_now = true,
            arc::log::Verbosity verbosity_level = arc::log::VERBOSITY_NOTICE);

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    // override
    virtual void set_enabled(bool enabled);

    // override
    virtual void write(
            arc::log::Verbosity verbosity,
            const arc::log::Profile& profile,
            const arc::str::UTF8String& message);

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The path to the file to write to.
     */
    arc::io::sys::Path m_path;

    /*!
     * \brief The file writer used to write the log messages to disk.
     */
    arc::io::sys::FileWriter m_writer;

    /*!
     * \brief Whether the file handle has been opened before.
     */
    bool m_opened_once;
};

} // namespace log
} // namespace arc

#endif
