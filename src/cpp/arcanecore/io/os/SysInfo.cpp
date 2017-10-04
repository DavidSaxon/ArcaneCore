#include "arcanecore/io/os/SysInfo.hpp"

#include <arcanecore/base/Exceptions.hpp>
#include <arcanecore/base/Preproc.hpp>

#ifdef ARC_OS_WINDOWS

    #include <windows.h>
    #include <intrin.h>
    #include <psapi.h>
    #include <VersionHelpers.h>

    #pragma comment(lib, "psapi.lib")

#elif defined(ARC_OS_LINUX)

    #include <fstream>
    #include <sched.h>
    #include <unistd.h>
    #include <sys/resource.h>
    #include "sys/sysinfo.h"
    #include "sys/types.h"

#endif


namespace arc
{
namespace io
{
namespace os
{

//------------------------------------------------------------------------------
//                                    GLOBALS
//------------------------------------------------------------------------------

// stores infomation about the CPU
static arc::str::UTF8String g_cpu_vendor;
static arc::str::UTF8String g_cpu_model;
static std::size_t g_cpu_phyiscal_cores     = 0;
static std::size_t g_cpu_logical_processors = 0;
static float g_cpu_clock_rate = 0.0F;

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

const arc::str::UTF8String& get_os_name()
{
    #ifdef ARC_OS_WINDOWS

        static arc::str::UTF8String os_name("Windows");

    #elif defined(ARC_OS_LINUX)

        static arc::str::UTF8String os_name("Linux");

    #elif defined(ARC_OS_MAC)

        static arc::str::UTF8String os_name("Mac");

    #elif defined(ARC_OS_UNIX)

        static arc::str::UTF8String os_name("UNKNOWN-UNIX");

    #else

        static arc::str::UTF8String os_name("UNKNOWN");

    #endif

    return os_name;
}

const arc::str::UTF8String& get_distro_name()
{
    static arc::str::UTF8String distro_name;
    if(distro_name.is_empty())
    {
        #ifdef ARC_OS_WINDOWS

            arc::str::UTF8String windows_type = "Client";
            if(IsWindowsServer())
            {
                windows_type = "Server";
            }
            windows_type = "Windows " + windows_type;

            typedef LONG NTSTATUS, *PNTSTATUS;
            typedef NTSTATUS (WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

            HMODULE hMod = GetModuleHandleW(L"ntdll.dll");
            if(hMod)
            {
                RtlGetVersionPtr fx_ptr =
                    (RtlGetVersionPtr) GetProcAddress(hMod, "RtlGetVersion");
                if(fx_ptr != nullptr)
                {
                    RTL_OSVERSIONINFOW rovi = {0};
                    rovi.dwOSVersionInfoSize = sizeof(rovi);
                    if(fx_ptr(&rovi) == 0)
                    {
                        distro_name
                            << rovi.dwMajorVersion << "."
                            << rovi.dwMinorVersion;
                    }
                }
            }

            distro_name = windows_type + " " + distro_name;

        #elif defined(ARC_OS_LINUX)

            std::ifstream distro_file("/etc/lsb-release");
            if(!distro_file.good())
            {
                throw arc::ex::IOError(
                    "Failed to open system file \"/etc/lsb-release\""
                );
            }

            arc::str::UTF8String distro_id("UNKNOWN");
            arc::str::UTF8String distro_id_key("DISTRIB_ID=");
            arc::str::UTF8String distro_version;
            arc::str::UTF8String distro_version_key("DISTRIB_RELEASE=");

            std::string line;
            while (std::getline(distro_file, line))
            {
                // TODO: this is not that efficient
                arc::str::UTF8String u_line(line.c_str(), line.length());

                if(u_line.starts_with(distro_id_key))
                {
                    distro_id = u_line.substring(
                        distro_id_key.get_length(),
                        u_line.get_length()
                    );
                }
                else if(u_line.starts_with(distro_version_key))
                {
                    distro_version = u_line.substring(
                        distro_version_key.get_length(),
                        u_line.get_length()
                    );
                }
            }

            distro_name = distro_id + "-" + distro_version;
        #else

            throw arc::ex::NotImplementedError(
                "get_distro_name has not been implemented for this platform."
            );

        #endif
    }
    return distro_name;

}

// discovers and stores information about this system's CPU - but only does this
// once.
static void discover_cpu_info()
{
    static bool discovery_done = false;
    if(discovery_done)
    {
        return;
    }

    #ifdef ARC_OS_WINDOWS

        // get vendor
        //----------------------------------------------------------------------
        arc::int32 vendor_regs[4] = {0};
        char c_vendor[13];
        __cpuid(vendor_regs, 0);
        memcpy(c_vendor + 0, &vendor_regs[1], 4);
        memcpy(c_vendor + 4, &vendor_regs[3], 4);
        memcpy(c_vendor + 8, &vendor_regs[2], 4);
        c_vendor[12] = '\0';
        g_cpu_vendor = c_vendor;

        // get model
        //----------------------------------------------------------------------
        arc::int32 model_regs[4] = {0};
        char c_model[64];
        __cpuid(model_regs, 0x80000000);

        arc::uint32 n = model_regs[0];
        for(arc::uint32 i = 0x80000000; i  < n; ++i)
        {
            __cpuid(model_regs, i);
            if(i == 0x80000002)
            {
                memcpy(c_model, model_regs, sizeof(model_regs));
            }
            else if(i == 0x80000003)
            {
                memcpy(c_model + 16, model_regs, sizeof(model_regs));
            }
            else if(i == 0x80000004)
            {
                memcpy(c_model + 32, model_regs, sizeof(model_regs));
            }
        }
        g_cpu_model = c_model;

        // get number of physical cores
        //----------------------------------------------------------------------
        typedef BOOL (WINAPI *LPFN_GLPI)(
                PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
                PDWORD
        );

        LPFN_GLPI glpi = (LPFN_GLPI) GetProcAddress(
            GetModuleHandle(TEXT("kernel32")),
            "GetLogicalProcessorInformation"
        );
        if(glpi != nullptr)
        {
            PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = nullptr;
            DWORD return_length = 0;
            bool done = false;
            bool failure = false;
            while(!done)
            {
                DWORD rc = glpi(buffer, &return_length);

                if(rc == FALSE)
                {
                    if(GetLastError() == ERROR_INSUFFICIENT_BUFFER)
                    {
                        if(buffer != nullptr)
                        {
                            free(buffer);
                        }

                        buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)
                            malloc(return_length);
                        if(buffer == nullptr)
                        {
                            failure = true;
                            break;
                        }
                    }
                    else
                    {
                        failure = true;
                        break;
                    }
                }
                else
                {
                    done = true;
                }
            }

            PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = buffer;
            DWORD byte_offset = 0;
            while(sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) + byte_offset <=
                    return_length &&
                !failure)
            {
                if(ptr->Relationship == RelationProcessorCore)
                {
                    ++g_cpu_phyiscal_cores;
                }

                byte_offset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
                ++ptr;
            }
        }

