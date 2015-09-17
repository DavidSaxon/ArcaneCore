/** \file
  * \brief This file is contains a collection of general preprocessor directives
  *        and macros.
  */

#ifndef CHAOSCORE_BASE_PREPROC_HPP_
#define CHAOSCORE_BASE_PREPROC_HPP_

//-----------------------------PLATFORM DIRECTIVES------------------------------

// These directives are used for determining what platform this code is being
// compiled for. While it may look at little strange that they are initially
// defined and then undefined again if they are not valid: this is done solely
// so correct Doxygen docs can be built for the preprocessor no matter what
// platform Doxygen is running from.

/**
  * \brief Directive that is defined if the current platform is a Windows
  *        operating system
  */
#define CHAOS_OS_WINDOWS
// clean up so code can still run as expected
#ifndef _WIN32
    #undef CHAOS_OS_WINDOWS
#endif

/**
  * \brief Directive that is defined if the current platform is a Unix based
  *        operating system
  */
#define CHAOS_OS_UNIX
// clean up so code can still run as expected
#if  !defined( __APPLE__ ) && !defined( __linux ) && !defined( __unix )
    #undef CHAOS_OS_UNIX
#endif

/**
  * \brief Directive that is defined if the current platform is a Mac
  *        operating system.
  *
  * \note The CHAOS_OS_UNIX directive will also be defined in this case.
  */
#define CHAOS_OS_MAC
// clean up so code can still run as expected
#ifndef __APPLE__
    #undef CHAOS_OS_MAC
#endif

/**
  * \brief Directive that is defined if the current platform is a Linux
  *        based operating system.
  *
  * \note The CHAOS_OS_UNIX directive will also be defined in this case.
  */
#define CHAOS_OS_LINUX
// clean up so code can still run as expected
#ifndef __linux
    #undef CHAOS_OS_LINUX
#endif

/**
  * \brief Directive that is defined if the current could not be detected
  */
#define CHAOS_OS_UNKNOWN
// clean up so code can still run as expected
#if defined( CHAOS_OS_WINDOWS ) || defined( CHAOS_OS_UNIX )
    #undef CHAOS_OS_UNKNOWN
#endif

//------------------------------CONSTRUCTOR MACROS------------------------------

/**
  * \brief Used to disable all construction methods for a class.
  *
  * This macro will explicitly delete the default constructor, copy constructor,
  * and the assignment operator. This is normally only needed in rare edge cases
  * for entirely static classes.
  *
  * To use this macro it must be declared in the base of the desired class and
  * the name of the class must be passed in as TypeName.
  */
#define CHAOS_DISALLOW_CONSTRUCTION( TypeName ) \
        TypeName() = delete;                    \
        TypeName( const TypeName& ) = delete;   \
        void operator=( const TypeName& ) = delete

/**
  * \brief Used to disable the copy constructor and assignment operator for a
  *  class.
  *
  * The purpose of this macro is to define classes that should not be copied. It
  * explicitly deletes the copy constructor and the assignment operator.
  *
  * To use this macro it must be declared in the base of the desired class and
  * the name of the class must be passed in as TypeName.
  */
#define CHAOS_DISALLOW_COPY_AND_ASSIGN( TypeName ) \
        TypeName( const TypeName& ) = delete;      \
        void operator=( const TypeName& ) = delete


#endif
