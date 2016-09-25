#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.Vec3)

#include "arcanecore/graphics_math/Vec3.hpp"

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
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT(default_constructor)
{
    TestVec3 v;

    // check that components are zero
    ARC_CHECK_EQUAL(v.x, 0);
    ARC_CHECK_EQUAL(v.y, 0);
    ARC_CHECK_EQUAL(v.z, 0);
}

//------------------------------------------------------------------------------
//                             COMPONENT CONSTRUCTOR
//------------------------------------------------------------------------------

class ComponentConstructorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec3DataType> x_components;
    std::vector<TestVec3DataType> y_components;
    std::vector<TestVec3DataType> z_components;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        x_components.push_back(0);
        y_components.push_back(0);
        z_components.push_back(0);

        x_components.push_back(1);
        y_components.push_back(0);
        z_components.push_back(1);

        x_components.push_back(5);
        y_components.push_back(78);
        z_components.push_back(12);

        x_components.push_back(-45);
        y_components.push_back(6);
        z_components.push_back(-85);

        x_components.push_back(-0);
        y_components.push_back(0);
        z_components.push_back(0);

        x_components.push_back(-5);
        y_components.push_back(-1);
        z_components.push_back(-19);

        x_components.push_back(464557);
        y_components.push_back(123);
        z_components.push_back(-91713);
    }
};

ARC_TEST_UNIT_FIXTURE(component_constructor, ComponentConstructorFixture)
{
    for(std::size_t i = 0; i < fixture->x_components.size(); i++)
    {
        TestVec3 v(
            fixture->x_components[i],
            fixture->y_components[i],
            fixture->z_components[i]
        );
        ARC_CHECK_EQUAL(v.x, fixture->x_components[i]);
        ARC_CHECK_EQUAL(v.y, fixture->y_components[i]);
        ARC_CHECK_EQUAL(v.z, fixture->z_components[i]);
    }
}

//------------------------------------------------------------------------------
//                               SCALAR CONSTRUCTOR
//------------------------------------------------------------------------------

class ScalarConstructorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec3DataType> scalars;

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
    for(TestVec3DataType scalar : fixture->scalars)
    {
        TestVec3 v(scalar);
        ARC_CHECK_EQUAL(v.x, scalar);
        ARC_CHECK_EQUAL(v.y, scalar);
        ARC_CHECK_EQUAL(v.z, scalar);
    }
}

//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

class CopyConstructorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<TestVec3> vecs;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        vecs.push_back(TestVec3());
        vecs.push_back(TestVec3(0, 1, 0));
        vecs.push_back(TestVec3(345, 0, 901));
        vecs.push_back(TestVec3(-45, -585, -18));
        vecs.push_back(TestVec3(9789, 145, 3902));
        vecs.push_back(TestVec3(6, -1, -31));
        vecs.push_back(TestVec3(-56, 85024, 782));
    }
};

ARC_TEST_UNIT_FIXTURE(copy_constructor, CopyConstructorFixture)
{
    for(const TestVec3& vec : fixture->vecs)
    {
        TestVec3 v(vec);
        ARC_CHECK_EQUAL(v.x, vec.x);
        ARC_CHECK_EQUAL(v.y, vec.y);
        ARC_CHECK_EQUAL(v.z, vec.z);
    }
}

//------------------------------------------------------------------------------
//                                MOVE CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(move_constructor, CopyConstructorFixture)
{
    for(TestVec3& vec : fixture->vecs)
    {
        TestVec3DataType x = vec.x;
        TestVec3DataType y = vec.y;
        TestVec3DataType z = vec.z;

        TestVec3 v(std::move(vec));

        ARC_CHECK_EQUAL(v.x, x);
        ARC_CHECK_EQUAL(v.y, y);
        ARC_CHECK_EQUAL(v.z, z);

        ARC_CHECK_EQUAL(vec.x, 0);
        ARC_CHECK_EQUAL(vec.y, 0);
        ARC_CHECK_EQUAL(vec.z, 0);
    }
}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(assignment_operator, CopyConstructorFixture)
{
    for(const TestVec3& vec : fixture->vecs)
    {
        TestVec3 v;
        v = vec;

        ARC_CHECK_EQUAL(v.x, vec.x);
        ARC_CHECK_EQUAL(v.y, vec.y);
        ARC_CHECK_EQUAL(v.z, vec.z);
    }
}

//------------------------------------------------------------------------------
//                           SCALAR ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(scalar_assignment_operator, ScalarConstructorFixture)
{
    for(const TestVec3DataType& s : fixture->scalars)
    {
        TestVec3 v;
        v = s;

        ARC_CHECK_EQUAL(v.x, s);
        ARC_CHECK_EQUAL(v.y, s);
        ARC_CHECK_EQUAL(v.z, s);
    }
}

//------------------------------------------------------------------------------
//                                 MOVE OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(move_operator, CopyConstructorFixture)
{
    for(TestVec3& vec : fixture->vecs)
    {
        TestVec3DataType x = vec.x;
        TestVec3DataType y = vec.y;
        TestVec3DataType z = vec.z;

        TestVec3 v;
        v = std::move(vec);

        ARC_CHECK_EQUAL(v.x, x);
        ARC_CHECK_EQUAL(v.y, y);
        ARC_CHECK_EQUAL(v.z, z);

        ARC_CHECK_EQUAL(vec.x, 0);
        ARC_CHECK_EQUAL(vec.y, 0);
        ARC_CHECK_EQUAL(vec.z, 0);
    }
}

} // namespace anonymous
