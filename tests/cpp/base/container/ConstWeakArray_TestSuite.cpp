#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(base.container.ConstWeakArray)

#include "arcanecore/base/container/ConstWeakArray.hpp"


namespace
{

//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class ConstWeakArrayFixture : public arc::test::Fixture
{
public:

    //-----------------------------TYPE DEFINITIONS-----------------------------

    typedef arc::int32 DataType;

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::size_t null_data_size;
    DataType* null_data;

    std::size_t data_1_size;
    DataType* data_1;

    std::size_t data_2_size;
    DataType* data_2;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        null_data_size = 0;
        null_data = nullptr;

        data_1_size = 1;
        data_1 = new DataType[data_1_size];
        data_1[0] = 12;

        data_2_size = 7;
        data_2 = new DataType[data_2_size];
        data_2[0] = 0;
        data_2[1] = 58585;
        data_2[2] = -45458;
        data_2[3] = -24;
        data_2[4] = 15;
        data_2[5] = 83;
        data_2[6] = -158;
    }

    virtual void teardown()
    {
        delete[] data_1;
        delete[] data_2;
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(default_constructor, ConstWeakArrayFixture)
{
    arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a;
    ARC_CHECK_EQUAL(&a[0], nullptr);
    ARC_CHECK_EQUAL(a.size(), 0);
    ARC_CHECK_TRUE(a.empty());
}

//------------------------------------------------------------------------------
//                                DATA CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(data_constructor, ConstWeakArrayFixture)
{
    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->null_data,
            fixture->null_data_size
        );
        ARC_CHECK_EQUAL(&a[0], fixture->null_data);
        ARC_CHECK_EQUAL(a.size(), fixture->null_data_size);
        ARC_CHECK_TRUE(a.empty());
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_1,
            fixture->data_1_size
        );
        ARC_CHECK_EQUAL(&a[0], fixture->data_1);
        ARC_CHECK_EQUAL(a.size(), fixture->data_1_size);
        ARC_CHECK_FALSE(a.empty());
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_2,
            fixture->data_2_size
        );
        ARC_CHECK_EQUAL(&a[0], fixture->data_2);
        ARC_CHECK_EQUAL(a.size(), fixture->data_2_size);
        ARC_CHECK_FALSE(a.empty());
    }
}

//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(copy_constructor, ConstWeakArrayFixture)
{
    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->null_data,
            fixture->null_data_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> c(a);
        ARC_CHECK_EQUAL(&c[0], fixture->null_data);
        ARC_CHECK_EQUAL(c.size(), fixture->null_data_size);
        ARC_CHECK_TRUE(c.empty());
        ARC_CHECK_TRUE(c == a);
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_1,
            fixture->data_1_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> c(a);
        ARC_CHECK_EQUAL(&c[0], fixture->data_1);
        ARC_CHECK_EQUAL(c.size(), fixture->data_1_size);
        ARC_CHECK_FALSE(c.empty());
        ARC_CHECK_TRUE(c == a);
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_2,
            fixture->data_2_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> c(a);
        ARC_CHECK_EQUAL(&c[0], fixture->data_2);
        ARC_CHECK_EQUAL(c.size(), fixture->data_2_size);
        ARC_CHECK_FALSE(c.empty());
        ARC_CHECK_TRUE(c == a);
    }
}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(assignment_operator, ConstWeakArrayFixture)
{
    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->null_data,
            fixture->null_data_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> c
        (
            fixture->data_1,
            fixture->data_1_size
        );
        c = a;
        ARC_CHECK_EQUAL(&c[0], fixture->null_data);
        ARC_CHECK_EQUAL(c.size(), fixture->null_data_size);
        ARC_CHECK_TRUE(c.empty());
        ARC_CHECK_TRUE(c == a);
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_1,
            fixture->data_1_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> c
        (
            fixture->null_data,
            fixture->null_data_size
        );
        c = a;
        ARC_CHECK_EQUAL(&c[0], fixture->data_1);
        ARC_CHECK_EQUAL(c.size(), fixture->data_1_size);
        ARC_CHECK_FALSE(c.empty());
        ARC_CHECK_TRUE(c == a);
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_2,
            fixture->data_2_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> c
        (
            fixture->data_1,
            fixture->data_1_size
        );
        c = a;
        ARC_CHECK_EQUAL(&c[0], fixture->data_2);
        ARC_CHECK_EQUAL(c.size(), fixture->data_2_size);
        ARC_CHECK_FALSE(c.empty());
        ARC_CHECK_TRUE(c == a);
    }
}

