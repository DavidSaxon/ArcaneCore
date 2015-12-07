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
        // vecs.push_back
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

    CHAOS_TEST_MESSAGE( "Checking X Component" );
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( results[ i ].x, fixture->comp_x[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking Y Component" );
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( results[ i ].y, fixture->comp_y[ i ] );
    }
}

} // namespace vector2_tests
