/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_LOG_LOGHANDLER_HPP_
#define ARCANECORE_LOG_LOGHANDLER_HPP_

#include <map>
#include <memory>
#include <vector>

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

class AbstractOutput;
class Input;

/*!
 * \brief Object that handles the association of logging inputs and outputs.
 *
 * A default arc::log::LogHandler instance is provided with ArcaneCore logging:
 * arc::log::default_handler.
 */
class LogHandler
    : private arc::lang::Noncopyable
    , private arc::lang::Nonmovable
    , private arc::lang::Noncomparable
{
public:

    //--------------------------------------------------------------------------
    //                              TYPE DEFINITIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief std::vector containing unique pointers to arc::log::Input objects.
     */
    typedef std::vector<std::unique_ptr<arc::log::Input>> InputVector;
    /*!
     * \brief std::vector containing unique pointers to arc::log::AbstractOutput
     *        objects.
     */
    typedef std::vector<std::unique_ptr<arc::log::AbstractOutput>> OutputVector;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new Logging object.
     *
     * LogHandlers are initialised with no input or outputs associated.
     */
    LogHandler();

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~LogHandler();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates and returns a new arc::log::Input associated with and
     *        owned by this log handler.
     *
     * \param profile The logging profile to use with this input.
     */
    arc::log::Input* vend_input(
            const arc::log::Profile& profile = arc::log::Profile());

    /*!
     * \brief Removes the given input from this LogHandler.
     *
     * \param output The pointer to the input to remove.
     *
     * \returns Whether the input exists in this log handler to be removed or
     *          not.
     */
    bool remove_input(arc::log::Input* input);

    /*!
     * \brief Returns a vector containing the arc::log::Output objects
     *        associated with this log handler.
     */
    const OutputVector& get_outputs() const;

    /*!
     * \brief Adds a new output writer to this LogHandler.
     *
     * \note The LogHandler will take ownership of the given output writer and
     *       will handle deleting it.
     *
     * \return The pointer to the given output.
     *
     * \throws arc::ex::ValueError If this LogHandler already holds a pointer
     *                               to the given writer.
     */
    arc::log::AbstractOutput* add_output(arc::log::AbstractOutput* output);

    /*!
     * \brief Removes the given output from this LogHandler.
     *
     * \param output The pointer to the output to remove.
     *
     * \returns Whether the output exists in this log handler to be removed or
     *          not.
     */
    bool remove_output(arc::log::AbstractOutput* output);

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The input streams attached to this LogHandler.
     */
    InputVector m_inputs;

    /*!
     * \brief The output writers of this log LogHandler.
     */
    OutputVector m_outputs;
};

} // namespace log
} // namespace arc

#endif