        // get number of logical processors
        //----------------------------------------------------------------------
        SYSTEM_INFO sysinfo;
        GetSystemInfo(&sysinfo);
        g_cpu_logical_processors = sysinfo.dwNumberOfProcessors;

        // get clock rate
        //----------------------------------------------------------------------
        HKEY h_key;
        long l_error = RegOpenKeyEx(
            HKEY_LOCAL_MACHINE,
            "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
            0,
            KEY_READ,
            &h_key
        );
        if(l_error == ERROR_SUCCESS)
        {
            DWORD dw_mhz = _MAX_PATH;
            DWORD buffer_size = _MAX_PATH;
            RegQueryValueEx(
                h_key,
                "~MHz",
                nullptr,
                nullptr,
                (LPBYTE) &dw_mhz,
                &buffer_size
            );
            g_cpu_clock_rate = static_cast<float>(dw_mhz);
        }

    #elif defined(ARC_OS_LINUX)

        // use ifsteam since this is special system file
        std::ifstream info_file("/proc/cpuinfo");
        if(!info_file.good())
        {
            throw arc::ex::IOError(
                "Failed to open system file \"/proc/cpuinfo\""
            );
        }

        // various keys within the file
        arc::str::UTF8String vendor_key("vendor_id\t: ");
        arc::str::UTF8String model_key("model name\t: ");
        arc::str::UTF8String physical_cores_key("cpu cores\t: ");
        arc::str::UTF8String logical_processors_key("processor\t: ");
        arc::str::UTF8String clock_rate_key("cpu MHz\t\t: ");


        std::string line;
        while (std::getline(info_file, line))
        {
            // TODO: this is not that efficient
            arc::str::UTF8String u_line(line.c_str(), line.length());

            if(g_cpu_vendor.is_empty() && u_line.starts_with(vendor_key))
            {
                g_cpu_vendor = u_line.substring(
                    vendor_key.get_length(),
                    u_line.get_length()
                );
            }
            if(g_cpu_model.is_empty() && u_line.starts_with(model_key))
            {
                g_cpu_model = u_line.substring(
                    model_key.get_length(),
                    u_line.get_length()
                );
            }
            else if(g_cpu_phyiscal_cores == 0 &&
                    u_line.starts_with(physical_cores_key))
            {
                g_cpu_phyiscal_cores = u_line.substring(
                    physical_cores_key.get_length(),
                    u_line.get_length()
                ).to_uint32();
            }
            else if(u_line.starts_with(logical_processors_key))
            {
                ++g_cpu_logical_processors;
            }
            else if(g_cpu_clock_rate <= 0.001F &&
                    u_line.starts_with(clock_rate_key))
            {
                g_cpu_clock_rate = u_line.substring(
                    clock_rate_key.get_length(),
                    u_line.get_length()
                ).to_float();
            }
        }

