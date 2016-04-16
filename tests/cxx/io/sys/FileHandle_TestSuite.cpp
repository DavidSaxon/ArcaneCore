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

    TestFileHandle(const chaos::io::sys::Path& path, chaos::uint32 flags = 0U)
        :
        FileHandle(path, flags)
    {
    }

    TestFileHandle(chaos::uint32 flags = 0U)
        :
        FileHandle(flags)
    {
    }

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void open()
    {
        // do nothing
    }

    virtual void close()
    {
        // do nothing
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

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // generate data
        {
            chaos::io::sys::Path p;
            p << "file.txt";
            paths.push_back(p);
            flags.push_back(TestFileHandle::FLAG_NONE);
        }
        {
            chaos::io::sys::Path p;
            p << "directory" << "file.txt";
            paths.push_back(p);
            flags.push_back(
                TestFileHandle::FLAG_FIRST  |
                TestFileHandle::FLAG_EIGHTH
            );
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
        }
        {
            chaos::io::sys::Path p;
            p << "d1" << "d2" << "a_";
            paths.push_back(p);
            flags.push_back(
                TestFileHandle::FLAG_SIXTH   |
                TestFileHandle::FLAG_SEVENTH
            );
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
        TestFileHandle f(fixture->paths[i], fixture->flags[i]);
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
}

} // namespace anonymous
