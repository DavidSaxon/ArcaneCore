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
     * \brief Less than operator.
     *
     * Compares whether this UTF8String is less than the other given UTF8String.
     *
     * Is the same as calling lexicographicalCompare( const UTF8String& ).
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
     * input data is expected to be utf-8 encoded.
     *
     * \param data Data buffer to copy from.
     */
    void assign( const char* data );

    /*!
     * \brief Assigns the internal data of this UTF8String to the data buffer.
     *
     * This operation will delete any current internal data of this object. The
     * input data is expected to be utf-8 encoded.
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
     * \brief Compares whether this UTF8String is less than the other given
              UTF8String.
     *
     * Less than is defined by performing a value comparison between each
     * Unicode code point in the string.
     *
     * \warning correct implementation in progress
     *
     * \param other UTF8String to perform a lexicographical comparison with.
     * \return Whether this UTF8String is considered less than the other */
     bool lexicographicalCompare( const UTF8String& other ) const;

     /*!
      * \brief Returns this as a standard library string.
      *
      * \return the std::string representation of this UTF8String.
      */
    std::string toStdString() const;


    //------------------------------DEV FUNCTIONS-------------------------------

    // TODO: REMOVE ME
    // TESTING FUNCTION
    void dev_inspectContents();

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    // internal attribute that represents whether this has any data assigned yet
    bool m_holdsData;

    // the array containing the data stored as consecutive bytes
    chaos::int8* m_data;
    // the length of the data int bytes (not the length of the string)
    size_t m_dataLength;

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
