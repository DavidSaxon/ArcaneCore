#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( io.format.format_operations )

#include "chaoscore/io/format/FormatOperations.hpp"

namespace format_operations_tests
{

//------------------------------------------------------------------------------
//                                  CENTRE TEXT
//------------------------------------------------------------------------------

class CentreTextFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > input;
    std::vector< chaos::uint32 > line_lengths;
    std::vector< chaos::uni::UTF8String > no_trim_results;
    std::vector< chaos::uni::UTF8String > trim_results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        input.push_back( "Hello World" );
        line_lengths.push_back( 20 );
        no_trim_results.push_back( "     Hello World    " );
        trim_results.push_back( "     Hello World" );

        input.push_back( "γειά σου Κόσμε" );
        line_lengths.push_back( 24 );
        no_trim_results.push_back( "     γειά σου Κόσμε     " );
        trim_results.push_back( "     γειά σου Κόσμε" );

        input.push_back( "this is a مزيج of text" );
        line_lengths.push_back( 80 );
        no_trim_results.push_back(
                "                             this is a مزيج of text           "
                "                  "
        );
        trim_results.push_back(
                "                             this is a مزيج of text"
        );

        input.push_back( "간" );
        line_lengths.push_back( 13 );
        no_trim_results.push_back( "      간      " );
        trim_results.push_back( "      간" );

        input.push_back( "Hello World" );
        line_lengths.push_back( 12 );
        no_trim_results.push_back( " Hello World" );
        trim_results.push_back( " Hello World" );

        input.push_back( "Hello World" );
        line_lengths.push_back( 8 );
        no_trim_results.push_back( "Hello World" );
        trim_results.push_back( "Hello World" );

        input.push_back( "γειά σου Κόσμε" );
        line_lengths.push_back( 1 );
        no_trim_results.push_back( "γειά σου Κόσμε" );
        trim_results.push_back( "γειά σου Κόσμε" );

        input.push_back( " مزيج " );
        line_lengths.push_back( 0 );
        no_trim_results.push_back( " مزيج " );
        trim_results.push_back( " مزيج " );
    }
};

CHAOS_TEST_UNIT_FIXTURE( centre_text, CentreTextFixture )
{
    CHAOS_TEST_MESSAGE( "Checking no trim trailing spaces" );
    for ( std::size_t i = 0; i < fixture->input.size(); ++i )
    {
        chaos::uni::UTF8String u( fixture->input[ i ] );
        chaos::io::format::centre_text( u, fixture->line_lengths[ i ] );

        CHAOS_CHECK_EQUAL( u, fixture->no_trim_results[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking trim trailing spaces" );
    for ( std::size_t i = 0; i < fixture->input.size(); ++i )
    {
        chaos::uni::UTF8String u( fixture->input[ i ] );
        chaos::io::format::centre_text( u, fixture->line_lengths[ i ], true );

        CHAOS_CHECK_EQUAL( u, fixture->trim_results[ i ] );
    }
}

} // format_operations_tests
