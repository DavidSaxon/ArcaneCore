#include <chaoscore/test/ChaosTest.hpp>

CHAOS_TEST_MODULE(io.sys.FileHandle)

#include <chaoscore/io/sys/FileHandle.hpp>

namespace
{

//------------------------------------------------------------------------------
//                              TEST IMPLEMENTATION
//------------------------------------------------------------------------------

// Object derived from chaos::io::sys::FileHandle used to test it
class TestFileHandle : public chaos::io::sys::FileHandle
{
public:

    //----------------------------------ENUMS-----------------------------------

    enum Flag
    {
        FLAG_NONE    = 0,
        FLAG_FIRST   = 1U << 0,
        FLAG_SECOND  = 1U << 1,
        FLAG_THIRD   = 1U << 2,
        FLAG_FOURTH  = 1U << 3,
        FLAG_FIFTH   = 1U << 4,
        FLAG_SIXTH   = 1U << 5,
        FLAG_SEVENTH = 1U << 6,
        FLAG_EIGHTH  = 1U << 7
    };

    //-------------------------------CONSTRUCTORS-------------------------------

    TestFileHandle(
            const chaos::io::sys::Path& path,
            chaos::uint32 flags = 0U,
            chaos::str::Encoding encoding = chaos::str::ENCODING_UTF8)
        :
        FileHandle(path, flags, encoding)
    {
    }

    TestFileHandle(
            chaos::uint32 flags = 0U,
            chaos::str::Encoding encoding = chaos::str::ENCODING_UTF8)
        :
        FileHandle(flags, encoding)
    {
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
};

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class FileHandleGenericFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<chaos::io::sys::Path> paths;
    std::vector<chaos::uint32> flags;
    std::vector<chaos::str::Encoding> encodings;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // generate data
        {
            chaos::io::sys::Path p;
            p << "file.txt";
            paths.push_back(p);
            flags.push_back(TestFileHandle::FLAG_NONE);
            encodings.push_back(chaos::str::ENCODING_ASCII);
        }
        {
            chaos::io::sys::Path p;
            p << "directory" << "file.txt";
            paths.push_back(p);
            flags.push_back(
                TestFileHandle::FLAG_FIRST  |
                TestFileHandle::FLAG_EIGHTH
            );
            encodings.push_back(chaos::str::ENCODING_UTF8);
        }
        {
            chaos::io::sys::Path p;
            p << "/" << "f.png";
            paths.push_back(p);
            flags.push_back(
                TestFileHandle::FLAG_SIXTH  |
                TestFileHandle::FLAG_FIRST  |
                TestFileHandle::FLAG_SECOND
            );
            encodings.push_back(chaos::str::ENCODING_UTF16_LITTLE_ENDIAN);
        }
        {
            chaos::io::sys::Path p;
            p << "d1" << "d2" << "a_";
            paths.push_back(p);
            flags.push_back(
                TestFileHandle::FLAG_SIXTH   |
                TestFileHandle::FLAG_SEVENTH
            );
            encodings.push_back(chaos::str::ENCODING_UTF16_BIG_ENDIAN);
        }
        {
            chaos::io::sys::Path p;
            p << "/" << "directory" << "file.txt";
            paths.push_back(p);
            flags.push_back(
                TestFileHandle::FLAG_FIRST   |
                TestFileHandle::FLAG_THIRD   |
                TestFileHandle::FLAG_FIFTH   |
                TestFileHandle::FLAG_SEVENTH
            );
            encodings.push_back(chaos::str::ENCODING_UTF16_BIG_ENDIAN);
        }
        {
            chaos::io::sys::Path p;
            p << ".." << "file.txt";
            paths.push_back(p);
            flags.push_back(
                TestFileHandle::FLAG_SECOND |
                TestFileHandle::FLAG_FOURTH |
                TestFileHandle::FLAG_SIXTH  |
                TestFileHandle::FLAG_EIGHTH
            );
            encodings.push_back(chaos::str::ENCODING_UTF8);
        }
        {
            chaos::io::sys::Path p;
            p << "." << "image.png";
            paths.push_back(p);
            flags.push_back(
                TestFileHandle::FLAG_FIRST   |
                TestFileHandle::FLAG_SECOND  |
                TestFileHandle::FLAG_THIRD   |
                TestFileHandle::FLAG_FOURTH  |
                TestFileHandle::FLAG_FIFTH   |
                TestFileHandle::FLAG_SIXTH   |
                TestFileHandle::FLAG_SEVENTH |
                TestFileHandle::FLAG_EIGHTH
            );
            encodings.push_back(chaos::str::ENCODING_UTF16_LITTLE_ENDIAN);
        }
    }
};

