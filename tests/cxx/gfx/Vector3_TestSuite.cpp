#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( gfx.vector3 )

#include "chaoscore/gfx/Vector3.hpp"

namespace vector3_tests
{

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class Vector3GenericFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector3 > vecs;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector3() );
        vecs.push_back( chaos::gfx::Vector3( 0.0F, 1.0F, 0.0F ) );
        vecs.push_back( chaos::gfx::Vector3( 1.0F, 0.0F, 1.0F ) );
        vecs.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        vecs.push_back( chaos::gfx::Vector3( 1.0F, -1.0F, 0.5F ) );
        vecs.push_back( chaos::gfx::Vector3( 12.0F, 53.945F, -49.345F ) );
        vecs.push_back( chaos::gfx::Vector3( -0.3434F, 0.00234F, 0.45623F ) );
        vecs.push_back( chaos::gfx::Vector3( -849895.9F, -32424.2F, 5894.3F ) );
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( default_constructor )
{
    chaos::gfx::Vector3 v;
    CHAOS_CHECK_EQUAL( v.x, 0.0F );
    CHAOS_CHECK_EQUAL( v.y, 0.0F );
    CHAOS_CHECK_EQUAL( v.z, 0.0F );
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

CHAOS_TEST_UNIT_FIXTURE( component_constructor, ComponentConstructorFixture )
{
    std::vector< chaos::gfx::Vector3 > results;
    for ( std::size_t i = 0; i < fixture->comp_x.size(); ++i )
    {
        results.push_back( chaos::gfx::Vector3(
                fixture->comp_x[ i ],
                fixture->comp_y[ i ],
                fixture->comp_z[ i ]
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
    std::vector< chaos::gfx::Vector3 > results;
    for ( std::size_t i = 0; i < fixture->scalars.size(); ++i )
    {
        results.push_back( chaos::gfx::Vector3( fixture->scalars[ i ] ) );
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
}

//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( copy_constructor, Vector3GenericFixture )
{
    CHAOS_FOR_EACH( it, fixture->vecs )
    {
        chaos::gfx::Vector3 copy( *it );
        CHAOS_CHECK_EQUAL( copy, *it );
    }
}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( assignemnt_operator, Vector3GenericFixture )
{
    CHAOS_FOR_EACH( it, fixture->vecs )
    {
        chaos::gfx::Vector3 copy;
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

    std::vector< chaos::gfx::Vector3 > vecs;
    std::vector< chaos::gfx::Vector3 > equal;
    std::vector< chaos::gfx::Vector3 > not_equal;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector3() );
        equal.push_back( chaos::gfx::Vector3() );
        not_equal.push_back( chaos::gfx::Vector3( 0.0F, 0.0F, 0.1F ) );

        vecs.push_back( chaos::gfx::Vector3( 0.0F, 1.0F, 0.0F ) );
        equal.push_back( chaos::gfx::Vector3( 0.0F, 1.0F, 0.0F ) );
        not_equal.push_back( chaos::gfx::Vector3( 0.0F, 0.0F, 1.0F ) );

        vecs.push_back( chaos::gfx::Vector3( 1.0F, 0.0F, 0.0F ) );
        equal.push_back( chaos::gfx::Vector3( 1.0F, 0.0F, 0.0F ) );
        not_equal.push_back( chaos::gfx::Vector3( 1.0F, 0.0F, 1.0F ) );

        vecs.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        equal.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        not_equal.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 0.5F ) );

        vecs.push_back( chaos::gfx::Vector3( 1.0F, -1.0F, 1.0F ) );
        equal.push_back( chaos::gfx::Vector3( 1.0F, -1.0F, 1.0F ) );
        not_equal.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );

        vecs.push_back( chaos::gfx::Vector3( 12.0F, 53.945F, -48.94F ) );
        equal.push_back( chaos::gfx::Vector3( 12.0F, 53.945F, -48.94F ) );
        not_equal.push_back( chaos::gfx::Vector3( 12.0F, 53.946F, -48.94F ) );

        vecs.push_back( chaos::gfx::Vector3( -0.3434F, 0.00234F, 0.0003F ) );
        equal.push_back( chaos::gfx::Vector3( -0.3434F, 0.00234F, 0.0003F ) );
        not_equal.push_back( chaos::gfx::Vector3( -0.3436F, 0.0341F, 0.035F ) );

        vecs.push_back( chaos::gfx::Vector3(
                    -849895.9F, -32424.2F, -4589.95F ) );
        equal.push_back( chaos::gfx::Vector3(
                    -849895.9F, -32424.2F, -4589.95F ) );
        not_equal.push_back( chaos::gfx::Vector3(
                    -849895.9F, 32424.2F, -4589.95F ) );
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

//------------------------------------------------------------------------------
//                                INVERSE OPERATOR
//------------------------------------------------------------------------------

class InverseOperatorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector3 > vecs;
    std::vector< chaos::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector3() );
        results.push_back( chaos::gfx::Vector3() );

        vecs.push_back( chaos::gfx::Vector3( 1.0F ) );
        results.push_back( chaos::gfx::Vector3( -1.0F ) );

        vecs.push_back( chaos::gfx::Vector3( 1.0F, 2.0F, 3.0F ) );
        results.push_back( chaos::gfx::Vector3( -1.0F, -2.0F, -3.0F ) );

        vecs.push_back( chaos::gfx::Vector3( -4.0F, 0.0F, 12.0F ) );
        results.push_back( chaos::gfx::Vector3( 4.0F, -0.0F, -12.0F ) );

        vecs.push_back( chaos::gfx::Vector3( 0.045F, -1.345F, -3.14F ) );
        results.push_back( chaos::gfx::Vector3( -0.045F, 1.345F, 3.14F ) );
    }
};

