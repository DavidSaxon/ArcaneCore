#include <chaoscore/test/ChaosTest.hpp>

CHAOS_TEST_MODULE(io.sys.FileReader)

#include <chaoscore/base/str/UnicodeOperations.hpp>
#include <chaoscore/io/sys/FileReader.hpp>

namespace
{

class FileReaderFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    chaos::io::sys::Path base_path;

    std::vector<chaos::io::sys::Path> paths;
    std::vector<chaos::uint32> flags;
    std::vector<chaos::str::Encoding> encodings;
    std::vector<chaos::int64> sizes;
    std::vector<std::vector<chaos::str::UTF8String>> lines;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        base_path << "tests" << "data" << "file_system";

        // generate data
        {
            chaos::io::sys::Path p(base_path);
            p << "empty_file";
            paths.push_back(p);
            flags.push_back(chaos::io::sys::FileReader::FLAG_NONE);
            encodings.push_back(chaos::str::ENCODING_ASCII);
            sizes.push_back(0);
            std::vector<chaos::str::UTF8String> l;
            lines.push_back(l);
        }
        {
            chaos::io::sys::Path p(base_path);
            p << "ascii.txt";
            paths.push_back(p);
            flags.push_back(chaos::io::sys::FileReader::FLAG_NONE);
            encodings.push_back(chaos::str::ENCODING_ASCII);
            sizes.push_back(121);
            std::vector<chaos::str::UTF8String> l;
            l.push_back("Hello World!\n");
            l.push_back("This is another line.\n");
            l.push_back("\n");
            l.push_back("\t\t     \t\t\n");
            l.push_back("And another line.\n");
            l.push_back("And some symbols:\n");
            l.push_back("$&*@$)@@\":\">?|\n");
            l.push_back(">>End of Transmission<<\n");
            lines.push_back(l);
        }
        // {
        //     chaos::io::sys::Path p(base_path);
        //     p << "utf8.txt";
        //     paths.push_back(p);
        //     flags.push_back(chaos::io::sys::FileReader::FLAG_NONE);
        //     encodings.push_back(chaos::str::ENCODING_UTF8);
        //     sizes.push_back(90);
        //     std::vector<chaos::str::UTF8String> l;
        //     l.push_back("Hello World!\n");
        //     l.push_back("γειά σου Κόσμε\n");
        //     l.push_back("\n");
        //     l.push_back("\t\t     \t\t\n");
        //     l.push_back("this is a مزيج of text\n");
        //     l.push_back("간\n");
        //     l.push_back("𐂣\n");
        //     lines.push_back(l);
        // }
        {
            chaos::io::sys::Path p(base_path);
            p << "ascii.binary";
            paths.push_back(p);
            flags.push_back(chaos::io::sys::FileReader::FLAG_BINARY);
            encodings.push_back(chaos::str::ENCODING_ASCII);
            sizes.push_back(121);
            std::vector<chaos::str::UTF8String> l;
            l.push_back("Hello World!\n");
            l.push_back("This is another line.\n");
            l.push_back("\n");
            l.push_back("\t\t     \t\t\n");
            l.push_back("And another line.\n");
            l.push_back("And some symbols:\n");
            l.push_back("$&*@$)@@\":\">?|\n");
            l.push_back(">>End of Transmission<<\n");
            lines.push_back(l);
        }
        {
            chaos::io::sys::Path p(base_path);
            p << "win_nl";
            paths.push_back(p);
            flags.push_back(chaos::io::sys::FileReader::FLAG_NONE);
            encodings.push_back(chaos::str::ENCODING_ASCII);
            sizes.push_back(129);
            std::vector<chaos::str::UTF8String> l;
            l.push_back("Hello World!\r\n");
            l.push_back("This is another line.\r\n");
            l.push_back("\r\n");
            l.push_back("\t\t     \t\t\r\n");
            l.push_back("And another line.\r\n");
            l.push_back("And some symbols:\r\n");
            l.push_back("$&*@$)@@\":\">?|\r\n");
            l.push_back(">>End of Transmission<<\r\n");
            lines.push_back(l);
        }
        // {
        //     chaos::io::sys::Path p(base_path);
        //     p << "mix_nl";
        //     paths.push_back(p);
        //     flags.push_back(chaos::io::sys::FileReader::FLAG_NONE);
        //     encodings.push_back(chaos::str::ENCODING_UTF8);
        //     sizes.push_back(94);
        //     std::vector<chaos::str::UTF8String> l;
        //     l.push_back("Hello World!\n");
        //     l.push_back("γειά σου Κόσμε\r\n");
        //     l.push_back("\n");
        //     l.push_back("\t\t     \t\t\r\n");
        //     l.push_back("this is a مزيج of text\r\n");
        //     l.push_back("간\r\n");
        //     l.push_back("𐂣\n");
        //     lines.push_back(l);
        // }
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE(default_constructor, FileReaderFixture)
{
    // empty path definition
    chaos::io::sys::Path empty_path;

    CHAOS_TEST_MESSAGE("Checking default values");
    chaos::io::sys::FileReader default_reader;
    CHAOS_CHECK_EQUAL(default_reader.get_path(), empty_path);
    CHAOS_CHECK_EQUAL(
        default_reader.get_flags(),
        chaos::io::sys::FileReader::FLAG_NONE
    );
    CHAOS_CHECK_EQUAL(default_reader.get_encoding(), chaos::str::ENCODING_UTF8);

    CHAOS_TEST_MESSAGE("Checking with defined values");
    std::vector<chaos::io::sys::FileReader> file_readers;
    for(std::size_t i = 0; i < fixture->paths.size(); ++i)
    {
        chaos::io::sys::FileReader r(
            fixture->flags[i],
            fixture->encodings[i]
        );
        file_readers.push_back(std::move(r));
    }

    CHAOS_TEST_MESSAGE("Checking flags");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(file_readers[i].get_flags(), fixture->flags[i]);
    }

