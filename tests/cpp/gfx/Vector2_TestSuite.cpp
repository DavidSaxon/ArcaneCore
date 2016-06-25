#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE( gfx.vector2 )

#include "arcanecore/gfx/Vector2.hpp"

namespace vector2_tests
{

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class Vector2GenericFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vecs;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector2() );
        vecs.push_back( arc::gfx::Vector2( 0.0F, 1.0F ) );
        vecs.push_back( arc::gfx::Vector2( 1.0F, 0.0F ) );
        vecs.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );
        vecs.push_back( arc::gfx::Vector2( 1.0F, -1.0F ) );
        vecs.push_back( arc::gfx::Vector2( 12.0F, 53.945F ) );
        vecs.push_back( arc::gfx::Vector2( -0.3434F, 0.00234F ) );
        vecs.push_back( arc::gfx::Vector2( -849895.9F, -32424.2F ) );
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT( default_constructor )
{
    arc::gfx::Vector2 v;
    ARC_CHECK_EQUAL( v.x, 0.0F );
    ARC_CHECK_EQUAL( v.y, 0.0F );
}

//------------------------------------------------------------------------------
//                             COMPONENT CONSTRUCTOR
//------------------------------------------------------------------------------

class ComponentConstructorFixture : public arc::test::Fixture
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

        comp_x.push_back( -333.0F );
        comp_y.push_back( -89234.0F );

        comp_x.push_back( 0.04F );
        comp_y.push_back( 0.003294F );

        comp_x.push_back( 1.34324F );
        comp_y.push_back( -20.003294F );

        comp_x.push_back( 3411.76F );
        comp_y.push_back( 0.200019F );
    }
};

