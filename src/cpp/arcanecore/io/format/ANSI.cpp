#include "chaoscore/io/format/ANSI.hpp"

namespace chaos
{
namespace io
{
namespace format
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

void apply_escape_sequence(
        chaos::str::UTF8String& text,
        ANSIColour              colour,
        ANSIAttribute           attribute )
{
    // start the opening escape sequence
    chaos::str::UTF8String r( "\033[" );
    // write the attribute
    switch ( attribute )
    {
        case ANSI_ATTR_NONE:
        {
            r << "00;";
            break;
        }
        case ANSI_ATTR_BOLD:
        {
            r << "01;";
            break;
        }
        case ANSI_ATTR_UNDERSCORE:
        {
            r << "04;";
            break;
        }
        case ANSI_ATTR_BLINK:
        {
            r << "05;";
            break;
        }
        case ANSI_ATTR_REVERSE:
        {
            r << "07;";
            break;
        }
    }
    // write the colour
    r << static_cast< chaos::uint32 >( colour ) << "m";
    // write the string and closing sequence
    r << text << "\033[00m";
    // done
    text.assign( r );
}

} // namespace format
} // namespace io
} // namespace chaos
