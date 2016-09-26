#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.Vec4Operations)

#include "arcanecore/graphics_math/Vec4Operations.hpp"

namespace
{

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

typedef arc::int32 TestVec4DataType;
/*
 * Typedefs a arc::int32 typed Vec4 to use for testing. We use a integral type
 * so we can more reliably perform equality tests.
 */
typedef arc::gm::Vec4<TestVec4DataType> TestVec4;

//------------------------------------------------------------------------------
//                                STREAM OPERATOR
//------------------------------------------------------------------------------

class StreamOperatorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec4> vecs;
    std::vector<arc::str::UTF8String> results;

    arc::str::UTF8String nonempty;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        nonempty = "Hello world!";

        vecs.push_back(TestVec4());
        results.push_back("(0, 0, 0, 0)");

        vecs.push_back(TestVec4(0, 1, 0, 1));
        results.push_back("(0, 1, 0, 1)");

        vecs.push_back(TestVec4(5, -1, -4, 3));
        results.push_back("(5, -1, -4, 3)");

        vecs.push_back(TestVec4(456, 59845, 87156, 3491));
        results.push_back("(456, 59845, 87156, 3491)");

        vecs.push_back(TestVec4(-17, 9847, 195, -48));
        results.push_back("(-17, 9847, 195, -48)");

        vecs.push_back(TestVec4(-589017, -4, -1845, -59267));
        results.push_back("(-589017, -4, -1845, -59267)");
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

    std::vector<TestVec4> vecs;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back(TestVec4());
        vecs.push_back(TestVec4(0, 1, 1, 0));
        vecs.push_back(TestVec4(5, -1, -4, 3));
        vecs.push_back(TestVec4(456, 59845, 1859, 847));
        vecs.push_back(TestVec4(-17, 9847, 818, -182));
        vecs.push_back(TestVec4(-589017, -4, -1475, -6832));
    }
};

ARC_TEST_UNIT_FIXTURE(equality_operator, EqualityOperatorFixture)
{
    ARC_TEST_MESSAGE("Checking true cases");
    for(const TestVec4& v : fixture->vecs)
    {
        TestVec4 c(v);
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
    for(const TestVec4& v : fixture->vecs)
    {
        TestVec4 c(v);
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

    std::vector<TestVec4> vecs;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back(TestVec4());
        vecs.push_back(TestVec4(0, 1, 1, 0));
        vecs.push_back(TestVec4(5, -1, -4, 3));
        vecs.push_back(TestVec4(456, 59845, 1859, 847));
        vecs.push_back(TestVec4(-17, 9847, 818, -182));
        vecs.push_back(TestVec4(-589017, -4, -1475, -6832));
    }
};

ARC_TEST_UNIT_FIXTURE(negation_operator, NegationOperatorFixture)
{
    for(const TestVec4& vec : fixture->vecs)
    {
        TestVec4 v(-vec);
        ARC_CHECK_EQUAL(v.x, -vec.x);
        ARC_CHECK_EQUAL(v.y, -vec.y);
        ARC_CHECK_EQUAL(v.z, -vec.z);
        ARC_CHECK_EQUAL(v.w, -vec.w);
    }
}

//------------------------------------------------------------------------------
//                            BINARY OPERATORS FIXTURE
//------------------------------------------------------------------------------

class BinaryOperatorsFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec4> vecs1;
    std::vector<TestVec4> vecs2;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs1.push_back(TestVec4());
        vecs2.push_back(TestVec4());

        vecs1.push_back(TestVec4(0, 1, 0, 1));
        vecs2.push_back(TestVec4(1, 0, 1, 0));

        vecs1.push_back(TestVec4(5, -1, 14, 3));
        vecs2.push_back(TestVec4(-5, 45, -5, 7));

        vecs1.push_back(TestVec4(456, 59845, -8918, -145));
        vecs2.push_back(TestVec4(85, -45834, -1845, 829));

        vecs1.push_back(TestVec4(-17, 9847, 395, -494));
        vecs2.push_back(TestVec4(-91, 9854, 8958, 919));

        vecs1.push_back(TestVec4(-589017, -4, -580, -959));
        vecs2.push_back(TestVec4(-8383, -5642, -7239, -195));
    }
};

//------------------------------------------------------------------------------
//                        SCALAR BINARY OPERATORS FIXTURE
//------------------------------------------------------------------------------

class ScalarBinaryOperatorsFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec4> vecs;
    std::vector<TestVec4DataType> scalars;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back(TestVec4());
        scalars.push_back(0);

        vecs.push_back(TestVec4(0, 1, 0, 1));
        scalars.push_back(1);

        vecs.push_back(TestVec4(5, -1, 14, 3));
        scalars.push_back(45);

        vecs.push_back(TestVec4(456, 59845, -8918, -145));
        scalars.push_back(-45834);

        vecs.push_back(TestVec4(-17, 9847, 395, -494));
        scalars.push_back(56895);

        vecs.push_back(TestVec4(-589017, -4, -580, -959));
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
        TestVec4 v(fixture->vecs1[i] + fixture->vecs2[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x + fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y + fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z + fixture->vecs2[i].z);
        ARC_CHECK_EQUAL(v.w, fixture->vecs1[i].w + fixture->vecs2[i].w);
    }
}

//------------------------------------------------------------------------------
//                           COMPOUND ADDITION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(compound_addition_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        TestVec4 v(fixture->vecs1[i]);
        v += fixture->vecs2[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x + fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y + fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z + fixture->vecs2[i].z);
        ARC_CHECK_EQUAL(v.w, fixture->vecs1[i].w + fixture->vecs2[i].w);
    }
}

