#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( gfx.vector2 )

#include "chaoscore/gfx/Vector2.hpp"

namespace vector2_tests
{

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class Vector2GenericFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector2 > vecs;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector2() );
        vecs.push_back( chaos::gfx::Vector2( 0.0F, 1.0F ) );
        vecs.push_back( chaos::gfx::Vector2( 1.0F, 0.0F ) );
        vecs.push_back( chaos::gfx::Vector2( 1.0F, 1.0F ) );
        vecs.push_back( chaos::gfx::Vector2( 1.0F, -1.0F ) );
        vecs.push_back( chaos::gfx::Vector2( 12.0F, 53.945F ) );
        vecs.push_back( chaos::gfx::Vector2( -0.3434F, 0.00234F ) );
        vecs.push_back( chaos::gfx::Vector2( -849895.9F, -32424.2F ) );
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( default_constructor )
{
    chaos::gfx::Vector2 v;
    CHAOS_CHECK_EQUAL( v.x, 0.0F );
    CHAOS_CHECK_EQUAL( v.y, 0.0F );
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

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_x.push_back( 0.0F );
        comp_y.push_back( 0.0F );

        comp_x.push_back( 1.0F );
        comp_y.push_back( 1.0F );

        comp_x.push_back( 333.0F );
        comp_y.push_back( 89234.0F );

        comp_x.push_back( 0.04F );
        comp_y.push_back( 0.003294F );

        comp_x.push_back( 1.34324F );
        comp_y.push_back( 20.003294F );

        comp_x.push_back( 3411.76F );
        comp_y.push_back( 0.200019F );
    }
};

CHAOS_TEST_UNIT_FIXTURE( component_constructor, ComponentConstructorFixture )
{
    std::vector< chaos::gfx::Vector2 > results;
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        results.push_back( chaos::gfx::Vector2(
                fixture->comp_x[ i ],
                fixture->comp_y[ i ]
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
}

//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( copy_constructor, Vector2GenericFixture )
{
    CHAOS_FOR_EACH( it, fixture->vecs )
    {
        chaos::gfx::Vector2 copy( *it );
        CHAOS_CHECK_EQUAL( copy, *it );
    }
}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( assignemnt_operator, Vector2GenericFixture )
{
    CHAOS_FOR_EACH( it, fixture->vecs )
    {
        chaos::gfx::Vector2 copy;
        copy = *it;
        CHAOS_CHECK_EQUAL( copy, *it );
    }
}

//------------------------------------------------------------------------------
//                               EQUALITY OPERATOR
//------------------------------------------------------------------------------

class EqualityFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector2 > vecs;
    std::vector< chaos::gfx::Vector2 > equal;
    std::vector< chaos::gfx::Vector2 > not_equal;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector2() );
        equal.push_back( chaos::gfx::Vector2() );
        not_equal.push_back( chaos::gfx::Vector2() );

        vecs.push_back( chaos::gfx::Vector2( 0.0F, 1.0F ) );
        equal.push_back( chaos::gfx::Vector2( 0.0F, 1.0F ) );
        not_equal.push_back( chaos::gfx::Vector2( 0.0F, 1.0F ) );


        vecs.push_back( chaos::gfx::Vector2( 1.0F, 0.0F ) );
        equal.push_back( chaos::gfx::Vector2( 1.0F, 0.0F ) );
        not_equal.push_back( chaos::gfx::Vector2( 1.0F, 0.0F ) );

        vecs.push_back( chaos::gfx::Vector2( 1.0F, 1.0F ) );
        equal.push_back( chaos::gfx::Vector2( 1.0F, 1.0F ) );
        not_equal.push_back( chaos::gfx::Vector2( 1.0F, 1.0F ) );

        vecs.push_back( chaos::gfx::Vector2( 1.0F, -1.0F ) );
        equal.push_back( chaos::gfx::Vector2( 1.0F, -1.0F ) );
        not_equal.push_back( chaos::gfx::Vector2( 1.0F, -1.0F ) );

        vecs.push_back( chaos::gfx::Vector2( 12.0F, 53.945F ) );
        equal.push_back( chaos::gfx::Vector2( 12.0F, 53.945F ) );
        not_equal.push_back( chaos::gfx::Vector2( 12.0F, 53.945F ) );

        vecs.push_back( chaos::gfx::Vector2( -0.3434F, 0.00234F ) );
        equal.push_back( chaos::gfx::Vector2( -0.3434F, 0.00234F ) );
        not_equal.push_back( chaos::gfx::Vector2( -0.3434F, 0.00234F ) );

        vecs.push_back( chaos::gfx::Vector2( -849895.9F, -32424.2F ) );
        equal.push_back( chaos::gfx::Vector2( -849895.9F, -32424.2F ) );
        not_equal.push_back( chaos::gfx::Vector2( -849895.9F, -32424.2F ) );
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
        CHAOS_CHECK_FALSE( fixture->vecs[ i ] != fixture->not_equal[ i ] );
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
        CHAOS_CHECK_TRUE( fixture->vecs[ i ] == fixture->not_equal[ i ] );
    }
}

} // namespace vector2_tests
