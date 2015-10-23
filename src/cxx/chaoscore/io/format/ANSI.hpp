/*!
 * \file
 * \brief Operations relating to ANSI codes.
 * author David Saxon
 */
#ifndef CHAOSCORE_IO_FORMAT_ANSI_HPP_
#define CHAOSCORE_IO_FORMAT_ANSI_HPP_

#include "chaoscore/base/string/UTF8String.hpp"

namespace chaos
{
namespace io
{
namespace format
{

//------------------------------------------------------------------------------
//                                  ENUMERATORS
//------------------------------------------------------------------------------

enum ANSIColour
{
    ANSI_FG_DEFAULT       = 39,
    ANSI_FG_BLACK         = 30,
    ANSI_FG_WHITE         = 97,
    ANSI_FG_RED           = 31,
    ANSI_FG_GREEN         = 32,
    ANSI_FG_YELLOW        = 33,
    ANSI_FG_BLUE          = 34,
    ANSI_FG_MAGENTA       = 35,
    ANSI_FG_CYAN          = 36,
    ANSI_FG_LIGHT_GREY    = 37,
    ANSI_FG_DARK_GREY     = 90,
    ANSI_FG_LIGHT_RED     = 91,
    ANSI_FG_LIGHT_GREEN   = 92,
    ANSI_FG_LIGHT_YELLOW  = 93,
    ANSI_FG_LIGHT_BLUE    = 94,
    ANSI_FG_LIGHT_MAGENTA = 95,
    ANSI_FG_LIGHT_CYAN    = 96,
    ANSI_BG_DEFAULT       = 49,
    ANSI_BG_RED           = 41,
    ANSI_BG_GREEN         = 42,
    ANSI_BG_BLUE          = 44
};

enum ANSIAttribute
{
    ANSI_ATTR_NONE,
    ANSI_ATTR_BOLD,
    ANSI_ATTR_UNDERSCORE,
    ANSI_ATTR_BLINK,
    ANSI_ATTR_REVERSE
};

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief TODO
 *
 * \TODO:
 */
chaos::str::UTF8String apply_escape_sequence(
        const chaos::str::UTF8String& s,
              ANSIColour              colour,
              ANSIAttribute           attribute = ANSI_ATTR_NONE );

} // namespace format
} // namespace io
} // namespace chaos

#endif