//------------------------------------------------------------------------------
//                                FLAG CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE(flag_constructor, FileHandleGenericFixture)
{
    CHAOS_FOR_EACH(it, fixture->flags)
    {
        TestFileHandle f(*it);
        CHAOS_CHECK_EQUAL(f.get_flags(), *it);
    }
}

//------------------------------------------------------------------------------
//                                PATH CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE(path_constructor, FileHandleGenericFixture)
{
    std::vector<TestFileHandle> file_handles;

    for(std::size_t i = 0; i < fixture->paths.size(); ++i)
    {
        TestFileHandle f(
            fixture->paths[i],
            fixture->flags[i],
            fixture->encodings[i]
        );
        file_handles.push_back(std::move(f));
    }

    CHAOS_TEST_MESSAGE("Checking paths");
    for(std::size_t i = 0; i < file_handles.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(file_handles[i].get_path(), fixture->paths[i]);
    }

    CHAOS_TEST_MESSAGE("Checking flags");
    for(std::size_t i = 0; i < file_handles.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(file_handles[i].get_path(), fixture->paths[i]);
    }

    CHAOS_TEST_MESSAGE("Checking encoding");
    for(std::size_t i = 0; i < file_handles.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(
            file_handles[i].get_encoding(), fixture->encodings[i]);
    }

    CHAOS_TEST_MESSAGE("Checking that files are closed");
    CHAOS_FOR_EACH(it, file_handles)
    {
        CHAOS_CHECK_FALSE(it->is_open());
    }

    CHAOS_TEST_MESSAGE("Opening files");
    CHAOS_FOR_EACH(it, file_handles)
    {
        it->open();
    }

    CHAOS_TEST_MESSAGE("Checking that files are open");
    CHAOS_FOR_EACH(it, file_handles)
    {
        CHAOS_CHECK_TRUE(it->is_open());
    }


    CHAOS_TEST_MESSAGE("Checking that setters are locked");
    for(std::size_t i = 0; i < file_handles.size(); ++i)
    {
        CHAOS_CHECK_THROW(
            file_handles[i].set_path(fixture->paths[i]),
            chaos::ex::StateError
        );
    }
    for(std::size_t i = 0; i < file_handles.size(); ++i)
    {
        CHAOS_CHECK_THROW(
            file_handles[i].set_flags(fixture->flags[i]),
            chaos::ex::StateError
        );
    }
    for(std::size_t i = 0; i < file_handles.size(); ++i)
    {
        CHAOS_CHECK_THROW(
            file_handles[i].set_encoding(fixture->encodings[i]),
            chaos::ex::StateError
        );
    }

    CHAOS_TEST_MESSAGE("Closing files");
    CHAOS_FOR_EACH(it, file_handles)
    {
        it->close();
    }

    CHAOS_TEST_MESSAGE("Checking that setters are unlocked");
    for(std::size_t i = 0; i < file_handles.size(); ++i)
    {
        file_handles[i].set_path(fixture->paths[file_handles.size() - i]);
        CHAOS_CHECK_EQUAL(
            file_handles[i].get_path(),
            fixture->paths[file_handles.size() - i]
        );
    }
    for(std::size_t i = 0; i < file_handles.size(); ++i)
    {
        file_handles[i].set_flags(fixture->flags[file_handles.size() - i]);
        CHAOS_CHECK_EQUAL(
            file_handles[i].get_flags(),
            fixture->flags[file_handles.size() - i]
        );
    }
    for(std::size_t i = 0; i < file_handles.size(); ++i)
    {
        file_handles[i].set_encoding(
            fixture->encodings[file_handles.size() - i]);
        CHAOS_CHECK_EQUAL(
            file_handles[i].get_encoding(),
            fixture->encodings[file_handles.size() - i]
        );
    }
}

} // namespace anonymous
