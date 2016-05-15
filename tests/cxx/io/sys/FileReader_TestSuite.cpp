#include <chaoscore/test/ChaosTest.hpp>

CHAOS_TEST_MODULE(io.sys.FileReader)

#include <chaoscore/base/str/UnicodeOperations.hpp>
#include <chaoscore/io/sys/FileReader.hpp>

namespace
{

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class FileReaderFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    chaos::io::sys::Path base_path;

    std::vector<chaos::io::sys::Path> paths;
    std::vector<chaos::io::sys::FileHandle2::Encoding> encodings;
    std::vector<chaos::io::sys::FileHandle2::Newline> newlines;
    std::vector<chaos::int64> sizes;
    std::vector<std::size_t> bom_lengths;
    std::vector<const char*> boms;
    std::vector<std::vector<std::size_t>> line_lengths;
    std::vector<std::vector<const char*>> lines;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        base_path << "tests" << "data" << "file_system";

        // generate data
        {
            chaos::io::sys::Path p(base_path);
            p << "empty_file";
            paths.push_back(p);
            encodings.push_back(chaos::io::sys::FileHandle2::ENCODING_RAW);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_UNIX);
            sizes.push_back(0);
            bom_lengths.push_back(0);
            boms.push_back("");
            std::vector<size_t> ll;
            std::vector<const char*> l;
            line_lengths.push_back(ll);
            lines.push_back(l);
        }
        {
            chaos::io::sys::Path p(base_path);
            p << "ascii.linux.txt";
            paths.push_back(p);
            encodings.push_back(chaos::io::sys::FileHandle2::ENCODING_RAW);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_UNIX);
            sizes.push_back(121);
            bom_lengths.push_back(0);
            boms.push_back("");
            std::vector<size_t> ll;
            std::vector<const char*> l;
            insert_ascii_line("Hello World!\n", ll, l);
            insert_ascii_line("This is another line.\n", ll, l);
            insert_ascii_line("\n", ll, l);
            insert_ascii_line("\t\t     \t\t\n", ll, l);
            insert_ascii_line("And another line.\n", ll, l);
            insert_ascii_line("And some symbols:\n", ll, l);
            insert_ascii_line("$&*@$)@@\":\">?|\n", ll, l);
            insert_ascii_line(">>End of Transmission<<\n", ll, l);
            line_lengths.push_back(ll);
            lines.push_back(l);
        }
        {
            chaos::io::sys::Path p(base_path);
            p << "ascii.windows.txt";
            paths.push_back(p);
            encodings.push_back(chaos::io::sys::FileHandle2::ENCODING_RAW);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_WINDOWS);
            sizes.push_back(129);
            bom_lengths.push_back(0);
            boms.push_back("");
            std::vector<size_t> ll;
            std::vector<const char*> l;
            insert_ascii_line("Hello World!\r\n", ll, l);
            insert_ascii_line("This is another line.\r\n", ll, l);
            insert_ascii_line("\r\n", ll, l);
            insert_ascii_line("\t\t     \t\t\r\n", ll, l);
            insert_ascii_line("And another line.\r\n", ll, l);
            insert_ascii_line("And some symbols:\r\n", ll, l);
            insert_ascii_line("$&*@$)@@\":\">?|\r\n", ll, l);
            insert_ascii_line(">>End of Transmission<<\r\n", ll, l);
            line_lengths.push_back(ll);
            lines.push_back(l);
        }
        {
            chaos::io::sys::Path p(base_path);
            p << "utf8.linux.txt";
            paths.push_back(p);
            encodings.push_back(chaos::io::sys::FileHandle2::ENCODING_UTF8);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_UNIX);
            sizes.push_back(90);
            bom_lengths.push_back(3);
            boms.push_back("\xEF\xBB\xBF");
            std::vector<size_t> ll;
            std::vector<const char*> l;
            insert_utf8_line("Hello World!\n", ll, l);
            insert_utf8_line("γειά σου Κόσμε\n", ll, l);
            insert_utf8_line("\n", ll, l);
            insert_utf8_line("\t\t     \t\t\n", ll, l);
            insert_utf8_line("this is a مزيج of text\n", ll, l);
            insert_utf8_line("간\n", ll, l);
            insert_utf8_line("𐂣\n", ll, l);
            line_lengths.push_back(ll);
            lines.push_back(l);
        }
        {
            chaos::io::sys::Path p(base_path);
            p << "utf8.windows.txt";
            paths.push_back(p);
            encodings.push_back(chaos::io::sys::FileHandle2::ENCODING_UTF8);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_WINDOWS);
            sizes.push_back(97);
            std::vector<size_t> ll;
            std::vector<const char*> l;
            bom_lengths.push_back(3);
            boms.push_back("\xEF\xBB\xBF");
            insert_utf8_line("Hello World!\r\n", ll, l);
            insert_utf8_line("γειά σου Κόσμε\r\n", ll, l);
            insert_utf8_line("\r\n", ll, l);
            insert_utf8_line("\t\t     \t\t\r\n", ll, l);
            insert_utf8_line("this is a مزيج of text\r\n", ll, l);
            insert_utf8_line("간\r\n", ll, l);
            insert_utf8_line("𐂣\r\n", ll, l);
            line_lengths.push_back(ll);
            lines.push_back(l);
        }
        {
            chaos::io::sys::Path p(base_path);
            p << "utf16le.linux.txt";
            paths.push_back(p);
            encodings.push_back(
                chaos::io::sys::FileHandle2::ENCODING_UTF16_LITTLE_ENDIAN);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_UNIX);
            sizes.push_back(136);
            bom_lengths.push_back(2);
            boms.push_back("\xFF\xFE");
            std::vector<size_t> ll;
            std::vector<const char*> l;
            insert_utf16le_line("Hello World!\n", ll, l);
            insert_utf16le_line("γειά σου Κόσμε\n", ll, l);
            insert_utf16le_line("\n", ll, l);
            insert_utf16le_line("\t\t     \t\t\n", ll, l);
            insert_utf16le_line("this is a مزيج of text\n", ll, l);
            insert_utf16le_line("간\n", ll, l);
            insert_utf16le_line("𐂣\n", ll, l);
            line_lengths.push_back(ll);
            lines.push_back(l);
        }
        {
            chaos::io::sys::Path p(base_path);
            p << "utf16le.windows.txt";
            paths.push_back(p);
            encodings.push_back(
                chaos::io::sys::FileHandle2::ENCODING_UTF16_LITTLE_ENDIAN);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_WINDOWS);
            sizes.push_back(150);
            bom_lengths.push_back(2);
            boms.push_back("\xFF\xFE");
            std::vector<size_t> ll;
            std::vector<const char*> l;
            insert_utf16le_line("Hello World!\r\n", ll, l);
            insert_utf16le_line("γειά σου Κόσμε\r\n", ll, l);
            insert_utf16le_line("\r\n", ll, l);
            insert_utf16le_line("\t\t     \t\t\r\n", ll, l);
            insert_utf16le_line("this is a مزيج of text\r\n", ll, l);
            insert_utf16le_line("간\r\n", ll, l);
            insert_utf16le_line("𐂣\r\n", ll, l);
            line_lengths.push_back(ll);
            lines.push_back(l);
        }
        {
            chaos::io::sys::Path p(base_path);
            p << "utf16be.linux.txt";
            paths.push_back(p);
            encodings.push_back(
                chaos::io::sys::FileHandle2::ENCODING_UTF16_BIG_ENDIAN);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_UNIX);
            sizes.push_back(136);
            bom_lengths.push_back(2);
            boms.push_back("\xFE\xFF");
            std::vector<size_t> ll;
            std::vector<const char*> l;
            insert_utf16be_line("Hello World!\n", ll, l);
            insert_utf16be_line("γειά σου Κόσμε\n", ll, l);
            insert_utf16be_line("\n", ll, l);
            insert_utf16be_line("\t\t     \t\t\n", ll, l);
            insert_utf16be_line("this is a مزيج of text\n", ll, l);
            insert_utf16be_line("간\n", ll, l);
            insert_utf16be_line("𐂣\n", ll, l);
            line_lengths.push_back(ll);
            lines.push_back(l);
        }
        {
            chaos::io::sys::Path p(base_path);
            p << "utf16be.windows.txt";
            paths.push_back(p);
            encodings.push_back(
                chaos::io::sys::FileHandle2::ENCODING_UTF16_BIG_ENDIAN);
            newlines.push_back(chaos::io::sys::FileHandle2::NEWLINE_UNIX);
            sizes.push_back(150);
            bom_lengths.push_back(2);
            boms.push_back("\xFE\xFF");
            std::vector<size_t> ll;
            std::vector<const char*> l;
            insert_utf16be_line("Hello World!\r\n", ll, l);
            insert_utf16be_line("γειά σου Κόσμε\r\n", ll, l);
            insert_utf16be_line("\r\n", ll, l);
            insert_utf16be_line("\t\t     \t\t\r\n", ll, l);
            insert_utf16be_line("this is a مزيج of text\r\n", ll, l);
            insert_utf16be_line("간\r\n", ll, l);
            insert_utf16be_line("𐂣\r\n", ll, l);
            line_lengths.push_back(ll);
            lines.push_back(l);
        }
    }

    void insert_ascii_line(
            const chaos::str::UTF8String& line,
            std::vector<std::size_t>& _line_lengths,
            std::vector<const char*>& _lines)
    {
        _line_lengths.push_back(line.get_byte_length() - 1);
        _lines.push_back(line.get_raw());
    }

    void insert_utf8_line(
            const chaos::str::UTF8String& line,
            std::vector<std::size_t>& _line_lengths,
            std::vector<const char*>& _lines)
    {
        _line_lengths.push_back(line.get_byte_length() - 1);
        _lines.push_back(line.get_raw());
    }

    void insert_utf16le_line(
            const chaos::str::UTF8String& line,
            std::vector<std::size_t>& _line_lengths,
            std::vector<const char*>& _lines)
    {
        std::size_t r_length = 0;
        _lines.push_back(chaos::str::utf8_to_utf16(
            line,
            r_length,
            chaos::data::ENDIAN_LITTLE
        ));
        _line_lengths.push_back(r_length - 2);
    }

    void insert_utf16be_line(
            const chaos::str::UTF8String& line,
            std::vector<std::size_t>& _line_lengths,
            std::vector<const char*>& _lines)
    {
        std::size_t r_length = 0;
        _lines.push_back(chaos::str::utf8_to_utf16(
            line,
            r_length,
            chaos::data::ENDIAN_BIG
        ));
        _line_lengths.push_back(r_length - 2);
    }
};

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
            fixture->encodings[i],
            fixture->newlines[i]
        );
        file_readers.push_back(std::move(r));
    }

    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(file_readers[i].get_size(), fixture->sizes[i]);
    }
}

} // namespace anonymous