    CHAOS_TEST_MESSAGE("Checking encoding");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(
            file_readers[i].get_encoding(), fixture->encodings[i]);
    }
}

//------------------------------------------------------------------------------
//                                PATH CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE(path_constructor, FileReaderFixture)
{
    // create readers
    std::vector<chaos::io::sys::FileReader> file_readers;
    for(std::size_t i = 0; i < fixture->paths.size(); ++i)
    {
        chaos::io::sys::FileReader r(
            fixture->paths[i],
            fixture->flags[i],
            fixture->encodings[i]
        );
        file_readers.push_back(std::move(r));
    }

    CHAOS_TEST_MESSAGE("Checking paths");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(file_readers[i].get_path(), fixture->paths[i]);
    }

    CHAOS_TEST_MESSAGE("Checking flags");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(file_readers[i].get_flags(), fixture->flags[i]);
    }

    CHAOS_TEST_MESSAGE("Checking encoding");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(
            file_readers[i].get_encoding(), fixture->encodings[i]);
    }
}

//------------------------------------------------------------------------------
//                                    GET SIZE
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE(get_size, FileReaderFixture)
{
    // create readers
    std::vector<chaos::io::sys::FileReader> file_readers;
    for(std::size_t i = 0; i < fixture->paths.size(); ++i)
    {
        chaos::io::sys::FileReader r(
            fixture->paths[i],
            fixture->flags[i],
            fixture->encodings[i]
        );
        file_readers.push_back(std::move(r));
    }

    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(file_readers[i].get_size(), fixture->sizes[i]);
    }
}

//------------------------------------------------------------------------------
//                                      READ
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE(read, FileReaderFixture)
{
    // create readers
    std::vector<chaos::io::sys::FileReader> file_readers;
    for(std::size_t i = 0; i < fixture->paths.size(); ++i)
    {
        chaos::io::sys::FileReader r(
            fixture->paths[i],
            fixture->flags[i],
            fixture->encodings[i]
        );
        file_readers.push_back(std::move(r));
    }

    CHAOS_TEST_MESSAGE("Testing reading entire file");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        // TODO: should move UnicodeOperations to StringOperations
        // create the contents
        chaos::str::UTF8String contents(
            chaos::str::join(fixture->lines[i], ""));

        // read data
        std::size_t read_size =
            static_cast<std::size_t>(file_readers[i].get_size());
        char* read_data = new char[read_size];
        file_readers[i].read(read_data, read_size);
        std::cout << "post pos: " << file_readers[i].tell() << std::endl;
        chaos::str::UTF8String data(read_data, read_size);
        // TODO: use claim
        // data.claim(read_data);

        CHAOS_CHECK_EQUAL(data, contents);
    }
}

} // namespace anonymous
