#include "chaoscore/io/format/FormatOperations.hpp"

namespace chaos
{
namespace io
{
namespace format
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

void centre_text(
        chaos::uni::UTF8String& text,
        const chaos::uint32     line_length,
        bool                    trim_trailing )
{
    // is the text too long?
    if ( text.get_length() >= line_length )
    {
        return;
    }

    // get the amount of whitespace to add
    chaos::uint32 whitespace = line_length - text.get_length();
    chaos::uint32 half = whitespace / 2;

    // prefix white-space
    chaos::uni::UTF8String s( " " );
    s *= ( whitespace - half );
    // text
    s << text;
    // trailing whitespace
    if ( !trim_trailing )
    {
        s << chaos::uni::UTF8String( " " ) * half;
    }

    // done
    text.assign( s );
}

} // namespace format
} // namespace io
} // namespace chaos
