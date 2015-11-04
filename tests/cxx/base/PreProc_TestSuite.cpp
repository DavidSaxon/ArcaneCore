#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( base.preproc )

#include <map>
#include <stdlib.h>
#include <time.h>
#include <vector>

//------------------------------------------------------------------------------
//                                    FOREACH
//------------------------------------------------------------------------------

class ForEachFixture : public chaos::test::Fixture
{
public:

    /*!
     * Override from chaos::test::Fixture
     */
    virtual void setup()
    {
        // seed random number generator
        srand( static_cast< unsigned >( time( NULL ) ) );
    }

    /*!
     * Returns a vector of the given length populated with random integers.
     */
    std::vector< chaos::int32 > getIntVector( size_t length )
    {
        std::vector< chaos::int32 > v;
        for ( size_t i = 0; i < length; ++i )
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
    size_t counter = 0;
    CHAOS_FOR_EACH( v_it_2, v1 )
    {
        ++counter;
    }
    CHAOS_CHECK_EQUAL( counter, v1.size() );

    // are the contents equal?
    for( size_t i = 0; i < v1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( v1[ i ], v2[ i ] );
    }

    // can we modify the contents
    CHAOS_FOR_EACH( v_it_3, v1 )
    {
        *v_it_3 = *v_it_3 + 1;
    }
    for( size_t i = 0; i < v1.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( v1[ i ], v2[ i ] + 1 );
    }

    // check const-ness
    size_t v1_total = 0;
    CHAOS_FOR_EACH( v_it_4, v1 )
    {
        v1_total += *v_it_4;
    }
    const std::vector< chaos::int32 > const_v1( v1 );
    size_t const_v1_total = 0;
    CHAOS_FOR_EACH( v_it_5, v1 )
    {
        const_v1_total += *v_it_5;
    }
    CHAOS_CHECK_EQUAL( v1_total, const_v1_total );
}
