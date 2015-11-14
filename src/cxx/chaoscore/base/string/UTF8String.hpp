/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_BASE_STRING_UTF8STRING_HPP_
#define CHAOSCORE_BASE_STRING_UTF8STRING_HPP_

#include <ostream>
#include <string>
#include <vector>

#include "chaoscore/base/Types.hpp"

namespace chaos
{
namespace str
{

/*!
 * \brief A string type designed for storing and manipulating UTF-8 encoded
 *        text.
 *
 * \note This object expects input text to already be UTF-8 encoded. For
 *       functions to convert encodings see UnicodeUtil.hpp
 *
 * The UTF8String data type is used extensively throughout ChaosCore and other
 * Chaos Foundation projects.
 *
 * ChaosCore stands by the principle that all string handling should be Unicode
 * aware. The `char` primitive should only be used for storing and manipulation
 * raw byte data, not for representing entire language characters. Furthermore
 * ChaosCore considers UTF-8 to be the only default encoding type for Unicode
 * text. Other encodings should only be used for special cases or interacting
 * with applications that require a different encoding (such as the Windows
 * API). For more info see http://utf8everywhere.org/
 *
 * For practicality the internal byte of an UTF8String is NULL terminated. This
 * means the raw data can easily be used as native C style strings.
 *
 * \par A Brief Introduction to UTF-8
 *
 * In order to fully make use of the UTF8String type's functionality its useful
 * to understand the UTF-8 encoding method.
 *
 * UTF-8 encodes each Unicode symbol in 1-4 bytes. The value of each symbol maps
 * directly to a Unicode code point that represents the symbol. For example:
 *
 * - "a" is stored using one byte with the hex value 0x61 or binary value
 *   `01100001`
 * - "ל" is stored using two bytes with the hex value 0xD79C or binary value
 *   `11010111 10011100`
 * - "∑" is stored using three bytes with the hex value 0xE28891 or binary
 *   value `11100010 10001000 10010001`
 * - "𝄞" is stored  using four bytes with the hex value 0xF09D849E or binary
 *   value `11110000 10011101 10000100 10011110`
 *
 * The byte size of a UTF-8 symbol can be recognised by the bit pattern that
 * makes up the start of each byte:
 *
 * - One byte symbol: `0xxxxxxx`
 * - Two byte symbol: `110xxxxx 10xxxxxx`
 * - Three byte symbol: `1110xxxx 10xxxxxx 10xxxxxx`
 * - Four byte symbol: `11110xxx 10xxxxxx 10xxxxxx 10xxxxxx`
 *
 * \par UTF8String Usage
 *
 * Here follows an example of using the UTF8String type:
 *
 * We have a C style string that cannot be encoded correctly with ASCII
 * (In this case we are assuming the input string is encoded in UTF-8):
 *
 * \code
 * const char* cstring = "aל∑";
 * \endcode
 *
 * If we inspect the length of the string we get unexpected results:
 *
 * \code
 * strlen( cstring );
 * // output: 6
 * \endcode
 *
 * This is because while the string only contains 3 symbols it contains 6 bytes
 * which is what `strlen` is counting. Next we construct a UTF8String using the
 * c string data, and inspect it's length:
 *
 * \code
 * chaos::str::UTF8String utf8( cstring );
 * utf8.get_length();
 * // output: 3
 * utf8.get_byte_length()
 * // output: 6
 * \endcode
 *
 * [TODO: iterator]
 * We can now inspect each symbol in the string:
 *
 * \code
 * for ( size_t i = 0; i < utf8.get_length(); ++i )
 * {
 *     chaos::str::UTF8String symbol( utf8.get_symbol( i ) );
 * }
 * \endcode
 *
 * Note that the symbol is returned as an UTF8String itself, this is due to the
 * fact that symbol has a variable byte-width so cannot be stored in a `char`,
 * nor is there any need to differentiate data types between a string of symbols
 * and an individual symbol.
 *
 * We can also inspect the byte-widths of each symbol in our string:
 *
 * \code
 * for ( size_t i = 0; i < utf8.get_length(); ++i )
 * {
 *     utf8.get_symbol_width( i );
 * }
 * // output: 1
 * // output: 2
 * // output: 3
 * \endcode
 *
 * The UTF8String class provides many convenience functions for manipulating
 * string data, such as `split`, `trim`, `starts_with`, `find_first`,
 * `to_cstring`, `to_stdstring`, etc.
 * \endcode
 */
class UTF8String
{
public:

