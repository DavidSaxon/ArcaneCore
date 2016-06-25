#include "arcanecore/io/format/FormatOperations.hpp"

namespace arc
{
namespace io
{
namespace format
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

void centre_text(
        arc::str::UTF8String& text,
        const arc::uint32     line_length,
        bool                    trim_trailing )
{
    // is the text too long?
    if ( text.get_length() >= line_length )
    {
        return;
    }

    // get the amount of whitespace to add
    arc::uint32 whitespace = line_length - text.get_length();
    arc::uint32 half = whitespace / 2;

    // prefix white-space
    arc::str::UTF8String s( " " );
    s *= ( whitespace - half );
    // text
    s << text;
    // trailing whitespace
    if ( !trim_trailing )
    {
        s << arc::str::UTF8String( " " ) * half;
    }

    // done
    text.assign( s );
}

} // namespace format
} // namespace io
} // namespace arc
