#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(base.math.MathOperations)

#include "arcanecore/base/math/MathOperations.hpp"

namespace math_operations_tests
{

//------------------------------------------------------------------------------
//                                      ABS
//------------------------------------------------------------------------------

ARC_TEST_UNIT(abs)
{
    {
        int v = -1;
        ARC_CHECK_EQUAL((arc::math::abs(v)), 1);
    }
    {
        float v = 3.0F;
        ARC_CHECK_EQUAL((arc::math::abs(v)), 3.0F);
    }
    {
        float v = -11.0F;
        ARC_CHECK_EQUAL((arc::math::abs(v)), 11.0F);
    }
    {
        arc::uint32 v = 34;
        ARC_CHECK_EQUAL((arc::math::abs(v)), 34);
    }
}

//------------------------------------------------------------------------------
//                                  CLAMP ABOVE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(clamp_above)
{
    ARC_CHECK_EQUAL((arc::math::clamp_above(10, 0)), 10);
    ARC_CHECK_EQUAL((arc::math::clamp_above(-19, -3)), -3);
    ARC_CHECK_EQUAL((arc::math::clamp_above(5, 5)), 5);
}

//------------------------------------------------------------------------------
//                                  CLAMP BELOW
//------------------------------------------------------------------------------

ARC_TEST_UNIT(clamp_below)
{
    ARC_CHECK_EQUAL((arc::math::clamp_below(10, 0)), 0);
    ARC_CHECK_EQUAL((arc::math::clamp_below(-19, -3)), -19);
    ARC_CHECK_EQUAL((arc::math::clamp_below(5, 5)), 5);
}

//------------------------------------------------------------------------------
//                                     CLAMP
//------------------------------------------------------------------------------

ARC_TEST_UNIT(clamp)
{
    ARC_CHECK_EQUAL((arc::math::clamp(10, 0, 15)), 10);
    ARC_CHECK_EQUAL((arc::math::clamp(-19, -20, -2)), -19);
    ARC_CHECK_EQUAL((arc::math::clamp(1, -2, 2)), 1);
}

//------------------------------------------------------------------------------
//                                  FLOAT EQUALS
//------------------------------------------------------------------------------

class FloatEqualsFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< float > reference;
    std::vector< float > literal;
    std::vector< float > precision_error;
    // std::vector< arc::uint32 > ulps;
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
        ARC_FOR_EACH( it, literal )
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

ARC_TEST_UNIT_FIXTURE( float_equals, FloatEqualsFixture )
{
    ARC_TEST_MESSAGE( "Checking literal equals" );
    for ( std::size_t i = 0; i < fixture->reference.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->reference[ i ] == fixture->literal[ i ],
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking precision error equals" );
    for ( std::size_t i = 0; i < fixture->reference.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                arc::math::float_equals(
                        fixture->reference[ i ],
                        fixture->precision_error[ i ]
                ),
                fixture->results[ i ]
        );
    }
}

} // namespace math_operations_tests