    //--------------------------------------------------------------------------
    //                          PUBLIC STATIC ATTRIBUTES
    //--------------------------------------------------------------------------


    /*!
     * \brief Value that is used to return an index that does not exists within
     *        the UTF8String.
     */
    static const size_t npos;

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

    /*!
     * \brief Addition operator.
     *
     * Performs the same function as concatenate() but does not cause any
     * modifications to this string, instead returns a new string which contains
     * the results of the concatenation.
     *
     * \param other UTF8String to append to the end of a copy of this string.
     * \return UTF8String that contains the results of the concatenation.
     */
    UTF8String operator+( const UTF8String& other ) const;

    /*!
     * \brief Compound addition operator.
     *
     * Performs the same function as concatenate().
     *
     * \other UTF8String to append to the end of this string.
     * \return A reference to this UTF8String after the concatenation has taken
     *         place.
     */
    const UTF8String& operator+=( const UTF8String& other );

    /*!
     * \brief Multiplication operator.
     *
     * Performs the same function as repeat() but does not cause any
     * modifications to this string, instead returns a new string which contains
     * the results of the repeat.
     *
     * \param count the number of times to repeat the string
     * \return UTF8String that contains the results of the repeat.
     */
    UTF8String operator*( chaos::uint32 count );

    /*!
     * \brief Compound multiplication operator.
     *
     * Performs the same function as repeat().
     *
     * \param count the number of times to repeat this string.
     * \return A reference to this UTF8String after the repeat operation has
     *         taken place.
     */
    const UTF8String& operator*=( chaos::uint32 count );

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given other UTF8String.
     */
    UTF8String& operator<<( const UTF8String& other );

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given string literal.
     */
    UTF8String& operator<<( const char* other );

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given std string.
     */
    UTF8String& operator<<( const std::string& other );

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given boolean.
     */
    UTF8String& operator<<( bool other );

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given char.
     */
    UTF8String& operator<<( char other );

// TODO: how to solve the ambiguous problem
#ifdef CHAOS_OS_WINDOWS

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given unsigned long.
     */
    UTF8String& operator<<( unsigned long other );

#endif

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given int8.
     */
    UTF8String& operator<<( chaos::int8 other );

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given uint8.
     */
    UTF8String& operator<<( chaos::uint8 other );

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given int16.
     */
    UTF8String& operator<<( chaos::int16 other );

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given uint16.
     */
    UTF8String& operator<<( chaos::uint16 other );

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given int32.
     */
    UTF8String& operator<<( chaos::int32 other );

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given unsigned int32.
     */
    UTF8String& operator<<( chaos::uint32 other );

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given int64.
     */
    UTF8String& operator<<( chaos::int64 other );

    /*!
     * \brief Stream operator.
     *
     * Extends this UTF8String with the given unsigned int64.
     */
    UTF8String& operator<<( chaos::uint64 other );

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
     * \brief Assigns the internal data of this UTF8String to the given string
     *        literal.
     *
     * This operation will delete any current internal data of this object. The
     * input data is expected to be utf-8 encoded. This function should be used
     * when the input data is not NULL terminated, or can be used for
     * optimisation purposes if the length of data is already known. This will
     * mean the length of the data will not need to be evaluated internally.
     *
     * \param data Data buffer to copy from.
     * \param length Number of bytes in the provided data buffer.
     */
    void assign( const char* data, size_t length );

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
     * \brief Concatenates another UTF8String on to the end of this string.
     *
     * \other UTF8String to append to the end of this string.
     * \return A reference to this UTF8String after the concatenation has taken
     *         place.
     */
    UTF8String& concatenate( const UTF8String& other );

    /*!
     * \brief Extends this string with a repeat of itself the given number of
     *  times.
     *
     * This operation modifies this UTF8String.
     *
     * \throws chaos::ex::ValueError If the given number of times to repeat is
     *                               negative.
     * \param count The number of times to repeat this string.
     * \return A reference to this UTF8String after repeat has taken place.
     */
    UTF8String& repeat( chaos::uint32 count );

