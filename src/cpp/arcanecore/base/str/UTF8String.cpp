#include <algorithm>
#include <cstddef>
#include <cstring>
#include <sstream>

#include "arcanecore/base/Exceptions.hpp"
#include "arcanecore/base/data/ByteOperations.hpp"
#include "arcanecore/base/str/UTF8String.hpp"
#include "arcanecore/base/str/StringOperations.hpp"

namespace arc
{
namespace str
{

//------------------------------------------------------------------------------
//                            PUBLIC STATIC ATTRIBUTES
//------------------------------------------------------------------------------

UTF8String::Opt UTF8String::default_opt(UTF8String::Opt::NONE);

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

UTF8String::UTF8String(Opt optimisations)
    :
    m_opt        (optimisations),
    m_data       (nullptr),
    m_data_length(0),
    m_length     (0)
{
    // assign the empty string
    try
    {
        assign_internal("", 0);
    }
    catch(...)
    {
        if(m_data)
        {
            delete[] m_data;
            m_data = nullptr;
        }
        throw;
    }
}

UTF8String::UTF8String(const char* data, Opt optimisations)
    :
    m_opt        (optimisations),
    m_data       (nullptr),
    m_data_length(0),
    m_length     (0)
{
    // assign the data
    try
    {
        assign_internal(data);
    }
    catch(...)
    {
        if(m_data)
        {
            delete[] m_data;
            m_data = nullptr;
        }
        throw;
    }
}

UTF8String::UTF8String(
        const char* data,
        std::size_t length,
        Opt optimisations)
    :
    m_opt        (optimisations),
    m_data       (nullptr),
    m_data_length(0),
    m_length     (0)
{
    // assign the data
    try
    {
        assign_internal(data, length);
    }
    catch(...)
    {
        if(m_data)
        {
            delete[] m_data;
            m_data = nullptr;
        }
        throw;
    }
}

UTF8String::UTF8String(const UTF8String& other)
    :
    m_opt        (other.m_opt),
    m_data       (nullptr),
    m_data_length(0),
    m_length     (0)
{
    // assign the data
    try
    {
        assign(other);
        // assign_internal(other.m_data, other.m_data_length);
    }
    catch(...)
    {
        if(m_data)
        {
            delete[] m_data;
            m_data = nullptr;
        }
        throw;
    }
}

UTF8String::UTF8String(UTF8String&& other)
    :
    m_opt        (other.m_opt),
    m_data       (other.m_data),
    m_data_length(other.m_data_length),
    m_length     (other.m_length)
{
    // reset the other's resources
    other.m_opt = default_opt;
    other.m_data = nullptr;
    other.m_data_length = 0;
    other.m_length = 0;
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

UTF8String::~UTF8String()
{
    // ensure we delete the internal data buffer
    if(m_data)
    {
        delete[] m_data;
    }
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

const UTF8String& UTF8String::operator=(const UTF8String& other)
{
    // copy optimisation parameters
    m_opt = other.m_opt;
    assign(other);
    return *this;
}

UTF8String& UTF8String::operator=(UTF8String&& other)
{
    // delete the current data
    if(m_data)
    {
        delete[] m_data;
    }

    // move resources
    m_opt = other.m_opt;
    m_data = other.m_data;
    m_data_length = other.m_data_length;
    m_length = other.m_length;

    // reset other resources
    other.m_opt = default_opt;
    other.m_data = nullptr;
    other.m_data_length = 0;
    other.m_length = 0;

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
    // iterate over each code point until we find one that is less than the
    // other
    for ( std::size_t i = 0;
          i < std::min( get_length(), other.get_length() );
          ++i )
    {
        // do a straight comparison on each code point until we find a character
        // that is less than
        arc::uint32 a = get_code_point( i );
        arc::uint32 b = other.get_code_point( i );
        if ( a < b )
        {
            return true;
        }
        if ( b < a )
        {
            return false;
        }
    }
    // is this string shorter?
    return get_length() < other.get_length();
}

UTF8String UTF8String::operator+( const UTF8String& other ) const
{
    return UTF8String( *this ).concatenate( other );
}

UTF8String& UTF8String::operator+=( const UTF8String& other )
{
    return this->concatenate( other );
}

UTF8String UTF8String::operator*( arc::uint32 count ) const
{
    return UTF8String( *this ).repeat( count );
}

UTF8String& UTF8String::operator*=( arc::uint32 count )
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

UTF8String& UTF8String::operator<<( const std::string& other )
{
    return this->concatenate( UTF8String( other.c_str() ) );
}

UTF8String& UTF8String::operator<<( bool other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( char other )
{
    // TODO: if over 128 cast to int to avoid encoding errors
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

#ifdef ARC_OS_WINDOWS

UTF8String& UTF8String::operator<<( unsigned long other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

#endif
// ARC_OS_WINDOWS

UTF8String& UTF8String::operator<<( arc::int8 other )
{
    // TODO: if over 128 cast to int to avoid encoding errors?
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( arc::uint8 other )
{
    // TODO: if over 128 cast to int to avoid encoding errors?
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( arc::int16 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( arc::uint16 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( arc::int32 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( arc::uint32 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( arc::int64 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( arc::uint64 other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<( float other )
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate( UTF8String( ss.str().c_str() ) );
}

UTF8String& UTF8String::operator<<(double other)
{
    // TODO: implement correctly
    std::stringstream ss;
    ss << other;
    return this->concatenate(UTF8String(ss.str().c_str()));
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void UTF8String::assign(const char* data)
{
    assign_internal(data);
}

void UTF8String::assign(const char* data, std::size_t length)
{
    assign_internal(data, length);
}

void UTF8String::assign(const UTF8String& other)
{
    // // delete the current data
    // if(m_data)
    // {
    //     delete[] m_data;
    // }

    // // since we know the data is coming from another UTF8String we can do a
    // // direct memory copy of the data
    // m_data = new char[other.m_data_length];
    // memcpy(m_data, other.m_data, other.m_data_length);
    // // update the length
    // m_data_length = other.m_data_length;
    // m_length = other.m_length;

    assign_internal(other.m_data, other.m_data_length);
}

void UTF8String::claim(char* data)
{
    // delete the current data
    if(m_data)
    {
        delete[] m_data;
    }

    // reassign
    m_data = data;
    // get number of bytes in the data
    m_data_length = strlen(data) + 1;

    // process the raw data
    process_raw();
}

UTF8String& UTF8String::concatenate(const UTF8String& other)
{
    // calculate the new size of the data (but remove the first string's NULL
    // terminator)
    std::size_t new_length = (m_data_length - 1) + other.m_data_length;
    // allocate a new array to hold the increase data size, ignoring one of the
    // NULL terminators
    char* new_data = new char[ new_length ];
    // copy over the data from the strings
    memcpy(new_data, m_data, m_data_length - 1);
    memcpy(
        new_data + (m_data_length - 1),
        other.m_data,
        other.m_data_length
    );
    // finally assign and return
    claim(new_data);
    // assign_internal( new_data, new_length );
    return *this;
}

UTF8String& UTF8String::repeat(arc::uint32 count)
{
    std::size_t c_length = m_data_length - 1;
    // calculate the new length
    std::size_t new_length = (c_length * count) + 1;
    // allocate a new block of data
    char* new_data = new char[new_length];
    // write new data
    for(std::size_t i = 0; i < count; ++i)
    {
        memcpy(
                new_data + (c_length * i),
                m_data,
                m_data_length - 1
        );
    }
    // add the null terminator
    new_data[new_length - 1] = '\0';
    // finally assign and return
    assign_internal(new_data, new_length);
    // clean up
    delete[] new_data;
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
    for ( std::size_t i = 0; i < substring.m_length; ++i )
    {
        if ( substring.get_symbol( i ) != get_symbol( i ) )
        {
            return false;
        }
    }

    // no mismatch
    return true;
}

bool UTF8String::ends_with( const UTF8String& substring ) const
{
    // the substring must be shorter than the actual string
    if ( substring.m_length > m_length )
    {
        return false;
    }
    // check until we find a mismatch
    std::size_t diff = m_length - substring.m_length;
    for ( std::size_t i = substring.m_length; i > 0; --i )
    {
        if ( substring.get_symbol( i - 1 ) != get_symbol( diff + ( i - 1 ) ) )
        {
            return false;
        }
    }

    // no mismatch
    return true;
}

std::size_t UTF8String::find_first( const UTF8String& substring ) const
{
    // the substring must be shorter than the actual string
    if ( substring.m_length > m_length )
    {
        return arc::str::npos;
    }
    // check against each character
    for( std::size_t i = 0; i < m_length - ( substring.m_length - 1 ); ++i )
    {
        // check that each symbol matches
        bool match = true;
        for ( std::size_t j = 0; j < substring.m_length; ++j )
        {
            if ( substring.get_symbol_value( j ) != get_symbol_value( i + j ) )
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
    return arc::str::npos;
}

std::size_t UTF8String::find_last( const UTF8String& substring ) const
{
    // the substring must be shorter than the actual string
    if ( substring.m_length > m_length )
    {
        return arc::str::npos;
    }
    // check against each character
    for( std::size_t i = m_length - substring.m_length;
         i != arc::str::npos;
         --i )
    {
        // check that each symbol matches
        bool match = true;
        for ( std::size_t j = 0; j < substring.m_length; ++j )
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
    return arc::str::npos;
}

std::vector< UTF8String > UTF8String::split(
        const UTF8String& delimiter ) const
{
    // check the delimiter
    if ( delimiter.is_empty() )
    {
        throw arc::ex::ValueError( "Provided delimiter is empty." );
    }

    // create the vector to return
    std::vector< UTF8String > elements;

    UTF8String element;
    for( std::size_t i = 0; i < m_length; )
    {
        // are we looking at the delimiter
        if ( substring( i, delimiter.get_length() ) == delimiter )
        {
            // add what we have so far
            elements.push_back( element );
            // clear element
            element = "";
            // increment past the delimiter
            i += delimiter.get_length();
        }
        else
        {
            element += get_symbol( i );
            ++i;
        }
    }
    // add the final element
    elements.push_back( element );


    return elements;
}

void UTF8String::remove_duplicates( const UTF8String& substring )
{
    // do nothing if an empty substring has been provided
    if ( substring.is_empty() )
    {
        return;
    }

    // TODO this can be optmised

    // input and output strings
    UTF8String input( *this );
    UTF8String output;

    std::size_t i = input.find_first( substring );
    while( i != arc::str::npos )
    {
        // add up to and including the substring
        output << input.substring(
                0,
                i + substring.get_length()
        );
        input = input.substring(
                i + substring.get_length(),
                input.get_length()
        );
        // filter away the rest of the duplicates
        while( input.starts_with( substring ) )
        {
            input = input.substring(
                    substring.get_length(),
                    input.get_length()
            );
        }
        i = input.find_first( substring );
    }
    // add what's left of the input
    output << input;

    assign( output );
}

bool UTF8String::is_int() const
{
    // iterate over each code point and ensure that it's a digit
    for ( std::size_t i = 0; i < m_length; ++i )
    {
        arc::uint32 code_point = get_code_point( i );

        // the first symbol is allowed to be '-'
        if ( i == 0                                  &&
            get_symbol( i ) != "-"                   &&
            !arc::str::is_digit( code_point )    )
        {
            return false;
        }
        // every other character must be a digit
        else if ( i != 0 && !arc::str::is_digit( code_point ) )
        {
            return false;
        }
    }
    // valid int
    return !is_empty();
}

bool UTF8String::is_uint() const
{
    // iterate of each code point and ensure that it's a digit
    for ( std::size_t i = 0; i < m_length; ++i )
    {
        if ( !arc::str::is_digit( get_symbol_value( i ) ) )
        {
            // not a digit
            return false;
        }
    }
    // valid unsigned int
    return !is_empty();
}

bool UTF8String::is_float() const
{
    bool point_found = false;
    // iterate of each code point
    for ( std::size_t i = 0; i < m_length; ++i )
    {
        arc::uint32 code_point = get_symbol_value( i );

        if ( !arc::str::is_digit( code_point ) )
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
    return !is_empty();
}

UTF8String UTF8String::substring( std::size_t start, std::size_t end ) const
{
    // return empty if the index is the length of this string
    if ( start == get_length() )
    {
        return UTF8String();
    }

    // is the index valid
    check_symbol_index( start );

    // TODO: can this be optimised to copy raw data array?

    UTF8String result;
    for ( std::size_t i = start;
          i < std::min( get_length(),  start + end );
          ++i )
    {
        result += get_symbol( i );
    }

    return result;
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
    // is the conversion valid?
    if ( !is_int() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to bool as it is "
                      << "not valid.";
        throw arc::ex::ConversionDataError( error_message );
    }
    // do conversion and return
    for ( std::size_t i = 0; i < get_length(); ++i )
    {
        if ( get_symbol( i ) != "0" )
        {
            return true;
        }
    }
    return false;
}

arc::int32 UTF8String::to_int32() const
{
    // is the conversion valid?
    if ( !is_int() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to int32 as it is "
                      << "not valid.";
        throw arc::ex::ConversionDataError( error_message );
    }
    // do and return conversion
    return static_cast< arc::int32 >( std::strtol( get_raw(), NULL, 0 ) );
}

arc::uint32 UTF8String::to_uint32() const
{
    // is the conversion valid?
    if ( !is_uint() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to uint32 as it is "
                      << "not valid.";
        throw arc::ex::ConversionDataError( error_message );
    }
    // do and return conversion
    return static_cast< arc::uint32 >( strtoul( get_raw(), NULL, 0 ) );
}

arc::int64 UTF8String::to_int64() const
{
    // is the conversion valid?
    if ( !is_int() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to int64 as it is "
                      << "not valid.";
        throw arc::ex::ConversionDataError( error_message );
    }
    // do and return conversion
    return static_cast< arc::int64 >( std::strtol( get_raw(), NULL, 0 ) );
}

arc::int64 UTF8String::to_uint64() const
{
    // is the conversion valid?
    if ( !is_uint() )
    {
        UTF8String error_message;
        error_message << "Cannot convert: \'" << *this << " to uint64 as it is "
                      << "not valid.";
        throw arc::ex::ConversionDataError( error_message );
    }
    // do and return conversion
    return static_cast< arc::uint64 >(
            std::strtoul( get_raw(), NULL, 0 ) );
}

//----------------------------------ACCESSORS-----------------------------------

std::size_t UTF8String::get_length() const
{
    return m_length;
}

bool UTF8String::is_empty() const
{
    // less than once since non-empty data will contain a NULL terminator
    return m_data_length <= 1;
}

UTF8String UTF8String::get_symbol( std::size_t index ) const
{
    // is the index valid
    check_symbol_index( index );

    // get the byte position
    std::size_t byte_index = get_byte_index_for_symbol_index( index );
    // get the width of the byte
    std::size_t byte_width = get_byte_width( byte_index );

    return UTF8String( &m_data[ byte_index ], byte_width );
}

arc::uint32 UTF8String::get_symbol_value( std::size_t index ) const
{
    // is the index valid?
    check_symbol_index( index );

    // get the bytes that make up the symbol
    std::size_t byte_index = get_byte_index_for_symbol_index( index );
    std::size_t byte_width = get_byte_width( byte_index );

    return arc::data::bytes_to_uint32( &m_data[ byte_index ], byte_width );
}

arc::uint32 UTF8String::get_code_point( std::size_t index ) const
{
    // is the index valid?
    check_symbol_index( index );

    // get the width so we know how to convert
    std::size_t width = get_symbol_width( index );
    arc::uint32 value = get_symbol_value( index );

    if ( width == 1 )
    {
        return value;
    }
    else if ( width == 2 )
    {
        return ( ( value << 6 ) & 0x00007C0 ) |
               ( ( value >> 8 ) & 0x0000003F );
    }
    else if ( width == 3 )
    {
        return ( ( value << 12 ) & 0x0000F000 ) |
               ( ( value >> 2  ) & 0x00000FC0 ) |
               ( ( value >> 16 ) & 0x0000003F );
    }
    else
    {
        return ( ( value << 18 ) & 0x001C0000 ) |
               ( ( value << 4  ) & 0x0003F000 ) |
               ( ( value >> 10 ) & 0x00000FC0 ) |
               ( ( value >> 24 ) & 0x0000003F );
    }
}

std::size_t UTF8String::get_byte_index_for_symbol_index(
        std::size_t symbol_index) const
{
    // is the index valid?
    check_symbol_index(symbol_index);

    if(m_opt.flags & Opt::FIXED_WIDTH)
    {
        // we can just calculate based on fixed width
        return symbol_index * m_opt.fixed_width_size;
    }

    std::size_t current_index = 0;
    for(std::size_t i = 0; i < m_data_length - 1;)
    {
        if (current_index == symbol_index)
        {
            return i;
        }

        ++current_index;
        // increase by byte width
        i += get_byte_width(i);
    }

    // something broke
    return arc::str::npos;
}

std::size_t UTF8String::get_symbol_width(std::size_t index) const
{
    // is the index valid
    check_symbol_index(index);

    if(m_opt.flags & Opt::FIXED_WIDTH)
    {
        // return from optimisation parameters
        return m_opt.fixed_width_size;
    }

    std::size_t byte_index = get_byte_index_for_symbol_index(index);
    return get_byte_width(byte_index);
}

const char* UTF8String::get_raw() const
{
    return m_data;
}

std::size_t UTF8String::get_byte_length() const
{
    return m_data_length;
}

std::size_t UTF8String::get_symbol_index_for_byte_index(
        std::size_t byte_index) const
{
    // is the index valid?
    check_byte_index(byte_index);

    if(m_opt.flags & Opt::FIXED_WIDTH)
    {
        // we can just calculate based on fixed width
        return byte_index / m_opt.fixed_width_size;
    }

    std::size_t current_index = 0;
    for (std::size_t i = 0; i < m_data_length - 1;)
    {
        std::size_t next = i + get_byte_width(i);

        if (byte_index >= i && byte_index < next)
        {
            return current_index;
        }

        ++current_index;
        // increase by byte width
        i = next;
    }

    // something broke
    return arc::str::npos;
}

std::size_t UTF8String::get_byte_width(std::size_t byte_index) const
{
    // is the index valid?
    check_byte_index(byte_index);

    if(m_opt.flags & Opt::FIXED_WIDTH)
    {
        // return from optimisation parameters
        return m_opt.fixed_width_size;
    }

    // TODO: function for single byte width?
    if((m_data[byte_index] & 0x80) == 0)
    {
        // single byte character
        return 1;
    }
    else if((m_data[byte_index] & 0xE0) == 0xC0)
    {
        // double byte character
        return 2;
    }
    else if((m_data[byte_index] & 0xF0) == 0xE0)
    {
        // triple byte character
        return 3;
    }
    else if((m_data[byte_index] & 0xF8) == 0xF0)
    {
        // quad byte character
        return 4;
    }
    else if(m_opt.flags & Opt::SKIP_VALID_CHECK)
    {
        // assume byte size of 1
        return 1;
    }

    return npos;
}

const UTF8String::Opt& UTF8String::get_optimisations() const
{
    return m_opt;
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void UTF8String::assign_internal(
        const char* data,
        std::size_t existing_length )
{
    // if we are assigning from the same object we don't need to do anything
    if(data == m_data)
    {
        return;
    }

    // if there is existing data delete it
    if(m_data)
    {
        delete[] m_data;
    }

    // get number of bytes in the data
    bool is_null_terminated = true;
    if ( existing_length == arc::str::npos )
    {
        // the length includes the NULL terminator
        existing_length = strlen( data ) + 1;
        m_data_length = existing_length;
    }
    else if ( existing_length > 0 && data[ existing_length - 1 ] == '\0' )
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
    m_data = new char[m_data_length];
    // copy data to internal array
    memcpy(m_data, data, existing_length);
    // should a NULL terminator be added to the end?
    if ( !is_null_terminated )
    {
        m_data[m_data_length - 1] = '\0';
    }

    // process the raw data
    process_raw();
}

void UTF8String::check_symbol_index( std::size_t index ) const
{
    if ( index >= m_length )
    {
        UTF8String error_message;
        error_message << "Provided index: " << index << " is greater or equal "
                      << "to the number of symbols in the string: " << m_length;
        throw arc::ex::IndexOutOfBoundsError( error_message );
    }
}

void UTF8String::check_byte_index( std::size_t index ) const
{
    if ( index >= m_data_length )
    {
        UTF8String error_message;
        error_message << "Provided index: " << index << " is greater or equal "
                      << "to the number of bytes in the string: "
                      << m_data_length;
        throw arc::ex::IndexOutOfBoundsError( error_message );
    }
}

void UTF8String::process_raw()
{
    // the number of bytes, not including the null terminator
    std::size_t char_count = m_data_length - 1;

    // clear length
    m_length = 0;

    if(m_opt.flags & Opt::FIXED_WIDTH)
    {
        // all symbols have the same number of bytes so just calculate the
        // the number of symbols based on the number of bytes
        m_length = char_count / m_opt.fixed_width_size;

        // we don't need to check data validity so skip over
        if(m_opt.flags & Opt::SKIP_VALID_CHECK)
        {
            return;
        }
    }

    // to calculate the number of utf-8 symbols in the string and check
    // the validity of the string
    // the current byte and symbol that are being checked
    std::size_t last_byte = 0;
    std::size_t last_symbol = 0;
    // the number of bytes in the current symbol
    arc::uint16 current_width = 0;
    // marks the number of bytes after a primary byte that are required to start
    // with 10xxxxxx, needed for checking validity
    arc::uint8 following_bytes = 0;
    // iterate over each bytes
    for(std::size_t i = 0; i < char_count; ++i)
    {
        // is this a following byte we need to check that it matches the
        // pattern: 10xxxxxx
        if(following_bytes > 0)
        {
            if((m_data[i] & 0xC0) == 0x80)
            {
                // valid following byte
                --following_bytes;
                continue;
            }
            else
            {
                arc::str::UTF8String error_message;
                error_message << "Error while reading byte: \'" << m_data[i]
                              << "\' following symbol at byte: " << last_byte
                              << " and symbol index: " << last_symbol << ". "
                              << "Expected symbol to consist of "
                              << current_width << " bytes.";
                throw arc::ex::EncodingError(error_message);
            }
        }

        // update the current byte
        last_byte = i;

        // since this is not a following byte check against valid primary bytes
        if((m_data[i] & 0x80) == 0)
        {
            // single byte character
            current_width = 1;
        }
        else if((m_data[i] & 0xE0) == 0xC0)
        {
            // double byte character
            current_width = 2;
        }
        else if((m_data[i] & 0xF0) == 0xE0)
        {
            // triple byte character
            current_width = 3;
        }
        else if((m_data[i] & 0xF8) == 0xF0)
        {
            // quad byte character
            current_width = 4;
        }
        else if(m_opt.flags & Opt::SKIP_VALID_CHECK)
        {
            // assume byte size of 1
            current_width = 1;
        }
        else
        {
            arc::str::UTF8String error_message;
            error_message << "Error while reading first byte: \'"
                          << static_cast<arc::int32>(m_data[i])
                          << "\' of symbol at byte: " << last_byte << " and "
                          << "symbol index: " << last_symbol << ". Expected "
                          << "byte to match one of the following binary "
                          << "patterns: 0xxxxxxx, 110xxxxx, 1110xxxx, or "
                          << "11110xxx.";
            throw arc::ex::EncodingError(error_message);
        }

        // update the current symbol
        ++last_symbol;
        // update the length
        if(!(m_opt.flags & Opt::FIXED_WIDTH))
        {
            ++m_length;
        }
        if(!(m_opt.flags & Opt::SKIP_VALID_CHECK))
        {
            // update the expected following bytes to be checked
            following_bytes = current_width - 1;
        }
        else
        {
            // jump to the next symbol byte
            i += (current_width -1);
        }
    }
}

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& stream, const UTF8String& s)
{
    // TODO: proper printing
    stream << s.get_raw();
    return stream;
}

} // namespace str
} // namespace arc