ARC_TEST_UNIT_FIXTURE( component_constructor, ComponentConstructorFixture )
{
    std::vector< arc::gfx::Vector2 > results;
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        results.push_back( arc::gfx::Vector2(
                fixture->comp_x[ i ],
                fixture->comp_y[ i ]
        ) );
    }

    ARC_TEST_MESSAGE( "Checking x component" );
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        ARC_CHECK_FLOAT_EQUAL( results[ i ].x, fixture->comp_x[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking y component" );
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        ARC_CHECK_FLOAT_EQUAL( results[ i ].y, fixture->comp_y[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               SCALAR CONSTRUCTOR
//------------------------------------------------------------------------------

class ScalarConstructorFixture : public arc::test::Fixture
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

ARC_TEST_UNIT_FIXTURE( scalar_constructor, ScalarConstructorFixture )
{
    std::vector< arc::gfx::Vector2 > results;
    for ( std::size_t i = 0; i < fixture->scalars.size(); ++i )
    {
        results.push_back( arc::gfx::Vector2( fixture->scalars[ i ] ) );
    }

    ARC_TEST_MESSAGE( "Checking x component" );
    for ( std::size_t i = 0; i < fixture->scalars.size(); ++i )
    {
        ARC_CHECK_FLOAT_EQUAL( results[ i ].x, fixture->scalars[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking y component" );
    for ( std::size_t i = 0; i < fixture->scalars.size(); ++i )
    {
        ARC_CHECK_FLOAT_EQUAL( results[ i ].y, fixture->scalars[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( copy_constructor, Vector2GenericFixture )
{
    ARC_FOR_EACH( it, fixture->vecs )
    {
        arc::gfx::Vector2 copy( *it );
        ARC_CHECK_EQUAL( copy, *it );
    }
}

//------------------------------------------------------------------------------
//                               COMPONENT ALIASES
//------------------------------------------------------------------------------

ARC_TEST_UNIT( component_aliases )
{
    ARC_TEST_MESSAGE( "Checking r component" );
    arc::gfx::Vector2 vr;
    ARC_CHECK_EQUAL( vr.x, vr.r );
    vr.x = 1.44F;
    ARC_CHECK_EQUAL( vr.x, vr.r );
    vr.r = -0.847F;
    ARC_CHECK_EQUAL( vr.x, vr.r );

    ARC_TEST_MESSAGE( "Checking g component" );
    arc::gfx::Vector2 vg;
    ARC_CHECK_EQUAL( vg.y, vg.g );
    vg.y = 3242.4F;
    ARC_CHECK_EQUAL( vg.y, vg.g );
    vg.g = -2.22222F;
    ARC_CHECK_EQUAL( vg.y, vg.g );

}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( assignemnt_operator, Vector2GenericFixture )
{
    ARC_FOR_EACH( it, fixture->vecs )
    {
        arc::gfx::Vector2 copy;
        copy = *it;
        ARC_CHECK_EQUAL( copy, *it );
    }
}

//------------------------------------------------------------------------------
//                               EQUALITY OPERATOR
//------------------------------------------------------------------------------

class EqualityFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vecs;
    std::vector< arc::gfx::Vector2 > equal;
    std::vector< arc::gfx::Vector2 > not_equal;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector2() );
        equal.push_back( arc::gfx::Vector2() );
        not_equal.push_back( arc::gfx::Vector2( 0.1F, 0.0F ) );

        vecs.push_back( arc::gfx::Vector2( 0.0F, 1.0F ) );
        equal.push_back( arc::gfx::Vector2( 0.0F, 1.0F ) );
        not_equal.push_back( arc::gfx::Vector2( 0.0F, 0.0F ) );

        vecs.push_back( arc::gfx::Vector2( 1.0F, 0.0F ) );
        equal.push_back( arc::gfx::Vector2( 1.0F, 0.0F ) );
        not_equal.push_back( arc::gfx::Vector2( 1.001F, 0.0F ) );

        vecs.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );
        equal.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );
        not_equal.push_back( arc::gfx::Vector2( 0.0F, 2.0F ) );

        vecs.push_back( arc::gfx::Vector2( 1.0F, -1.0F ) );
        equal.push_back( arc::gfx::Vector2( 1.0F, -1.0F ) );
        not_equal.push_back( arc::gfx::Vector2( -1.0F, 1.0F ) );

        vecs.push_back( arc::gfx::Vector2( 12.0F, 53.945F ) );
        equal.push_back( arc::gfx::Vector2( 12.0F, 53.945F ) );
        not_equal.push_back( arc::gfx::Vector2( 12.0F, 54.945F ) );

        vecs.push_back( arc::gfx::Vector2( -0.3434F, 0.00234F ) );
        equal.push_back( arc::gfx::Vector2( -0.3434F, 0.00234F ) );
        not_equal.push_back( arc::gfx::Vector2( -0.3434F, 0.00235F ) );

        vecs.push_back( arc::gfx::Vector2( -849895.9F, -32424.2F ) );
        equal.push_back( arc::gfx::Vector2( -849895.9F, -32424.2F ) );
        not_equal.push_back( arc::gfx::Vector2( -849895.01F, -31424.2F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( equality_operator, EqualityFixture )
{
    ARC_TEST_MESSAGE( "Checking equals" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        ARC_CHECK_TRUE( fixture->vecs[ i ] == fixture->equal[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking not equals" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->vecs[ i ] == fixture->not_equal[ i ] );
    }
}

//------------------------------------------------------------------------------
//                              INEQUALITY OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( inequality_operator, EqualityFixture )
{
    ARC_TEST_MESSAGE( "Checking not equals" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->vecs[ i ] != fixture->equal[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking equals" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        ARC_CHECK_TRUE( fixture->vecs[ i ] != fixture->not_equal[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                INVERSE OPERATOR
//------------------------------------------------------------------------------

class InverseOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vecs;
    std::vector< arc::gfx::Vector2 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector2() );
        results.push_back( arc::gfx::Vector2() );

        vecs.push_back( arc::gfx::Vector2( 1.0F ) );
        results.push_back( arc::gfx::Vector2( -1.0F ) );

        vecs.push_back( arc::gfx::Vector2( 1.0F, 2.0F ) );
        results.push_back( arc::gfx::Vector2( -1.0F, -2.0F ) );

        vecs.push_back( arc::gfx::Vector2( -4.0F, 0.0F ) );
        results.push_back( arc::gfx::Vector2( 4.0F, -0.0F ) );

        vecs.push_back( arc::gfx::Vector2( 0.045F, -1.345F ) );
        results.push_back( arc::gfx::Vector2( -0.045F, 1.345F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( inverse_operator, InverseOperatorFixture )
{
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        ARC_CHECK_EQUAL( -fixture->vecs[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                SCALAR ADDITION
//------------------------------------------------------------------------------

class ScalarAdditionFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vecs;
    std::vector< float > scalars;
    std::vector< arc::gfx::Vector2 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector2() );
        scalars.push_back( 0.0F );
        results.push_back( arc::gfx::Vector2() );

        vecs.push_back( arc::gfx::Vector2() );
        scalars.push_back( 1.0F );
        results.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );

        vecs.push_back( arc::gfx::Vector2() );
        scalars.push_back( -0.048F );
        results.push_back( arc::gfx::Vector2( -0.048F, -0.048F ) );

        vecs.push_back( arc::gfx::Vector2( 0.3F, -84.08F ) );
        scalars.push_back( 0.0F );
        results.push_back( arc::gfx::Vector2(  0.3F, -84.08F  ) );

        vecs.push_back( arc::gfx::Vector2( -20.007F, 0.009F ) );
        scalars.push_back( 0.01F );
        results.push_back( arc::gfx::Vector2(  -19.997F, 0.019F  ) );

        vecs.push_back( arc::gfx::Vector2( 0.34F, 2.6F ) );
        scalars.push_back( -1.5F );
        results.push_back( arc::gfx::Vector2( -1.16F, 1.1F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( scalar_addition, ScalarAdditionFixture )
{
    ARC_TEST_MESSAGE( "Checking addition" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] + fixture->scalars[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound addition" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] );
        v += fixture->scalars[ i ];

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                VECTOR ADDITION
//------------------------------------------------------------------------------

class VectorAdditionFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vecs;
    std::vector< arc::gfx::Vector2 > add;
    std::vector< arc::gfx::Vector2 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector2() );
        add.push_back( arc::gfx::Vector2() );
        results.push_back( arc::gfx::Vector2() );

        vecs.push_back( arc::gfx::Vector2() );
        add.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );
        results.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );

        vecs.push_back( arc::gfx::Vector2() );
        add.push_back( arc::gfx::Vector2( -9.49F, -0.34F ) );
        results.push_back( arc::gfx::Vector2( -9.49F, -0.34F ) );

        vecs.push_back( arc::gfx::Vector2( -4.98F, 0.0074F ) );
        add.push_back( arc::gfx::Vector2() );
        results.push_back( arc::gfx::Vector2( -4.98F, 0.0074F ) );

        vecs.push_back( arc::gfx::Vector2( 3.083F, 0.23F ) );
        add.push_back( arc::gfx::Vector2( -1.2F, -0.08F ) );
        results.push_back( arc::gfx::Vector2( 1.883F, 0.15F ) );

        vecs.push_back( arc::gfx::Vector2( 10.3F, -2.004F ) );
        add.push_back( arc::gfx::Vector2( 49.94F, 0.054F ) );
        results.push_back( arc::gfx::Vector2( 60.24F, -1.95F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( vector_addition, VectorAdditionFixture )
{
    ARC_TEST_MESSAGE( "Checking addition" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] + fixture->add[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound addition" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] );
        v += fixture->add[ i ];

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               SCALAR SUBTRACTION
//------------------------------------------------------------------------------

class ScalarSubtractionFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vecs;
    std::vector< float > scalars;
    std::vector< arc::gfx::Vector2 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector2() );
        scalars.push_back( 0.0F );
        results.push_back( arc::gfx::Vector2() );

        vecs.push_back( arc::gfx::Vector2() );
        scalars.push_back( 1.0F );
        results.push_back( arc::gfx::Vector2( -1.0F, -1.0F ) );

        vecs.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );
        scalars.push_back( 1.0F );
        results.push_back( arc::gfx::Vector2( 0.0F, 0.0F ) );

        vecs.push_back( arc::gfx::Vector2() );
        scalars.push_back( -0.048F );
        results.push_back( arc::gfx::Vector2( 0.048F, 0.048F ) );

        vecs.push_back( arc::gfx::Vector2( 0.3F, -84.08F ) );
        scalars.push_back( 0.0F );
        results.push_back( arc::gfx::Vector2(  0.3F, -84.08F  ) );

        vecs.push_back( arc::gfx::Vector2( -20.007F, 0.009F ) );
        scalars.push_back( 0.01F );
        results.push_back( arc::gfx::Vector2(  -20.017F, -0.001F  ) );

        vecs.push_back( arc::gfx::Vector2( 0.34F, 2.6F ) );
        scalars.push_back( 1.5F );
        results.push_back( arc::gfx::Vector2( -1.16F, 1.1F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( scalar_subtraction, ScalarSubtractionFixture )
{
    ARC_TEST_MESSAGE( "Checking subtraction" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] - fixture->scalars[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound subtraction" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] );
        v -= fixture->scalars[ i ];

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               VECTOR SUBTRACTION
//------------------------------------------------------------------------------

class VectorSubtractionFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vecs;
    std::vector< arc::gfx::Vector2 > sub;
    std::vector< arc::gfx::Vector2 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector2() );
        sub.push_back( arc::gfx::Vector2() );
        results.push_back( arc::gfx::Vector2() );

        vecs.push_back( arc::gfx::Vector2() );
        sub.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );
        results.push_back( arc::gfx::Vector2( -1.0F, -1.0F ) );

        vecs.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );
        sub.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );
        results.push_back( arc::gfx::Vector2() );

        vecs.push_back( arc::gfx::Vector2() );
        sub.push_back( arc::gfx::Vector2( 9.49F, 0.34F ) );
        results.push_back( arc::gfx::Vector2( -9.49F, -0.34F ) );

        vecs.push_back( arc::gfx::Vector2( -4.98F, 0.0074F ) );
        sub.push_back( arc::gfx::Vector2() );
        results.push_back( arc::gfx::Vector2( -4.98F, 0.0074F ) );

        vecs.push_back( arc::gfx::Vector2( 3.083F, 0.23F ) );
        sub.push_back( arc::gfx::Vector2( -1.2F, -0.08F ) );
        results.push_back( arc::gfx::Vector2( 4.283F, 0.31F ) );

        vecs.push_back( arc::gfx::Vector2( 10.3F, -2.004F ) );
        sub.push_back( arc::gfx::Vector2( 49.94F, 0.054F ) );
        results.push_back( arc::gfx::Vector2( -39.64F, -2.058F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( vector_subtraction, VectorSubtractionFixture )
{
    ARC_TEST_MESSAGE( "Checking subtraction" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] - fixture->sub[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound subtraction" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] );
        v -= fixture->sub[ i ];

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             SCALAR MULTIPLICATION
//------------------------------------------------------------------------------

class ScalarMultiplicationFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vecs;
    std::vector< float > scalars;
    std::vector< arc::gfx::Vector2 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector2() );
        scalars.push_back( 0.0F );
        results.push_back( arc::gfx::Vector2() );

        vecs.push_back( arc::gfx::Vector2() );
        scalars.push_back( 1.0F );
        results.push_back( arc::gfx::Vector2() );

        vecs.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );
        scalars.push_back( 1.0F );
        results.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );

        vecs.push_back( arc::gfx::Vector2( 1.0F, -1.0F ) );
        scalars.push_back( 2.0F );
        results.push_back( arc::gfx::Vector2( 2.0F, -2.0F ) );

        vecs.push_back( arc::gfx::Vector2( 12.0F, 5.5F ) );
        scalars.push_back( 0.5F );
        results.push_back( arc::gfx::Vector2( 6.0F, 2.75F ) );

        vecs.push_back( arc::gfx::Vector2( 456.0F, 549.23F ) );
        scalars.push_back( 12.0F );
        results.push_back( arc::gfx::Vector2( 5472.0F, 6590.76F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( scalar_multiplication, ScalarMultiplicationFixture )
{
    ARC_TEST_MESSAGE( "Checking multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] * fixture->scalars[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] );
        v *= fixture->scalars[ i ];

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             VECTOR MULTIPLICATION
//------------------------------------------------------------------------------

class VectorMultiplicationFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vecs;
    std::vector< arc::gfx::Vector2 > mul;
    std::vector< arc::gfx::Vector2 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector2() );
        mul.push_back( arc::gfx::Vector2() );
        results.push_back( arc::gfx::Vector2() );

        vecs.push_back( arc::gfx::Vector2() );
        mul.push_back( arc::gfx::Vector2( 1.0F ) );
        results.push_back( arc::gfx::Vector2() );

        vecs.push_back( arc::gfx::Vector2( 1.0F ) );
        mul.push_back( arc::gfx::Vector2( 1.0F ) );
        results.push_back( arc::gfx::Vector2( 1.0F ) );

        vecs.push_back( arc::gfx::Vector2( -1.0F, 2.0F ) );
        mul.push_back( arc::gfx::Vector2( 3.0F, -2.0F ) );
        results.push_back( arc::gfx::Vector2( -3.0F, -4.0F ) );

        vecs.push_back( arc::gfx::Vector2( 0.4F, -2.556F ) );
        mul.push_back( arc::gfx::Vector2( -0.5F, -1.56F ) );
        results.push_back( arc::gfx::Vector2( -0.2F, 3.98736F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( vector_multiplication, VectorMultiplicationFixture )
{
    ARC_TEST_MESSAGE( "Checking multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] * fixture->mul[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] );
        v *= fixture->mul[ i ];

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                SCALAR DIVISION
//------------------------------------------------------------------------------

class ScalarDivisionFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vecs;
    std::vector< float > scalars;
    std::vector< arc::gfx::Vector2 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector2() );
        scalars.push_back( 0.3F );
        results.push_back( arc::gfx::Vector2() );

        vecs.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );
        scalars.push_back( 1.0F );
        results.push_back( arc::gfx::Vector2( 1.0F, 1.0F ) );

        vecs.push_back( arc::gfx::Vector2( 1.0F, -1.0F ) );
        scalars.push_back( 2.0F );
        results.push_back( arc::gfx::Vector2( 0.5F, -0.5F ) );

        vecs.push_back( arc::gfx::Vector2( 12.0F, 5.5F ) );
        scalars.push_back( 0.5F );
        results.push_back( arc::gfx::Vector2( 24.0F, 11.0F ) );

        vecs.push_back( arc::gfx::Vector2( 456.0F, 549.0F ) );
        scalars.push_back( 12.0F );
        results.push_back( arc::gfx::Vector2( 38.0F, 45.75F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( scalar_division, ScalarDivisionFixture )
{
    ARC_TEST_MESSAGE( "Checking division" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] / fixture->scalars[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound division" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] );
        v /= fixture->scalars[ i ];

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                VECTOR DIVISION
//------------------------------------------------------------------------------

class VectorDivisionFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector2 > vecs;
    std::vector< arc::gfx::Vector2 > div;
    std::vector< arc::gfx::Vector2 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector2() );
        div.push_back( arc::gfx::Vector2( 1.0F ) );
        results.push_back( arc::gfx::Vector2() );

        vecs.push_back( arc::gfx::Vector2( 1.0F ) );
        div.push_back( arc::gfx::Vector2( 1.0F ) );
        results.push_back( arc::gfx::Vector2( 1.0F ) );

        vecs.push_back( arc::gfx::Vector2( 1.0F, -2.0F ) );
        div.push_back( arc::gfx::Vector2( 2.0F, 8.0F ) );
        results.push_back( arc::gfx::Vector2( 0.5F, -0.25F ) );

        vecs.push_back( arc::gfx::Vector2( 0.054F, 1.4F ) );
        div.push_back( arc::gfx::Vector2( -0.2F, 2.4F ) );
        results.push_back( arc::gfx::Vector2( -0.27F, 0.583333F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( vector_division, VectorDivisionFixture )
{
    ARC_TEST_MESSAGE( "Checking multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] / fixture->div[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector2 v( fixture->vecs[ i ] );
        v /= fixture->div[ i ];

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

} // namespace vector2_tests
