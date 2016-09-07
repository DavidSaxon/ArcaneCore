#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(base.Preproc)

#include <map>
#include <stdlib.h>
#include <time.h>
#include <vector>

namespace
{

//------------------------------------------------------------------------------
//                                    FOR EACH
//------------------------------------------------------------------------------

class ForEachFixture : public arc::test::Fixture
{
public:

    virtual void setup()
    {
        // seed random number generator
        srand( static_cast< unsigned >( time( NULL ) ) );
    }

    /*!
     * Returns a vector of the given length populated with random integers.
     */
    std::vector< arc::int32 > getIntVector( std::size_t length )
    {
        std::vector< arc::int32 > v;
        for ( std::size_t i = 0; i < length; ++i )
        {
            v.push_back( ( rand() % 200 ) - 50 );
        }

        return v;
    }
};

// ARC_TEST_UNIT_FIXTURE(for_each, ForEachFixture)

namespace
{
struct for_each : public arc::test::internal::UnitTest
{
    ForEachFixture* fixture;

    for_each()
        :
        UnitTest("for_each"),
        fixture (nullptr)
    {
    }

    virtual ~for_each()
    {
        delete fixture;

    }
    virtual arc::test::Fixture* get_fixture()
    {
        if(fixture == nullptr)
        {
            fixture = new ForEachFixture();
        }
        return fixture;
    }

    virtual void execute();
};

static arc::test::internal::TestCore object_for_each(
        "for_each", new for_each(), __FILE__, __LINE__);

} // namespace anonymous


void for_each::execute()
{
    // test on a vector
    std::vector< arc::int32 > v1 = fixture->getIntVector( 100 );
    std::vector< arc::int32 > v2;
    // copy using a for each loop
    ARC_FOR_EACH( v_it_1, v1 )
    {
        v2.push_back( *v_it_1 );
    }
    ARC_TEST_MESSAGE( "Checking for each assigned size" );
    ARC_CHECK_EQUAL( v1.size(), v2.size() );

    ARC_TEST_MESSAGE( "Checking each value is iterated" );
    std::size_t counter = 0;
    ARC_FOR_EACH( v_it_2, v1 )
    {
        ++counter;
    }
    ARC_CHECK_EQUAL( counter, v1.size() );

    ARC_TEST_MESSAGE( "Checking correct for each assigned contents" );
    for( std::size_t i = 0; i < v1.size(); ++i )
    {
        ARC_CHECK_EQUAL( v1[ i ], v2[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking for each value modifications" );
    ARC_FOR_EACH( v_it_3, v1 )
    {
        *v_it_3 = *v_it_3 + 1;
    }
    for( std::size_t i = 0; i < v1.size(); ++i )
    {
        ARC_CHECK_EQUAL( v1[ i ], v2[ i ] + 1 );
    }

    ARC_TEST_MESSAGE( "Checking const-ness" );
    std::size_t v1_total = 0;
    ARC_FOR_EACH( v_it_4, v1 )
    {
        v1_total += *v_it_4;
    }
    const std::vector< arc::int32 > const_v1( v1 );
    std::size_t const_v1_total = 0;
    ARC_FOR_EACH( v_it_5, v1 )
    {
        const_v1_total += *v_it_5;
    }
    ARC_CHECK_EQUAL( v1_total, const_v1_total );
}

//------------------------------------------------------------------------------
//                                 CONST FOR EACH
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(const_for_each, ForEachFixture)
{
    // test on a vector
    const std::vector< arc::int32 > v1(fixture->getIntVector(100));
    std::vector< arc::int32 > v2;
    // copy using a for each loop
    ARC_CONST_FOR_EACH(v_it_1, v1)
    {
        v2.push_back(*v_it_1);
    }
    ARC_TEST_MESSAGE("Checking for each assigned size");
    ARC_CHECK_EQUAL(v1.size(), v2.size());

    ARC_TEST_MESSAGE("Checking each value is iterated");
    std::size_t counter = 0;
    ARC_CONST_FOR_EACH(v_it_2, v1)
    {
        ++counter;
    }
    ARC_CHECK_EQUAL(counter, v1.size());

    ARC_TEST_MESSAGE( "Checking correct for each assigned contents" );
    for(std::size_t i = 0; i < v1.size(); ++i)
    {
        ARC_CHECK_EQUAL(v1[i], v2[i]);
    }
}

} // namespace anonymous
