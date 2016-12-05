#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.Vec3Operations)

#include "arcanecore/graphics_math/Vec3Operations.hpp"

namespace
{

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

typedef arc::int32 TestVec3DataType;
/*
 * Typedefs a arc::int32 typed Vec3 to use for testing. We use a integral type
 * so we can more reliably perform equality tests.
 */
typedef arc::gm::Vec3<TestVec3DataType> TestVec3;

//------------------------------------------------------------------------------
//                                STREAM OPERATOR
//------------------------------------------------------------------------------

class StreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec3> vecs;
    std::vector<arc::str::UTF8String> results;

    arc::str::UTF8String nonempty;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        nonempty = "Hello world!";

        vecs.push_back(TestVec3());
        results.push_back("(0, 0, 0)");

        vecs.push_back(TestVec3(0, 1, 0));
        results.push_back("(0, 1, 0)");

        vecs.push_back(TestVec3(5, -1, -4));
        results.push_back("(5, -1, -4)");

        vecs.push_back(TestVec3(456, 59845, 87156));
        results.push_back("(456, 59845, 87156)");

        vecs.push_back(TestVec3(-17, 9847, 195));
        results.push_back("(-17, 9847, 195)");

        vecs.push_back(TestVec3(-589017, -4, -1845));
        results.push_back("(-589017, -4, -1845)");
    }
};

ARC_TEST_UNIT_FIXTURE(stream_operator, StreamOperatorFixture)
{
    ARC_TEST_MESSAGE("Checking empty strings");
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        arc::str::UTF8String s;
        s << fixture->vecs[i];

        ARC_CHECK_EQUAL(s, fixture->results[i]);
    }

    ARC_TEST_MESSAGE("Checking non-empty strings");
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        arc::str::UTF8String s(fixture->nonempty);
        s << fixture->vecs[i];

        ARC_CHECK_EQUAL(s, (fixture->nonempty + fixture->results[i]));
    }
}

//------------------------------------------------------------------------------
//                               EQUALITY OPERATOR
//------------------------------------------------------------------------------

class EqualityOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec3> vecs;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back(TestVec3());
        vecs.push_back(TestVec3(0, 1, 1));
        vecs.push_back(TestVec3(5, -1, -4));
        vecs.push_back(TestVec3(456, 59845, 1859));
        vecs.push_back(TestVec3(-17, 9847, 818));
        vecs.push_back(TestVec3(-589017, -4, -1475));
    }
};

ARC_TEST_UNIT_FIXTURE(equality_operator, EqualityOperatorFixture)
{
    ARC_TEST_MESSAGE("Checking true cases");
    for(const TestVec3& v : fixture->vecs)
    {
        TestVec3 c(v);
        ARC_CHECK_TRUE(v == c);
    }

    ARC_TEST_MESSAGE("Checking true cases");
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        for(std::size_t j = 0; j < fixture->vecs.size(); j++)
        {
            if(i == j)
            {
                continue;
            }

            ARC_CHECK_FALSE(fixture->vecs[i] == fixture->vecs[j]);
        }
    }
}

//------------------------------------------------------------------------------
//                              INEQUALITY OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(inequality_operator, EqualityOperatorFixture)
{
    ARC_TEST_MESSAGE("Checking false cases");
    for(const TestVec3& v : fixture->vecs)
    {
        TestVec3 c(v);
        ARC_CHECK_FALSE(v != c);
    }

    ARC_TEST_MESSAGE("Checking true cases");
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        for(std::size_t j = 0; j < fixture->vecs.size(); j++)
        {
            if(i == j)
            {
                continue;
            }

            ARC_CHECK_TRUE(fixture->vecs[i] != fixture->vecs[j]);
        }
    }
}

//------------------------------------------------------------------------------
//                               NEGATION OPERATOR
//------------------------------------------------------------------------------

class NegationOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec3> vecs;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back(TestVec3());
        vecs.push_back(TestVec3(0, 1, 1));
        vecs.push_back(TestVec3(5, -1, -4));
        vecs.push_back(TestVec3(456, 59845, 1859));
        vecs.push_back(TestVec3(-17, 9847, 818));
        vecs.push_back(TestVec3(-589017, -4, -1475));
    }
};

