/*!
 * \file
 * \brief Operations relating to string formatting.
 * author David Saxon
 */
#ifndef CHAOSCORE_IO_FORMATOPERATIONS_HPP_
#define CHAOSCORE_IO_FORMATOPERATIONS_HPP_

#include "chaoscore/base/uni/UTF8String.hpp"

namespace chaos
{
namespace io
{
namespace format
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief Centres the given text with whitespace on either side so that has a
 *        symbol length equal to line_length.
 *
 * If the symbol length of the text is greater than line_length then the text
 * will be left unmodified.
 *
 * \param text The text to be centered.
 * \param line_length The desired number of symbols in the line after this
 *                    operation has taken place.
 * \param trim_trailing whether trailing whitespace should be not be added.
 */
void centre_text(
        chaos::uni::UTF8String& text,
        const chaos::uint32     line_length,
        bool                    trim_trailing = false );

} // namespace format
} // namespace io
} // namespace chaos

#endif
