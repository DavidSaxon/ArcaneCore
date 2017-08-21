/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_BASE_CONTAINER_CONSTWEAKARRAY_HPP_
#define ARCANECORE_BASE_CONTAINER_CONSTWEAKARRAY_HPP_

#include "arcanecore/base/iterator/ConstRandomAccessIterator.hpp"


namespace arc
{
namespace container
{

/*!
 * \brief A stl style container that points to contiguous block of read-only
 *        data that is not owned by this object.
 *
 * This means the validity of this object is use-case specific. The data is only
 * valid until it is deleted by the owner, in which case this object has no way
 * of determining if the data is valid or not.
 *
 * \tparam T_DataType The type of the data this array contains.
 */
template<typename T_DataType>
class ConstWeakArray
{
public:

    //--------------------------------------------------------------------------
    //                              TYPE DEFINITIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief The iterator type of the ConstWeakArray.
     */
    typedef arc::iterator::ConstRandomAccessIterator<T_DataType> iterator;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Constructs a new weak array with no underlying memory.
     */
    ConstWeakArray()
        : m_data(nullptr)
        , m_size(0)
    {
    }

    /*!
     * \brief Constructs a new array that points to the given data.
     *
     * \param data The data this array will hold a weak reference to.
     * \param size The number of elements in the provided data.
     */
    ConstWeakArray(const T_DataType* data, std::size_t size)
        : m_data(data)
        , m_size(size)
    {
    }

    /*!
     * \brief Copy constructor.
     */
    ConstWeakArray(const ConstWeakArray& other)
        : m_data(other.m_data)
        , m_size(other.m_size)
    {
    }

    /*!
     * \brief Move constructor.
     */
    ConstWeakArray(ConstWeakArray&& other)
        : m_data(other.m_data)
        , m_size(other.m_size)
    {
        other.m_data = nullptr;
        other.m_size = 0;
    }

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~ConstWeakArray()
    {
        // no deleting!
    }

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Copy assignment operator.
     */
    ConstWeakArray& operator=(const ConstWeakArray& other)
    {
        m_data = other.m_data;
        m_size = other.m_size;

        return *this;
    }

    /*!
     * \brief Move assignment operator.
     */
    ConstWeakArray& operator=(ConstWeakArray&& other)
    {
        m_data = other.m_data;
        m_size = other.m_size;

        other.m_data = nullptr;
        other.m_size = 0;

        return *this;
    }

    /*!
     * \brief Equality operator.
     */
    bool operator==(const ConstWeakArray& other)
    {
        return m_data == other.m_data && m_size == other.m_size;
    }

    /*!
     * \brief Inequality operator.
     */
    bool operator!=(const ConstWeakArray& other)
    {
        return !((*this) == other);
    }

    /*!
     * \brief Returns the element of the array at the given index.
     */
    const T_DataType& operator[](std::size_t index) const
    {
        return at(index);
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Returns the number of elements in this array.
     */
    std::size_t size() const
    {
        return m_size;
    }

    /*!
     * \brief Returns whether the vector is empty.
     */
    bool empty() const
    {
        return m_size == 0;
    }

    /*!
     * \brief Returns the element of the array at the given index.
     */
    const T_DataType& at(std::size_t index) const
    {
        return m_data[index];
    }

    /*!
     * \brief Returns the first element in the array.
     */
    const T_DataType& front() const
    {
        return m_data[0];
    }

    /*!
     * \brief Returns the last element in the array.
     */
    const T_DataType& back() const
    {
        return m_data[m_size - 1];
    }

    /*!
     * \brief Returns an iterator to the first element in this array.
     */
    iterator begin() const
    {
        return iterator(m_data);
    }

    /*!
     * \brief Returns an iterator referring to the past-the-end element in this
     *        array.
     */
    iterator end() const
    {
        // note: works for empty data since m_size is 0
        return iterator(m_data + m_size);
    }

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    // the non-owned data of this array
    const T_DataType* m_data;
    // the number of element in this array
    std::size_t m_size;
};

} // namespace container
} // namespace arc

#endif
