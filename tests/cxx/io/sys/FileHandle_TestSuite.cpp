#include <chaoscore/test/ChaosTest.hpp>

CHAOS_TEST_MODULE(io.sys.FileHandle)

#include <chaoscore/io/sys/FileHandle.hpp>

namespace
{

//------------------------------------------------------------------------------
//                              TEST IMPLEMENTATION
//------------------------------------------------------------------------------

class TestFileHandle2 : public chaos::io::sys::FileHandle2
{
public:

    //-------------------------------CONSTRUCTORS-------------------------------

    TestFileHandle2(
            chaos::io::sys::FileHandle2::Encoding encoding =
                chaos::io::sys::FileHandle2::ENCODING_DETECT,
            chaos::io::sys::FileHandle2::Newline newline =
                chaos::io::sys::FileHandle2::NEWLINE_UNIX)
        :
        FileHandle2(encoding, newline)
    {
    }

    TestFileHandle2(
            const chaos::io::sys::Path& path,
            chaos::io::sys::FileHandle2::Encoding encoding =
                chaos::io::sys::FileHandle2::ENCODING_DETECT,
            chaos::io::sys::FileHandle2::Newline newline =
                chaos::io::sys::FileHandle2::NEWLINE_UNIX)
        :
        FileHandle2(path, encoding, newline)
    {
        open();
    }

    TestFileHandle2(TestFileHandle2&& other)
        :
        FileHandle2(std::move(other))
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

    virtual chaos::int64 get_size() const
    {
        return 0;
    }

    virtual chaos::int64 tell() const
    {
        return 0;
    }

    virtual void seek(chaos::int64 index)
    {
    }
};

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class FileHandle2GenericFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<chaos::io::sys::Path> paths;
    std::vector<chaos::io::sys::FileHandle2::Encoding> encodings;
    std::vector<chaos::io::sys::FileHandle2::Newline> newlines;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // generate data
        {
            chaos::io::sys::Path p;
            p << "file.txt";
            paths.push_back(p);
            encodings.push_back(chaos::io::sys::FileHandle2::ENCODING_DETECT);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_DETECT);
        }
        {
            chaos::io::sys::Path p;
            p << "directory" << "file.txt";
            paths.push_back(p);
            encodings.push_back(chaos::io::sys::FileHandle2::ENCODING_UTF8);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_DETECT);
        }
        {
            chaos::io::sys::Path p;
            p << "/" << "f.png";
            paths.push_back(p);
            encodings.push_back(
                chaos::io::sys::FileHandle2::ENCODING_UTF16_LITTLE_ENDIAN);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_WINDOWS);
        }
        {
            chaos::io::sys::Path p;
            p << "d1" << "d2" << "a_";
            paths.push_back(p);
            encodings.push_back(chaos::io::sys::FileHandle2::ENCODING_RAW);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_UNIX);
        }
        {
            chaos::io::sys::Path p;
            p << "/" << "directory" << "file.txt";
            paths.push_back(p);
            encodings.push_back(
                    chaos::io::sys::FileHandle2::ENCODING_UTF16_BIG_ENDIAN);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_DETECT);
        }
        {
            chaos::io::sys::Path p;
            p << ".." << "file.txt";
            paths.push_back(p);
            encodings.push_back(chaos::io::sys::FileHandle2::ENCODING_DETECT);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_UNIX);
        }
        {
            chaos::io::sys::Path p;
            p << "." << "image.png";
            paths.push_back(p);
            encodings.push_back(chaos::io::sys::FileHandle2::ENCODING_RAW);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_WINDOWS);
        }
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE(default_constructor, FileHandle2GenericFixture)
{
    // build file handles
    std::vector<TestFileHandle2> handles;
    for(std::size_t i = 0; i < fixture->encodings.size(); ++i)
    {
        TestFileHandle2 f(fixture->encodings[i], fixture->newlines[i]);
        handles.push_back(std::move(f));
    }

    CHAOS_TEST_MESSAGE("Checking encodings");
    for(std::size_t i = 0; i < handles.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(handles[i].get_encoding(), fixture->encodings[i]);
    }

    CHAOS_TEST_MESSAGE("Checking newlines");
    for(std::size_t i = 0; i < handles.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(handles[i].get_newline(), fixture->newlines[i]);
    }

    CHAOS_TEST_MESSAGE("Checking that files are closed");
    CHAOS_FOR_EACH(it, handles)
    {
        CHAOS_CHECK_FALSE(it->is_open());
    }
}

//------------------------------------------------------------------------------
//                                PATH CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE(path_constructor, FileHandle2GenericFixture)
{
    // build file handles
    std::vector<TestFileHandle2> handles;
    for(std::size_t i = 0; i < fixture->encodings.size(); ++i)
    {
        TestFileHandle2 f(
            fixture->paths[i],
            fixture->encodings[i],
            fixture->newlines[i]
        );
        handles.push_back(std::move(f));
    }

    CHAOS_TEST_MESSAGE("Checking paths");
    for(std::size_t i = 0; i < handles.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(handles[i].get_path(), fixture->paths[i]);
    }

    CHAOS_TEST_MESSAGE("Checking encodings");
    for(std::size_t i = 0; i < handles.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(handles[i].get_encoding(), fixture->encodings[i]);
    }

    CHAOS_TEST_MESSAGE("Checking newlines");
    for(std::size_t i = 0; i < handles.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(handles[i].get_newline(), fixture->newlines[i]);
    }

    CHAOS_TEST_MESSAGE("Checking that files are open");
    CHAOS_FOR_EACH(it, handles)
    {
        CHAOS_CHECK_TRUE(it->is_open());
    }
}

} // namespace anonymous
