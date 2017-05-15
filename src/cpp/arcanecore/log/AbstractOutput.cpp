#include "arcanecore/log/AbstractOutput.hpp"

namespace arc
{
namespace log
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

AbstractOutput::AbstractOutput(arc::log::Verbosity verbosity_level)
    :
    m_enabled        (true),
    m_verbosity_level(verbosity_level)
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

bool AbstractOutput::is_enabled() const
{
    return m_enabled;
}

void AbstractOutput::set_enabled(bool enabled)
{
    m_enabled = enabled;
}

arc::log::Verbosity AbstractOutput::get_verbosity_level() const
{
    return m_verbosity_level;
}

void AbstractOutput::set_verbosity_level(arc::log::Verbosity verbosity_level)
{
    m_verbosity_level = verbosity_level;
}

} // namespace log
} // namespace arc
