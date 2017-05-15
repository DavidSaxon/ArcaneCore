/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_LOG_INPUT_HPP_
#define ARCANECORE_LOG_INPUT_HPP_

#include <arcanecore/base/Preproc.hpp>
#include <arcanecore/base/lang/Restrictors.hpp>

#include "arcanecore/log/Stream.hpp"


namespace arc
{
namespace log
{

/*!
 * \brief Log input object that provides streams for writing log messages with
 *        varying severity.
 *
 * Inputs cannot be manually constructed, see arc::log::LogHandler::vend_input()
 * for creating inputs.
 */
class Input
    : private arc::lang::Noncopyable
    , private arc::lang::Nonmovable
    , private arc::lang::Noncomparable
{
private:

    //--------------------------------------------------------------------------
    //                                  FRIENDS
    //--------------------------------------------------------------------------

    friend class LogHandler;

public:

    //--------------------------------------------------------------------------
    //                             PUBLIC ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief For reporting imminent catastrophic failure.
     */
    arc::log::Stream critical;
    /*!
     * \brief For reporting an unexpected error which may cause failure.
     */
    arc::log::Stream error;
    /*!
     * \brief For reporting an unexpected error which may cause the application
     *        to perform unexpectedly.
     */
    arc::log::Stream warning;
    /*!
     * \brief For reporting high level notices about the runtime of the
     *        application.
     */
    arc::log::Stream notice;
    /*!
     * \brief For reporting explicit information about the the runtime of the
     *        application.
     */
    arc::log::Stream info;
    /*!
     * \brief For reporting implementation specific information to aid in
     *        development and debugging.
     */
    arc::log::Stream debug;

protected:

    //--------------------------------------------------------------------------
    //                           PROTECTED CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new Input.
     *
     * \param log_handler Pointer to the log_handler that owns this Input.
     * \param profile The logging profile to use for any messages reported
     *                through this input.
     */
    Input(arc::log::LogHandler* log_handler, const arc::log::Profile& profile);
};

} // namespace log
} // namespace arc

#endif
