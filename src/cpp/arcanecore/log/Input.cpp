#include "arcanecore/log/Input.hpp"

#include "arcanecore/log/LogHandler.hpp"


namespace arc
{
namespace log
{

//------------------------------------------------------------------------------
//                             PROTECTED CONSTRUCTOR
//------------------------------------------------------------------------------

Input::Input(
        arc::log::LogHandler* log_handler,
        const arc::log::Profile& profile)
    :
    critical(log_handler, arc::log::VERBOSITY_CRITICAL, profile),
    error   (log_handler, arc::log::VERBOSITY_ERROR,    profile),
    warning (log_handler, arc::log::VERBOSITY_WARNING,  profile),
    notice  (log_handler, arc::log::VERBOSITY_NOTICE,   profile),
    info    (log_handler, arc::log::VERBOSITY_INFO,     profile),
    debug   (log_handler, arc::log::VERBOSITY_DEBUG,    profile)
{
}

} // namespace log
} // namespace arc
