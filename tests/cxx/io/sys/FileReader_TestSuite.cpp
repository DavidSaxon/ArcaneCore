#include <chaoscore/test/ChaosTest.hpp>

CHAOS_TEST_MODULE(io.sys.FileReader)

#include <cstring>

#include <chaoscore/base/str/StringOperations.hpp>
#include <chaoscore/io/sys/FileReader.hpp>

// TODO: REMOVE ME
#include <fstream>

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
    std::vector<std::size_t> bom_sizes;
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
            bom_sizes.push_back(0);
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
            bom_sizes.push_back(0);
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
            bom_sizes.push_back(0);
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
            bom_sizes.push_back(chaos::str::UTF8_BOM_SIZE);
            boms.push_back(chaos::str::UTF8_BOM);
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
            bom_sizes.push_back(chaos::str::UTF8_BOM_SIZE);
            boms.push_back(chaos::str::UTF8_BOM);
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
            bom_sizes.push_back(chaos::str::UTF16_BOM_SIZE);
            boms.push_back(chaos::str::UTF16LE_BOM);
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
            bom_sizes.push_back(chaos::str::UTF16_BOM_SIZE);
            boms.push_back(chaos::str::UTF16LE_BOM);
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
            bom_sizes.push_back(chaos::str::UTF16_BOM_SIZE);
            boms.push_back(chaos::str::UTF16BE_BOM);
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
            bom_sizes.push_back(chaos::str::UTF16_BOM_SIZE);
            boms.push_back(chaos::str::UTF16BE_BOM);
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

    virtual void teardown()
    {
        CHAOS_FOR_EACH(file_lines, lines)
        {
            CHAOS_FOR_EACH(line, (*file_lines))
            {
                delete[] *line;
            }
        }
    }

    void insert_ascii_line(
            const chaos::str::UTF8String& line,
            std::vector<std::size_t>& _line_lengths,
            std::vector<const char*>& _lines)
    {
        _line_lengths.push_back(line.get_byte_length() - 1);
        char* copy = new char[line.get_byte_length()];
        memcpy(copy, line.get_raw(), line.get_byte_length());
        _lines.push_back(copy);
    }

    void insert_utf8_line(
            const chaos::str::UTF8String& line,
            std::vector<std::size_t>& _line_lengths,
            std::vector<const char*>& _lines)
    {
        _line_lengths.push_back(line.get_byte_length() - 1);
        char* copy = new char[line.get_byte_length()];
        memcpy(copy, line.get_raw(), line.get_byte_length());
        _lines.push_back(copy);
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
            chaos::data::ENDIAN_LITTLE,
            false
        ));
        _line_lengths.push_back(r_length);
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
            chaos::data::ENDIAN_BIG,
            false
        ));
        _line_lengths.push_back(r_length);
    }

    void build_file_readers(std::vector<chaos::io::sys::FileReader>& readers)
    {
        for(std::size_t i = 0; i < paths.size(); ++i)
        {
            chaos::io::sys::FileReader r(paths[i], encodings[i], newlines[i]);
            readers.push_back(std::move(r));
        }
    }
};

//------------------------------------------------------------------------------
//                                    GET SIZE
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE(get_size, FileReaderFixture)
{
    // create readers
    std::vector<chaos::io::sys::FileReader> file_readers;
    fixture->build_file_readers(file_readers);

    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(file_readers[i].get_size(), fixture->sizes[i]);
    }
}

CHAOS_TEST_UNIT_FIXTURE(has_bom, FileReaderFixture)
{
    // create readers
    std::vector<chaos::io::sys::FileReader> file_readers;
    fixture->build_file_readers(file_readers);

    CHAOS_TEST_MESSAGE("Checking files with correct BOMS");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        CHAOS_CHECK_EQUAL(
            file_readers[i].has_bom(),
            fixture->bom_sizes[i] != 0
        );
    }
    CHAOS_TEST_MESSAGE("Checking position is still 0");
    CHAOS_FOR_EACH(reader, file_readers)
    {
        CHAOS_CHECK_EQUAL(reader->tell(), 0);
    }

    CHAOS_TEST_MESSAGE("Checking position is retained");
    CHAOS_FOR_EACH(reader, file_readers)
    {
        chaos::int64 position = reader->get_size() / 2;
        reader->seek(position);
        reader->has_bom();
        CHAOS_CHECK_EQUAL(reader->tell(), position);
    }
}

CHAOS_TEST_UNIT_FIXTURE(read_char, FileReaderFixture)
{
    // create readers
    std::vector<chaos::io::sys::FileReader> file_readers;
    fixture->build_file_readers(file_readers);

    // combine lines
    std::vector<char*> combined_lines;
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        char* combine = new char[static_cast<std::size_t>(fixture->sizes[i])];
        std::size_t l_pos = fixture->bom_sizes[i];
        memcpy(combine, fixture->boms[i], l_pos);
        for(std::size_t j = 0; j < fixture->lines[i].size(); ++j)
        {
            memcpy(
                combine + l_pos,
                fixture->lines[i][j],
                fixture->line_lengths[i][j]
            );
            l_pos += fixture->line_lengths[i][j];
        }
        // store
        combined_lines.push_back(combine);
    }

    CHAOS_TEST_MESSAGE("Checking reading the entire file");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        std::size_t byte_size = static_cast<std::size_t>(fixture->sizes[i]);

        //perform read
        char* read_data = new char[byte_size];
        file_readers[i].read(read_data, byte_size);
        // check
        CHAOS_CHECK_TRUE(memcmp(read_data, combined_lines[i], byte_size) == 0);

        // clean up
        delete[] read_data;
    }

    CHAOS_TEST_MESSAGE("Checking EOF");
    CHAOS_FOR_EACH(reader, file_readers)
    {
        CHAOS_CHECK_TRUE(reader->eof());
        // reset the file
        reader->close();
        reader->open();
    }

    CHAOS_TEST_MESSAGE("Checking reading the file in two parts");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        std::size_t byte_size = static_cast<std::size_t>(fixture->sizes[i]);
        std::size_t first_size = byte_size / 2;
        std::size_t second_size = byte_size - first_size;

        //perform first read
        char* read_data_1 = new char[first_size];
        file_readers[i].read(read_data_1, first_size);
        // check
        CHAOS_CHECK_TRUE(
            memcmp(read_data_1, combined_lines[i], first_size) == 0);

        // check position (but don't bother for the empty file)
        if(file_readers[i].get_size() != 0)
        {
            CHAOS_CHECK_EQUAL(file_readers[i].tell(), first_size);
            CHAOS_CHECK_FALSE(file_readers[i].eof());
        }

        // perform second read
        char* read_data_2 = new char[second_size];
        file_readers[i].read(read_data_2, second_size);
        // check
        CHAOS_CHECK_TRUE(memcmp(
            read_data_2,
            combined_lines[i] + first_size,
            second_size
        ) == 0);

        // check eof
        CHAOS_CHECK_TRUE(file_readers[i].eof());

        // clean up
        delete[] read_data_1;
        delete[] read_data_2;
    }

    // clean up
    CHAOS_FOR_EACH(line, combined_lines)
    {
        delete[] *line;
    }
}

} // namespace anonymous
