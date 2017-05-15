/*!
 * \file
 * \brief Provides the default shared logging handler.
 * \author David Saxon
 */
#ifndef ARCANECORE_LOG_SHARED_HPP_
#define ARCANECORE_LOG_SHARED_HPP_

#include <arcanecore/base/Preproc.hpp>

#include "arcanecore/log/Input.hpp"
#include "arcanecore/log/LogHandler.hpp"

#ifdef ARC_OS_WINDOWS
    #ifdef ARCANECORE_LOG_GLOBAL_EXPORT
        #define ARCANECORE_LOG_GLOBAL_API __declspec(dllexport)
    #else
        #define ARCANECORE_LOG_GLOBAL_API __declspec(dllimport)
    #endif
#else
    #define ARCANECORE_LOG_GLOBAL_API
#endif


namespace arc
{
namespace log
{

/*!
 * \brief Library provided arc::log::LogHandler instance.
 *
 * In most cases this is should be the only arc::log::LogHandler needed. Using
 * this handler means multi-library applications can use the same handler
 * without libraries need to provide access to their own handler instances.
 */
ARCANECORE_LOG_GLOBAL_API extern arc::log::LogHandler shared_handler;

} // namespace log
} // namespace arc

#endif