ARC_TEST_UNIT_FIXTURE(negation_operator, NegationOperatorFixture)
{
    for(const TestVec3& vec : fixture->vecs)
    {
        TestVec3 v(-vec);
        ARC_CHECK_EQUAL(v.x, -vec.x);
        ARC_CHECK_EQUAL(v.y, -vec.y);
        ARC_CHECK_EQUAL(v.z, -vec.z);
    }
}

//------------------------------------------------------------------------------
//                            BINARY OPERATORS FIXTURE
//------------------------------------------------------------------------------

class BinaryOperatorsFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec3> vecs1;
    std::vector<TestVec3> vecs2;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs1.push_back(TestVec3());
        vecs2.push_back(TestVec3());

        vecs1.push_back(TestVec3(0, 1, 0));
        vecs2.push_back(TestVec3(1, 0, 1));

        vecs1.push_back(TestVec3(5, -1, 14));
        vecs2.push_back(TestVec3(-5, 45, -5));

        vecs1.push_back(TestVec3(456, 59845, -8918));
        vecs2.push_back(TestVec3(85, -45834, -1845));

        vecs1.push_back(TestVec3(-17, 9847, 395));
        vecs2.push_back(TestVec3(-91, 9854, 8958));

        vecs1.push_back(TestVec3(-589017, -4, -580));
        vecs2.push_back(TestVec3(-8383, -5642, -7239));
    }
};

//------------------------------------------------------------------------------
//                        SCALAR BINARY OPERATORS FIXTURE
//------------------------------------------------------------------------------

class ScalarBinaryOperatorsFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec3> vecs;
    std::vector<TestVec3DataType> scalars;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back(TestVec3());
        scalars.push_back(0);

        vecs.push_back(TestVec3(0, 1, 0));
        scalars.push_back(1);

        vecs.push_back(TestVec3(5, -1, 14));
        scalars.push_back(45);

        vecs.push_back(TestVec3(456, 59845, -8918));
        scalars.push_back(-45834);

        vecs.push_back(TestVec3(-17, 9847, 395));
        scalars.push_back(56895);

        vecs.push_back(TestVec3(-589017, -4, -580));
        scalars.push_back(19);
    }
};

//------------------------------------------------------------------------------
//                               ADDITION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(addition_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        TestVec3 v(fixture->vecs1[i] + fixture->vecs2[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x + fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y + fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z + fixture->vecs2[i].z);
    }
}

//------------------------------------------------------------------------------
//                           COMPOUND ADDITION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(compound_addition_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        TestVec3 v(fixture->vecs1[i]);
        v += fixture->vecs2[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x + fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y + fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z + fixture->vecs2[i].z);
    }
}

//------------------------------------------------------------------------------
//                            SCALAR ADDITION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(scalar_addition_operator, ScalarBinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        TestVec3 v(fixture->vecs[i] + fixture->scalars[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x + fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y + fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z + fixture->scalars[i]);
    }
}

//------------------------------------------------------------------------------
//                       SCALAR COMPOUND ADDITION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(
        scalar_compound_addition_operator,
        ScalarBinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        TestVec3 v(fixture->vecs[i]);
        v += fixture->scalars[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x + fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y + fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z + fixture->scalars[i]);
    }
}

//------------------------------------------------------------------------------
//                              SUBTRACTION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(subtraction_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        TestVec3 v(fixture->vecs1[i] - fixture->vecs2[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x - fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y - fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z - fixture->vecs2[i].z);
    }
}

//------------------------------------------------------------------------------
//                         COMPOUND SUBTRACTION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(compound_subtraction_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        TestVec3 v(fixture->vecs1[i]);
        v -= fixture->vecs2[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x - fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y - fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z - fixture->vecs2[i].z);
    }
}

//------------------------------------------------------------------------------
//                          SCALAR SUBTRACTION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(scalar_subtraction_operator, ScalarBinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        TestVec3 v(fixture->vecs[i] - fixture->scalars[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x - fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y - fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z - fixture->scalars[i]);
    }
}

