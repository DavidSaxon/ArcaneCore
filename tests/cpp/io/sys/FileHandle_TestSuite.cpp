#include <arcanecore/test/ArcTest.hpp>

ARC_TEST_MODULE(io.sys.FileHandle)

#include <arcanecore/io/sys/FileHandle.hpp>

namespace
{

//------------------------------------------------------------------------------
//                              TEST IMPLEMENTATION
//------------------------------------------------------------------------------

class TestFileHandle : public arc::io::sys::FileHandle
{
public:

    //-------------------------------CONSTRUCTORS-------------------------------

    TestFileHandle(
            arc::io::sys::FileHandle::Encoding encoding =
                arc::io::sys::FileHandle::ENCODING_DETECT,
            arc::io::sys::FileHandle::Newline newline =
                arc::io::sys::FileHandle::NEWLINE_UNIX)
        :
        FileHandle(encoding, newline)
    {
    }

    TestFileHandle(
            const arc::io::sys::Path& path,
            arc::io::sys::FileHandle::Encoding encoding =
                arc::io::sys::FileHandle::ENCODING_DETECT,
            arc::io::sys::FileHandle::Newline newline =
                arc::io::sys::FileHandle::NEWLINE_UNIX)
        :
        FileHandle(path, encoding, newline)
    {
        open();
    }

    TestFileHandle(TestFileHandle&& other)
        :
        FileHandle(std::move(other))
    {
    }

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void open()
    {
        m_open = true;
    }

    virtual void close()
    {
        m_open = false;
    }

    virtual arc::int64 get_size() const
    {
        return 0;
    }

    virtual arc::int64 tell() const
    {
        return 0;
    }

    virtual void seek(arc::int64 index)
    {
    }
};

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class FileHandleGenericFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<arc::io::sys::Path> paths;
    std::vector<arc::io::sys::FileHandle::Encoding> encodings;
    std::vector<arc::io::sys::FileHandle::Newline> newlines;
    std::vector<std::size_t> bom_sizes;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // generate data
        {
            arc::io::sys::Path p;
            p << "file.txt";
            paths.push_back(p);
            encodings.push_back(arc::io::sys::FileHandle::ENCODING_DETECT);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_UNIX);
            bom_sizes.push_back(0);
        }
        {
            arc::io::sys::Path p;
            p << "directory" << "file.txt";
            paths.push_back(p);
            encodings.push_back(arc::io::sys::FileHandle::ENCODING_UTF8);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_UNIX);
            bom_sizes.push_back(3);
        }
        {
            arc::io::sys::Path p;
            p << "/" << "f.png";
            paths.push_back(p);
            encodings.push_back(
                arc::io::sys::FileHandle::ENCODING_UTF16_LITTLE_ENDIAN);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_WINDOWS);
            bom_sizes.push_back(2);
        }
        {
            arc::io::sys::Path p;
            p << "d1" << "d2" << "a_";
            paths.push_back(p);
            encodings.push_back(arc::io::sys::FileHandle::ENCODING_RAW);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_UNIX);
            bom_sizes.push_back(0);
        }
        {
            arc::io::sys::Path p;
            p << "/" << "directory" << "file.txt";
            paths.push_back(p);
            encodings.push_back(
                    arc::io::sys::FileHandle::ENCODING_UTF16_BIG_ENDIAN);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_WINDOWS);
            bom_sizes.push_back(2);
        }
        {
            arc::io::sys::Path p;
            p << ".." << "file.txt";
            paths.push_back(p);
            encodings.push_back(arc::io::sys::FileHandle::ENCODING_DETECT);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_UNIX);
            bom_sizes.push_back(0);
        }
        {
            arc::io::sys::Path p;
            p << "." << "image.png";
            paths.push_back(p);
            encodings.push_back(arc::io::sys::FileHandle::ENCODING_RAW);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_WINDOWS);
            bom_sizes.push_back(0);
        }
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(default_constructor, FileHandleGenericFixture)
{
    // build file handles
    std::vector<TestFileHandle> handles;
    for(std::size_t i = 0; i < fixture->encodings.size(); ++i)
    {
        TestFileHandle f(fixture->encodings[i], fixture->newlines[i]);
        handles.push_back(std::move(f));
    }

    ARC_TEST_MESSAGE("Checking encodings");
    for(std::size_t i = 0; i < handles.size(); ++i)
    {
        ARC_CHECK_EQUAL(handles[i].get_encoding(), fixture->encodings[i]);
    }

    ARC_TEST_MESSAGE("Checking newlines");
    for(std::size_t i = 0; i < handles.size(); ++i)
    {
        ARC_CHECK_EQUAL(handles[i].get_newline(), fixture->newlines[i]);
    }

    ARC_TEST_MESSAGE("Checking that files are closed");
    ARC_FOR_EACH(it, handles)
    {
        ARC_CHECK_FALSE(it->is_open());
    }
}

//------------------------------------------------------------------------------
//                                PATH CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(path_constructor, FileHandleGenericFixture)
{
    // build file handles
    std::vector<TestFileHandle> handles;
    for(std::size_t i = 0; i < fixture->encodings.size(); ++i)
    {
        TestFileHandle f(
            fixture->paths[i],
            fixture->encodings[i],
            fixture->newlines[i]
        );
        handles.push_back(std::move(f));
    }

    ARC_TEST_MESSAGE("Checking paths");
    for(std::size_t i = 0; i < handles.size(); ++i)
    {
        ARC_CHECK_EQUAL(handles[i].get_path(), fixture->paths[i]);
    }

    ARC_TEST_MESSAGE("Checking encodings");
    for(std::size_t i = 0; i < handles.size(); ++i)
    {
        ARC_CHECK_EQUAL(handles[i].get_encoding(), fixture->encodings[i]);
    }

    ARC_TEST_MESSAGE("Checking newlines");
    for(std::size_t i = 0; i < handles.size(); ++i)
    {
        ARC_CHECK_EQUAL(handles[i].get_newline(), fixture->newlines[i]);
    }

    ARC_TEST_MESSAGE("Checking that files are open");
    ARC_FOR_EACH(it, handles)
    {
        ARC_CHECK_TRUE(it->is_open());
    }

    ARC_TEST_MESSAGE("Checking BOM sizes");
    for(std::size_t i = 0; i < handles.size(); ++i)
    {
        ARC_CHECK_EQUAL(handles[i].get_bom_size(), fixture->bom_sizes[i]);
    }
}

} // namespace anonymous
