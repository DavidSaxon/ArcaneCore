/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_LOG_OUTPUTS_STDOUTPUT_HPP_
#define ARCANECORE_LOG_OUTPUTS_STDOUTPUT_HPP_

#include "arcanecore/log/AbstractOutput.hpp"

namespace arc
{
namespace log
{

/*!
 * \brief Implementation of arc::log::AbstractOutput that writes logging
 *        messages to either ```std::cout``` (notice, info, and debug) or to
 *        ```std::cerr``` (critical, error, and warning).
 */
class StdOutput : public arc::log::AbstractOutput
{
public:

    //--------------------------------------------------------------------------
    //                                ENUMERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Enumerator that signifies whether ANSI escape sequence should be
     *        used to decorate text outputted to ```std::cout``` and
     *        ```std::cerr```.
     */
    enum UseANSI
    {
        /// ANSI escape sequences are never used to decorate output text.
        USEANSI_NEVER = 0,
        /// ANSI escape sequences are always used to decorate output text.
        USEANSI_ALWAYS,
        /// ANSI escape sequences are used to decorate output text if the
        /// current operating system's default shell supports them. For example
        /// ANSI escape sequences will be used on Linux systems but not on
        /// Windows systems.
        USEANSI_IF_SUPPORTED
    };

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new StdOutput.
     *
     * \param verbosity_level The initial level of verbosity of this output.
     * \param use_ansi Whether ANSI escape sequences will be used to decorate
     *                 the output messages.
     */
    StdOutput(
            arc::log::Verbosity verbosity_level = arc::log::VERBOSITY_NOTICE,
            UseANSI use_ansi = USEANSI_IF_SUPPORTED);

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    // override
    virtual void write(
            arc::log::Verbosity verbosity,
            const arc::log::Profile& profile,
            const arc::str::UTF8String& message);

    /*!
     * \brief Returns whether ANSI escape sequences will be used to decorate the
     *        output messages.
     */
    UseANSI get_use_ansi() const;

    /*!
     * \brief Sets whether ANSI escape sequences will be used to decorate the
     *        output messages.
     */
    void set_use_ansi(UseANSI use_ansi);

private:

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Whether ANSI escape sequences should be used or not.
     */
    UseANSI m_use_ansi;
};

} // namespace log
} // namespace arc

#endif
