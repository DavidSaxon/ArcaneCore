#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(io.os.SysInfo)

#include <arcanecore/io/os/SysInfo.hpp>


namespace
{

ARC_TEST_UNIT(get_os_name)
{
    // can't actually test but just make sure we get something back...
    ARC_CHECK_NOT_EQUAL(arc::io::os::get_os_name(), "");
}

ARC_TEST_UNIT(get_distro_name)
{
    // can't actually test but just make sure we get something back...
    ARC_CHECK_NOT_EQUAL(arc::io::os::get_distro_name(), "");
}

ARC_TEST_UNIT(get_cpu_vendor)
{
    // can't actually test but just make sure we get something back...
    ARC_CHECK_NOT_EQUAL(arc::io::os::get_cpu_vendor(), "");
}

ARC_TEST_UNIT(get_cpu_model)
{
    // can't actually test but just make sure we get something back...
    ARC_CHECK_NOT_EQUAL(arc::io::os::get_cpu_model(), "");
}

ARC_TEST_UNIT(get_cpu_physical_cores)
{
    // can't actually test but just make sure we get something back...
    ARC_CHECK_NOT_EQUAL(arc::io::os::get_cpu_physical_cores(), 0);
}

ARC_TEST_UNIT(get_cpu_logical_processors)
{
    // can't actually test but just make sure we get something back...
    ARC_CHECK_NOT_EQUAL(arc::io::os::get_cpu_logical_processors(), 0);
}

ARC_TEST_UNIT(get_cpu_clock_rate)
{
    // can't actually test but just make sure we get something back...
    ARC_CHECK_NOT_EQUAL(arc::io::os::get_cpu_clock_rate(), 0.0F);
}

ARC_TEST_UNIT(get_thread_processor)
{
    // can't actually test but just make sure we get something back...
    ARC_CHECK_NOT_EQUAL(arc::io::os::get_thread_processor(), 894358439);
}

ARC_TEST_UNIT(get_total_ram)
{
    // can't actually test but just make sure we get something back...
    ARC_CHECK_NOT_EQUAL(arc::io::os::get_total_ram(), 0);
}

ARC_TEST_UNIT(get_free_ram)
{
    // can't actually test but just make sure we get something back...
    ARC_CHECK_NOT_EQUAL(arc::io::os::get_free_ram(), 0);
}

ARC_TEST_UNIT(get_total_virtual_memory)
{
    // can't actually test but just make sure we get something back...
    ARC_CHECK_NOT_EQUAL(arc::io::os::get_total_virtual_memory(), 0);
}

ARC_TEST_UNIT(get_free_virtual_memory)
{
    // can't actually test but just make sure we get something back...
    ARC_CHECK_NOT_EQUAL(arc::io::os::get_free_virtual_memory(), 0);
}

} // namespace anonymous