CHAOS_TEST_UNIT_FIXTURE( inverse_operator, InverseOperatorFixture )
{
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( -fixture->vecs[ i ], fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                SCALAR ADDITION
//------------------------------------------------------------------------------

class ScalarAdditionFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector3 > vecs;
    std::vector< float > scalars;
    std::vector< chaos::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector3() );
        scalars.push_back( 0.0F );
        results.push_back( chaos::gfx::Vector3() );

        vecs.push_back( chaos::gfx::Vector3() );
        scalars.push_back( 1.0F );
        results.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );

        vecs.push_back( chaos::gfx::Vector3() );
        scalars.push_back( -0.048F );
        results.push_back( chaos::gfx::Vector3( -0.048F, -0.048F, -0.048F ) );

        vecs.push_back( chaos::gfx::Vector3( 0.3F, -84.08F, 12.456F ) );
        scalars.push_back( 0.0F );
        results.push_back( chaos::gfx::Vector3(  0.3F, -84.08F, 12.456F ) );

        vecs.push_back( chaos::gfx::Vector3( -20.007F, 0.009F, 8.0F ) );
        scalars.push_back( 0.01F );
        results.push_back( chaos::gfx::Vector3(  -19.997F, 0.019F, 8.01F ) );

        vecs.push_back( chaos::gfx::Vector3( 0.34F, 2.6F, 34.87F ) );
        scalars.push_back( -1.5F );
        results.push_back( chaos::gfx::Vector3( -1.16F, 1.1F, 33.37F ) );
    }
};

CHAOS_TEST_UNIT_FIXTURE( scalar_addition, ScalarAdditionFixture )
{
    CHAOS_TEST_MESSAGE( "Checking addition" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        chaos::gfx::Vector3 v( fixture->vecs[ i ] + fixture->scalars[ i ] );

        CHAOS_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking compound addition" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        chaos::gfx::Vector3 v( fixture->vecs[ i ] );
        v += fixture->scalars[ i ];

        CHAOS_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                VECTOR ADDITION
//------------------------------------------------------------------------------

class VectorAdditionFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector3 > vecs;
    std::vector< chaos::gfx::Vector3 > add;
    std::vector< chaos::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector3() );
        add.push_back( chaos::gfx::Vector3() );
        results.push_back( chaos::gfx::Vector3() );

        vecs.push_back( chaos::gfx::Vector3() );
        add.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        results.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );

        vecs.push_back( chaos::gfx::Vector3() );
        add.push_back( chaos::gfx::Vector3( -9.49F, -0.34F, 3.045F ) );
        results.push_back( chaos::gfx::Vector3( -9.49F, -0.34F, 3.045F ) );

        vecs.push_back( chaos::gfx::Vector3( -4.98F, 0.0074F, -5.00034F ) );
        add.push_back( chaos::gfx::Vector3() );
        results.push_back( chaos::gfx::Vector3( -4.98F, 0.0074F, -5.00034F ) );

        vecs.push_back( chaos::gfx::Vector3( 3.083F, 0.23F, 0.0001F ) );
        add.push_back( chaos::gfx::Vector3( -1.2F, -0.08F, 0.2F ) );
        results.push_back( chaos::gfx::Vector3( 1.883F, 0.15F, 0.2001F ) );

        vecs.push_back( chaos::gfx::Vector3( 10.3F, -2.004F, -7.87F ) );
        add.push_back( chaos::gfx::Vector3( 49.94F, 0.054F, 12.7485F ) );
        results.push_back( chaos::gfx::Vector3( 60.24F, -1.95F, 4.8785F ) );
    }
};

