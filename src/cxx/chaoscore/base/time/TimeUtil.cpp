#include "chaoscore/base/time/TimeUtil.hpp"

#include <boost/date_time/date.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace chaos
{
namespace time
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

chaos::uint64 getCurrentTime()
{
    // get epoch
    boost::posix_time::ptime epoch( boost::gregorian::date( 1970, 1, 1 ) );
    // get the time now
    boost::posix_time::ptime now(
            boost::posix_time::microsec_clock::local_time() );
    // get the difference since epoch
    boost::posix_time::time_duration diff = now - epoch;
    // return in milliseconds
    return diff.total_milliseconds();
}

} // namespace time
} // namespace chaos