    /*!
     * \brief Checks whether this UTF8String starts with the given string.
     */
    bool starts_with( const UTF8String& substring ) const;

    /*!
     * \brief Finds the first occurrence of the given substring and returns the
     *        index of it.
     *
     * \param substring UTF8String to find the first occurrence of in this
     *                  string.
     * \return The index of the beginning of the first occurrence of the
     *         substring in this string. If the substring could not be found,
     *         chaos::str::UTF8String::npos is returned instead.
     */
    size_t find_first( const UTF8String& substring ) const;

    /*!
     * \brief Finds the last occurrence of the given substring and returns the
     *        index of it.
     *
     * \param substring UTF8String to find the last occurrence of in this
     *                  string.
     * \return The index of the beginning of the last occurrence of the
     *         substring in this string. If the substring could not be found,
     *         chaos::str::UTF8String::npos is returned instead.
     */
    size_t find_last( const UTF8String& substring ) const;

    /*!
     * \brief Splits this UTF8String by the given delimiter and places devisions
     *        into a vector.
     *
     * \param delimiter String to use as delimiter to split each sub-string on.
     * \return std::vector containing the results of the split.
     */
    const std::vector< UTF8String > split( const UTF8String& delimiter ) const;

    /*!
     * \brief Returns if this UTF8String represents a signed integer.
     */
    bool is_int() const;

    /*!
     * \brief Returns if this UTF8String represents an unsigned integer.
     */
    bool is_uint() const;

    /*!
     * \brief Returns whether this UTF8String represents a floating point
     *        number.
     */
    bool is_float() const;

    /*!
     * \brief Returns a UTF8String composed of a substring of this string.
     *
     * \throws chaos::ex::IndexOutOfBoundsError If the provided starting index
     *                                          is out of bounds of the string
     *                                          length.
     *
     * \param start Index of the symbol to start the substring from.
     * \param length the length of the substring. If greater than the possible
     *               symbols to allocate it will be clamped to the maximum
     *               length of the substring.
     * \return new UTF8String containing the substring.
     */
    UTF8String substring( size_t start, size_t length ) const;

    /*!
     * \brief Gets the raw byte data of this UTF8String as c style string
              (const char*).
     *
     * This function is the same as get_raw_data() except the data is casted to
     * const char*.
     *
     * \return a pointer to the c style string representation of the data.
     */
    const char* to_cstring() const;

    /*!
     * \brief Returns this as a standard library string.
     *
     * \return the std::string representation of this UTF8String.
     */
    std::string to_std_string() const;

    /*!
     * \brief Returns this UTF8String as an bool if the conversion is valid.
     *
     * \throws chaos::ex::ConversionDataError If the data of the string is not a
     *                                        a valid bool.
     */
    bool to_bool() const;

    /*!
     * \brief Returns this UTF8String as an int32 if the conversion is valid.
     *
     * \throws chaos::ex::ConversionDataError If the data of the string is not a
     *                                        a valid int32.
     */
    chaos::int32 to_int32() const;

    /*!
     * \brief Returns this UTF8String as an uint32 if the conversion is valid.
     *
     * \throws chaos::ex::ConversionDataError If the data of the string is not a
     *                                        a valid uint32.
     */
    chaos::uint32 to_uint32() const;

    /*!
     * \brief Returns this UTF8String as an int64 if the conversion is valid.
     *
     * \throws chaos::ex::ConversionDataError If the data of the string is not a
     *                                        a valid int64.
     */
    chaos::int64 to_int64() const;

    /*!
     * \brief Returns this UTF8String as an uint64 if the conversion is valid.
     *
     * \throws chaos::ex::ConversionDataError If the data of the string is not a
     *                                        a valid uint64.
     */
    chaos::int64 to_uint64() const;


    //--------------------------------ACCESSORS---------------------------------

    /*!
     * /brief Return the length of this UTF8String
     *
     * The length is defined how many utf-8 symbols there are in the string,
     * this length doesn't not necessarily equal the byte length of the string.
     *
     * \return The number of utf-8 symbols in this UTF8String.
     */
    size_t get_length() const;

