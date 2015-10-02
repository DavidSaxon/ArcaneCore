#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( base.preproc )

#include <map>
#include <stdlib.h>
#include <time.h>
#include <vector>

//------------------------------------------------------------------------------
//                                    FOREACH
//------------------------------------------------------------------------------

class ForEachFixture : chaos::test::Fixture
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
    CHAOS_FOR_EACH( vIt, v1 )
    {
        v2.push_back( *vIt );
    }
    // is the size the same?
    CHAOS_TEST_EQUAL( v1.size(), v2.size() + 2 );

    std::cout << "RUN DISALLOW COPY AND ASSIGN" << std::endl;
}
