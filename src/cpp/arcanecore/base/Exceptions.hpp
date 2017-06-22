/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_BASE_EXCEPTIONS_HPP_
#define ARCANECORE_BASE_EXCEPTIONS_HPP_

#include <stdexcept>

#include "arcanecore/base/introspect/IntrospectOperations.hpp"
#include "arcanecore/base/str/UTF8String.hpp"

namespace arc
{

/*!
 * \brief Base generic exceptions defined by ArcaneCore.
 */
namespace ex
{

//------------------------------------------------------------------------------
//                                 ARC EXCEPTION
//------------------------------------------------------------------------------

/*!
 * \brief Abstract base class that all ArcaneCore Exceptions extend from.
 *
 * This class directly inherits from std::runtime_error.
 */
class ArcException : public std::runtime_error
{
public:

    //-------------------------------CONSTRUCTOR--------------------------------

    /*!
     * \brief Creates a new generic ArcException.
     *
     * \param message A message describing the reason for the exception.
     */
    ArcException(const arc::str::UTF8String& message)
        :
        std::runtime_error(
            arc::str::UTF8String("[ArcException] " + message).get_raw()
        )
    {
    }

    //--------------------------------DESTRUCTOR--------------------------------

    virtual ~ArcException() throw()
    {
    }

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    /*!
     * \return The reason for the exception.
     */
    const arc::str::UTF8String get_message() const
    {
        return arc::str::UTF8String(what());
    }

    /*!
     * \brief Returns the type of this exception as a string.
     */
    const arc::str::UTF8String& get_type() const
    {
        return m_type;
    }

protected:

    //-------------------------------CONSTRUCTOR--------------------------------

    /*!
     * \brief Super constructor for derived classes of ArcException.
     *
     * The type name of the derived class will be prefixed to the exception
     * message.
     *
     * \tparam T_derived_type The type of the class that is inheriting from
     *                        ArcException.
     *
     * \param message A message describing the reason for the exception.
     */
    template<typename T_derived_type>
    ArcException(
            const arc::str::UTF8String& message,
            const T_derived_type* derived)
        : std::runtime_error(
            arc::str::UTF8String(
                "[" + arc::introspect::get_typename<T_derived_type>() +
                "] " + message
            ).get_raw()
          )
        , m_type(arc::introspect::get_typename<T_derived_type>())
    {
    }

private:

    //----------------------------PRIVATE ATTRIBUTES----------------------------

    // The string representing the type of this exception
    const arc::str::UTF8String m_type;
};

//------------------------------------------------------------------------------
//                                 RUNTIME ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns of an unexpected error that occurred at process runtime.
 */
class RuntimeError : public ArcException
{
public:

    RuntimeError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                             NOT IMPLEMENTED ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that an operations has been performed that has not yet been
 *        implemented.
 */
class NotImplementedError : public ArcException
{
public:

    NotImplementedError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                                   TYPE ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that an invalid type has been supplied.
 */
class TypeError : public ArcException
{
public:

    TypeError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};


//------------------------------------------------------------------------------
//                                  VALUE ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that an invalid value has been supplied.
 */
class ValueError : public ArcException
{
public:

    ValueError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                                  STATE ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that an action has been requested that is not valid for the
 *        current state.
 */
class StateError : public ArcException
{
public:

    StateError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                              ILLEGAL ACTION ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that an illegal action has been performed.
 */
class IllegalActionError : public ArcException
{
public:

    IllegalActionError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                           INDEX OUT OF BOUNDS ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that an index has been requested outside of the allowed bounds.
 */
class IndexOutOfBoundsError : public ArcException
{
public:

    IndexOutOfBoundsError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                                   KEY ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that a map key has been requested that does not exist.
 */
class KeyError : public ArcException
{
public:

    KeyError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                                  MEMORY ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that of an error relating to allocating, deleting or accessing
 *        memory.
 */
class MemoryError : public ArcException
{
public:

    MemoryError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                                ARITHMETIC ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns of a failure due to bad arithmetic, e.g. zero division error.
 */
class ArithmeticError : public ArcException
{
public:

    ArithmeticError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                                 ENCODING ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that data was not provided in the expected encoding format.
 */
class EncodingError : public ArcException
{
public:

    EncodingError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                             CONVERSION DATA ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that the provided data for a type conversion was bad or invalid.
 */
class ConversionDataError : public ArcException
{
public:

    ConversionDataError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                                VALIDATION ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that a data validation check has failed.
 */
class ValidationError : public ArcException
{
public:

    ValidationError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                                  PARSE ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns of error while parsing data.
 */
class ParseError : public ArcException
{
public:

    ParseError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                               INVALID PATH ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns of an error accessing the file system.
 */
class IOError : public ArcException
{
public:

    IOError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                               END OF FILE ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns that the end of file marker has been reached.
 */
class EOFError : public ArcException
{
public:

    EOFError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                                 CONTEXT ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns of an error relating to the current runtime context.
 */
class ContextError : public ArcException
{
public:

    ContextError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

//------------------------------------------------------------------------------
//                               DYNAMIC LINK ERROR
//------------------------------------------------------------------------------

/*!
 * \brief Warns of an error relating to dynamic linking.
 */
class DynamicLinkError : public ArcException
{
public:

    DynamicLinkError(const arc::str::UTF8String& message)
        : ArcException(message, this)
    {
    }
};

} // namespace ex
} // namespace arc

#endif
