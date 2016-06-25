#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE( gfx.vector3 )

#include "arcanecore/gfx/Vector3.hpp"

namespace vector3_tests
{

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class Vector3GenericFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::gfx::Vector3 > vecs;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector3() );
        vecs.push_back( arc::gfx::Vector3( 0.0F, 1.0F, 0.0F ) );
        vecs.push_back( arc::gfx::Vector3( 1.0F, 0.0F, 1.0F ) );
        vecs.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        vecs.push_back( arc::gfx::Vector3( 1.0F, -1.0F, 0.5F ) );
        vecs.push_back( arc::gfx::Vector3( 12.0F, 53.945F, -49.345F ) );
        vecs.push_back( arc::gfx::Vector3( -0.3434F, 0.00234F, 0.45623F ) );
        vecs.push_back( arc::gfx::Vector3( -849895.9F, -32424.2F, 5894.3F ) );
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT( default_constructor )
{
    arc::gfx::Vector3 v;
    ARC_CHECK_EQUAL( v.x, 0.0F );
    ARC_CHECK_EQUAL( v.y, 0.0F );
    ARC_CHECK_EQUAL( v.z, 0.0F );
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
    std::vector< float > comp_z;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        comp_x.push_back( 0.0F );
        comp_y.push_back( 0.0F );
        comp_z.push_back( 0.0F );

        comp_x.push_back( 1.0F );
        comp_y.push_back( 1.0F );
        comp_z.push_back( 1.0F );

        comp_x.push_back( -333.0F );
        comp_y.push_back( -89234.0F );
        comp_z.push_back( -4561.0F );

        comp_x.push_back( 0.04F );
        comp_y.push_back( 0.003294F );
        comp_z.push_back( 0.00039F );

        comp_x.push_back( 1.34324F );
        comp_y.push_back( -20.003294F );
        comp_z.push_back( 12.00043F );

        comp_x.push_back( 3411.76F );
        comp_y.push_back( 0.200019F );
        comp_z.push_back( 34.2355F );
    }
};