//------------------------------------------------------------------------------
//                      SCALAR COMPOUND SUBTRACTION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(
        scalar_compound_subtraction_operator,
        ScalarBinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        TestVec3 v(fixture->vecs[i]);
        v -= fixture->scalars[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x - fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y - fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z - fixture->scalars[i]);
    }
}

//------------------------------------------------------------------------------
//                            MULTIPLICATION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(multiplication_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        TestVec3 v(fixture->vecs1[i] * fixture->vecs2[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x * fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y * fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z * fixture->vecs2[i].z);
    }
}

//------------------------------------------------------------------------------
//                        COMPOUND MULTIPLICATION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(compound_multiplication_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        TestVec3 v(fixture->vecs1[i]);
        v *= fixture->vecs2[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x * fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y * fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z * fixture->vecs2[i].z);
    }
}

//------------------------------------------------------------------------------
//                         SCALAR MULTIPLICATION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(
        scalar_multiplication_operator,
        ScalarBinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        TestVec3 v(fixture->vecs[i] * fixture->scalars[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x * fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y * fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z * fixture->scalars[i]);
    }
}

//------------------------------------------------------------------------------
//                    SCALAR COMPOUND MULTIPLICATION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(
        scalar_compound_multiplication_operator,
        ScalarBinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        TestVec3 v(fixture->vecs[i]);
        v *= fixture->scalars[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x * fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y * fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z * fixture->scalars[i]);
    }
}

//------------------------------------------------------------------------------
//                               DIVISION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(division_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        // avoid divide by zero
        if(fixture->vecs2[i].x == 0 ||
           fixture->vecs2[i].y == 0 ||
           fixture->vecs2[i].z == 0)
        {
            continue;
        }

        TestVec3 v(fixture->vecs1[i] / fixture->vecs2[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x / fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y / fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z / fixture->vecs2[i].z);
    }
}

//------------------------------------------------------------------------------
//                           COMPOUND DIVISION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(compound_division_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        // avoid divide by zero
        if(fixture->vecs2[i].x == 0 ||
           fixture->vecs2[i].y == 0 ||
           fixture->vecs2[i].z == 0)
        {
            continue;
        }

        TestVec3 v(fixture->vecs1[i]);
        v /= fixture->vecs2[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x / fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y / fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z / fixture->vecs2[i].z);
    }
}

//------------------------------------------------------------------------------
//                            SCALAR DIVISION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(
        scalar_division_operator,
        ScalarBinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        // avoid divide by zero
        if(fixture->scalars[i] == 0)
        {
            continue;
        }

        TestVec3 v(fixture->vecs[i] / fixture->scalars[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x / fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y / fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z / fixture->scalars[i]);
    }
}

//------------------------------------------------------------------------------
//                       SCALAR COMPOUND DIVISION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(
        scalar_compound_division_operator,
        ScalarBinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        // avoid divide by zero
        if(fixture->scalars[i] == 0)
        {
            continue;
        }

        TestVec3 v(fixture->vecs[i]);
        v /= fixture->scalars[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x / fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y / fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z / fixture->scalars[i]);
    }
}

//------------------------------------------------------------------------------
// Most of the following tests are just here to make sure the template functions
// actually compile. At some point I need to come back and make them proper
// tests.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                               SQUARED MAGNITUDE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(magnitude2)
{
    TestVec3 v(2, 4, 3);
    ARC_CHECK_EQUAL(arc::gm::magnitude2(v), 29);
}

//------------------------------------------------------------------------------
//                                   MAGNITUDE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(magnitude)
{
    TestVec3 v(2, 4, 3);
    ARC_CHECK_EQUAL(arc::gm::magnitude(v), 5);
}

//------------------------------------------------------------------------------
//                                   NORMALISE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(normalise)
{
    TestVec3 v(2, 4, 6);
    TestVec3 r(0, 0, 0);
    ARC_CHECK_EQUAL(arc::gm::normalise(v), r);
}

//------------------------------------------------------------------------------
//                                  DOT PRODUCT
//------------------------------------------------------------------------------

ARC_TEST_UNIT(dot)
{
    TestVec3 a(3, 4, 8);
    TestVec3 b(5, 6, -2);
    ARC_CHECK_EQUAL(arc::gm::dot(a, b), 23);
}

} // namespace anonymous