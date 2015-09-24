/*!
 * \file
 *
 * \author David Saxon
 */
#ifndef CHAOSCORE_BASE_STRING_USTRING_HPP_
#define CHAOSCORE_BASE_STRING_USTRING_HPP_

#include <string>

#include "chaoscore/base/Types.hpp"

namespace chaos
{
namespace str
{

/*!
 * \brief A generic string type for storing Unicode data. TODO
 *
 * TODO: detailed description
 *
 * TODO: Is NULL terminated data
 */
class UTF8String
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Default constructor.
     *
     * TODO: DOC
     */
    UTF8String();

    /*!
     * \brief String literal constructor.
     *
     * TODO: DOC
     */
    UTF8String( const char* data );

    /*!
     * \brief TODO: DOC
     *
     * TODO: DOC
     */
    UTF8String( const char* data, size_t length );

    /*!
     * \brief Copy constructor.
     *
     * Creates a new UTF8String from a copy of the values from the given
     * UTF8String.
     *
     * \param other UTF8String to copy from.
     */
    UTF8String( const UTF8String& other );


    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~UTF8String();

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assignment operator.
     *
     * Assigns the internal of data this UTF8String as a copy from the internal
     * data of the provided UTF8String.
     *
     * Is the same as calling assign( const UTF8String& ).
     *
     * \param other UTF8String to copy internal data from.
     * \return A reference to this UTF8String after the assignment has taken
     *         place.
     */
    const UTF8String& operator=( const UTF8String& other );

    /*!
     * \brief Equality operator.
     *
     * Compares whether this UTF8String and the other given UTF8String are
     * considered equal.
     *
     * \param other UTF8String to compare this against.
     * \return Whether the strings are equal.
     */
    bool operator==( const UTF8String& other ) const;

    /*!
     * \brief Inequality operator.
     *
     * Compares whether this UTF8String and the other given UTF8String are
     * considered not equal.
     * \param other UTF8String to compare this against.
     * \return Whether the strings are not equal.
     */
    bool operator!=( const UTF8String& other ) const;

    /*!
     * \brief Less than operator.
     *
     * Compares whether this UTF8String is less than the other given UTF8String.
     *
     * Less than is defined by performing a value comparison between each
     * Unicode code point in the string.
     *
     * \warning correct implementation in progress
     *
     * \param other UTF8String to compare against.
     * \return Whether this UTF8String is less than the other.
     */
    bool operator<( const UTF8String& other ) const;

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assigns the internal data of this UTF8String to the given string
     *        literal.
     *
     * This operation will delete any current internal data of this object. The
     * input data is expected to be utf-8 encoded and NULL terminated.
     *
     * \param data Data buffer to copy from.
     */
    void assign( const char* data );

    /*!
     * \brief Assigns the internal data of this UTF8String to the data buffer.
     *
     * This operation will delete any current internal data of this object. The
     * input data is expected to be utf-8 encoded and NULL terminated.
     *
     * \param data Data buffer to copy from.
     */
    void assign( const chaos::int8* data );

    /*!
     * \brief Assigns internal data from another UTF8String.
     *
     * Assigns the internal of data this UTF8String as a copy from the internal
     * data of the provided UTF8String.
     *
     * \param other UTF8String to copy internal data from.
     */
    void assign( const UTF8String& other );

    /*!
     * \return Whether the this UTF8String contains any characters or not.
     */
    bool isEmpty() const;

     /*!
      * \brief Returns this as a standard library string.
      *
      * \return the std::string representation of this UTF8String.
      */
    std::string toStdString() const;

    //--------------------------------ACCESSORS---------------------------------

    /*!
     * /brief Return the length of this UTF8String
     *
     * The length is defined how many utf-8 symbols there are in the string,
     * this length doesn't not necessarily equal the byte length of the string.
     *
     * \return The number of utf-8 symbols in this UTF8String.
     */
    size_t getLength() const;

    // TODO: add [] operators
    /*!
     * \brief Get the utf-8 symbol defined at the given index.
     *
     * \todo implement correctly
     *
     * \throws chaos::ex::IndexOutOfBoundsError If the provided index is out of
                                                bounds of the string length.
     *
     * \param index Position of the symbol to retrieve in the string with
     *              respect to the length returned by getLength()
     * \return A UTF8String containing the single utf-8 symbol at the given
     *         index.
     */
    UTF8String getSymbol( size_t index );

    /*!
     * \brief Get the length of the internal buffer data in bytes.
     *
     * This is exactly the number of bytes in the internal raw data of this
     * UTF8String which can be accessed through getRawData(). Note that this
     * data is NULL ('\0') terminated and this length includes the NULL
     * terminator. Therefore if UTF8String == "" then getByteLength() == 1.
     *
     * \note This is not equal to the character length of the string as utf-8
     *       encoded characters can take up multiple bytes.
     *
     * \return The length of the internal data.
     */
    size_t getByteLength() const;

    /*!
     * \brief Get the raw byte data of this UTF8String.
     *
     * \return a pointer to a constant representation of the internal data.
     */
    const chaos::int8* getRawData() const;

    //--------------------------------------------------------------------------


    //------------------------------DEV FUNCTIONS-------------------------------

    // TODO: REMOVE ME
    // TESTING FUNCTION
    void dev_inspectContents();

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    // the array containing the data stored as consecutive bytes
    chaos::int8* m_data;
    // the length of the data int bytes (not the length of the string)
    size_t m_dataLength;

    // the number of utf-8 symbols in this string
    size_t m_length;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \internal
     *
     * Internal function used for assigning raw data to this UTF8String. The
     * input data is expect to be 1-byte aligned and been utf-8 encoded. This
     * function will delete any existing internal data, and allocate storage
     * for the new data.
     *
     * \param data The input data to assign to the internal buffer
     * \param existingLength Optimisation parameter. If equal to
     *                       std::string::npos the length of the data will be
     *                       evaluated, however if already known the length can
     *                       be passed in here to skip this step.
     */
    void assign_internal(
            const void* data,
            size_t existingLength = std::string::npos );
};


} // namespace str
} // namespace chaos

#endif