ARC_TEST_UNIT_FIXTURE( component_constructor, ComponentConstructorFixture )
{
    std::vector< arc::gfx::Vector3 > results;
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        results.push_back( arc::gfx::Vector3(
                fixture->comp_x[ i ],
                fixture->comp_y[ i ],
                fixture->comp_z[ i ]
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

    ARC_TEST_MESSAGE( "Checking z component" );
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        ARC_CHECK_FLOAT_EQUAL( results[ i ].z, fixture->comp_z[ i ] );
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
    std::vector< arc::gfx::Vector3 > results;
    for ( std::size_t i = 0; i < fixture->scalars.size(); ++i )
    {
        results.push_back( arc::gfx::Vector3( fixture->scalars[ i ] ) );
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

    ARC_TEST_MESSAGE( "Checking z component" );
    for ( std::size_t i = 0; i < fixture->scalars.size(); ++i )
    {
        ARC_CHECK_FLOAT_EQUAL( results[ i ].z, fixture->scalars[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( copy_constructor, Vector3GenericFixture )
{
    ARC_FOR_EACH( it, fixture->vecs )
    {
        arc::gfx::Vector3 copy( *it );
        ARC_CHECK_EQUAL( copy, *it );
    }
}

//------------------------------------------------------------------------------
//                               COMPONENT ALIASES
//------------------------------------------------------------------------------

ARC_TEST_UNIT( component_aliases )
{
    ARC_TEST_MESSAGE( "Checking r component" );
    arc::gfx::Vector3 vr;
    ARC_CHECK_EQUAL( vr.x, vr.r );
    vr.x = 1.44F;
    ARC_CHECK_EQUAL( vr.x, vr.r );
    vr.r = -0.847F;
    ARC_CHECK_EQUAL( vr.x, vr.r );

    ARC_TEST_MESSAGE( "Checking g component" );
    arc::gfx::Vector3 vg;
    ARC_CHECK_EQUAL( vg.y, vg.g );
    vg.y = 3242.4F;
    ARC_CHECK_EQUAL( vg.y, vg.g );
    vg.g = -2.22222F;
    ARC_CHECK_EQUAL( vg.y, vg.g );

    ARC_TEST_MESSAGE( "Checking b component" );
    arc::gfx::Vector3 vb;
    ARC_CHECK_EQUAL( vb.z, vb.b );
    vb.z = -87.08F;
    ARC_CHECK_EQUAL( vb.z, vb.b );
    vb.b = 0.0076F;
    ARC_CHECK_EQUAL( vb.z, vb.b );
}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( assignemnt_operator, Vector3GenericFixture )
{
    ARC_FOR_EACH( it, fixture->vecs )
    {
        arc::gfx::Vector3 copy;
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

    std::vector< arc::gfx::Vector3 > vecs;
    std::vector< arc::gfx::Vector3 > equal;
    std::vector< arc::gfx::Vector3 > not_equal;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector3() );
        equal.push_back( arc::gfx::Vector3() );
        not_equal.push_back( arc::gfx::Vector3( 0.0F, 0.0F, 0.1F ) );

        vecs.push_back( arc::gfx::Vector3( 0.0F, 1.0F, 0.0F ) );
        equal.push_back( arc::gfx::Vector3( 0.0F, 1.0F, 0.0F ) );
        not_equal.push_back( arc::gfx::Vector3( 0.0F, 0.0F, 1.0F ) );

        vecs.push_back( arc::gfx::Vector3( 1.0F, 0.0F, 0.0F ) );
        equal.push_back( arc::gfx::Vector3( 1.0F, 0.0F, 0.0F ) );
        not_equal.push_back( arc::gfx::Vector3( 1.0F, 0.0F, 1.0F ) );

        vecs.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        equal.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        not_equal.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 0.5F ) );

        vecs.push_back( arc::gfx::Vector3( 1.0F, -1.0F, 1.0F ) );
        equal.push_back( arc::gfx::Vector3( 1.0F, -1.0F, 1.0F ) );
        not_equal.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );

        vecs.push_back( arc::gfx::Vector3( 12.0F, 53.945F, -48.94F ) );
        equal.push_back( arc::gfx::Vector3( 12.0F, 53.945F, -48.94F ) );
        not_equal.push_back( arc::gfx::Vector3( 12.0F, 53.946F, -48.94F ) );

        vecs.push_back( arc::gfx::Vector3( -0.3434F, 0.00234F, 0.0003F ) );
        equal.push_back( arc::gfx::Vector3( -0.3434F, 0.00234F, 0.0003F ) );
        not_equal.push_back( arc::gfx::Vector3( -0.3436F, 0.0341F, 0.035F ) );

        vecs.push_back( arc::gfx::Vector3(
                    -849895.9F, -32424.2F, -4589.95F ) );
        equal.push_back( arc::gfx::Vector3(
                    -849895.9F, -32424.2F, -4589.95F ) );
        not_equal.push_back( arc::gfx::Vector3(
                    -849895.9F, 32424.2F, -4589.95F ) );
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

    std::vector< arc::gfx::Vector3 > vecs;
    std::vector< arc::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector3() );
        results.push_back( arc::gfx::Vector3() );

        vecs.push_back( arc::gfx::Vector3( 1.0F ) );
        results.push_back( arc::gfx::Vector3( -1.0F ) );

        vecs.push_back( arc::gfx::Vector3( 1.0F, 2.0F, 3.0F ) );
        results.push_back( arc::gfx::Vector3( -1.0F, -2.0F, -3.0F ) );

        vecs.push_back( arc::gfx::Vector3( -4.0F, 0.0F, 12.0F ) );
        results.push_back( arc::gfx::Vector3( 4.0F, -0.0F, -12.0F ) );

        vecs.push_back( arc::gfx::Vector3( 0.045F, -1.345F, -3.14F ) );
        results.push_back( arc::gfx::Vector3( -0.045F, 1.345F, 3.14F ) );
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

    std::vector< arc::gfx::Vector3 > vecs;
    std::vector< float > scalars;
    std::vector< arc::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector3() );
        scalars.push_back( 0.0F );
        results.push_back( arc::gfx::Vector3() );

        vecs.push_back( arc::gfx::Vector3() );
        scalars.push_back( 1.0F );
        results.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );

        vecs.push_back( arc::gfx::Vector3() );
        scalars.push_back( -0.048F );
        results.push_back( arc::gfx::Vector3( -0.048F, -0.048F, -0.048F ) );

        vecs.push_back( arc::gfx::Vector3( 0.3F, -84.08F, 12.456F ) );
        scalars.push_back( 0.0F );
        results.push_back( arc::gfx::Vector3(  0.3F, -84.08F, 12.456F ) );

        vecs.push_back( arc::gfx::Vector3( -20.007F, 0.009F, 8.0F ) );
        scalars.push_back( 0.01F );
        results.push_back( arc::gfx::Vector3(  -19.997F, 0.019F, 8.01F ) );

        vecs.push_back( arc::gfx::Vector3( 0.34F, 2.6F, 34.87F ) );
        scalars.push_back( -1.5F );
        results.push_back( arc::gfx::Vector3( -1.16F, 1.1F, 33.37F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( scalar_addition, ScalarAdditionFixture )
{
    ARC_TEST_MESSAGE( "Checking addition" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] + fixture->scalars[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound addition" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] );
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

    std::vector< arc::gfx::Vector3 > vecs;
    std::vector< arc::gfx::Vector3 > add;
    std::vector< arc::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector3() );
        add.push_back( arc::gfx::Vector3() );
        results.push_back( arc::gfx::Vector3() );

        vecs.push_back( arc::gfx::Vector3() );
        add.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        results.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );

        vecs.push_back( arc::gfx::Vector3() );
        add.push_back( arc::gfx::Vector3( -9.49F, -0.34F, 3.045F ) );
        results.push_back( arc::gfx::Vector3( -9.49F, -0.34F, 3.045F ) );

        vecs.push_back( arc::gfx::Vector3( -4.98F, 0.0074F, -5.00034F ) );
        add.push_back( arc::gfx::Vector3() );
        results.push_back( arc::gfx::Vector3( -4.98F, 0.0074F, -5.00034F ) );

        vecs.push_back( arc::gfx::Vector3( 3.083F, 0.23F, 0.0001F ) );
        add.push_back( arc::gfx::Vector3( -1.2F, -0.08F, 0.2F ) );
        results.push_back( arc::gfx::Vector3( 1.883F, 0.15F, 0.2001F ) );

        vecs.push_back( arc::gfx::Vector3( 10.3F, -2.004F, -7.87F ) );
        add.push_back( arc::gfx::Vector3( 49.94F, 0.054F, 12.7485F ) );
        results.push_back( arc::gfx::Vector3( 60.24F, -1.95F, 4.8785F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( vector_addition, VectorAdditionFixture )
{
    ARC_TEST_MESSAGE( "Checking addition" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] + fixture->add[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound addition" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] );
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

    std::vector< arc::gfx::Vector3 > vecs;
    std::vector< float > scalars;
    std::vector< arc::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector3() );
        scalars.push_back( 0.0F );
        results.push_back( arc::gfx::Vector3() );

        vecs.push_back( arc::gfx::Vector3() );
        scalars.push_back( 1.0F );
        results.push_back( arc::gfx::Vector3( -1.0F, -1.0F, -1.0F ) );

        vecs.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        scalars.push_back( 1.0F );
        results.push_back( arc::gfx::Vector3( 0.0F, 0.0F, 0.0F ) );

        vecs.push_back( arc::gfx::Vector3() );
        scalars.push_back( -0.048F );
        results.push_back( arc::gfx::Vector3( 0.048F, 0.048F, 0.048F ) );

        vecs.push_back( arc::gfx::Vector3( 0.3F, -84.08F, 8.348F ) );
        scalars.push_back( 0.0F );
        results.push_back( arc::gfx::Vector3(  0.3F, -84.08F, 8.348F ) );

        vecs.push_back( arc::gfx::Vector3( -20.007F, 0.009F, 34.0005F ) );
        scalars.push_back( 0.01F );
        results.push_back( arc::gfx::Vector3(
                 -20.017F, -0.001F, 33.9905F ) );

        vecs.push_back( arc::gfx::Vector3( 0.34F, 2.6F, -2.4F ) );
        scalars.push_back( 1.5F );
        results.push_back( arc::gfx::Vector3( -1.16F, 1.1F, -3.9F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( scalar_subtraction, ScalarSubtractionFixture )
{
    ARC_TEST_MESSAGE( "Checking subtraction" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] - fixture->scalars[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound subtraction" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] );
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

    std::vector< arc::gfx::Vector3 > vecs;
    std::vector< arc::gfx::Vector3 > sub;
    std::vector< arc::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector3() );
        sub.push_back( arc::gfx::Vector3() );
        results.push_back( arc::gfx::Vector3() );

        vecs.push_back( arc::gfx::Vector3() );
        sub.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        results.push_back( arc::gfx::Vector3( -1.0F, -1.0F, -1.0F ) );

        vecs.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        sub.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        results.push_back( arc::gfx::Vector3() );

        vecs.push_back( arc::gfx::Vector3() );
        sub.push_back( arc::gfx::Vector3( 9.49F, 0.34F, -345.39F ) );
        results.push_back( arc::gfx::Vector3( -9.49F, -0.34F, 345.39F ) );

        vecs.push_back( arc::gfx::Vector3( -4.98F, 0.0074F, 670.34F ) );
        sub.push_back( arc::gfx::Vector3() );
        results.push_back( arc::gfx::Vector3( -4.98F, 0.0074F, 670.34F ) );

        vecs.push_back( arc::gfx::Vector3( 3.083F, 0.23F, -12.89F ) );
        sub.push_back( arc::gfx::Vector3( -1.2F, -0.08F, 0.12F ) );
        results.push_back( arc::gfx::Vector3( 4.283F, 0.31F, -13.01F ) );

        vecs.push_back( arc::gfx::Vector3( 10.3F, -2.004F, 0.0037F ) );
        sub.push_back( arc::gfx::Vector3( 49.94F, 0.054F, -47.0F ) );
        results.push_back( arc::gfx::Vector3( -39.64F, -2.058F, 47.0037F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( vector_subtraction, VectorSubtractionFixture )
{
    ARC_TEST_MESSAGE( "Checking subtraction" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] - fixture->sub[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound subtraction" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] );
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

    std::vector< arc::gfx::Vector3 > vecs;
    std::vector< float > scalars;
    std::vector< arc::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector3() );
        scalars.push_back( 0.0F );
        results.push_back( arc::gfx::Vector3() );

        vecs.push_back( arc::gfx::Vector3() );
        scalars.push_back( 1.0F );
        results.push_back( arc::gfx::Vector3() );

        vecs.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        scalars.push_back( 1.0F );
        results.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );

        vecs.push_back( arc::gfx::Vector3( 1.0F, -1.0F, 5.0F ) );
        scalars.push_back( 2.0F );
        results.push_back( arc::gfx::Vector3( 2.0F, -2.0F, 10.0F ) );

        vecs.push_back( arc::gfx::Vector3( 12.0F, 5.5F, 28.5F ) );
        scalars.push_back( 0.5F );
        results.push_back( arc::gfx::Vector3( 6.0F, 2.75F, 14.25F ) );

        vecs.push_back( arc::gfx::Vector3( 456.0F, 549.23F, 0.1F ) );
        scalars.push_back( 12.0F );
        results.push_back( arc::gfx::Vector3( 5472.0F, 6590.76F, 1.2F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( scalar_multiplication, ScalarMultiplicationFixture )
{
    ARC_TEST_MESSAGE( "Checking multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] * fixture->scalars[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] );
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

    std::vector< arc::gfx::Vector3 > vecs;
    std::vector< arc::gfx::Vector3 > mul;
    std::vector< arc::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector3() );
        mul.push_back( arc::gfx::Vector3() );
        results.push_back( arc::gfx::Vector3() );

        vecs.push_back( arc::gfx::Vector3() );
        mul.push_back( arc::gfx::Vector3( 1.0F ) );
        results.push_back( arc::gfx::Vector3() );

        vecs.push_back( arc::gfx::Vector3( 1.0F ) );
        mul.push_back( arc::gfx::Vector3( 1.0F ) );
        results.push_back( arc::gfx::Vector3( 1.0F ) );

        vecs.push_back( arc::gfx::Vector3( -1.0F, 2.0F, -3.0F ) );
        mul.push_back( arc::gfx::Vector3( 3.0F, -2.0F, -1.0F ) );
        results.push_back( arc::gfx::Vector3( -3.0F, -4.0F, 3.0F ) );

        vecs.push_back( arc::gfx::Vector3( 0.4F, -2.556F, 0.005F ) );
        mul.push_back( arc::gfx::Vector3( -0.5F, -1.56F, 2.87F ) );
        results.push_back( arc::gfx::Vector3( -0.2F, 3.98736F, 0.01435F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( vector_multiplication, VectorMultiplicationFixture )
{
    ARC_TEST_MESSAGE( "Checking multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] * fixture->mul[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] );
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

    std::vector< arc::gfx::Vector3 > vecs;
    std::vector< float > scalars;
    std::vector< arc::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector3() );
        scalars.push_back( 0.3F );
        results.push_back( arc::gfx::Vector3() );

        vecs.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        scalars.push_back( 1.0F );
        results.push_back( arc::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );

        vecs.push_back( arc::gfx::Vector3( 1.0F, -1.0F, 0.0F ) );
        scalars.push_back( 2.0F );
        results.push_back( arc::gfx::Vector3( 0.5F, -0.5F, 0.0F ) );

        vecs.push_back( arc::gfx::Vector3( 12.0F, 5.5F, 100.1F ) );
        scalars.push_back( 0.5F );
        results.push_back( arc::gfx::Vector3( 24.0F, 11.0F, 200.2F ) );

        vecs.push_back( arc::gfx::Vector3( 456.0F, 549.0F, -73.34F ) );
        scalars.push_back( 12.0F );
        results.push_back( arc::gfx::Vector3( 38.0F, 45.75F, -6.11167F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( scalar_division, ScalarDivisionFixture )
{
    ARC_TEST_MESSAGE( "Checking division" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] / fixture->scalars[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound division" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] );
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

    std::vector< arc::gfx::Vector3 > vecs;
    std::vector< arc::gfx::Vector3 > div;
    std::vector< arc::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( arc::gfx::Vector3() );
        div.push_back( arc::gfx::Vector3( 1.0F ) );
        results.push_back( arc::gfx::Vector3() );

        vecs.push_back( arc::gfx::Vector3( 1.0F ) );
        div.push_back( arc::gfx::Vector3( 1.0F ) );
        results.push_back( arc::gfx::Vector3( 1.0F ) );

        vecs.push_back( arc::gfx::Vector3( 1.0F, -2.0F, 3.0 ) );
        div.push_back( arc::gfx::Vector3( 2.0F, 8.0F, -2.0F ) );
        results.push_back( arc::gfx::Vector3( 0.5F, -0.25F, -1.5F ) );

        vecs.push_back( arc::gfx::Vector3( 0.054F, 1.4F, -4.4F ) );
        div.push_back( arc::gfx::Vector3( -0.2F, 2.4F, -8.0F ) );
        results.push_back( arc::gfx::Vector3( -0.27F, 0.583333F, 0.55F ) );
    }
};

ARC_TEST_UNIT_FIXTURE( vector_division, VectorDivisionFixture )
{
    ARC_TEST_MESSAGE( "Checking multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] / fixture->div[ i ] );

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        arc::gfx::Vector3 v( fixture->vecs[ i ] );
        v /= fixture->div[ i ];

        ARC_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

} // namespace vector3_tests
