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
template<class T_derived_class>
class AlignedBase
{
private:

    /*!
     * \brief The minimum size memory can be aligned to.
     */
    static const std::size_t s_minimum_alignment = sizeof(void*);

public:

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    void* operator new(std::size_t count) throw()
    {
        // TODO: check requirements on multiplies
        // calculate alignment
        std::size_t alignment = alignof(T_derived_class);
        if(alignment < s_minimum_alignment)
        {
            alignment = s_minimum_alignment;
        }

        #if defined(__GNUC__) || defined(__INTEL_COMPILER)

            void* ptr = nullptr;
            int error_code = posix_memalign(&ptr, alignment, count);
            // TODO TEST ERROR
            if(error_code != 0)
            {
                std::cout << "error code: " << error_code << std::endl;
            }
            return ptr;


        #elif defined(_MSC_VER)

            void* ptr = _aligned_malloc(count, alignment);
            if(ptr = nullptr)
            {
                // TODO:
                std::cout << "ALIGN MALLOC FAILURE" << std::endl;
            }
            return ptr;

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
