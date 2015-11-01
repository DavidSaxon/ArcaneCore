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
#include <set>
#include <sstream>
#include <vector>

#include "chaoscore/base/Preproc.hpp"
#include "chaoscore/base/string/UTF8String.hpp"
#include "chaoscore/test/TestLogger.hpp"

// fork
#ifdef CHAOS_OS_UNIX
    #include <unistd.h>
    #include <sys/wait.h>
// create process
#elif defined( CHAOS_OS_WINDOWS )
    #include <windows.h>
#endif



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
public:

    virtual ~Fixture()
    {
    }

    virtual void setup()
    {
    }

    virtual void teardown()
    {
    }
};

// hide from doxygen
#ifndef IN_DOXYGEN

namespace internal
{

//------------------------------------------------------------------------------
//                                    CLASSES
//------------------------------------------------------------------------------

/*!
 * \brief Structure used to wrap up a unit test. UnitTests will override this
 * class and implement the execute member function.
 */
class UnitTest
{
public:

    UnitTest( const chaos::str::UTF8String& name ) : m_name( name )
    {
    }

    virtual ~UnitTest()
    {
    }

    const chaos::str::UTF8String& get_name()
    {
        return m_name;
    }

    virtual Fixture* get_fixture() = 0;

    virtual void execute() = 0;

private:

    chaos::str::UTF8String m_name;
};

/*!
 * \brief Simple structure for storing verbosity level and format for output
 *        option.
 */
struct OutInfo
{
    chaos::uint16 verbosity;
    TestLogger::OutFormat format;

    OutInfo( chaos::uint8 v, TestLogger::OutFormat f )
        :
        verbosity( v ),
        format   ( f )
    {
    }
};

/*!
 * \brief Structure containing information about the test run configuration,
 */
struct RunInfo
{
    // the current testing id
    chaos::str::UTF8String id;
    // whether the tests should be run in a single process or not
    bool single_proc;
    // whether the test is being run as a sub-process of a parent testing
    // process
    bool sub_proc;
    // the paths to the tests to run
    std::set< chaos::str::UTF8String > paths;
    // whether the standard output stream is being used
    bool use_stdout;
    // information for stdout
    OutInfo stdout_info;
    // mapping from file path to write to, to the format to use
    std::map< chaos::str::UTF8String, OutInfo* > files;

    RunInfo()
        :
        single_proc( false ),
        sub_proc   ( false ),
        use_stdout ( true ),
        stdout_info( 3, TestLogger::OUT_PRETTY_TEXT )
    {
    }
};

/*!
 * \brief Hacky object for performing test magic.
 *
 * For oddities relating to the static global variables used this object is
 * declared entirely inline.
 */
class TestCore
{
public:

    //-------------------------PUBLIC STATIC ATTRIBUTES-------------------------

    static TestLogger                                    logger;
    static std::map< chaos::str::UTF8String, UnitTest* > test_map;
    static std::set< chaos::str::UTF8String >            base_modules;
    static std::set< chaos::str::UTF8String >            known_modules;
    static chaos::str::UTF8String                        current_module;

    //-------------------------------CONSTRUCTOR--------------------------------

    /*!
     * \brief This constructor should be used like a function.
     *
     * This constructor performs multiple operations: declaring test modules,
     * declaring unit tests, and running tests. Which operations are performed
     * are dependent on which parameters are provided.
     */
    TestCore(
            const chaos::str::UTF8String& path,
                  UnitTest*               unit_test,
            const chaos::str::UTF8String& file,
                  chaos::int32            line,
                  bool                    module  = false,
                  RunInfo*                run_info = NULL )
    {
        // TODO: try - catch

        // run tests
        if ( run_info )
        {
            TestCore::setup( run_info );
            TestCore::run( run_info );
            TestCore::teardown( run_info );
            return;
        }

        // module declaration
        if ( module )
        {
            TestCore::declare_module( path, file, line );
            return;
        }

        // unit declaration
        TestCore::declare_unit( path, unit_test, file, line );
    }

private:

    //-------------------------PRIVATE MEMBER FUNCTIONS-------------------------

