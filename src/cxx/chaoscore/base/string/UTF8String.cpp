#include "chaoscore/base/string/UTF8String.hpp"

#include <cstddef>
#include <cstring>
#include <limits>
#include <sstream>
#include <stdarg.h>

#include "chaoscore/base/BaseExceptions.hpp"
#include "chaoscore/base/string/UnicodeUtil.hpp"

// TODO: only used for lexicographical_compare
// can be removed once implemented correctly
#include <algorithm>

// TODO: REMOVE ME
#include <iostream>

namespace chaos
{
namespace str
{

//------------------------------------------------------------------------------
//                            PUBLIC STATIC ATTRIBUTES
//------------------------------------------------------------------------------

const size_t UTF8String::npos = std::numeric_limits< size_t >::min();

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UTF8String::UTF8String()
    :
    m_data       ( nullptr ),
    m_data_length( 0 ),
    m_length      ( 0 )
{
    // assign the empty string
    assign_internal( "", 0 );
}

UTF8String::UTF8String( const char* data )
    :
    m_data       ( nullptr ),
    m_data_length( 0 ),
    m_length      ( 0 )
{
    // assign the data
    assign_internal( data );
}

UTF8String::UTF8String( const char* data, size_t length )
    :
    m_data       ( nullptr ),
    m_data_length( 0 ),
    m_length     ( 0 )
{
    // assign the data
    assign_internal( data, length );
}

UTF8String::UTF8String( const chaos::int8* data )
    :
    m_data       ( nullptr ),
    m_data_length( 0 ),
    m_length     ( 0 )
{
    // assign the data
    assign_internal( data );
}

UTF8String::UTF8String( const chaos::int8* data, size_t length )
    :
    m_data       ( nullptr ),
    m_data_length( 0 ),
    m_length     ( 0 )
{
    // assign the data
    assign_internal( data, length );
}

UTF8String::UTF8String( const UTF8String& other )
    :
    m_data       ( nullptr ),
    m_data_length( 0 ),
    m_length     ( 0 )
{
    // assign the data with the known length
   assign_internal( other.m_data, other.m_data_length );
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

UTF8String::~UTF8String()
{
    // ensure we delete the internal data buffer
    delete[] m_data;
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

const UTF8String& UTF8String::operator=( const UTF8String& other )
{
    assign( other );
    return *this;
}

bool UTF8String::operator==( const UTF8String& other ) const
{
    return strcmp(
            reinterpret_cast< const char* >( m_data ),
            reinterpret_cast< const char* >( other.m_data )
    ) == 0;
}

bool UTF8String::operator!=( const UTF8String& other ) const
{
    return !( ( *this ) == other );
}

bool UTF8String::operator<( const UTF8String& other ) const
{
    // TODO: fix this
    std::string this_string ( to_std_string() );
    std::string other_string( other.to_std_string() );
    return std::lexicographical_compare(
            this_string.begin(),  this_string.end(),
            other_string.begin(), other_string.end()
    );
}

UTF8String UTF8String::operator+( const UTF8String& other ) const
{
    return UTF8String( *this ).concatenate( other );
}

const UTF8String& UTF8String::operator+=( const UTF8String& other )
{
    return this->concatenate( other );
}

UTF8String UTF8String::operator*( chaos::uint32 count )
{
    return UTF8String( *this ).repeat( count );
}

const UTF8String& UTF8String::operator*=( chaos::uint32 count )
{
    return this->repeat( count );
}

UTF8String& UTF8String::operator<<( const UTF8String& other )
{
    return this->concatenate( other );
}

UTF8String& UTF8String::operator<<( const char* other )
{
    return this->concatenate( UTF8String( other ) );
}

UTF8String& UTF8String::operator<<( bool other )
{
    // TODO: doesn't seem very efficient :(
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( char other )
{
    // TODO: doesn't seem very efficient :(
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

#ifdef CHAOS_OS_WINDOWS

UTF8String& UTF8String::operator<<( unsigned long other )
{
    // TODO: doesn't seem very efficient :(
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

#endif

UTF8String& UTF8String::operator<<( chaos::int8 other )
{
    // TODO: doesn't seem very efficient :(
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::uint8 other )
{
    // TODO: doesn't seem very efficient :(
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::int16 other )
{
    // TODO: doesn't seem very efficient :(
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::uint16 other )
{
    // TODO: doesn't seem very efficient :(
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::int32 other )
{
    // TODO: doesn't seem very efficient :(
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::uint32 other )
{
    // TODO: doesn't seem very efficient :(
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::int64 other )
{
    // TODO: doesn't seem very efficient :(
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( chaos::uint64 other )
{
    // TODO: doesn't seem very efficient :(
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void UTF8String::assign( const char* data )
{
    assign_internal( data );
}

void UTF8String::assign( const char* data, size_t length )
{
    assign_internal( data, length );
}

void UTF8String::assign( const chaos::int8* data )
{
    assign_internal( data );
}

void UTF8String::assign( const chaos::int8* data, size_t length )
{
    assign_internal( data, length );
}

void UTF8String::assign( const UTF8String& other )
{
    assign_internal( other.m_data, other.m_data_length );
}

UTF8String& UTF8String::concatenate( const UTF8String& other )
{
    // calculate the new size of the data (but remove the first string's NULL
    // terminator)
    size_t new_length = ( m_data_length - 1 ) + other.m_data_length;
    // allocate a new array to hold the increase data size, ignoring one of the
    // NULL terminators
    chaos::int8* new_data = new chaos::int8[ new_length ];
    // copy over the data from the strings
    memcpy( new_data, m_data, m_data_length - 1 );
    memcpy(
            new_data + ( m_data_length - 1 ),
            other.m_data,
            other.m_data_length
    );
    // finally assign and return
    assign_internal( new_data, new_length );
    return *this;
}

UTF8String& UTF8String::repeat( chaos::uint32 count )
{
    size_t c_length = m_data_length - 1;
    // calculate the new length
    size_t new_length = ( c_length * count ) + 1;
    // allocate a new block of data
    chaos::int8* new_data = new chaos::int8[ new_length ];
    // write new data
    for( size_t i = 0; i < count; ++i )
    {
        memcpy(
                new_data + ( c_length * i ),
                m_data,
                m_data_length - 1
        );
    }
    // add the null terminator
    new_data[ new_length - 1 ] = '\0';
    // finally assign and return
    assign_internal( new_data, new_length );
    return *this;
}

bool UTF8String::starts_with( const UTF8String& substring ) const
{
    // the substring must be shorter than the actual string
    if ( substring.m_length > m_length )
    {
        return false;
    }
    // check until we find a mismatch
    for ( size_t i = 0; i < substring.m_length; ++i )
    {
        if ( substring.get_symbol( i ) != get_symbol( i ) )
        {
            return false;
        }
    }

    // no mismatch
    return true;
}

size_t UTF8String::find_first( const UTF8String& substring ) const
{
    // the substring must be shorter than the actual string
    if ( substring.m_length > m_length )
    {
        return false;
    }
    // check against each character
    for( size_t i = 0; i < m_length - substring.m_length; ++i )
    {
        // check that each symbol matches
        bool match = true;
        for ( size_t j = 0; j < substring.m_length; ++j )
        {
            if ( substring.get_symbol( j ) != get_symbol( i + j ) )
            {
                match = false;
                break;
            }
        }
        if ( match )
        {
            return i;
        }
    }
    return UTF8String::npos;
}

size_t UTF8String::find_last( const UTF8String& substring ) const
{
    // the substring must be shorter than the actual string
    if ( substring.m_length > m_length )
    {
        return false;
    }
    // check against each character
    for( size_t i = m_length - substring.m_length; i != UTF8String::npos; --i )
    {
        // check that each symbol matches
        bool match = true;
        for ( size_t j = 0; j < substring.m_length; ++j )
        {
            if ( substring.get_symbol( j ) != get_symbol( i + j ) )
            {
                match = false;
                break;
            }
        }
        if ( match )
        {
            return i;
        }
    }
    return UTF8String::npos;
}

// TODO: this could use find
const std::vector< UTF8String > UTF8String::split(
        const UTF8String& delimiter ) const
{
    // create the vector to return
    std::vector< UTF8String > elements;

    // iterate over the string until we reach the end
    size_t current_index = 0;
    size_t last_index = 0;
    for ( ; current_index < m_length; ++current_index )
    {
        // is there  anymore to process
        if ( current_index + delimiter.m_length >= m_length )
        {
            break;
        }
        // does the current index match the delimiter
        bool match = true;
        for ( size_t i = 0; i < delimiter.m_length; ++i )
        {
            if ( delimiter.get_symbol( i ) !=
                 get_symbol( current_index + i  ) )
            {
                match = false;
            }
        }
        // did the delimiter match?
        if ( !match )
        {
            continue;
        }
        // add the string and discard the delimiter
        elements.push_back( substring(
                last_index, current_index - last_index
        ) );
        // since it's about to be incremented go one less than the length of the
        // delimiter
        current_index += delimiter.m_length - 1;
        last_index = current_index + 1;
    }

    // add the final string
    if ( last_index < m_length - 1 )
    {
        elements.push_back( substring( last_index, m_length ) );
    }

    return elements;
}

bool UTF8String::is_int() const
{
    // iterate over each code point and ensure that it's a digit
    for ( size_t i = 0; i < m_length; ++i )
    {
        chaos::uint32 code_point = get_code_point( i );

        // the first symbol is allowed to be '-'
        if ( i == 0                                  &&
            get_symbol( i ) != "-"                   &&
            !chaos::str::utf8_is_digit( code_point )    )
        {
            return false;
        }
        // every other character must be a digit
        else if ( i != 0 && !chaos::str::utf8_is_digit( code_point ) )
        {
            return false;
        }
    }
    // valid int
    return true;
}

bool UTF8String::is_uint() const
{
    // iterate of each code point and ensure that it's a digit
    for ( size_t i = 0; i < m_length; ++i )
    {
        if ( !chaos::str::utf8_is_digit( get_code_point( i ) ) )
        {
            // not a digit
            return false;
        }
    }
    // valid unsigned int
    return true;
}

bool UTF8String::is_float() const
{
    bool point_found = false;
    // iterate of each code point
    for ( size_t i = 0; i < m_length; ++i )
    {
        chaos::uint32 code_point = get_code_point( i );

        if ( !chaos::str::utf8_is_digit( code_point ) )
        {
            if ( i == 0 && get_symbol( i ) == "-" )
            {
                continue;
            }
            if ( get_symbol( i ) == "." && !point_found )
            {
                point_found = true;
                continue;
            }
            return false;
        }
    }
    return true;
}

UTF8String UTF8String::substring( size_t start, size_t end ) const
{
    // TODO: FIX ME
    return( UTF8String( to_std_string().substr( start, end ).c_str() ) );
}

const char* UTF8String::to_cstring() const
{
    return reinterpret_cast< char* >( m_data );
}

std::string UTF8String::to_std_string() const
{
    return std::string(
            reinterpret_cast< char* >( m_data ),
            m_data_length - 1
    );
}

bool UTF8String::to_bool() const
{
    // TODO: bool check?
    // is the conversion valid?
    if ( !is_int() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to bool as it is "
                      << "not valid.";
        throw chaos::ex::ConversionDataError( error_message );
    }
    // do conversion and return
    for ( size_t i = 0; i < get_length(); ++i )
    {
        if ( get_symbol( i ) != "0" )
        {
            return true;
        }
    }
    return false;
}

chaos::int32 UTF8String::to_int32() const
{
    // is the conversion valid?
    if ( !is_int() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to int32 as it is "
                      << "not valid.";
        throw chaos::ex::ConversionDataError( error_message );
    }
    // do and return conversion
    return static_cast< chaos::int32 >( std::strtol( to_cstring(), NULL, 0 ) );
}

chaos::uint32 UTF8String::to_uint32() const
{
    // is the conversion valid?
    if ( !is_uint() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to uint32 as it is "
                      << "not valid.";
        throw chaos::ex::ConversionDataError( error_message );
    }
    // do and return conversion
    return static_cast< chaos::uint32 >( strtoul( to_cstring(), NULL, 0 ) );
}

chaos::int64 UTF8String::to_int64() const
{
    // is the conversion valid?
    if ( !is_int() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to int64 as it is "
                      << "not valid.";
        throw chaos::ex::ConversionDataError( error_message );
    }
    // do and return conversion
    return static_cast< chaos::int64 >( std::strtol( to_cstring(), NULL, 0 ) );
}

chaos::int64 UTF8String::to_uint64() const
{
    // is the conversion valid?
    if ( !is_uint() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to uint64 as it is "
                      << "not valid.";
        throw chaos::ex::ConversionDataError( error_message );
    }
    // do and return conversion
    return static_cast< chaos::uint64 >(
            std::strtoul( to_cstring(), NULL, 0 ) );
}

//----------------------------------ACCESSORS-----------------------------------

size_t UTF8String::get_length() const
{
    return m_length;
}

bool UTF8String::is_empty() const
{
    // less than once since non-empty data will contain a NULL terminator
    return m_data_length <= 1;
}

UTF8String UTF8String::get_symbol( size_t index ) const
{
    // is the index valid
    validate_symbol_index( index );

    // TODO: fix

    return UTF8String( &m_data[ index ], 1 );
}

chaos::uint32 UTF8String::get_code_point( size_t index ) const
{
    // is the index valid
    validate_symbol_index( index );

    return static_cast< chaos::uint32 >(
            static_cast< char >( m_data[ index ] )
    );
}

size_t UTF8String::get_byte_length() const
{
    return m_data_length;
}

const chaos::int8* UTF8String::get_raw_data() const
{
    return m_data;
}

//------------------------------------------------------------------------------

//--------------------------------DEV FUNCTIONS---------------------------------

void UTF8String::dev_inspect_contents()
{
    std::cout << "\n-----------------------------------------------------------"
              << "---------------------" << std::endl;

    // put that shit in a standard string
    std::string s( to_std_string() );

    std::cout << "DATA LENGTH         : " << m_data_length << std::endl;
    std::cout << "STRING LENGTH:      : " << s.length() << std::endl;
    std::cout << "STRING CONTENTS     : " << s << std::endl;

    std::cout << "CHARACTERS          : ";
    for ( size_t i = 0; i < s.length(); ++i )
    {
        std::cout << "|_ " << s[ i ] << " _| ";
    }
    std::cout << std::endl;

    std::cout << "VALUES:             : ";
    for ( size_t i = 0; i < s.length(); ++i )
    {
        std::cout << "|_" << static_cast< int >( s[ i ] ) << "_| ";
    }
    std::cout << std::endl;

    std::cout << "INTERNAL CHARACTERS : ";
    for ( size_t i = 0; i < s.length(); ++i )
    {
        std::cout << "|_ " << m_data[ i ] << " _| ";
    }
    std::cout << std::endl;

    std::cout << "INTERNAL VALUES     : ";
    for ( size_t i = 0; i < s.length(); ++i )
    {
        std::cout << "|_" << static_cast< int >( m_data[ i ] ) << "_| ";
    }
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------"
              << "-------------------\n" << std::endl;
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void UTF8String::assign_internal( const void* data, size_t existing_length )
{
    // if there is already content in the internal buffer delete it
    delete[] m_data;

    // cast the incoming data to a cstring
    const char* cData = static_cast< const char* >( data );

    // get number of bytes in the data
    bool is_null_terminated = true;
    if ( existing_length == std::string::npos )
    {
        // the length includes the NULL terminator
        existing_length = strlen( cData ) + 1;
        m_data_length = existing_length;
    }
    else if ( existing_length > 0 && cData[ existing_length - 1 ] == '\0' )
    {
        // the length includes a NULL terminator
        is_null_terminated = true;
        m_data_length = existing_length;
    }
    else
    {
        // the length doesn't include a NULL terminator
        is_null_terminated = false;
        m_data_length = existing_length + 1;
    }

    // allocate storage for the internal data buffer
    m_data = new chaos::int8[ m_data_length ];
    // copy data to internal array
    memcpy( m_data, cData, existing_length );
    // should a NULL terminator be added to the end?
    if ( !is_null_terminated )
    {
        m_data[ m_data_length - 1 ] = '\0';
    }

    // to calculate the number of utf-8 symbols in the string
    // TODO:
    m_length = m_data_length - 1;
}

void UTF8String::validate_symbol_index( size_t index ) const
{
    if ( index >= m_length )
    {
        UTF8String error_message;
        error_message << "Provided index: " << index << " is greater or equal "
                      << "to the number of symbols in the string: " << m_length;
        throw chaos::ex::IndexOutOfBoundsError( error_message );
    }
}

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

std::ostream& operator<<( std::ostream& stream, const UTF8String& str )
{
    // TODO: proper printing
    stream << str.to_cstring();
    return stream;
}

} // namespace str
} // namespace chaos

