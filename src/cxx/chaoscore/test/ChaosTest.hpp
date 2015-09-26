/*!
 * \file
 *
 * The ChaosCore testing module.
 *
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_CHAOSTEST_HPP_
#define CHAOSCORE_TEST_CHAOSTEST_HPP_

#include <map>
#include <vector>

#include "chaoscore/base/BaseExceptions.hpp"
#include "chaoscore/base/BaseLiterals.hpp"
#include "chaoscore/base/string/UTF8String.hpp"

// TODO: REMOVE ME
#include <iostream>

// use ChaosCore literals
CHAOS_BASE_USE_LITERALS

namespace chaos
{
/*!
 * \brief ChaosCore's testing module.
 */
namespace test
{

//------------------------------------------------------------------------------
//                                    CLASSES
//------------------------------------------------------------------------------

/*!
 * \brief TODO: DOC
 *
 * TODO: DOC
 */
class Fixture
{
};

/*!
 * \brief Warns of an unexpected error during testing procedures.
 */
class TestError : public chaos::ex::ChaosException
{
public:

    TestError( const chaos::str::UTF8String& message )
        :
        ChaosException( message )
    {
    }
};

// hide from doxygen
#ifndef IN_DOXYGEN
/*!
 * \internal
 */
namespace internal
{

//------------------------------------------------------------------------------
//                                    STRUCTS
//------------------------------------------------------------------------------

/*!
 * \internal
 *
 * Structure used to wrap up a unit test. UnitTests will override this class and
 * implement the execute member function.
 */
struct UnitTest
{
    virtual void execute( chaos::test::Fixture& fixture ) = 0;
};

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

// the map type from test paths to the UnitTest pointer
typedef std::map< chaos::str::UTF8String, UnitTest* > TestMap;

//------------------------------------------------------------------------------
//                                    CLASSES
//------------------------------------------------------------------------------

/*!
 * \internal
 *
 * Templated object which means a static TestMap can be defined from purely
 * within a header.
 */
template < typename T >
struct StaticHeaderDefine
{
    static T testMap;
};
template < typename T >
T StaticHeaderDefine< T >::testMap;

/*!
 * \internal
 *
 * Object that abuse it's constructive as if it were calling a function outside
 * of a function body.
 */
class DeclareTest : private StaticHeaderDefine< TestMap >
{
public:

    /*!
     * \internal
     *
     * This constructor should be used like a function to declare a unit test.
     *
     * \param path Unique string path used to identify the test.
     * \param unitTest UnitTest object that is wrapping up the test function.
     */
    DeclareTest(
            const chaos::str::UTF8String& path,
                  UnitTest*               unitTest,
                  Fixture*                fixture   )
    {
        // validate
        // ensure the path is not empty
        if ( path.isEmpty() )
        {
            throw TestError( "Unit test declared with no path."_utf8 );
        }
        // check that first or last symbols are not a periods
        if ( path.getSymbol( 0 )                    == "."_utf8 ||
             path.getSymbol( path.getLength() - 1 ) == "."_utf8    )
        {
            throw TestError(
                    "Invalid test path: \""_utf8 + path +
                    "\". Test paths cannot start or end with \'.\'"
            );
        }
        // check that there are not two consecutive periods
        for ( size_t i = 0; i < path.getLength() - 1; ++i )
        {
            if ( path.getSymbol( i )     == "."_utf8 &&
                 path.getSymbol( i + 1 ) == "."_utf8    )
            {
                throw TestError(
                        "Invalid test path: \""_utf8 + path +
                        "\". Test paths cannot contain two or more "_utf8 +
                        "consecutive \'.\'"
                );
            }
        }
        // check that path is not already in the map
        if ( testMap.find( path ) != testMap.end() )
        {
            throw TestError(
                    "Test path: \""_utf8 + path +
                    "\" has multiple definitions"_utf8
            );
        }

        // pass the test unit into the global mapping
        testMap[ path ] = unitTest;
    }
};

} // namespace internal

#endif
// IN_DOXYGEN


//------------------------------------------------------------------------------
//                                     MACROS
//------------------------------------------------------------------------------

/*!
 * \brief TODO: DOC
 *
 * TODO: DOC
 */
#define CHAOS_TEST_UNIT( path ) \
        CHAOS_TEST_UNIT_FIXTURE( path, chaos::test::Fixture )

/*!
 * \brief TODO: DOC
 *
 * TODO: DOC
 */
#define CHAOS_TEST_UNIT_FIXTURE( path, fixtureType )                           \
    namespace CHAOS_UNIQUE_NAME( chaos_unit_test )                             \
    {                                                                          \
    struct ThisUnitWrapper : public chaos::test::internal::UnitTest            \
    {                                                                          \
        virtual void execute( chaos::test::Fixture& fixture );                 \
    };                                                                         \
    chaos::test::internal::DeclareTest chaos_declare_test(                     \
            #path,                                                             \
            new ThisUnitWrapper(),                                             \
            new fixtureType()                                                  \
    );                                                                         \
    }                                                                          \
    void CHAOS_UNIQUE_NAME( chaos_unit_test )::ThisUnitWrapper::execute(       \
            chaos::test::Fixture& fixture )

} // namespace test
} // namespace chaos

#endif