//------------------------------------------------------------------------------
//                               EQUALITY OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(equality, ConstWeakArrayFixture)
{
    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->null_data,
            fixture->null_data_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> b
        (
            fixture->null_data,
            fixture->null_data_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> c(a);
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> ne
        (
            fixture->data_1,
            fixture->data_1_size
        );

        ARC_CHECK_TRUE(a == b);
        ARC_CHECK_TRUE(b == a);
        ARC_CHECK_TRUE(a == c);
        ARC_CHECK_FALSE(a == ne);
        ARC_CHECK_FALSE(ne == a);
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_1,
            fixture->data_1_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> b
        (
            fixture->data_1,
            fixture->data_1_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> c(a);
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> ne
        (
            fixture->null_data,
            fixture->null_data_size
        );

        ARC_CHECK_TRUE(a == b);
        ARC_CHECK_TRUE(b == a);
        ARC_CHECK_TRUE(a == c);
        ARC_CHECK_FALSE(a == ne);
        ARC_CHECK_FALSE(ne == a);
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_2,
            fixture->data_2_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> b
        (
            fixture->data_2,
            fixture->data_2_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> c(a);
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> ne
        (
            fixture->data_1,
            fixture->data_1_size
        );

        ARC_CHECK_TRUE(a == b);
        ARC_CHECK_TRUE(b == a);
        ARC_CHECK_TRUE(a == c);
        ARC_CHECK_FALSE(a == ne);
        ARC_CHECK_FALSE(ne == a);
    }
}

//------------------------------------------------------------------------------
//                              INEQUALITY OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(inequality, ConstWeakArrayFixture)
{
    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->null_data,
            fixture->null_data_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> b
        (
            fixture->null_data,
            fixture->null_data_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> c(a);
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> ne
        (
            fixture->data_1,
            fixture->data_1_size
        );

        ARC_CHECK_FALSE(a != b);
        ARC_CHECK_FALSE(b != a);
        ARC_CHECK_FALSE(a != c);
        ARC_CHECK_TRUE(a != ne);
        ARC_CHECK_TRUE(ne != a);
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_1,
            fixture->data_1_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> b
        (
            fixture->data_1,
            fixture->data_1_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> c(a);
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> ne
        (
            fixture->null_data,
            fixture->null_data_size
        );

        ARC_CHECK_FALSE(a != b);
        ARC_CHECK_FALSE(b != a);
        ARC_CHECK_FALSE(a != c);
        ARC_CHECK_TRUE(a != ne);
        ARC_CHECK_TRUE(ne != a);
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_2,
            fixture->data_2_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> b
        (
            fixture->data_2,
            fixture->data_2_size
        );
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> c(a);
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> ne
        (
            fixture->data_1,
            fixture->data_1_size
        );

        ARC_CHECK_FALSE(a != b);
        ARC_CHECK_FALSE(b != a);
        ARC_CHECK_FALSE(a != c);
        ARC_CHECK_TRUE(a != ne);
        ARC_CHECK_TRUE(ne != a);
    }
}

//------------------------------------------------------------------------------
//                                       AT
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(at, ConstWeakArrayFixture)
{
    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_1,
            fixture->data_1_size
        );

        for(std::size_t i = 0; i < fixture->data_1_size; ++i)
        {
            ARC_CHECK_EQUAL(a.at(i), fixture->data_1[i]);
            ARC_CHECK_EQUAL(a[i], fixture->data_1[i]);
        }
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_2,
            fixture->data_2_size
        );

        for(std::size_t i = 0; i < fixture->data_2_size; ++i)
        {
            ARC_CHECK_EQUAL(a.at(i), fixture->data_2[i]);
            ARC_CHECK_EQUAL(a[i], fixture->data_2[i]);
        }
    }
}

//------------------------------------------------------------------------------
//                                     FRONT
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(front, ConstWeakArrayFixture)
{
    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_1,
            fixture->data_1_size
        );
        ARC_CHECK_EQUAL(a.front(), fixture->data_1[0]);
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_2,
            fixture->data_2_size
        );
        ARC_CHECK_EQUAL(a.front(), fixture->data_2[0]);
    }
}

//------------------------------------------------------------------------------
//                                      BACK
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(back, ConstWeakArrayFixture)
{
    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_1,
            fixture->data_1_size
        );
        ARC_CHECK_EQUAL(a.back(), fixture->data_1[fixture->data_1_size - 1]);
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_2,
            fixture->data_2_size
        );
        ARC_CHECK_EQUAL(a.back(), fixture->data_2[fixture->data_2_size - 1]);
    }
}

//------------------------------------------------------------------------------
//                                    ITERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(iterator, ConstWeakArrayFixture)
{
    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->null_data,
            fixture->null_data_size
        );
        ARC_CHECK_TRUE(a.begin() == a.end());
        ARC_CHECK_FALSE(a.begin() != a.end());
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_1,
            fixture->data_1_size
        );
        ARC_CHECK_FALSE(a.begin() == a.end());
        ARC_CHECK_TRUE(a.begin() != a.end());

        arc::container::ConstWeakArray<
            ConstWeakArrayFixture::DataType
        >::iterator it;
        std::size_t counter = 0;
        for(it = a.begin(); it != a.end(); ++it)
        {
            ARC_CHECK_EQUAL(*it, fixture->data_1[counter]);
            ++counter;
        }
        ARC_CHECK_EQUAL(counter, fixture->data_1_size);
    }

    {
        arc::container::ConstWeakArray<ConstWeakArrayFixture::DataType> a
        (
            fixture->data_2,
            fixture->data_2_size
        );
        ARC_CHECK_FALSE(a.begin() == a.end());
        ARC_CHECK_TRUE(a.begin() != a.end());

        std::size_t counter = 0;
        for(auto d : a)
        {
            ARC_CHECK_EQUAL(d, fixture->data_2[counter]);
            ++counter;
        }
        ARC_CHECK_EQUAL(counter, fixture->data_2_size);
    }
}

} // namespace anonymous
