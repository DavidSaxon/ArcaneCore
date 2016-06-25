#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( base.preproc )

#include <map>
#include <stdlib.h>
#include <time.h>
#include <vector>

namespace
{

//------------------------------------------------------------------------------
//                                    FOR EACH
//------------------------------------------------------------------------------

class ForEachFixture : public chaos::test::Fixture
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
    std::vector< chaos::int32 > getIntVector( std::size_t length )
    {
        std::vector< chaos::int32 > v;
        for ( std::size_t i = 0; i < length; ++i )
        {
            v.push_back( ( rand() % 200 ) - 50 );
        }

        return v;
    }
};

CHAOS_TEST_UNIT_FIXTURE( for_each, ForEachFixture )
{
    // test on a vector
    std::vector< chaos::int32 > v1 = fixture->getIntVector( 100 );
    std::vector< chaos::int32 > v2;
    // copy using a for each loop
    CHAOS_FOR_EACH( v_it_1, v1 )
    {
        v2.push_back( *v_it_1 );
    }
    CHAOS_TEST_MESSAGE( "Checking for each assigned size" );
    CHAOS_CHECK_EQUAL( v1.size(), v2.size() );

    CHAOS_TEST_MESSAGE( "Checking each value is iterated" );
    std::size_t counter = 0;
    CHAOS_FOR_EACH( v_it_2, v1 )
    {
        ++counter;
    }
    CHAOS_CHECK_EQUAL( counter, v1.size() );

    CHAOS_TEST_MESSAGE( "Checking correct for each assigned contents" );
    for( std::size_t i = 0; i < v1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( v1[ i ], v2[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking for each value modifications" );
    CHAOS_FOR_EACH( v_it_3, v1 )
    {
        *v_it_3 = *v_it_3 + 1;
    }
    for( std::size_t i = 0; i < v1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( v1[ i ], v2[ i ] + 1 );
    }

    CHAOS_TEST_MESSAGE( "Checking const-ness" );
    std::size_t v1_total = 0;
    CHAOS_FOR_EACH( v_it_4, v1 )
    {
        v1_total += *v_it_4;
    }
    const std::vector< chaos::int32 > const_v1( v1 );
    std::size_t const_v1_total = 0;
    CHAOS_FOR_EACH( v_it_5, v1 )
    {
        const_v1_total += *v_it_5;
    }
    CHAOS_CHECK_EQUAL( v1_total, const_v1_total );
}

//------------------------------------------------------------------------------
//                                 CONST FOR EACH
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE(const_for_each, ForEachFixture)
{
    // test on a vector
    const std::vector< chaos::int32 > v1(fixture->getIntVector(100));
    std::vector< chaos::int32 > v2;
    // copy using a for each loop
    CHAOS_CONST_FOR_EACH(v_it_1, v1)
    {
        v2.push_back(*v_it_1);
    }
    CHAOS_TEST_MESSAGE("Checking for each assigned size");
    CHAOS_CHECK_EQUAL(v1.size(), v2.size());

    CHAOS_TEST_MESSAGE("Checking each value is iterated");
    std::size_t counter = 0;
    CHAOS_CONST_FOR_EACH(v_it_2, v1)
    {
        ++counter;
    }
    CHAOS_CHECK_EQUAL(counter, v1.size());

    CHAOS_TEST_MESSAGE( "Checking correct for each assigned contents" );
    for(std::size_t i = 0; i < v1.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(v1[i], v2[i]);
    }
}

} // namespace anonymous
