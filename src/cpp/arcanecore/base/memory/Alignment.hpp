#ifndef ARCANECORE_BASE_MEMORY_ALIGNMENT_HPP_
#define ARCANECORE_BASE_MEMORY_ALIGNMENT_HPP_

#include <new>

#include "arcanecore/base/Exceptions.hpp"
#include "arcanecore/base/Preproc.hpp"
#include "arcanecore/base/os/OSOperations.hpp"

// TODO: REMOVE ME
#include <iostream>

/*!
 * \brief Declaration specifier to set the minimum alignment of the the type in
 *        bytes.
 */
#define ARC_MEMORY_ALIGN(Alignment)

#if defined(__GNUC__)
    #undef ARC_MEMORY_ALIGN
    #define ARC_MEMORY_ALIGN(Alignment) __attribute__((aligned(Alignment)))

#elif defined(_MSC_VER)
    #undef ARC_MEMORY_ALIGN
    #define ARC_MEMORY_ALIGN(Alignment) __declspec(align(Alignment))

#elif defined(__INTEL_COMPILER)
    #undef ARC_MEMORY_ALIGN
    #define ARC_MEMORY_ALIGN(Alignment) __attribute__((aligned(Alignment)))

#endif


namespace arc
{
namespace memory
{

/*!
 * \brief Base class for objects that require non-standard (8-byte) alignment on
 *        the heap.
 */
template<class T_DerivedClass>
class AlignedBase
{
private:

    /*!
     * \brief The expected alignment of the the derived class.
     *
     * This cannot be smaller than sizeof(void*) as this is the minimum
     * alignable size.
     */
    static constexpr std::size_t ALIGNMENT =
        (alignof(T_DerivedClass) < sizeof(void*)) ?
            sizeof(void*) : alignof(T_DerivedClass);

public:

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    void* operator new(std::size_t count) throw()
    {
        #if defined(__GNUC__) || defined(__INTEL_COMPILER)

            std::cout << "ALIGNED NEW: " << ALIGNMENT << " : " << count
                      << std::endl;

            void* ptr = nullptr;
            int error_code = posix_memalign(&ptr, ALIGNMENT, count);
            // int error_code = posix_memalign(&ptr, 4, count);
            // TODO TEST ERROR
            if(error_code != 0)
            {
                std::cout << "error code: " << error_code << std::endl;
            }
            return ptr;


        #elif defined(_MSC_VER)

            // TODO:

        #else

            throw arc::ex::NotImplementedError(
                "AlignedBase not implemented for this compiler"
            );

        #endif
    }

    // void* operator new(std::size_t count, void* ptr) throw()
    // {

    // }

    // void operator delete(void* ptr) throw()
    // {

    // }

    // void operator delete(void* ptr, void* place) throw()
    // {

    // }

    // void* operator new[](std::size_t count) throw()
    // {

    // }

    // void operator delete[](void* ptr) throw()
    // {

    // }
};

} // namespace memory
} // namespace arc

#endif
