/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_LOG_ABSTRACTOUTPUT_HPP_
#define ARCANECORE_LOG_ABSTRACTOUTPUT_HPP_

#include <arcanecore/base/lang/Restrictors.hpp>
#include <arcanecore/base/str/UTF8String.hpp>

#include "arcanecore/log/Profile.hpp"
#include "arcanecore/log/Verbosity.hpp"


namespace arc
{
namespace log
{

//------------------------------------------------------------------------------
//                              FORWARD DECLARATIONS
//------------------------------------------------------------------------------

class Stream;

/*!
 * \brief Abstract base class that represents a logging output.
 *
 * Outputs receive logging messages (along with the verbosity and logging
 * profile) from all arc::log::Input objects connected to the parent
 * arc::log::LogHandler. It is then up the output implementation on how to
 * handle the message.
 */
class AbstractOutput
    : private arc::lang::Noncopyable
    , private arc::lang::Nonmovable
    , private arc::lang::Noncomparable
{
private:

    //--------------------------------------------------------------------------
    //                                  FRIENDS
    //--------------------------------------------------------------------------

    friend class Stream;

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Super constructor.
     *
     * \param verbosity_level The initial level of verbosity of this output.
     */
    AbstractOutput(arc::log::Verbosity verbosity_level);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~AbstractOutput()
    {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Returns whether this output is enabled or not.
     */
    bool is_enabled() const;

    /*!
     * \brief Sets whether this output is enabled or not.
     */
    virtual void set_enabled(bool enabled);

    /*!
     * \brief Returns the maximum verbosity level of messages this output will
     *        display.
     */
    arc::log::Verbosity get_verbosity_level() const;

    /*!
     * \brief Sets the maximum verbosity level of messages this output will
     *        display.
     */
    void set_verbosity_level(arc::log::Verbosity verbosity_level);

protected:

    //--------------------------------------------------------------------------
    //                            PROTECTED ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief Whether this output is enabled or not.
     */
    bool m_enabled;

    /*!
     * \brief The maximum verbosity level of messages this output should
     *        display.
     */
    arc::log::Verbosity m_verbosity_level;

    //--------------------------------------------------------------------------
    //                        PROTECETED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Is called by inputs streams to handle the outputting of the given
     *        log message.
     *
     * \note This function must be implemented by derived outputs.
     *
     * \param verbosity The verbosity of the message.
     * \param profile The logging profile associated with the message.
     * \param message The message to output.
     */
    virtual void write(
            arc::log::Verbosity verbosity,
            const arc::log::Profile& profile,
            const arc::str::UTF8String& message) = 0;
};

} // namespace log
} // namespace arc

#endif