    #else

        throw arc::ex::NotImplementedError(
            "discover_cpu_info has not been implemented for this platform."
        );

    #endif

    discovery_done = true;
}

const arc::str::UTF8String& get_cpu_vendor()
{
    discover_cpu_info();

    return g_cpu_vendor;
}

const arc::str::UTF8String& get_cpu_model()
{
    discover_cpu_info();

    return g_cpu_model;
}

std::size_t get_cpu_physical_cores()
{
    discover_cpu_info();

    return g_cpu_phyiscal_cores;
}

std::size_t get_cpu_logical_processors()
{
    discover_cpu_info();

    return g_cpu_logical_processors;
}

float get_cpu_clock_rate()
{
    discover_cpu_info();

    return g_cpu_clock_rate;
}

std::size_t get_thread_processor()
{
    #ifdef ARC_OS_WINDOWS

        return static_cast<std::size_t>(GetCurrentProcessorNumber());

    #elif defined(ARC_OS_LINUX)

        return static_cast<std::size_t>(sched_getcpu());

    #else

        throw arc::ex::NotImplementedError(
            "get_thread_processor has not been implemented for this platform."
        );

    #endif
}

std::size_t get_total_ram()
{
    #ifdef ARC_OS_WINDOWS

    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx (&statex);
    return static_cast<std::size_t>(statex.ullTotalPhys);

    #elif defined(ARC_OS_LINUX)

        struct sysinfo mem_info;
        sysinfo(&mem_info);
        return static_cast<std::size_t>(mem_info.totalram);

    #else

        throw arc::ex::NotImplementedError(
            "get_total_ram has not been implemented for this platform."
        );

    #endif
}

std::size_t get_free_ram()
{
    #ifdef ARC_OS_WINDOWS

        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx (&statex);
        return static_cast<std::size_t>(statex.ullAvailPhys);

    #elif defined(ARC_OS_LINUX)

        struct sysinfo mem_info;
        sysinfo(&mem_info);
        return static_cast<std::size_t>(mem_info.freeram);

    #else

        throw arc::ex::NotImplementedError(
            "get_free_ram has not been implemented for this platform."
        );

    #endif
}

std::size_t get_total_virtual_memory()
{
    #ifdef ARC_OS_WINDOWS

        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx (&statex);
        return static_cast<std::size_t>(statex.ullTotalVirtual);

    #elif defined(ARC_OS_LINUX)

        struct sysinfo mem_info;
        sysinfo(&mem_info);
        return static_cast<std::size_t>(mem_info.totalswap);

    #else

        throw arc::ex::NotImplementedError(
            "get_total_virtual_memory has not been implemented for this "
            "platform."
        );

    #endif
}

std::size_t get_free_virtual_memory()
{
    #ifdef ARC_OS_WINDOWS

        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx (&statex);
        return static_cast<std::size_t>(statex.ullAvailVirtual);

    #elif defined(ARC_OS_LINUX)

        struct sysinfo mem_info;
        sysinfo(&mem_info);
        return static_cast<std::size_t>(mem_info.freeswap);

    #else

        throw arc::ex::NotImplementedError(
            "get_free_virtual_memory has not been implemented for this "
            "platform."
        );

    #endif
}

std::size_t get_rss()
{
    #ifdef ARC_OS_WINDOWS

        PROCESS_MEMORY_COUNTERS info;
        GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
        return static_cast<size_t>(info.WorkingSetSize);

    #elif defined(ARC_OS_LINUX)

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

        throw arc::ex::NotImplementedError(
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

    #elif defined(ARC_OS_LINUX)

        struct rusage rusage;
        getrusage(RUSAGE_SELF, &rusage);
        return static_cast<size_t>(rusage.ru_maxrss * 1024L);

    #elif defined(ARC_OS_MAC)

        struct rusage rusage;
        getrusage(RUSAGE_SELF, &rusage);
        return static_cast<size_t>(rusage.ru_maxrss);

    #else

        throw arc::ex::NotImplementedError(
            "get_peak_rss has not been implemented for this platform."
        );

    #endif
}

} // namespace os
} // namespace io
} // namespace arc