    /*!
     * \brief Declares a test module.
     */
    static void declare_module(
            const chaos::str::UTF8String& path,
            const chaos::str::UTF8String& file,
                  chaos::int32            line );

    /*!
     * \brief Declares a unit test.
     */
    static void declare_unit(
            const chaos::str::UTF8String& path,
                  UnitTest*               unit_test,
            const chaos::str::UTF8String& file,
                  chaos::int32            line );

    /*!
     * \brief Sets up the state to begin running test.
     */
    static void setup( RunInfo* run_info );

    /*!
     * \brief Cleanup after tests have been run.
     */
    static void teardown( RunInfo* run_info );

    /*!
     * Runs tests defined by the run configuration information.
     */
    static void run( RunInfo* run_info );

    /*!
     * \brief runs the single given unit test with the given run configuration.
     */
    static void run_test(
            UnitTest*                     unit_test,
            const chaos::str::UTF8String& full_path,
            RunInfo*                      run_info );

    /*!
     * \brief Runs the test on this current process.
     */
    static void run_current_proc(
            UnitTest*                     unit_test,
            const chaos::str::UTF8String& full_path,
            RunInfo*                      run_info );

    /*!
     * \brief Runs the test on this current process with no log open and close.
     */
    static void run_current_proc_no_open(
            UnitTest* unit_test,
            RunInfo*  run_info );

    /*!
     * \brief Runs the current test in a new process.
     */
    static void run_new_proc(
            UnitTest*                     unit_test,
            const chaos::str::UTF8String& full_path,
            RunInfo*                      run_info );

    /*!
     * \brief Generates a new unique id for the given unit test name.
     */
    static chaos::str::UTF8String generate_id(
            const chaos::str::UTF8String& name );

    /*!
     * \brief Converts a test logger output format to a UTF8String for the
     * command line.
     */
    static chaos::str::UTF8String log_format_to_string(
            TestLogger::OutFormat format );

    /*!
     * \brief Formats and throws a TestDeclerationError.
     */
    static void throw_error(
            const chaos::str::UTF8String& message,
            const chaos::str::UTF8String& file,
                  chaos::int32            line );
};

} // namespace internal

#endif
// IN_DOXYGEN


//------------------------------------------------------------------------------
//                                     MACROS
//------------------------------------------------------------------------------

// TODO: don't show macro value in docs..

/*!
 * \brief TODO: DOC
 *
 * TODO: DOC
 */
#define CHAOS_TEST_MODULE( path )                                              \
        namespace                                                              \
        {                                                                      \
        chaos::test::internal::TestCore t( #path, NULL, "", 0, true );         \
        }

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
#define CHAOS_TEST_UNIT_FIXTURE( path, fixture_type )                          \
    struct path : public chaos::test::internal::UnitTest                       \
    {                                                                          \
        fixture_type* fixture;                                                 \
        path() : UnitTest( #path ), fixture( new fixture_type() ){}            \
        virtual ~path(){ delete fixture; }                                     \
        virtual chaos::test::Fixture* get_fixture() { return fixture; }        \
        virtual void execute();                                                \
    };                                                                         \
    static chaos::test::internal::TestCore object_##path (                     \
            #path, new path(), __FILE__, __LINE__ );                           \
    void path::execute()


/*!
 * \brief TODO: DOC
 *
 * TODO: DOC
 */
#define CHAOS_CHECK_EQUAL( a, b )                                              \
        if ( a == b )                                                          \
        {                                                                      \
            chaos::test::internal::TestCore::logger.report_check_pass(         \
                    "CHAOS_CHECK_EQUAL", __FILE__, __LINE__ );                 \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            chaos::str::UTF8String f_e_m;                                      \
            f_e_m << a << " does not equal " << b;                             \
            chaos::test::internal::TestCore::logger.report_check_fail(         \
                    "CHAOS_CHECK_EQUAL", __FILE__, __LINE__, f_e_m );          \
        }

} // namespace test
} // namespace chaos

#endif

// reset the current module
namespace chaos_test_include
{
static chaos::test::internal::TestCore reset( "", NULL, "", 0, true );
}
