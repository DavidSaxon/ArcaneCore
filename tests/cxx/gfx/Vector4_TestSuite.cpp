#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( gfx.vector4 )

#include "chaoscore/gfx/Vector4.hpp"

namespace vector4_tests
{

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class Vector4GenericFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector4 > vecs;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector4() );
        vecs.push_back( chaos::gfx::Vector4( 0.0F, 1.0F, 0.0F, 1.0F ) );
        vecs.push_back( chaos::gfx::Vector4( 1.0F, 0.0F, 1.0F, 0.0F ) );
        vecs.push_back( chaos::gfx::Vector4( 1.0F, 1.0F, 1.0F, 1.0F ) );
        vecs.push_back( chaos::gfx::Vector4( 1.0F, -1.0F, 0.5F, -0.5F ) );
        vecs.push_back( chaos::gfx::Vector4(
                12.0F, 53.945F, -49.345F, 8.59F ) );
        vecs.push_back( chaos::gfx::Vector4(
                -0.3434F, 0.00234F, 0.45623F, -0.6383F ) );
        vecs.push_back( chaos::gfx::Vector4(
                -849895.9F, -32424.2F, 5894.3F, -5894.34F ) );
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( default_constructor )
{
    chaos::gfx::Vector4 v;
    CHAOS_CHECK_EQUAL( v.x, 0.0F );
    CHAOS_CHECK_EQUAL( v.y, 0.0F );
    CHAOS_CHECK_EQUAL( v.z, 0.0F );
    CHAOS_CHECK_EQUAL( v.w, 0.0F );
}

//------------------------------------------------------------------------------
//                             COMPONENT CONSTRUCTOR
//------------------------------------------------------------------------------

class ComponentConstructorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< float > comp_x;
    std::vector< float > comp_y;
    std::vector< float > comp_z;
    std::vector< float > comp_w;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_x.push_back( 0.0F );
        comp_y.push_back( 0.0F );
        comp_z.push_back( 0.0F );
        comp_w.push_back( 0.0F );

        comp_x.push_back( 1.0F );
        comp_y.push_back( 1.0F );
        comp_z.push_back( 1.0F );
        comp_w.push_back( 1.0F );

        comp_x.push_back( -333.0F );
        comp_y.push_back( -89234.0F );
        comp_z.push_back( -4561.0F );
        comp_w.push_back( -948.0F );

        comp_x.push_back( 0.04F );
        comp_y.push_back( 0.003294F );
        comp_z.push_back( 0.00039F );
        comp_w.push_back( 0.0001F );

        comp_x.push_back( 1.34324F );
        comp_y.push_back( -20.003294F );
        comp_z.push_back( 12.00043F );
        comp_w.push_back( -9.002F );

        comp_x.push_back( 3411.76F );
        comp_y.push_back( 0.200019F );
        comp_z.push_back( 34.2355F );
        comp_w.push_back( 42.98F );
    }
};

