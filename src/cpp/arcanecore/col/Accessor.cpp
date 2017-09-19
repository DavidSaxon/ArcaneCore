#include "arcanecore/col/Accessor.hpp"

#include <arcanecore/base/Exceptions.hpp>
#include <arcanecore/base/str/StringOperations.hpp>
#include <arcanecore/io/sys/FileReader.hpp>
#include <arcanecore/io/sys/FileSystemOperations.hpp>

#include <arcanecore/log/Input.hpp>
#include <arcanecore/log/LogHandler.hpp>

namespace arc
{
namespace col
{

//------------------------------------------------------------------------------
//                            PUBLIC STATIC ATTRIBUTES
//------------------------------------------------------------------------------

bool Accessor::force_real_resources = false;
std::unique_ptr<arc::log::Input> Accessor::logger;

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

Accessor::Accessor(const arc::io::sys::Path& table_of_contents)
    :
    m_table_of_contents(table_of_contents)
{
    reload();
}

Accessor::Accessor(const Accessor& other)
    :
    m_table_of_contents(other.m_table_of_contents),
    m_resources        (other.m_resources)
{
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

Accessor::~Accessor()
{
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

Accessor& Accessor::operator=(const Accessor& other)
{
    m_table_of_contents = other.m_table_of_contents;
    m_resources = other.m_resources;

    return *this;
}

//------------------------------------------------------------------------------
//                            PUBLIC STATIC FUNCTIONS
//------------------------------------------------------------------------------

void Accessor::set_logging(
        arc::log::LogHandler* handler,
        const arc::str::UTF8String& profile_name)
{
    // ensure the handler is not null
    if(handler == nullptr)
    {
        throw arc::ex::ValueError(
            "arc::log::LogHandler parameter cannot be null.");
    }

    // vent the input
    logger.reset(handler->vend_input(arc::log::Profile(profile_name)));
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Accessor::reload()
{
    // clear the current resources
    m_resources.clear();

    // should we actually load?
    if(force_real_resources)
    {
        return;
    }

    // open the table of contents
    arc::io::sys::FileReader reader(
        m_table_of_contents,
        arc::io::sys::FileHandle::ENCODING_UTF8,
        arc::io::sys::FileHandle::NEWLINE_UNIX
    );

    // optimisation structure
    static arc::str::UTF8String::Opt known_utf8(
        arc::str::UTF8String::Opt::SKIP_VALID_CHECK);

    // read each line of the file
    while(!reader.eof())
    {
        arc::str::UTF8String line;
        reader.read_line(line);

        // skip any empty lines
        if(line.is_empty())
        {
            continue;
        }

        // split the line by commas
        std::vector<arc::str::UTF8String> line_elements(line.split(","));
        // check that there are the correct number of components
        if(line_elements.size() != 5)
        {
            // warn if logging is enabled
            if(logger)
            {
                logger->warning << "Failed to parse resource line due to "
                                << "invalid when reading from table of "
                                << "contents at \"" << m_table_of_contents
                                << "\": \"" << line << "\"." << std::endl;
            }
            continue;
        }

        // get the resource path
        arc::io::sys::Path resource =
            arc::io::sys::Path::from_unix_string(line_elements[0]);

        // create a new resource location to load the entry into
        ResourceLocation location;
        location.base_path =
            arc::io::sys::Path::from_unix_string(line_elements[1]);
        // get and check page index is valid
        if(!line_elements[2].is_uint())
        {
            // warn if logging is enabled
            if(logger)
            {
                logger->warning << "Failed to parse resource line because the "
                                << "page index \"" << line_elements[2] << "\" "
                                << "is not a valid unsigned integral, when "
                                << "reading from table of contents at \""
                                << m_table_of_contents << "\": \"" << line
                                << "\"." << std::endl;
            }
            continue;
        }
        location.page_index = line_elements[2].to_uint32();
        // get and check offset is valid
        if(!line_elements[3].is_int())
        {
            // warn if logging is enabled
            if(logger)
            {
                logger->warning << "Failed to parse resource line because the "
                                << "offset \"" << line_elements[3] << "\" is "
                                << "not a valid integral, when reading from "
                                << "table of contents at \""
                                << m_table_of_contents << "\": \"" << line
                                << "\"." << std::endl;
            }
            continue;
        }
        location.offset = line_elements[3].to_int64();
        // get and check size is valid
        if(!line_elements[4].is_int())
        {
            // warn if logging is enabled
            if(logger)
            {
                logger->warning << "Failed to parse resource line because the "
                                << "size \"" << line_elements[4] << "\" is not "
                                << "a valid integral, when reading from table "
                                << "of contents at \"" << m_table_of_contents
                                << "\": \"" << line << "\"." << std::endl;
            }
            continue;
        }
        location.size = line_elements[4].to_int64();

        // warn if the are multiple entries
        if(m_resources.find(resource) != m_resources.end() && logger)
        {
            logger->warning << "Multiple entries for resource \"" << resource
                           << "\" in table of contents at \""
                           << m_table_of_contents << "\". The last most entry "
                           << "for this resource will be used." << std::endl;
        }

        // finally add the resource to the internal mapping
        m_resources[resource] = location;
    }
}

const arc::io::sys::Path& Accessor::get_table_of_contents_path() const
{
    return m_table_of_contents;
}

void Accessor::set_table_of_contents_path(const arc::io::sys::Path& path)
{
    m_table_of_contents = path;
    reload();
}

bool Accessor::has_resource(const arc::io::sys::Path& resource_path) const
{
    return m_resources.find(resource_path) != m_resources.end();
}

void Accessor::get_resource(
        const arc::io::sys::Path& resource_path,
        arc::io::sys::Path& base_path,
        std::size_t& page_index,
        arc::int64& offset,
        arc::int64& size) const
{
    // check that the resource is in the map
    std::map<arc::io::sys::Path, ResourceLocation>::const_iterator r_find =
        m_resources.find(resource_path);
    if(r_find == m_resources.end())
    {
        arc::str::UTF8String error_message;
        error_message << "No resource in Accessor for \"" << resource_path
                      << "\".";
        throw arc::ex::KeyError(error_message);
    }

    // set the return parameters
    base_path = r_find->second.base_path;
    page_index = r_find->second.page_index;
    offset = r_find->second.offset;
    size = r_find->second.size;
}

std::vector<arc::io::sys::Path> Accessor::list(const arc::io::sys::Path& path)
{
    // use real resources?
    if(Accessor::force_real_resources)
    {
        std::vector<arc::io::sys::Path> initial =
            arc::io::sys::list(path, false);
        // strip directories
        std::vector<arc::io::sys::Path> ret;
        ret.reserve(initial.size());
        for(const arc::io::sys::Path& p : initial)
        {
            if(arc::io::sys::is_file(p, true))
            {
                ret.push_back(p);
            }
        }
        return ret;
    }

    std::vector<arc::io::sys::Path> ret;

    // iterate over the resources in this accessor
    std::map<arc::io::sys::Path, ResourceLocation>::const_iterator it;
    for(it = m_resources.begin(); it != m_resources.end(); ++it)
    {
        const arc::io::sys::Path& l_path = it->first;
        // look for resources that are exactly 1 component longer than this
        // path
        if((path.get_length() + 1) == l_path.get_length())
        {
            // do the components match
            bool match = true;
            for(std::size_t i = 0; i < path.get_length(); ++i)
            {
                if(path[i] != l_path[i])
                {
                    match = false;
                    break;
                }
            }
            // if there was a match, add this path to the return list
            if(match)
            {
                ret.push_back(l_path);
            }
        }
    }

    return ret;
}

std::vector< arc::io::sys::Path> Accessor::list_rec(
        const arc::io::sys::Path& path)
{
    // use real resources?
    if(Accessor::force_real_resources)
    {
        std::vector<arc::io::sys::Path> initial =
            arc::io::sys::list_rec(path, false);
        // strip directories
        std::vector<arc::io::sys::Path> ret;
        ret.reserve(initial.size());
        for(const arc::io::sys::Path& p : initial)
        {
            if(arc::io::sys::is_file(p, true))
            {
                ret.push_back(p);
            }
        }
        return ret;
    }

    std::vector<arc::io::sys::Path> ret;

    // iterate over the resources in this accessor
    std::map<arc::io::sys::Path, ResourceLocation>::const_iterator it;
    for(it = m_resources.begin(); it != m_resources.end(); ++it)
    {
        const arc::io::sys::Path& l_path = it->first;
        // look for resources that are at least 1 component longer than this
        // path
        if(path.get_length() < l_path.get_length())
        {
            // do the components match
            bool match = true;
            for(std::size_t i = 0; i < path.get_length(); ++i)
            {
                if(path[i] != l_path[i])
                {
                    match = false;
                    break;
                }
            }
            // if there was a match, add this path to the return list
            if(match)
            {
                ret.push_back(l_path);
            }
        }
    }

    return ret;
}

} // namespace col
} // namespace arc
