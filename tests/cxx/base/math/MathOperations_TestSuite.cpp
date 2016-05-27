#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE(base.math.MathOperations)

#include "chaoscore/base/math/MathOperations.hpp"

namespace math_operations_tests
{

//------------------------------------------------------------------------------
//                                  FLOAT EQUALS
//------------------------------------------------------------------------------

class FloatEqualsFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< float > reference;
    std::vector< float > literal;
    std::vector< float > precision_error;
    // std::vector< chaos::uint32 > ulps;
    // std::vector< float > delta;
    std::vector< bool > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // --- true ---

        reference.push_back( 0.0F );
        literal.push_back( 0.0F );
        results.push_back( true );

        reference.push_back( 0.0F );
        literal.push_back( -0.0F );
        results.push_back( true );

        reference.push_back( 1.0F );
        literal.push_back( 1.0F );
        results.push_back( true );

        reference.push_back( -0.1F );
        literal.push_back( -0.1F );
        results.push_back( true );

        reference.push_back( 0.4359F );
        literal.push_back( 0.4359F );
        results.push_back( true );

        reference.push_back( 0.000054F );
        literal.push_back( 0.000054F );
        results.push_back( true );

        reference.push_back( 4589345.0F );
        literal.push_back( 4589345.0F );
        results.push_back( true );

        reference.push_back( 2590.000058F );
        literal.push_back( 2590.000058F );
        results.push_back( true );

        // --- false ---

        reference.push_back( 0.0F );
        literal.push_back( 1.0F );
        results.push_back( false );

        reference.push_back( 0.1F );
        literal.push_back( 0.0F );
        results.push_back( false );

        reference.push_back( 0.0F );
        literal.push_back( 0.000001F );
        results.push_back( false );

        reference.push_back( -0.000001F );
        literal.push_back( 0.000001F );
        results.push_back( false );

        reference.push_back( 58950.0F );
        literal.push_back( 58950.5F );
        results.push_back( false );

        reference.push_back( 58950.0F );
        literal.push_back( - 58950.0F );
        results.push_back( false );

        // --- precision errors ---
        generate_precision_errors();
    }

    /*!
     * Generates values that are "equal" to the reference values but suffer from
     * a precision error.
     */
    void generate_precision_errors()
    {
        CHAOS_FOR_EACH( it, literal )
        {
            float p = *it;
            ++p;
            for ( size_t i = 0; i < 10; ++i )
            {
                p -= 0.1F;
            }
            precision_error.push_back( p );
        }
    }
};

CHAOS_TEST_UNIT_FIXTURE( float_equals, FloatEqualsFixture )
{
    CHAOS_TEST_MESSAGE( "Checking literal equals" );
    for ( std::size_t i = 0; i < fixture->reference.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->reference[ i ] == fixture->literal[ i ],
                fixture->results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking precision error equals" );
    for ( std::size_t i = 0; i < fixture->reference.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::math::float_equals(
                        fixture->reference[ i ],
                        fixture->precision_error[ i ]
                ),
                fixture->results[ i ]
        );
    }
}

} // namespace math_operations_tests
