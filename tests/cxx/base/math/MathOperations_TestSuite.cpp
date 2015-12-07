#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( base.math.math_operations )

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

    std::vector< float > comp_1;
    std::vector< float > comp_2;
    std::vector< float > epsilon;
    std::vector< bool > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {

        // -- true --

        comp_1.push_back( 0.0F );
        comp_2.push_back( 0.0F );
        epsilon.push_back( chaos::math::EPSILON );
        results.push_back( true );

        comp_1.push_back( 1.0F );
        comp_2.push_back( 1.0F );
        epsilon.push_back( chaos::math::EPSILON );
        results.push_back( true );

        comp_1.push_back( 0.000453F );
        comp_2.push_back( 0.000453F );
        epsilon.push_back( chaos::math::EPSILON );
        results.push_back( true );

        comp_1.push_back( 324.3457899F );
        comp_2.push_back( 324.3457899F );
        epsilon.push_back( chaos::math::EPSILON );
        results.push_back( true );

        comp_1.push_back( 0.0F );
        comp_2.push_back( 0.0F );
        epsilon.push_back( 0.1F );
        results.push_back( true );

        comp_1.push_back( 0.0F );
        comp_2.push_back( 1.0F );
        epsilon.push_back( 1.1F );
        results.push_back( true );

        // -- false --

        comp_1.push_back( 0.0F );
        comp_2.push_back( 1.0F );
        epsilon.push_back( chaos::math::EPSILON );
        results.push_back( false );

        comp_1.push_back( 1.0F );
        comp_2.push_back( 1.1F );
        epsilon.push_back( chaos::math::EPSILON );
        results.push_back( false );

        comp_1.push_back( 0.000004721F );
        comp_2.push_back( 0.00000472F );
        epsilon.push_back( chaos::math::EPSILON );
        results.push_back( false );

        comp_1.push_back( 24393.458935F );
        comp_2.push_back( 24383.4589356F );
        epsilon.push_back( chaos::math::EPSILON );
        results.push_back( false );

        comp_1.push_back(  47.0F );
        comp_2.push_back(  47.0002F );
        epsilon.push_back( 0.0001F );
        results.push_back( false );

        comp_1.push_back( 0.0F );
        comp_2.push_back( 1.001F );
        epsilon.push_back( 1.0F );
        results.push_back( false );
    }
};

CHAOS_TEST_UNIT_FIXTURE( float_equals, FloatEqualsFixture )
{
    for ( std::size_t i = 0; i < fixture->comp_1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::math::float_equals(
                        fixture->comp_1[ i ],
                        fixture->comp_2[ i ],
                        fixture->epsilon[ i ]
                ),
                fixture->results[ i ]
        );
    }
}

} // namespace math_operations_tests
