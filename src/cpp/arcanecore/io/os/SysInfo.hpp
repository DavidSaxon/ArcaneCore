/*!
 * \file
 * \brief Module for retrieving about the current system.
 * \author David Saxon
 */
#ifndef ARCANECORE_BASE_IO_OS_SYSINFO_HPP_
#define ARCANECORE_BASE_IO_OS_SYSINFO_HPP_

#include <cstddef>

#include <arcanecore/base/str/UTF8String.hpp>


namespace arc
{
namespace io
{
namespace os
{

// TODO: get OS name

/*!
 * \brief Returns the name of this operating system.
 */
const arc::str::UTF8String& get_os_name();

/*!
 * \brief Returns the name/version of this operating system's distribution.
 */
const arc::str::UTF8String& get_distro_name();

/*!
 * \brief Returns the vendor of this system's CPU.
 */
const arc::str::UTF8String& get_cpu_vendor();

/*!
 * \brief Returns the model of this system's CPU.
 */
const arc::str::UTF8String& get_cpu_model();

/*!
 * \brief Returns the number of physical cores this machine has.
 */
std::size_t get_cpu_physical_cores();

/*!
 * \brief Returns the number of logical processing units this machine has.
 */
std::size_t get_cpu_logical_processors();

/*!
 * \brief Get the clock rate (in MHz) of this machine's cpu.
 */
float get_cpu_clock_rate();

/*!
 * \brief Get the logical processor this thread is executing on.
 */
std::size_t get_thread_processor();

/*!
 * \brief Returns the total amount of main RAM on this system, measured in
 *        bytes.
 */
std::size_t get_total_ram();

/*!
 * \brief Returns the amount of RAM that is currently free, measured in bytes.
 */
std::size_t get_free_ram();

/*!
 * \brief Returns the total amount of virtual memory on this system, measured
 *        in bytes.
 */
std::size_t get_total_virtual_memory();

/*!
 * \brief Returns the amount of virtual memory that is currently free, measured
 *        in bytes.
 */
std::size_t get_free_virtual_memory();

/*!
 * \brief Returns the current resident set size (physical memory use) measured
 *        in bytes.
 */
std::size_t get_rss();

/*!
 * \brief Returns the peak (maximum so far) resident set size (physical memory
 *        use) measured in bytes.
 */
std::size_t get_peak_rss();

} // namespace os
} // namespace io
} // namespace arc

#endif
