#include "arcanecore/base/os/MemoryOperations.hpp"

#include <arcanecore/base/Exceptions.hpp>
#include <arcanecore/base/Preproc.hpp>

#ifdef ARC_OS_WINDOWS

    #include <windows.h>
    #include <psapi.h>

    #pragma comment(lib, "psapi.lib")

#elif defined(ARC_OS_UNIX)

    #include <unistd.h>
    #include <sys/resource.h>

#endif


namespace arc
{
namespace os
{

std::size_t get_rss()
{
    #ifdef ARC_OS_WINDOWS

        PROCESS_MEMORY_COUNTERS info;
        GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
        return static_cast<size_t>(info.WorkingSetSize);

    #elif defined(ARC_OS_UNIX)

        long rss = 0L;
        FILE* file = nullptr;
        // open the file
        if((file = fopen("/proc/self/statm", "r")) == nullptr)
        {
            throw arc::ex::IOError(
                "Failed to open \"/proc/self/statm\" to read RSS"
            );
        }
        // read from the file
        if(fscanf(file, "%*s%ld", &rss) != 1)
        {
            fclose(file);
            throw arc::ex::ParseError(
                "Failed to parse \"/proc/self/statm\" to read RSS"
            );
        }
        fclose(file);
        return
            static_cast<size_t>(rss) *
            static_cast<size_t>(sysconf( _SC_PAGESIZE));

    #elif defined(ARC_OS_MAC)

        struct mach_task_basic_info info;
        mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
        if(task_info(
                mach_task_self(),
                MACH_TASK_BASIC_INFO,
                (task_info_t) &info,
                &infoCount
            ) != KERN_SUCCESS
        )
        {
            return 0;
        }
        return static_cast<size_t>(info.resident_size);

    #else

        throw arc::test::ex::NotImplementedError(
            "get_rss has not been implemented for this platform."
        );

    #endif
}

std::size_t get_peak_rss()
{
    #ifdef ARC_OS_WINDOWS

        PROCESS_MEMORY_COUNTERS info;
        GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
        return static_cast<size_t>(info.PeakWorkingSetSize);

    #elif defined(ARC_OS_UNIX)

        struct rusage rusage;
        getrusage(RUSAGE_SELF, &rusage);
        return static_cast<size_t>(rusage.ru_maxrss * 1024L);

    #elif defined(ARC_OS_MAC)

        struct rusage rusage;
        getrusage(RUSAGE_SELF, &rusage);
        return static_cast<size_t>(rusage.ru_maxrss);

    #else

        throw arc::test::ex::NotImplementedError(
            "get_peak_rss has not been implemented for this platform."
        );

    #endif
}

} // namespace os
} // namespace arc
