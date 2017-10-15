/*!
 * \file
 * \brief Module for querying the operating system error state.
 * \author David Saxon
 */
#ifndef ARCANECORE_BASE_IO_OS_ERRORSTATE_HPP_
#define ARCANECORE_BASE_IO_OS_ERRORSTATE_HPP_

#include "arcanecore/base/str/UTF8String.hpp"


namespace arc
{
namespace io
{
namespace os
{

/*!
 * \brief Gets the last system error message.
 *
 * This should be used after platform specific call that has failed. The related
 * error message will attempt to be retrieved as an arc::str::UTF8String.
 */
arc::str::UTF8String get_last_system_error_message();

} // namespace os
} // namespace io
} // namespace arc

#endif