    /*!
     * \return Whether the this UTF8String contains any characters or not.
     */
    bool is_empty() const;

    /*!
     * \brief Get the utf-8 symbol defined at the given index.
     *
     * \todo implement correctly
     *
     * \throws chaos::ex::IndexOutOfBoundsError If the provided index is out of
                                                bounds of the string length.
     *
     * \param index Position of the symbol to retrieve in the string with
     *              respect to the length returned by get_length()
     * \return A UTF8String containing the single utf-8 symbol at the given
     *         index.
     */
    UTF8String get_symbol( size_t index ) const;

    /*!
     * \brief Gets the integer/hex value for the utf8 symbol at the given index.
     *
     * \throws chaos::ex::IndexOutOfBoundsError If the provided index is out of
     *                                          bounds of the string length.
     *
     * \param index Position of the symbol to retrieve the value for with
     *              respect to the length returned by get_length()
     * \return A uint32 containing the value of the symbol.
     */
    chaos::uint32 get_symbol_value( size_t index ) const;

    /*!
     * \brief Gets the unicode code point for the utf8 symbol at the given
     *        index.
     *
     * \throws chaos::ex::IndexOutOfBoundsError If the provided index is out of
     *                                          bounds of the string length.
     *
     * \param index Position of the symbol to retrieve the code point for with
     *              respect to the length returned by get_length()
     * \return A uint32 containing the code point of the symbol.
     */
    chaos::uint32 get_code_point( size_t index ) const;

    /*!
     * \brief Gets the index of the first byte for the symbol at the given
     *        index.
     * \throws chaos::ex::IndexOutOfBoundsError If the provided index is out of
                                                bounds of the string length.
     */
    size_t get_byte_index_for_symbol_index( size_t symbol_index ) const;

    /*!
     * \brief Gets the size in bytes of the symbol at the given index.
     */
    size_t get_symbol_width( size_t index ) const;

    /*!
     * \brief Gets the length of the internal buffer data in bytes.
     *
     * This is exactly the number of bytes in the internal raw data of this
     * UTF8String which can be accessed through get_raw_data(). Note that this
     * data is NULL ('\0') terminated and this length includes the NULL
     * terminator. Therefore if UTF8String == "" then get_byte_length() == 1.
     *
     * \note This is not equal to the character length of the string as utf-8
     *       encoded characters can take up multiple bytes.
     *
     * \return The length of the internal data.
     */
    size_t get_byte_length() const;

    /*!
     * \brief Gets the symbol index for the given byte index.
     */
    size_t get_symbol_index_for_byte_index( size_t byte_index ) const;

    /*!
     * \brief Gets the width in bytes of the symbol at the given byte.
     *
     * \warning If the given byte index is not the start of a utf8 symbol this
     *          operation will return unexpected results.
     */
    size_t get_byte_width( size_t byte_index ) const;

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    // the array containing the data stored as consecutive bytes
    char* m_data;
    // the length of the data int bytes (not the length of the string)
    size_t m_data_length;

    // the number of utf-8 symbols in this string
    size_t m_length;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * Internal function used for assigning raw data to this UTF8String. The
     * input data is expect to be 1-byte aligned and been utf-8 encoded. This
     * function will delete any existing internal data, and allocate storage
     * for the new data.
     *
     * \param data The input data to assign to the internal buffer
     * \param existing_length Optimisation parameter. If equal to
     *                        std::string::npos the length of the data will be
     *                        evaluated, however if already known the length can
     *                        be passed in here to skip this step.
     */
    void assign_internal(
            const char*  data,
            size_t       existing_length = std::string::npos );

    /*!
     * Internal function used to check if a given index is within the symbol
     * length (get_length) of the string. If it is not an IndexOutOfBoundsError
     * is thrown.
     */
    void validate_symbol_index( size_t index ) const;

    /*!
     * Internal function used to check if a given index is within the byte
     * length (get_byte_length) of the string. If it is not an
     * IndexOutOfBoundsError is thrown.
     */
    void validate_byte_index( size_t index ) const;
};

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

std::ostream& operator<<( std::ostream& stream, const UTF8String& str );

} // namespace str
} // namespace chaos



#endif
