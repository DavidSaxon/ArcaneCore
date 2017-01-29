#include "arcanecore/io/sys/Path.hpp"

#include <cstddef>
#include <cstring>

#include "arcanecore/base/Exceptions.hpp"
#include "arcanecore/base/str/StringOperations.hpp"

#ifdef ARC_OS_UNIX

    #include <limits.h>
    #include <unistd.h>

#elif defined(ARC_OS_WINDOWS)

    #include <windows.h>

#endif

namespace arc
{
namespace io
{
namespace sys
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

Path::Path()
{
}

Path::Path(const std::vector<arc::str::UTF8String>& components)
    :
    m_components(components)
{
}

Path::Path(
        const std::vector<arc::str::UTF8String>::const_iterator& begin,
        const std::vector<arc::str::UTF8String>::const_iterator& end)
    :
    m_components(begin, end)
{
}

Path::Path(const arc::str::UTF8String& string_path)
{
    // split the path into components based on the operating system
#ifdef ARC_OS_UNIX

    arc::str::UTF8String santised_path(string_path);
    static const arc::str::UTF8String UNIX_SEP("/");
    santised_path.remove_duplicates(UNIX_SEP);
    m_components = santised_path.split(UNIX_SEP);

    if(m_components.size() > 0 && m_components[0] == "")
    {
        m_components[0] = "/";
    }

#elif defined(ARC_OS_WINDOWS)

    arc::str::UTF8String santised_path(string_path);
    const arc::str::UTF8String WINDOWS_SEP("\\");
    santised_path.remove_duplicates(WINDOWS_SEP);
    m_components = santised_path.split(WINDOWS_SEP);

#endif

    // remove final space if the path ended with /
    if(m_components.size() > 0 && m_components.back() == "")
    {
        m_components = std::vector<arc::str::UTF8String>(
            m_components.begin(), m_components.end() - 1);
    }
}

Path::Path(const Path& other)
    :
    m_components(other.m_components)
{
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

Path::~Path()
{
}

//------------------------------------------------------------------------------
//                            PUBLIC STATIC FUNCTIONS
//------------------------------------------------------------------------------

Path Path::from_unix_string(const arc::str::UTF8String& string_path)
{
    arc::str::UTF8String santised_path(string_path);
    static const arc::str::UTF8String UNIX_SEP("/");
    santised_path.remove_duplicates(UNIX_SEP);
    std::vector<arc::str::UTF8String> components =
        santised_path.split(UNIX_SEP);

    // start the path with / if the split returned a space
    if(components.size() > 0 && components[0] == "")
    {
        components[0] = "/";
    }

    // remove final space if the path ended with /
    if(components.size() > 0 && components.back() == "")
    {
        components = std::vector<arc::str::UTF8String>(
            components.begin(), components.end() - 1);
    }

    return Path(components);
}

Path Path::from_windows_string(const arc::str::UTF8String& string_path)
{
    arc::str::UTF8String santised_path(string_path);
    const arc::str::UTF8String WINDOWS_SEP("\\");
    santised_path.remove_duplicates(WINDOWS_SEP);
     std::vector<arc::str::UTF8String> components =
        santised_path.split(WINDOWS_SEP);

    // remove final space if the path ended with /
    if(components.size() > 0 && components.back() == "")
    {
        components = std::vector<arc::str::UTF8String>(
            components.begin(), components.end() - 1);
    }

    return Path(components);
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

const Path& Path::operator=(const Path& other)
{
    m_components = other.m_components;
    return *this;
}

bool Path::operator==(const Path& other) const
{
    // check length first
    if(m_components.size() != other.m_components.size())
    {
        return false;
    }

    // check each component
    for(std::size_t i = 0; i < m_components.size(); ++i)
    {
        if(m_components[i] != other.m_components [i])
        {
            return false;
        }
    }

    return true;
}

bool Path::operator!=(const Path& other) const
{
    return !((*this) == other);
}

bool Path::operator<(const Path& other) const
{
    // do the paths have the same length?
    if(m_components.size() == other.m_components.size())
    {
        // perform check on each component
        for(std::size_t i = 0; i < m_components.size(); ++i)
        {
            if(m_components[i] != other.m_components[i])
            {
                return m_components[i] < other.m_components[i];
            }
        }
        return false;
    }

    // compare based on length
    return m_components.size() < other.m_components.size();
}

arc::str::UTF8String& Path::operator[](std::size_t index)
{
    return m_components[index];
}

const arc::str::UTF8String& Path::operator[](std::size_t index) const
{
    return m_components[index];
}

Path Path::operator+(const Path& other) const
{
    // create a new path which is a copy of this path
    Path copy(*this);
    // now use compound operator
    return copy += other;
}

Path& Path::operator+=(const Path& other)
{
    // extend with other path's components
    ARC_FOR_EACH(it, other.m_components)
    {
        m_components.push_back(*it);
    }

    return *this;
}

Path& Path::operator<<(const arc::str::UTF8String& component)
{
    return join(component);
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

Path& Path::join(const arc::str::UTF8String& component)
{
    m_components.push_back(component);
    return *this;
}

void Path::insert(std::size_t index, const arc::str::UTF8String& component)
{
    // check bounds
    if(index > m_components.size())
    {
        arc::str::UTF8String error_message;
        error_message << "Provided index: " << index << " is greater than the "
                      << "number of components in the path: "
                      << m_components.size();
        throw arc::ex::IndexOutOfBoundsError(error_message);
    }

    // new vector to contain components
    std::vector<arc::str::UTF8String> components;
    // copy with the insert
    for(std::size_t i = 0; i <= m_components.size(); ++i)
    {
        if(i < index)
        {
            components.push_back(m_components[i]);
        }
        else if(i > index)
        {
            components.push_back(m_components[i - 1]);
        }
        else
        {
            components.push_back(component);
        }
    }
    // replace the current list of components
    m_components = components;
}

void Path::clear()
{
    m_components.clear();
}

void Path::remove(std::size_t index)
{
    // check bounds
    if(index >= m_components.size())
    {
        arc::str::UTF8String error_message;
        error_message << "Provided index: " << index << " is greater or equal "
                      << "to the number of components in the path: "
                      << m_components.size();
        throw arc::ex::IndexOutOfBoundsError(error_message);
    }

    // new vector to contain components
    std::vector<arc::str::UTF8String> components;
    // copy with the remove
    for(std::size_t i = 0; i < m_components.size(); ++i)
    {
        if(i < index)
        {
            components.push_back(m_components[i]);
        }
        else if(i > index)
        {
            components.push_back(m_components[i]);
        }
    }
    // replace the current list of components
    m_components = components;
}

arc::str::UTF8String Path::to_native() const
{
#ifdef ARC_OS_UNIX

    return to_unix();

#elif defined(ARC_OS_WINDOWS)

    return to_windows();

#endif
}

arc::str::UTF8String Path::to_unix() const
{
    std::vector<arc::str::UTF8String> components;
    // special case for root (/)
    bool is_root = false;
    if(m_components.size() > 0 && m_components[0] == "/" )
    {
        is_root = true;
        components = std::vector<arc::str::UTF8String>(
                m_components.begin() + 1, m_components.end());
    }
    else
    {
        components = m_components;
    }

    arc::str::UTF8String ret = arc::str::join(components, "/");
    if(is_root)
    {
        ret = arc::str::UTF8String("/") + ret;
    }

    return ret;
}

arc::str::UTF8String Path::to_windows() const
{
    return arc::str::join(m_components, "\\");
}

Path Path::to_absolute() const
{
    // TODO: resolve . and ..

#ifdef ARC_OS_UNIX

    // if the path is already from root just return a copy of it
    if(!is_empty() && get_front() == "/")
    {
        return Path(*this);
    }

    // otherwise get the current working directory and prepend it to this path
    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);
    // create a new path and append
    Path abs_path(cwd);
    abs_path += *this;
    return abs_path;

#elif defined(ARC_OS_WINDOWS)

    // get the path as utf-16
    std::size_t length = 0;
    const char* p = arc::str::utf8_to_utf16(
            to_windows(),
            length,
            arc::data::ENDIAN_LITTLE
    );

    wchar_t full_path[MAX_PATH];
    GetFullPathNameW((const wchar_t*) p, MAX_PATH, full_path, NULL);

    // convert back to utf-8
    arc::str::UTF8String utf8_fullpath(
        arc::str::utf16_to_utf8(
            (const char*) full_path,
            arc::str::npos
        )
    );

    return Path(utf8_fullpath);

#else

    throw arc::test::ex::NotImplementedError(
            "Path::to_absolute() is not yet supported for the current platform"
    );

#endif
}

//----------------------------------ACCESSORS-----------------------------------

std::size_t Path::get_length() const
{
    return m_components.size();
}

bool Path::is_empty() const
{
    return get_length() == 0;
}

const std::vector<arc::str::UTF8String>& Path::get_components() const
{
    return m_components;
}

const arc::str::UTF8String& Path::get_front() const
{
    // is the path empty?
    if(is_empty())
    {
        throw arc::ex::IndexOutOfBoundsError(
                "Cannot get the front component of an empty path."
        );
    }

    return m_components.front();
}

const arc::str::UTF8String& Path::get_back() const
{
    // is the path empty?
    if(is_empty())
    {
        throw arc::ex::IndexOutOfBoundsError(
                "Cannot get the back component of an empty path."
        );
    }

    return m_components.back();
}

arc::str::UTF8String Path::get_extension() const
{
    // is there a final component?
    if(!m_components.empty())
    {
        // does the final component contain a period?
        std::size_t loc = m_components.back().find_last(".");
        if(loc != arc::str::npos)
        {
            // return the extension substring
            return m_components.back().substring(
                    loc + 1,
                    m_components.back().get_length()
            );
        }
    }
    // there is no extension, return an empty string
    return "";
}

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

arc::str::UTF8String& operator<<(arc::str::UTF8String& s, const Path& p)
{
    s << p.to_native();
    return s;
}

std::ostream& operator<<(std::ostream& stream, const Path& p)
{
    stream << p.to_native();
    return stream;
}

} // namespace sys
} // namespace io
} // namespace arc