CHAOS_TEST_UNIT_FIXTURE( vector_addition, VectorAdditionFixture )
{
    CHAOS_TEST_MESSAGE( "Checking addition" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        chaos::gfx::Vector3 v( fixture->vecs[ i ] + fixture->add[ i ] );

        CHAOS_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking compound addition" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        chaos::gfx::Vector3 v( fixture->vecs[ i ] );
        v += fixture->add[ i ];

        CHAOS_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               SCALAR SUBTRACTION
//------------------------------------------------------------------------------

class ScalarSubtractionFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector3 > vecs;
    std::vector< float > scalars;
    std::vector< chaos::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector3() );
        scalars.push_back( 0.0F );
        results.push_back( chaos::gfx::Vector3() );

        vecs.push_back( chaos::gfx::Vector3() );
        scalars.push_back( 1.0F );
        results.push_back( chaos::gfx::Vector3( -1.0F, -1.0F, -1.0F ) );

        vecs.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        scalars.push_back( 1.0F );
        results.push_back( chaos::gfx::Vector3( 0.0F, 0.0F, 0.0F ) );

        vecs.push_back( chaos::gfx::Vector3() );
        scalars.push_back( -0.048F );
        results.push_back( chaos::gfx::Vector3( 0.048F, 0.048F, 0.048F ) );

        vecs.push_back( chaos::gfx::Vector3( 0.3F, -84.08F, 8.348F ) );
        scalars.push_back( 0.0F );
        results.push_back( chaos::gfx::Vector3(  0.3F, -84.08F, 8.348F ) );

        vecs.push_back( chaos::gfx::Vector3( -20.007F, 0.009F, 34.0005F ) );
        scalars.push_back( 0.01F );
        results.push_back( chaos::gfx::Vector3(
                 -20.017F, -0.001F, 33.9905F ) );

        vecs.push_back( chaos::gfx::Vector3( 0.34F, 2.6F, -2.4F ) );
        scalars.push_back( 1.5F );
        results.push_back( chaos::gfx::Vector3( -1.16F, 1.1F, -3.9F ) );
    }
};

CHAOS_TEST_UNIT_FIXTURE( scalar_subtraction, ScalarSubtractionFixture )
{
    CHAOS_TEST_MESSAGE( "Checking subtraction" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        chaos::gfx::Vector3 v( fixture->vecs[ i ] - fixture->scalars[ i ] );

        CHAOS_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking compound subtraction" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        chaos::gfx::Vector3 v( fixture->vecs[ i ] );
        v -= fixture->scalars[ i ];

        CHAOS_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               VECTOR SUBTRACTION
//------------------------------------------------------------------------------

class VectorSubtractionFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector3 > vecs;
    std::vector< chaos::gfx::Vector3 > sub;
    std::vector< chaos::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector3() );
        sub.push_back( chaos::gfx::Vector3() );
        results.push_back( chaos::gfx::Vector3() );

        vecs.push_back( chaos::gfx::Vector3() );
        sub.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        results.push_back( chaos::gfx::Vector3( -1.0F, -1.0F, -1.0F ) );

        vecs.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        sub.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        results.push_back( chaos::gfx::Vector3() );

        vecs.push_back( chaos::gfx::Vector3() );
        sub.push_back( chaos::gfx::Vector3( 9.49F, 0.34F, -345.39F ) );
        results.push_back( chaos::gfx::Vector3( -9.49F, -0.34F, 345.39F ) );

        vecs.push_back( chaos::gfx::Vector3( -4.98F, 0.0074F, 670.34F ) );
        sub.push_back( chaos::gfx::Vector3() );
        results.push_back( chaos::gfx::Vector3( -4.98F, 0.0074F, 670.34F ) );

        vecs.push_back( chaos::gfx::Vector3( 3.083F, 0.23F, -12.89F ) );
        sub.push_back( chaos::gfx::Vector3( -1.2F, -0.08F, 0.12F ) );
        results.push_back( chaos::gfx::Vector3( 4.283F, 0.31F, -13.01F ) );

        vecs.push_back( chaos::gfx::Vector3( 10.3F, -2.004F, 0.0037F ) );
        sub.push_back( chaos::gfx::Vector3( 49.94F, 0.054F, -47.0F ) );
        results.push_back( chaos::gfx::Vector3( -39.64F, -2.058F, 47.0037F ) );
    }
};

