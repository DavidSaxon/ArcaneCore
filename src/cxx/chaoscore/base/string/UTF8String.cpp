#include "chaoscore/base/string/UTF8String.hpp"

#include <cstddef>
#include <cstring>

#include "chaoscore/base/BaseExceptions.hpp"

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
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UTF8String::UTF8String()
    :
    m_data      ( nullptr ),
    m_dataLength( 0 ),
    m_length    ( 0 )
{
    // assign the empty string
    assign_internal( "", 0 );
}

UTF8String::UTF8String( const char* data )
    :
    m_data      ( nullptr ),
    m_dataLength( 0 ),
    m_length    ( 0 )
{
    // assign the data
    assign_internal( data );

    //TODO: REMOVE ME
    dev_inspectContents();
}

UTF8String::UTF8String( const char* data, size_t length )
    :
    m_data      ( nullptr ),
    m_dataLength( 0 ),
    m_length    ( 0 )
{
    // assign the data
    assign_internal( data, length );
}

UTF8String::UTF8String( const UTF8String& other )
    :
    m_data      ( nullptr ),
    m_dataLength( 0 ),
    m_length    ( 0 )
{
    // assign the data with the known length
   assign_internal( other.m_data, other.m_dataLength );
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
    std::string thisString ( toStdString() );
    std::string otherString( other.toStdString() );
    return std::lexicographical_compare(
            thisString.begin(),  thisString.end(),
            otherString.begin(), otherString.end()
    );
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void UTF8String::assign( const char* data )
{
    assign_internal( data );
}

void UTF8String::assign( const chaos::int8* data )
{
    assign_internal( data );
}

void UTF8String::assign( const UTF8String& other )
{
    assign_internal( other.m_data, other.m_dataLength );
}

bool UTF8String::isEmpty() const
{
    // less than once since non-empty data will contain a NULL terminator
    return m_dataLength <= 1;
}

std::string UTF8String::toStdString() const
{
    return std::string( reinterpret_cast< char* >( m_data ), m_dataLength );
}

//----------------------------------ACCESSORS-----------------------------------

size_t UTF8String::getLength() const
{
    return m_length;
}

UTF8String UTF8String::getSymbol( size_t index )
{
    // TODO: fix

    // is the index valid
    if ( index != m_length )
    {
        // TODO:
        throw chaos::ex::IndexOutOfBoundsError( "" );
    }
}

size_t UTF8String::getByteLength() const
{
    return m_dataLength;
}

const chaos::int8* UTF8String::getRawData() const
{
    return m_data;
}

//------------------------------------------------------------------------------

//--------------------------------DEV FUNCTIONS---------------------------------

void UTF8String::dev_inspectContents()
{
    std::cout << "\n-----------------------------------------------------------"
              << "---------------------" << std::endl;

    // put that shit in a standard string
    std::string s( toStdString() );

    std::cout << "DATA LENGTH         : " << m_dataLength << std::endl;
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

void UTF8String::assign_internal( const void* data, size_t existingLength )
{
    // if there is already content in the internal buffer delete it
    delete[] m_data;

    // cast the incoming data to a cstring
    const char* cData = static_cast< const char* >( data );

    // get number of bytes in the data
    bool isNullTerminated = true;
    if ( existingLength == std::string::npos )
    {
        // the length includes the NULL terminator
        existingLength = strlen( cData ) + 1;
        m_dataLength = existingLength;
    }
    else if ( existingLength > 0 && cData[ existingLength - 1 ] == '\0' )
    {
        // the length includes a NULL terminator
        isNullTerminated = true;
        m_dataLength = existingLength;
    }
    else
    {
        // the length doesn't include a NULL terminator
        isNullTerminated = false;
        m_dataLength = existingLength + 1;
    }

    // allocate storage for the internal data buffer
    m_data = new chaos::int8[ m_dataLength ];
    // copy data to internal array
    memcpy( m_data, cData, existingLength );
    // should a NULL terminator be added to the end?
    if ( !isNullTerminated )
    {
        m_data[ m_dataLength - 1 ] = '\0';
    }

    // to calculate the number of utf-8 symbols in the string
    // TODO:
    m_length = m_dataLength;
}

} // namespace str
} // namespace chaos
