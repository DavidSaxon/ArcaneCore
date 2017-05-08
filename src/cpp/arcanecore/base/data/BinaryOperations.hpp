/*!
 * \file
 * \brief functions for manipulating and reading binary data.
 * \author David Saxon
 */
#ifndef ARCANECORE_BASE_DATA_BINARYOPERATIONS_HPP_
#define ARCANECORE_BASE_DATA_BINARYOPERATIONS_HPP_

namespace arc
{
namespace data
{

//------------------------------------------------------------------------------
//                                  ENUMERATORS
//------------------------------------------------------------------------------

/*!
 * \brief The possible endian types.
 */
enum Endianness
{
    /// The least-significant byte is stored at the highest memory address.
    ENDIAN_BIG = 0,
    /// The least-significant byte is stored at the lowest memory address.
    ENDIAN_LITTLE
};

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief Returns the endianness of the current system this is running on.
 */
Endianness get_system_endianness();

/*!
 * \brief Casts the given value from T_in_type to T_out_type without changing
 *        the bits of the data.
 */
template<typename T_out_type, typename T_in_type>
T_out_type bit_cast(const T_in_type& v)
{
    return *((T_out_type*)&v);
}

} // namespace data
} // namespace arc

#endif