CHAOS_TEST_UNIT_FIXTURE( vector_subtraction, VectorSubtractionFixture )
{
    CHAOS_TEST_MESSAGE( "Checking subtraction" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        chaos::gfx::Vector3 v( fixture->vecs[ i ] - fixture->sub[ i ] );

        CHAOS_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking compound subtraction" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        chaos::gfx::Vector3 v( fixture->vecs[ i ] );
        v -= fixture->sub[ i ];

        CHAOS_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                             SCALAR MULTIPLICATION
//------------------------------------------------------------------------------

class ScalarMultiplicationFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector3 > vecs;
    std::vector< float > scalars;
    std::vector< chaos::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector3() );
        scalars.push_back( 0.0F );
        results.push_back( chaos::gfx::Vector3() );

        vecs.push_back( chaos::gfx::Vector3() );
        scalars.push_back( 1.0F );
        results.push_back( chaos::gfx::Vector3() );

        vecs.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        scalars.push_back( 1.0F );
        results.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );

        vecs.push_back( chaos::gfx::Vector3( 1.0F, -1.0F, 5.0F ) );
        scalars.push_back( 2.0F );
        results.push_back( chaos::gfx::Vector3( 2.0F, -2.0F, 10.0F ) );

        vecs.push_back( chaos::gfx::Vector3( 12.0F, 5.5F, 28.5F ) );
        scalars.push_back( 0.5F );
        results.push_back( chaos::gfx::Vector3( 6.0F, 2.75F, 14.25F ) );

        vecs.push_back( chaos::gfx::Vector3( 456.0F, 549.23F, 0.1F ) );
        scalars.push_back( 12.0F );
        results.push_back( chaos::gfx::Vector3( 5472.0F, 6590.76F, 1.2F ) );
    }
};

CHAOS_TEST_UNIT_FIXTURE( scalar_multiplication, ScalarMultiplicationFixture )
{
    CHAOS_TEST_MESSAGE( "Checking multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        chaos::gfx::Vector3 v( fixture->vecs[ i ] * fixture->scalars[ i ] );

        CHAOS_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking compound multiplication" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        chaos::gfx::Vector3 v( fixture->vecs[ i ] );
        v *= fixture->scalars[ i ];

        CHAOS_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                SCALAR DIVISION
//------------------------------------------------------------------------------

class ScalarDivisionFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::gfx::Vector3 > vecs;
    std::vector< float > scalars;
    std::vector< chaos::gfx::Vector3 > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back( chaos::gfx::Vector3() );
        scalars.push_back( 0.3F );
        results.push_back( chaos::gfx::Vector3() );

        vecs.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );
        scalars.push_back( 1.0F );
        results.push_back( chaos::gfx::Vector3( 1.0F, 1.0F, 1.0F ) );

        vecs.push_back( chaos::gfx::Vector3( 1.0F, -1.0F, 0.0F ) );
        scalars.push_back( 2.0F );
        results.push_back( chaos::gfx::Vector3( 0.5F, -0.5F, 0.0F ) );

        vecs.push_back( chaos::gfx::Vector3( 12.0F, 5.5F, 100.1F ) );
        scalars.push_back( 0.5F );
        results.push_back( chaos::gfx::Vector3( 24.0F, 11.0F, 200.2F ) );

        vecs.push_back( chaos::gfx::Vector3( 456.0F, 549.0F, -73.34F ) );
        scalars.push_back( 12.0F );
        results.push_back( chaos::gfx::Vector3( 38.0F, 45.75F, -6.11167F ) );
    }
};

CHAOS_TEST_UNIT_FIXTURE( scalar_division, ScalarDivisionFixture )
{
    CHAOS_TEST_MESSAGE( "Checking division" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        chaos::gfx::Vector3 v( fixture->vecs[ i ] / fixture->scalars[ i ] );

        CHAOS_CHECK_EQUAL( v, fixture->results[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking compound division" );
    for ( std::size_t i = 0; i < fixture->vecs.size(); ++i )
    {
        chaos::gfx::Vector3 v( fixture->vecs[ i ] );
        v /= fixture->scalars[ i ];

        CHAOS_CHECK_EQUAL( v, fixture->results[ i ] );
    }
}

} // namespace vector3_tests
