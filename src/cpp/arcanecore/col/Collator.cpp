#include "arcanecore/col/Collator.hpp"

#include <algorithm>
#include <cassert>
#include <limits>

#include <arcanecore/base/Exceptions.hpp>
#include <arcanecore/io/sys/FileReader.hpp>
#include <arcanecore/io/sys/FileSystemOperations.hpp>
#include <arcanecore/io/sys/FileWriter.hpp>

#include "arcanecore/col/TableOfContents.hpp"


namespace arc
{
namespace col
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Collator::Collator(
        TableOfContents* table_of_contents,
        const arc::io::sys::Path& base_path,
        arc::int64 page_size,
        std::size_t read_size)
    :
    m_table_of_contents(table_of_contents),
    m_base_path        (base_path),
    m_page_size        (page_size),
    m_read_size        (read_size)
{
    // ensure the table of contents is not null
    if(table_of_contents == nullptr)
    {
        throw arc::ex::ValueError("TableOfContents cannot be null.");
    }

    // ensure there is at least one component in the path
    if(m_base_path.is_empty())
    {
        throw arc::ex::ValueError("base_path cannot be null.");
    }
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

TableOfContents* Collator::get_table_of_contents() const
{
    return m_table_of_contents;
}

const arc::io::sys::Path& Collator::get_base_path() const
{
    return m_base_path;
}

arc::int64 Collator::get_page_size() const
{
    return m_page_size;
}

std::size_t Collator::get_read_size() const
{
    return m_read_size;
}

const std::vector<arc::io::sys::Path>& Collator::get_resources() const
{
    return m_resources;
}

bool Collator::add_resource(const arc::io::sys::Path& resource_path)
{
    // has the resource been added already?
    if(std::find(m_resources.begin(), m_resources.end(), resource_path) ==
       m_resources.end())
    {
        m_resources.push_back(resource_path);
        return true;
    }

    return false;
}

void Collator::execute()
{
    // the number of this page
    std::size_t page_index = 0;
    // the number of bytes in the current page
    arc::int64 page_current_size = 0;
    // pointer to the file writer currently being used
    arc::io::sys::FileWriter* writer = new_page(page_index);

    for(const arc::io::sys::Path& resource : m_resources)
    {
        // open the resource
        arc::io::sys::FileReader resource_reader(
            resource, arc::io::sys::FileHandle::ENCODING_RAW);
        // add to the table of contents
        m_table_of_contents->add_resource(
            resource,
            m_base_path,
            page_index,
            page_current_size,
            resource_reader.get_size()
        );

        // read the file in chunks until we reach the end of the file
        while(!resource_reader.eof())
        {
            // do we need to allocate a new page?
            if(m_page_size > 0)
            {
                // reached the end of the page?
                if(page_current_size == m_page_size)
                {
                    writer->close();
                    delete writer;
                    writer = new_page(++page_index);
                    page_current_size = 0;
                }
            }

            // find the remaining free data in this chunk
            std::size_t this_read_size =
                std::numeric_limits<std::size_t>::max();
            if(m_page_size > 0)
            {
                this_read_size =
                    static_cast<std::size_t>(m_page_size - page_current_size);
            }

            // if the remaining page data is greater than the read size, use the
            // read size instead
            if(this_read_size > m_read_size)
            {
                this_read_size = m_read_size;
            }

            // compare against the amount of data actually remaining in the file
            arc::int64 file_remaining =
                resource_reader.get_size() - resource_reader.tell();
            if(file_remaining < static_cast<arc::int64>(this_read_size))
            {
                this_read_size = static_cast<std::size_t>(file_remaining);
            }

            // allocate the number of bytes to be read
            char* resource_data = new char[this_read_size];
            resource_reader.read(
                resource_data,
                static_cast<arc::int64>(this_read_size)
            );

            // write the data to the collated file
            writer->write(resource_data, this_read_size);

            // clean up
            delete[] resource_data;

            // increase the byte count in this page
            page_current_size += this_read_size;
            assert(m_page_size < 0 || page_current_size <= m_page_size);
        }
    }

    // clean up the final writer
    writer->close();
    delete writer;
}

void Collator::revert()
{
    // iterate over the created files and delete them
    for(const arc::io::sys::Path& path : m_created)
    {
        try
        {
            arc::io::sys::delete_path(path);
        }
        catch(...)
        {
            // do nothing and continue
        }
    }

    // clear the list of created list
    m_created.clear();
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

arc::io::sys::FileWriter* Collator::new_page(std::size_t page_index)
{
    // get (and remove) the final component of the base path
    arc::str::UTF8String filename(m_base_path.get_back());
    arc::io::sys::Path dir(m_base_path);
    dir.remove(dir.get_length() - 1);

    arc::io::sys::Path writer_path(dir);
    arc::str::UTF8String writer_filename(filename);
    writer_filename << "." << page_index;
    writer_path << writer_filename;

    m_created.push_back(writer_path);
    return new arc::io::sys::FileWriter(
            writer_path,
            arc::io::sys::FileWriter::OPEN_TRUNCATE,
            arc::io::sys::FileHandle::ENCODING_RAW
    );
}

} // namespace col
} // namespace arc
