#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.Vec2)

#include "arcanecore/graphics_math/Vec2.hpp"

namespace
{

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

typedef arc::int32 TestVec2DataType;
/*
 * Typedefs a arc::int32 typed Vec2 to use for testing. We use a integral type
 * so we can more reliably perform equality tests.
 */
typedef arc::gm::Vec2<TestVec2DataType> TestVec2;

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT(default_constructor)
{
    TestVec2 v;

    // check that components are zero
    ARC_CHECK_EQUAL(v.x, 0);
    ARC_CHECK_EQUAL(v.y, 0);
}

//------------------------------------------------------------------------------
//                             COMPONENT CONSTRUCTOR
//------------------------------------------------------------------------------

class ComponentConstructorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec2DataType> x_components;
    std::vector<TestVec2DataType> y_components;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        x_components.push_back(0);
        y_components.push_back(0);

        x_components.push_back(1);
        y_components.push_back(0);

        x_components.push_back(5);
        y_components.push_back(78);

        x_components.push_back(-45);
        y_components.push_back(6);

        x_components.push_back(-0);
        y_components.push_back(0);

        x_components.push_back(-5);
        y_components.push_back(-1);

        x_components.push_back(464557);
        y_components.push_back(123);
    }
};

ARC_TEST_UNIT_FIXTURE(component_constructor, ComponentConstructorFixture)
{
    for(std::size_t i = 0; i < fixture->x_components.size(); i++)
    {
        TestVec2 v(fixture->x_components[i], fixture->y_components[i]);
        ARC_CHECK_EQUAL(v.x, fixture->x_components[i]);
        ARC_CHECK_EQUAL(v.y, fixture->y_components[i]);
    }
}

//------------------------------------------------------------------------------
//                               SCALAR CONSTRUCTOR
//------------------------------------------------------------------------------

class ScalarConstructorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec2DataType> scalars;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        scalars.push_back(0);
        scalars.push_back(-0);
        scalars.push_back(1);
        scalars.push_back(6);
        scalars.push_back(568);
        scalars.push_back(451534);
        scalars.push_back(-4);
        scalars.push_back(-158);
        scalars.push_back(-91475);
    }
};

ARC_TEST_UNIT_FIXTURE(scalar_constructor, ScalarConstructorFixture)
{
    for(TestVec2DataType scalar : fixture->scalars)
    {
        TestVec2 v(scalar);
        ARC_CHECK_EQUAL(v.x, scalar);
        ARC_CHECK_EQUAL(v.y, scalar);
    }
}

//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

class CopyConstructorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec2> vecs;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back(TestVec2());
        vecs.push_back(TestVec2(0, 1));
        vecs.push_back(TestVec2(345, 0));
        vecs.push_back(TestVec2(-45, -585));
        vecs.push_back(TestVec2(9789, 145));
        vecs.push_back(TestVec2(6, -1));
        vecs.push_back(TestVec2(-56, 85024));
    }
};

ARC_TEST_UNIT_FIXTURE(copy_constructor, CopyConstructorFixture)
{
    for(const TestVec2& vec : fixture->vecs)
    {
        TestVec2 v(vec);
        ARC_CHECK_EQUAL(v.x, vec.x);
        ARC_CHECK_EQUAL(v.y, vec.y);
    }
}

//------------------------------------------------------------------------------
//                                MOVE CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(move_constructor, CopyConstructorFixture)
{
    for(TestVec2& vec : fixture->vecs)
    {
        TestVec2DataType x = vec.x;
        TestVec2DataType y = vec.y;

        TestVec2 v(std::move(vec));

        ARC_CHECK_EQUAL(v.x, x);
        ARC_CHECK_EQUAL(v.y, y);

        ARC_CHECK_EQUAL(vec.x, 0);
        ARC_CHECK_EQUAL(vec.y, 0);
    }
}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(assignment_operator, CopyConstructorFixture)
{
    for(const TestVec2& vec : fixture->vecs)
    {
        TestVec2 v;
        v = vec;

        ARC_CHECK_EQUAL(v.x, vec.x);
        ARC_CHECK_EQUAL(v.y, vec.y);
    }
}

//------------------------------------------------------------------------------
//                           SCALAR ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(scalar_assignment_operator, ScalarConstructorFixture)
{
    for(const TestVec2DataType& s : fixture->scalars)
    {
        TestVec2 v;
        v = s;

        ARC_CHECK_EQUAL(v.x, s);
        ARC_CHECK_EQUAL(v.y, s);
    }
}

//------------------------------------------------------------------------------
//                                 MOVE OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(move_operator, CopyConstructorFixture)
{
    for(TestVec2& vec : fixture->vecs)
    {
        TestVec2DataType x = vec.x;
        TestVec2DataType y = vec.y;

        TestVec2 v;
        v = std::move(vec);

        ARC_CHECK_EQUAL(v.x, x);
        ARC_CHECK_EQUAL(v.y, y);

        ARC_CHECK_EQUAL(vec.x, 0);
        ARC_CHECK_EQUAL(vec.y, 0);
    }
}

} // namespace anonymous
