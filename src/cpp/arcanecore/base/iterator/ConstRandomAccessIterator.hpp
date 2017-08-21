/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_BASE_ITERATOR_CONSTRANDOMACCESSITERATOR_HPP_
#define ARCANECORE_BASE_ITERATOR_CONSTRANDOMACCESSITERATOR_HPP_

#include <iterator>


namespace arc
{
namespace iterator
{

/*!
 * \brief A random access iterator for a contiguous read-only data block.
 *
 * \tparam T_DataType The type of the data being iterated.
 */
template<typename T_DataType>
class ConstRandomAccessIterator
    : public std::iterator<std::random_access_iterator_tag, T_DataType>
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Constructs a new ConstRandomAccessIterator that points to null
     *        data.
     */
    ConstRandomAccessIterator()
        : m_data_ptr(nullptr)
    {
    }

    /*!
     * \brief Constructs a new ConstRandomAccessIterator that point to the
     *        given data.
     */
    ConstRandomAccessIterator(const T_DataType* data_ptr)
        : m_data_ptr(data_ptr)
    {
    }

    /*!
     * \brief Copy constructor.
     */
    ConstRandomAccessIterator(const ConstRandomAccessIterator& other)
        : m_data_ptr(other.m_data_ptr)
    {
    }

    /*!
     * \brief Move constructor.
     */
    ConstRandomAccessIterator(ConstRandomAccessIterator&& other)
        : m_data_ptr(other.m_data_ptr)
    {
        other.m_data_ptr = nullptr;
    }

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~ConstRandomAccessIterator()
    {
    }

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assigns the data being iterated.
     */
    ConstRandomAccessIterator& operator=(const T_DataType* data_ptr)
    {
        m_data_ptr = data_ptr;
        return *this;
    }

    /*!
     * \brief Copy assignment.
     */
    ConstRandomAccessIterator& operator=(const ConstRandomAccessIterator& other)
    {
        m_data_ptr = other.m_data_ptr;
        return *this;
    }

    /*!
     * \brief Move assignment.
     */
    ConstRandomAccessIterator& operator=(ConstRandomAccessIterator&& other)
    {
        m_data_ptr = other.m_data_ptr;
        other.m_data_ptr = nullptr;
        return *this;
    }

    /*!
     * \brief Equality operator.
     */
    bool operator==(const ConstRandomAccessIterator& other) const
    {
        return m_data_ptr == other.m_data_ptr;
    }

    /*!
     * \brief Inequality operator.
     */
    bool operator!=(const ConstRandomAccessIterator& other) const
    {
        return m_data_ptr != other.m_data_ptr;
    }

    /*!
     * \brief Greater than operator.
     */
    bool operator>(const ConstRandomAccessIterator& other) const
    {
        return m_data_ptr > other.m_data_ptr;
    }

    /*!
     * \brief Greater than or equal to operator.
     */
    bool operator>=(const ConstRandomAccessIterator& other) const
    {
        return m_data_ptr >= other.m_data_ptr;
    }

    /*!
     * \brief Less than operator.
     */
    bool operator<(const ConstRandomAccessIterator& other) const
    {
        return m_data_ptr < other.m_data_ptr;
    }

    /*!
     * \brief Less than or equal to operator.
     */
    bool operator<=(const ConstRandomAccessIterator& other) const
    {
        return m_data_ptr <= other.m_data_ptr;
    }

    /*!
     * \brief Returns the underlying data value this iterator points to.
     */
    const T_DataType& operator*() const
    {
        return *m_data_ptr;
    }

    /*!
     * \brief Returns the underlying data value this iterator points to.
     */
    const T_DataType& operator->() const
    {
        return *m_data_ptr;
    }

    /*!
     * \brief Returns a new iterator that is moved forward from this iterator by
     *        given amount.
     */
    ConstRandomAccessIterator operator+(int amount) const
    {
        return ConstRandomAccessIterator(m_data_ptr + amount);
    }

    /*!
     * \brief Moves this iterator forward by the given amount.
     */
    ConstRandomAccessIterator& operator+=(int amount)
    {
        m_data_ptr += amount;
    }

    /*!
     * \brief Moves this iterator forward by one position.
     */
    ConstRandomAccessIterator& operator++()
    {
        ++m_data_ptr;
        return *this;
    }

    /*!
     * \brief Returns a new iterator at the current position and moves this
     *        iterator forward by one position.
     */
    ConstRandomAccessIterator operator++(int amount)
    {
        ConstRandomAccessIterator temp(*this);
        ++m_data_ptr;
        return temp;
    }

    /*!
     * \brief Returns a new iterator that is moved backward from this iterator
     *        by given amount.
     */
    ConstRandomAccessIterator operator-(int amount) const
    {
        return ConstRandomAccessIterator(m_data_ptr - amount);
    }

    /*!
     * \brief Moves this iterator backward by the given amount.
     */
    ConstRandomAccessIterator& operator-=(int amount)
    {
        m_data_ptr -= amount;
    }

    /*!
     * \brief Moves this iterator backward by one position.
     */
    ConstRandomAccessIterator& operator--()
    {
        --m_data_ptr;
        return *this;
    }

    /*!
     * \brief Returns a new iterator at the current position and moves this
     *        iterator backward by one position.
     */
    ConstRandomAccessIterator operator--(int amount)
    {
        ConstRandomAccessIterator temp(*this);
        --m_data_ptr;
        return temp;
    }

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief Pointer to the data being iterated.
     */
    const T_DataType* m_data_ptr;
};

} // namespace iterator
} // namespace arc

#endif
