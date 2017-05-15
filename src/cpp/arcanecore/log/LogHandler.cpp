#include "arcanecore/log/LogHandler.hpp"

#include <arcanecore/base/Exceptions.hpp>

#include "arcanecore/log/AbstractOutput.hpp"
#include "arcanecore/log/Input.hpp"


namespace arc
{
namespace log
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

LogHandler::LogHandler()
{
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

LogHandler::~LogHandler()
{
    // do nothing -- required for using std::unique_ptr with forward
    // declarations.
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

arc::log::Input* LogHandler::vend_input(const arc::log::Profile& profile)
{
    std::unique_ptr<Input> input(new Input(this, profile));
    arc::log::Input* ptr = input.get();
    m_inputs.push_back(std::move(input));
    return ptr;
}

bool LogHandler::remove_input(arc::log::Input* input)
{
    for(auto it = m_inputs.begin(); it != m_inputs.end(); ++it)
    {
        if(it->get() == input)
        {
            m_inputs.erase(it);
            return true;
        }
    }
    return true;
}

const LogHandler::OutputVector& LogHandler::get_outputs() const
{
    return m_outputs;
}

arc::log::AbstractOutput* LogHandler::add_output(
        arc::log::AbstractOutput* output)
{
    // check that we're not already holding the output
    ARC_FOR_EACH(it, m_outputs)
    {
        if(it->get() == output)
        {
            throw arc::ex::ValueError(
                "LogHandler already contains a pointer to the given output.");
        }
    }

    // add with a unique pointer
    std::unique_ptr<AbstractOutput> out(output);
    m_outputs.push_back(std::move(out));

    return output;
}

bool LogHandler::remove_output(arc::log::AbstractOutput* output)
{
    bool removed = false;
    OutputVector::iterator it;
    for(it = m_outputs.begin(); it != m_outputs.end();)
    {
        if(it->get() == output)
        {
            it = m_outputs.erase(it);
            removed = true;
        }
        else
        {
            ++it;
        }
    }

    return removed;
}

} // namespace log
} // namespace arc
