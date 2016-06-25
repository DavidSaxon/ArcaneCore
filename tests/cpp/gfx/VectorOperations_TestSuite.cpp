#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE( gfx.vector_operations )

#include "arcanecore/gfx/VectorOperations.hpp"

namespace vector_operations_tests
{

class VectorOperationsBaseFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vec2;
    std::vector< arc::gfx::Vector3 > vec3;
    std::vector< arc::gfx::Vector4 > vec4;

    std::vector< arc::gfx::Vector2 > vec2_sec;
    std::vector< arc::gfx::Vector3 > vec3_sec;
    std::vector< arc::gfx::Vector4 > vec4_sec;

protected:

    //------------------------PROTECTED MEMBER FUNCTIONS------------------------

    /*!
     * \brief Populates the 3 vector types with the given components.
     */
    void build_vecs( float x, float y, float z, float w )
    {
        vec2.push_back( arc::gfx::Vector2( x, y ) );
        vec3.push_back( arc::gfx::Vector3( x, y, z ) );
        vec4.push_back( arc::gfx::Vector4( x, y, z, w ) );
    }

    /*!
     * \brief Populates the 6 primary and secondary vector types with the given
              components.
     */
    void build_vecs( float x_1, float y_1, float z_1, float w_1,
                     float x_2, float y_2, float z_2, float w_2 )
    {
        vec2.push_back( arc::gfx::Vector2( x_1, y_1 ) );
        vec3.push_back( arc::gfx::Vector3( x_1, y_1, z_1 ) );
        vec4.push_back( arc::gfx::Vector4( x_1, y_1, z_1, w_1 ) );

        vec2_sec.push_back( arc::gfx::Vector2( x_2, y_2 ) );
        vec3_sec.push_back( arc::gfx::Vector3( x_2, y_2, z_2 ) );
        vec4_sec.push_back( arc::gfx::Vector4( x_2, y_2, z_2, w_2 ) );
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

ARC_TEST_UNIT_FIXTURE( magnitude, MagnitudeFixture )
{
    ARC_TEST_MESSAGE( "Checking Vector2 magnitude" );
    for ( std::size_t i = 0; i < fixture->vec2.size(); ++i )
    {
        ARC_CHECK_FLOAT_EQUAL(
                arc::gfx::magnitude( fixture->vec2[ i ] ),
                fixture->vec2_results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking Vector3 magnitude" );
    for ( std::size_t i = 0; i < fixture->vec3.size(); ++i )
    {
        ARC_CHECK_FLOAT_EQUAL(
                arc::gfx::magnitude( fixture->vec3[ i ] ),
                fixture->vec3_results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking Vector4 magnitude" );
    for ( std::size_t i = 0; i < fixture->vec4.size(); ++i )
    {
        ARC_CHECK_FLOAT_EQUAL(
                arc::gfx::magnitude( fixture->vec4[ i ] ),
                fixture->vec4_results[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                   NORMALISE
//------------------------------------------------------------------------------

class NormaliseFixture : public VectorOperationsBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vec2_results;
    std::vector< arc::gfx::Vector3 > vec3_results;
    std::vector< arc::gfx::Vector4 > vec4_results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        build_vecs( 0.0F, 0.0F, 0.0F, 0.0F );
        vec2_results.push_back( arc::gfx::Vector2( 0.0F, 0.0F ) );
        vec3_results.push_back( arc::gfx::Vector3( 0.0F, 0.0F, 0.0F ) );
        vec4_results.push_back( arc::gfx::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );

        build_vecs( 1.0F, 0.0F, 2.0F, 0.0F );
        vec2_results.push_back( arc::gfx::Vector2( 1.0F, 0.0F ) );
        vec3_results.push_back( arc::gfx::Vector3(
                0.447213595F, 0.0F, 0.894427191F ) );
        vec4_results.push_back( arc::gfx::Vector4(
                0.447213595F, 0.0F, 0.894427191F, 0.0F ) );

        build_vecs( -2.0F, 5.0F, 8.0F, -1.0F );
        vec2_results.push_back( arc::gfx::Vector2(
                -0.371390676F, 0.928476691F ) );
        vec3_results.push_back( arc::gfx::Vector3(
                -0.207390339F, 0.518475847F, 0.829561356F ) );
        vec4_results.push_back( arc::gfx::Vector4(
                -0.206284249F, 0.515710623F, 0.825136997F, -0.103142125F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( normalise, NormaliseFixture )
{
    ARC_TEST_MESSAGE( "Checking normalise Vector2" );
    for ( std::size_t i = 0; i < fixture->vec2.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vec2[ i ] );
        arc::gfx::normalise( v );
        ARC_CHECK_EQUAL( v, fixture->vec2_results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking normalise Vector3" );
    for ( std::size_t i = 0; i < fixture->vec3.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vec3[ i ] );
        arc::gfx::normalise( v );
        ARC_CHECK_EQUAL( v, fixture->vec3_results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking normalise Vector4" );
    for ( std::size_t i = 0; i < fixture->vec4.size(); ++i )
    {
        arc::gfx::Vector4 v( fixture->vec4[ i ] );
        arc::gfx::normalise( v );
        ARC_CHECK_EQUAL( v, fixture->vec4_results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                  DOT PRODUCT
//------------------------------------------------------------------------------

class DotProductFixture : public VectorOperationsBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< float > vec2_results;
    std::vector< float > vec3_results;
    std::vector< float > vec4_results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        build_vecs( 0.0F, 0.0F, 0.0F, 0.0F,
                    0.0F, 0.0F, 0.0F, 0.0F );
        vec2_results.push_back( 0.0F );
        vec3_results.push_back( 0.0F );
        vec4_results.push_back( 0.0F );

        build_vecs( 1.0F, 0.0F, 2.0F, 0.0F,
                    0.0F, 1.0F, 0.0F, 2.0F );
        vec2_results.push_back( 0.0F );
        vec3_results.push_back( 0.0F );
        vec4_results.push_back( 0.0F );

        build_vecs( 1.0F, 0.0F, 2.0F, 0.0F,
                    1.0F, 0.0F, 2.0F, 0.0F );
        vec2_results.push_back( 1.0F );
        vec3_results.push_back( 5.0F );
        vec4_results.push_back( 5.0F );

        build_vecs( -7.0F, 2.0F, -3.0F, 2.0F,
                     4.0F, 2.0F, -9.0F, 1.0F );
        vec2_results.push_back( -24.0F );
        vec3_results.push_back( 3.0F );
        vec4_results.push_back( 5.0F );

        build_vecs( 0.345F, -0.52F,  1.85F, -0.483F,
                    0.27F,   4.08F, -0.11F, -0.067F );
        vec2_results.push_back( -2.02845F );
        vec3_results.push_back( -2.23195F );
        vec4_results.push_back( -2.19959F );
    }
};

ARC_TEST_UNIT_FIXTURE( dot_product, DotProductFixture )
{
    ARC_TEST_MESSAGE( "Checking Vector2 dot product" );
    for ( std::size_t i = 0; i < fixture->vec2.size(); ++i )
    {
        ARC_CHECK_FLOAT_EQUAL(
                arc::gfx::dot_product(
                        fixture->vec2[ i ],
                        fixture->vec2_sec[ i ]
                ),
                fixture->vec2_results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking Vector3 dot product" );
    for ( std::size_t i = 0; i < fixture->vec3.size(); ++i )
    {
        ARC_CHECK_FLOAT_EQUAL(
                arc::gfx::dot_product(
                        fixture->vec3[ i ],
                        fixture->vec3_sec[ i ]
                ),
                fixture->vec3_results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking Vector4 dot product" );
    for ( std::size_t i = 0; i < fixture->vec4.size(); ++i )
    {
        ARC_CHECK_FLOAT_EQUAL(
                arc::gfx::dot_product(
                        fixture->vec4[ i ],
                        fixture->vec4_sec[ i ]
                ),
                fixture->vec4_results[ i ]
        );
    }
}

} // namespace vector_operations_tests