//------------------------------------------------------------------------------
//                            SCALAR ADDITION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(scalar_addition_operator, ScalarBinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        TestVec4 v(fixture->vecs[i] + fixture->scalars[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x + fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y + fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z + fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.w, fixture->vecs[i].w + fixture->scalars[i]);
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
        TestVec4 v(fixture->vecs[i]);
        v += fixture->scalars[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x + fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y + fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z + fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.w, fixture->vecs[i].w + fixture->scalars[i]);
    }
}

//------------------------------------------------------------------------------
//                              SUBTRACTION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(subtraction_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        TestVec4 v(fixture->vecs1[i] - fixture->vecs2[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x - fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y - fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z - fixture->vecs2[i].z);
        ARC_CHECK_EQUAL(v.w, fixture->vecs1[i].w - fixture->vecs2[i].w);
    }
}

//------------------------------------------------------------------------------
//                         COMPOUND SUBTRACTION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(compound_subtraction_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        TestVec4 v(fixture->vecs1[i]);
        v -= fixture->vecs2[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x - fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y - fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z - fixture->vecs2[i].z);
        ARC_CHECK_EQUAL(v.w, fixture->vecs1[i].w - fixture->vecs2[i].w);
    }
}

//------------------------------------------------------------------------------
//                          SCALAR SUBTRACTION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(scalar_subtraction_operator, ScalarBinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs.size(); i++)
    {
        TestVec4 v(fixture->vecs[i] - fixture->scalars[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x - fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y - fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z - fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.w, fixture->vecs[i].w - fixture->scalars[i]);
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
        TestVec4 v(fixture->vecs[i]);
        v -= fixture->scalars[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x - fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y - fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z - fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.w, fixture->vecs[i].w - fixture->scalars[i]);
    }
}

//------------------------------------------------------------------------------
//                            MULTIPLICATION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(multiplication_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        TestVec4 v(fixture->vecs1[i] * fixture->vecs2[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x * fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y * fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z * fixture->vecs2[i].z);
        ARC_CHECK_EQUAL(v.w, fixture->vecs1[i].w * fixture->vecs2[i].w);
    }
}

//------------------------------------------------------------------------------
//                        COMPOUND MULTIPLICATION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(compound_multiplication_operator, BinaryOperatorsFixture)
{
    for(std::size_t i = 0; i < fixture->vecs1.size(); i++)
    {
        TestVec4 v(fixture->vecs1[i]);
        v *= fixture->vecs2[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x * fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y * fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z * fixture->vecs2[i].z);
        ARC_CHECK_EQUAL(v.w, fixture->vecs1[i].w * fixture->vecs2[i].w);
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
        TestVec4 v(fixture->vecs[i] * fixture->scalars[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x * fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y * fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z * fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.w, fixture->vecs[i].w * fixture->scalars[i]);
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
        TestVec4 v(fixture->vecs[i]);
        v *= fixture->scalars[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x * fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y * fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z * fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.w, fixture->vecs[i].w * fixture->scalars[i]);
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
           fixture->vecs2[i].z == 0 ||
           fixture->vecs2[i].w == 0)
        {
            continue;
        }

        TestVec4 v(fixture->vecs1[i] / fixture->vecs2[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x / fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y / fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z / fixture->vecs2[i].z);
        ARC_CHECK_EQUAL(v.w, fixture->vecs1[i].w / fixture->vecs2[i].w);
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
           fixture->vecs2[i].z == 0 ||
           fixture->vecs2[i].w == 0)
        {
            continue;
        }

        TestVec4 v(fixture->vecs1[i]);
        v /= fixture->vecs2[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs1[i].x / fixture->vecs2[i].x);
        ARC_CHECK_EQUAL(v.y, fixture->vecs1[i].y / fixture->vecs2[i].y);
        ARC_CHECK_EQUAL(v.z, fixture->vecs1[i].z / fixture->vecs2[i].z);
        ARC_CHECK_EQUAL(v.w, fixture->vecs1[i].w / fixture->vecs2[i].w);
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

        TestVec4 v(fixture->vecs[i] / fixture->scalars[i]);

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x / fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y / fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z / fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.w, fixture->vecs[i].w / fixture->scalars[i]);
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

        TestVec4 v(fixture->vecs[i]);
        v /= fixture->scalars[i];

        ARC_CHECK_EQUAL(v.x, fixture->vecs[i].x / fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.y, fixture->vecs[i].y / fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.z, fixture->vecs[i].z / fixture->scalars[i]);
        ARC_CHECK_EQUAL(v.w, fixture->vecs[i].w / fixture->scalars[i]);
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
    TestVec4 v(2, 4, 3, 7);
    ARC_CHECK_EQUAL(arc::gm::magnitude2(v), 78);
}

//------------------------------------------------------------------------------
//                                   MAGNITUDE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(magnitude)
{
    TestVec4 v(2, 4, 3, 7);
    ARC_CHECK_EQUAL(arc::gm::magnitude(v), 8);
}

//------------------------------------------------------------------------------
//                                   NORMALISE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(normalise)
{
    TestVec4 v(2, 4, 6, -5);
    TestVec4 r(0, 0, 0, 0);
    ARC_CHECK_EQUAL(arc::gm::normalise(v), r);
}

//------------------------------------------------------------------------------
//                                  DOT PRODUCT
//------------------------------------------------------------------------------

ARC_TEST_UNIT(dot)
{
    TestVec4 a(3, 4, 8, -234);
    TestVec4 b(5, 6, -2, 56);
    ARC_CHECK_EQUAL(arc::gm::dot(a, b), -13081);
}

} // namespace anonymous
