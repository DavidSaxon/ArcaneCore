#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( gfx.vector_operations )

#include "chaoscore/gfx/VectorOperations.hpp"

namespace vector_operations_tests
{

class VectorOperationsBaseFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector2 > vec2;
    std::vector< chaos::gfx::Vector3 > vec3;
    std::vector< chaos::gfx::Vector4 > vec4;

protected:

    //------------------------PROTECTED MEMBER FUNCTIONS------------------------

    /*!
     * \brief Populates the 3d vector types with the given components.
     */
    void build_vecs( float x, float y, float z, float w )
    {
        vec2.push_back( chaos::gfx::Vector2( x, y ) );
        vec3.push_back( chaos::gfx::Vector3( x, y, z ) );
        vec4.push_back( chaos::gfx::Vector4( x, y, z, w ) );
    }
};

//------------------------------------------------------------------------------
//                                   MAGNITUDE
//------------------------------------------------------------------------------

class MagnitudeFixture : public VectorOperationsBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< float > vec2_results;
    std::vector< float > vec3_results;
    std::vector< float > vec4_results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        build_vecs( 0.0F, 0.0F, 0.0F, 0.0F );
        vec2_results.push_back( 0.0F );
        vec3_results.push_back( 0.0F );
        vec4_results.push_back( 0.0F );

        build_vecs( 1.0F, 0.0F, 2.0F, 0.0F );
        vec2_results.push_back( 1.0F );
        vec3_results.push_back( 2.23607F );
        vec4_results.push_back( 2.23607F );

        build_vecs( -7.0F, 2.0F, -3.0F, 2.0F );
        vec2_results.push_back( 7.28011F );
        vec3_results.push_back( 7.87401F );
        vec4_results.push_back( 8.12404F );

        build_vecs( 0.345F, -0.52F, 1.85F, -0.483F );
        vec2_results.push_back( 0.624039262F );
        vec3_results.push_back( 1.952415171F );
        vec4_results.push_back( 2.011271737F );
    }
};

CHAOS_TEST_UNIT_FIXTURE( magnitude, MagnitudeFixture )
{
    CHAOS_TEST_MESSAGE( "Checking Vector2 magnitude" );
    for ( std::size_t i = 0; i < fixture->vec2.size(); ++i )
    {
        CHAOS_CHECK_FLOAT_EQUAL(
                chaos::gfx::magnitude( fixture->vec2[ i ] ),
                fixture->vec2_results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking Vector3 magnitude" );
    for ( std::size_t i = 0; i < fixture->vec3.size(); ++i )
    {
        CHAOS_CHECK_FLOAT_EQUAL(
                chaos::gfx::magnitude( fixture->vec3[ i ] ),
                fixture->vec3_results[ i ]
        );
    }

    CHAOS_TEST_MESSAGE( "Checking Vector4 magnitude" );
    for ( std::size_t i = 0; i < fixture->vec4.size(); ++i )
    {
        CHAOS_CHECK_FLOAT_EQUAL(
                chaos::gfx::magnitude( fixture->vec4[ i ] ),
                fixture->vec4_results[ i ]
        );
    }
}

} // namespace vector_operations_tests
