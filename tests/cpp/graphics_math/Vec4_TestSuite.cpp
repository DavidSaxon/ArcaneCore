#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.Vec4)

#include "arcanecore/graphics_math/Vec4.hpp"

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
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT(default_constructor)
{
    TestVec4 v;

    // check that components are zero
    ARC_CHECK_EQUAL(v.x, 0);
    ARC_CHECK_EQUAL(v.y, 0);
    ARC_CHECK_EQUAL(v.z, 0);
    ARC_CHECK_EQUAL(v.w, 0);
}

//------------------------------------------------------------------------------
//                             COMPONENT CONSTRUCTOR
//------------------------------------------------------------------------------

class ComponentConstructorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec4DataType> x_components;
    std::vector<TestVec4DataType> y_components;
    std::vector<TestVec4DataType> z_components;
    std::vector<TestVec4DataType> w_components;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        x_components.push_back(0);
        y_components.push_back(0);
        z_components.push_back(0);
        w_components.push_back(0);

        x_components.push_back(1);
        y_components.push_back(0);
        z_components.push_back(1);
        w_components.push_back(0);

        x_components.push_back(5);
        y_components.push_back(78);
        z_components.push_back(12);
        w_components.push_back(1);

        x_components.push_back(-45);
        y_components.push_back(6);
        z_components.push_back(-85);
        w_components.push_back(4);

        x_components.push_back(-0);
        y_components.push_back(0);
        z_components.push_back(0);
        w_components.push_back(-0);

        x_components.push_back(-5);
        y_components.push_back(-1);
        z_components.push_back(-19);
        w_components.push_back(-34);

        x_components.push_back(464557);
        y_components.push_back(123);
        z_components.push_back(-91713);
        w_components.push_back(-7483);
    }
};

ARC_TEST_UNIT_FIXTURE(component_constructor, ComponentConstructorFixture)
{
    for(std::size_t i = 0; i < fixture->x_components.size(); i++)
    {
        TestVec4 v(
            fixture->x_components[i],
            fixture->y_components[i],
            fixture->z_components[i],
            fixture->w_components[i]
        );
        ARC_CHECK_EQUAL(v.x, fixture->x_components[i]);
        ARC_CHECK_EQUAL(v.y, fixture->y_components[i]);
        ARC_CHECK_EQUAL(v.z, fixture->z_components[i]);
        ARC_CHECK_EQUAL(v.w, fixture->w_components[i]);
    }
}

//------------------------------------------------------------------------------
//                               SCALAR CONSTRUCTOR
//------------------------------------------------------------------------------

class ScalarConstructorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec4DataType> scalars;

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
    for(TestVec4DataType scalar : fixture->scalars)
    {
        TestVec4 v(scalar);
        ARC_CHECK_EQUAL(v.x, scalar);
        ARC_CHECK_EQUAL(v.y, scalar);
        ARC_CHECK_EQUAL(v.z, scalar);
        ARC_CHECK_EQUAL(v.w, scalar);
    }
}

//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

class CopyConstructorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec4> vecs;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back(TestVec4());
        vecs.push_back(TestVec4(0, 1, 0, 1));
        vecs.push_back(TestVec4(345, 0, 901, 24));
        vecs.push_back(TestVec4(-45, -585, -18, -81));
        vecs.push_back(TestVec4(9789, 145, 3902, 9828));
        vecs.push_back(TestVec4(6, -1, -31, 14));
        vecs.push_back(TestVec4(-56, 85024, 782, -1825));
    }
};

ARC_TEST_UNIT_FIXTURE(copy_constructor, CopyConstructorFixture)
{
    for(const TestVec4& vec : fixture->vecs)
    {
        TestVec4 v(vec);
        ARC_CHECK_EQUAL(v.x, vec.x);
        ARC_CHECK_EQUAL(v.y, vec.y);
        ARC_CHECK_EQUAL(v.z, vec.z);
        ARC_CHECK_EQUAL(v.w, vec.w);
    }
}

//------------------------------------------------------------------------------
//                                MOVE CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(move_constructor, CopyConstructorFixture)
{
    for(TestVec4& vec : fixture->vecs)
    {
        TestVec4DataType x = vec.x;
        TestVec4DataType y = vec.y;
        TestVec4DataType z = vec.z;
        TestVec4DataType w = vec.w;

        TestVec4 v(std::move(vec));

        ARC_CHECK_EQUAL(v.x, x);
        ARC_CHECK_EQUAL(v.y, y);
        ARC_CHECK_EQUAL(v.z, z);
        ARC_CHECK_EQUAL(v.w, w);

        ARC_CHECK_EQUAL(vec.x, 0);
        ARC_CHECK_EQUAL(vec.y, 0);
        ARC_CHECK_EQUAL(vec.z, 0);
        ARC_CHECK_EQUAL(vec.w, 0);
    }
}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(assignment_operator, CopyConstructorFixture)
{
    for(const TestVec4& vec : fixture->vecs)
    {
        TestVec4 v;
        v = vec;

        ARC_CHECK_EQUAL(v.x, vec.x);
        ARC_CHECK_EQUAL(v.y, vec.y);
        ARC_CHECK_EQUAL(v.z, vec.z);
        ARC_CHECK_EQUAL(v.w, vec.w);
    }
}

//------------------------------------------------------------------------------
//                           SCALAR ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(scalar_assignment_operator, ScalarConstructorFixture)
{
    for(const TestVec4DataType& s : fixture->scalars)
    {
        TestVec4 v;
        v = s;

        ARC_CHECK_EQUAL(v.x, s);
        ARC_CHECK_EQUAL(v.y, s);
        ARC_CHECK_EQUAL(v.z, s);
        ARC_CHECK_EQUAL(v.w, s);
    }
}

//------------------------------------------------------------------------------
//                                 MOVE OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(move_operator, CopyConstructorFixture)
{
    for(TestVec4& vec : fixture->vecs)
    {
        TestVec4DataType x = vec.x;
        TestVec4DataType y = vec.y;
        TestVec4DataType z = vec.z;
        TestVec4DataType w = vec.w;

        TestVec4 v;
        v = std::move(vec);

        ARC_CHECK_EQUAL(v.x, x);
        ARC_CHECK_EQUAL(v.y, y);
        ARC_CHECK_EQUAL(v.z, z);
        ARC_CHECK_EQUAL(v.w, w);

        ARC_CHECK_EQUAL(vec.x, 0);
        ARC_CHECK_EQUAL(vec.y, 0);
        ARC_CHECK_EQUAL(vec.z, 0);
        ARC_CHECK_EQUAL(vec.w, 0);
    }
}

} // namespace anonymous
