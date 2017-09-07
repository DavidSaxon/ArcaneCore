/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_CRYPT_SPOOKYHASH_HPP_
#define ARCANECORE_CRYPT_SPOOKYHASH_HPP_

#include <arcanecore/base/Preproc.hpp>
#include <arcanecore/base/Types.hpp>
#include <arcanecore/base/lang/Restrictors.hpp>


namespace arc
{
namespace crypt
{

// TODO: DOC
class SpookyHash
    : private arc::lang::Noncopyable
    , private arc::lang::Nonmovable
    , private arc::lang::Noncomparable
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    // TODO:
};

} // namespace crypt
} // namespace arc

#endif
