/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_LOG_STREAM_HPP_
#define ARCANECORE_LOG_STREAM_HPP_

#include <memory>

#include <arcanecore/base/lang/Restrictors.hpp>

#include "arcanecore/log/Profile.hpp"
#include "arcanecore/log/Verbosity.hpp"


namespace arc
{
namespace log
{

//------------------------------------------------------------------------------
//                              FORWARD DECLARATIONS
//------------------------------------------------------------------------------

class LogHandler;
class Input;

/*!
 * \brief Stream that inherits from ```std::ostream``` for writing log messages
 *        to.
 *
 * All stream objects are owned by and provided by arc::log::Input objects.
 */
class Stream
    : public std::ostream
    , private arc::lang::Noncopyable
    , private arc::lang::Nonmovable
    , private arc::lang::Noncomparable
{
private:

    //--------------------------------------------------------------------------
    //                                  FRIENDS
    //--------------------------------------------------------------------------

    friend class Input;

    //--------------------------------------------------------------------------
    //                            FORWARD DECLARATIONS
    //--------------------------------------------------------------------------

    class StreamBuffer;

public:

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~Stream();

protected:

    //--------------------------------------------------------------------------
    //                           PROTECTED CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new Stream.
     *
     * \param log_handler The arc::log::LogHandler that owns this stream's parent
     *                    arc::log::Input.
     * \param verbosity The verbosity of this stream.
     * \param profile The logging profile of this stream's parent
     *                arc::log::Input.
     */
    Stream(
            arc::log::LogHandler* log_handler,
            arc::log::Verbosity verbosity,
            const arc::log::Profile& profile);

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Sends the given message to the outputs associated with this
     *        Stream's parent arc::log::LogHandler.
     */
    void send_to_outputs(const arc::str::UTF8String& message);

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The internal buffer of this stream.
     */
    std::unique_ptr<arc::log::Stream::StreamBuffer> m_buffer;

    /*!
     * \brief Pointer to the arc::log::LogHandler object this Stream's parent is
     *        associated with.
     */
    arc::log::LogHandler* m_log_handler;

    /*!
     * \brief The verbosity level of this stream.
     */
    const arc::log::Verbosity m_verbosity;

    /*!
     * \brief The logging profile of this Stream's parent input.
     */
    const arc::log::Profile m_profile;
};

} // namespace log
} // namespace arc

#endif
