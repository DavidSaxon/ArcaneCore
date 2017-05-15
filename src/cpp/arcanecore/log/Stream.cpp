#include "arcanecore/log/Stream.hpp"

#include <sstream>

#include "arcanecore/log/AbstractOutput.hpp"
#include "arcanecore/log/LogHandler.hpp"


namespace arc
{
namespace log
{

//------------------------------------------------------------------------------
//                                 STREAM BUFFER
//------------------------------------------------------------------------------

/*!
 * \brief Stream buffer which will be used internal to arc::log::Stream.
 */
class Stream::StreamBuffer : public std::stringbuf
{
public:

    //-------------------------------CONSTRUCTOR--------------------------------

    StreamBuffer(Stream* stream)
        :
        m_stream(stream)
    {
    }

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual int sync()
    {
        // TODO: optimise UTF8?
        // send to outputs
        m_stream->send_to_outputs(str().c_str());
        // clear
        str("");

        return 0;
    }

private:

    //----------------------------PRIVATE ATTRIBUTES----------------------------

    /*!
     * \brief The parent Stream of this StreamBuffer.
     */
    Stream* m_stream;
};


//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

Stream::~Stream()
{
}

//------------------------------------------------------------------------------
//                             PROTECTED CONSTRUCTOR
//------------------------------------------------------------------------------

Stream::Stream(
        arc::log::LogHandler* log_handler,
        arc::log::Verbosity verbosity,
        const arc::log::Profile& profile)
    :
    std::ostream (new StreamBuffer(this)),
    m_buffer     (static_cast<StreamBuffer*>(rdbuf())),
    m_log_handler(log_handler),
    m_verbosity  (verbosity),
    m_profile    (profile)
{
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Stream::send_to_outputs(const arc::str::UTF8String& message)
{
    ARC_FOR_EACH(it, (m_log_handler->get_outputs()))
    {
        // TODO: optimise UTF8?
        (*it)->write(m_verbosity, m_profile, message);
    }
}

} // namespace log
} // namespace arc