CHAOS_TEST_UNIT_FIXTURE( component_constructor, ComponentConstructorFixture )
{
    std::vector< chaos::gfx::Vector4 > results;
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        results.push_back( chaos::gfx::Vector4(
                fixture->comp_x[ i ],
                fixture->comp_y[ i ],
                fixture->comp_z[ i ],
                fixture->comp_w[ i ]
        ) );
    }

    CHAOS_TEST_MESSAGE( "Checking x component" );
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        CHAOS_CHECK_FLOAT_EQUAL( results[ i ].x, fixture->comp_x[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking y component" );
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        CHAOS_CHECK_FLOAT_EQUAL( results[ i ].y, fixture->comp_y[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking z component" );
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        CHAOS_CHECK_FLOAT_EQUAL( results[ i ].z, fixture->comp_z[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking w component" );
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        CHAOS_CHECK_FLOAT_EQUAL( results[ i ].w, fixture->comp_w[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               SCALAR CONSTRUCTOR
//------------------------------------------------------------------------------

class ScalarConstructorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< float > scalars;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        scalars.push_back( 0.0F );

        scalars.push_back( 1.0F );

        scalars.push_back( -333.0F );

        scalars.push_back( 0.04F );

        scalars.push_back( -1.34324F );

        scalars.push_back( 3411.76F );
    }
};

CHAOS_TEST_UNIT_FIXTURE( scalar_constructor, ScalarConstructorFixture )
{
    std::vector< chaos::gfx::Vector4 > results;
    for ( std::size_t i = 0; i < fixture->scalars.size(); ++i )
    {
        results.push_back( chaos::gfx::Vector4( fixture->scalars[ i ] ) );
    }

    CHAOS_TEST_MESSAGE( "Checking x component" );
    for ( std::size_t i = 0; i < fixture->scalars.size(); ++i )
    {
        CHAOS_CHECK_FLOAT_EQUAL( results[ i ].x, fixture->scalars[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking y component" );
    for ( std::size_t i = 0; i < fixture->scalars.size(); ++i )
    {
        CHAOS_CHECK_FLOAT_EQUAL( results[ i ].y, fixture->scalars[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking z component" );
    for ( std::size_t i = 0; i < fixture->scalars.size(); ++i )
    {
        CHAOS_CHECK_FLOAT_EQUAL( results[ i ].z, fixture->scalars[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking w component" );
    for ( std::size_t i = 0; i < fixture->scalars.size(); ++i )
    {
        CHAOS_CHECK_FLOAT_EQUAL( results[ i ].w, fixture->scalars[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               EQUALITY OPERATOR
//------------------------------------------------------------------------------

class EqualityFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector4 > vecs;
    std::vector< chaos::gfx::Vector4 > equal;
    std::vector< chaos::gfx::Vector4 > not_equal;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector4() );
        equal.push_back( chaos::gfx::Vector4() );
        not_equal.push_back( chaos::gfx::Vector4( 0.0F, 0.0F, 0.1F, 0.0F ) );

        vecs.push_back( chaos::gfx::Vector4( 0.0F, 1.0F, 0.0F, 1.0F ) );
        equal.push_back( chaos::gfx::Vector4( 0.0F, 1.0F, 0.0F, 1.0F ) );
        not_equal.push_back( chaos::gfx::Vector4( 0.0F, 0.0F, 1.0F, 0.0F ) );

        vecs.push_back( chaos::gfx::Vector4( 1.0F, 0.0F, 0.0F, 0.0F ) );
        equal.push_back( chaos::gfx::Vector4( 1.0F, 0.0F, 0.0F, 0.0F ) );
        not_equal.push_back( chaos::gfx::Vector4( 1.0F, 0.0F, 0.0F, 1.0F ) );

        vecs.push_back( chaos::gfx::Vector4( 1.0F, 1.0F, 1.0F, 1.0F ) );
        equal.push_back( chaos::gfx::Vector4( 1.0F, 1.0F, 1.0F, 1.0F ) );
        not_equal.push_back( chaos::gfx::Vector4( 1.0F, 0.5F, 1.0F, 1.0F ) );

        vecs.push_back( chaos::gfx::Vector4( 1.0F, -1.0F, 1.0F, -1.0F ) );
        equal.push_back( chaos::gfx::Vector4( 1.0F, -1.0F, 1.0F, -1.0F ) );
        not_equal.push_back( chaos::gfx::Vector4( -1.0F, -1.0F, 1.0F, -1.0F ) );

        vecs.push_back( chaos::gfx::Vector4(
                12.0F, 53.945F, -48.94F, 99.99F ) );
        equal.push_back( chaos::gfx::Vector4(
                12.0F, 53.945F, -48.94F, 99.99F ) );
        not_equal.push_back( chaos::gfx::Vector4(
                12.0F, 53.946F, -48.94F, 99.99F ) );

        vecs.push_back( chaos::gfx::Vector4(
                -0.3434F, 0.00234F, 0.0003F, 0.0946F ) );
        equal.push_back( chaos::gfx::Vector4(
                -0.3434F, 0.00234F, 0.0003F, 0.0946F ) );
        not_equal.push_back( chaos::gfx::Vector4(
                -0.3436F, 0.0341F, 0.035F, 0.0946F ) );

        vecs.push_back( chaos::gfx::Vector4(
                    -849895.9F, -32424.2F, -4589.95F, 489234.2F ) );
        equal.push_back( chaos::gfx::Vector4(
                    -849895.9F, -32424.2F, -4589.95F, 489234.2F ) );
        not_equal.push_back( chaos::gfx::Vector4(
                    -849895.9F, -32424.2F, -4589.95F, 489239.0F ) );
    }
};

CHAOS_TEST_UNIT_FIXTURE( equality_operator, EqualityFixture )
{
    CHAOS_TEST_MESSAGE( "Checking equals" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        CHAOS_CHECK_TRUE( fixture->vecs[ i ] == fixture->equal[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking not equals" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        CHAOS_CHECK_FALSE( fixture->vecs[ i ] == fixture->not_equal[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              INEQUALITY OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( inequality_operator, EqualityFixture )
{
    CHAOS_TEST_MESSAGE( "Checking not equals" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        CHAOS_CHECK_FALSE( fixture->vecs[ i ] != fixture->equal[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking equals" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        CHAOS_CHECK_TRUE( fixture->vecs[ i ] != fixture->not_equal[ i ] );
    }
}

} // namespace vector4_tests
