#include <arcanecore/test/ArcTest.hpp>

ARC_TEST_MODULE(io.sys.FileReader)

#include <cstring>

#include <arcanecore/base/str/StringOperations.hpp>
#include <arcanecore/io/sys/FileReader.hpp>

namespace
{

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class FileReaderFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    arc::io::sys::Path base_path;

    std::vector<arc::io::sys::Path> paths;
    std::vector<arc::io::sys::FileHandle::Encoding> encodings;
    std::vector<arc::io::sys::FileHandle::Newline> newlines;
    std::vector<arc::int64> sizes;
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
            arc::io::sys::Path p(base_path);
            p << "empty_file";
            paths.push_back(p);
            encodings.push_back(arc::io::sys::FileHandle::ENCODING_RAW);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_UNIX);
            sizes.push_back(0);
            bom_sizes.push_back(0);
            boms.push_back("");
            std::vector<size_t> ll;
            std::vector<const char*> l;
            line_lengths.push_back(ll);
            lines.push_back(l);
        }
        {
            arc::io::sys::Path p(base_path);
            p << "empty_file.utf8";
            paths.push_back(p);
            encodings.push_back(arc::io::sys::FileHandle::ENCODING_UTF8);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_UNIX);
            sizes.push_back(3);
            bom_sizes.push_back(arc::str::UTF8_BOM_SIZE);
            boms.push_back(arc::str::UTF8_BOM);
            std::vector<size_t> ll;
            std::vector<const char*> l;
            line_lengths.push_back(ll);
            lines.push_back(l);
        }
        {
            arc::io::sys::Path p(base_path);
            p << "ascii.linux.txt";
            paths.push_back(p);
            encodings.push_back(arc::io::sys::FileHandle::ENCODING_RAW);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_UNIX);
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
            arc::io::sys::Path p(base_path);
            p << "ascii.windows.txt";
            paths.push_back(p);
            encodings.push_back(arc::io::sys::FileHandle::ENCODING_RAW);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_WINDOWS);
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
            arc::io::sys::Path p(base_path);
            p << "utf8.linux.txt";
            paths.push_back(p);
            encodings.push_back(arc::io::sys::FileHandle::ENCODING_UTF8);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_UNIX);
            sizes.push_back(90);
            bom_sizes.push_back(arc::str::UTF8_BOM_SIZE);
            boms.push_back(arc::str::UTF8_BOM);
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
            arc::io::sys::Path p(base_path);
            p << "utf8.windows.txt";
            paths.push_back(p);
            encodings.push_back(arc::io::sys::FileHandle::ENCODING_UTF8);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_WINDOWS);
            sizes.push_back(97);
            std::vector<size_t> ll;
            std::vector<const char*> l;
            bom_sizes.push_back(arc::str::UTF8_BOM_SIZE);
            boms.push_back(arc::str::UTF8_BOM);
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
            arc::io::sys::Path p(base_path);
            p << "utf16le.linux.txt";
            paths.push_back(p);
            encodings.push_back(
                arc::io::sys::FileHandle::ENCODING_UTF16_LITTLE_ENDIAN);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_UNIX);
            sizes.push_back(136);
            bom_sizes.push_back(arc::str::UTF16_BOM_SIZE);
            boms.push_back(arc::str::UTF16LE_BOM);
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
            arc::io::sys::Path p(base_path);
            p << "utf16le.windows.txt";
            paths.push_back(p);
            encodings.push_back(
                arc::io::sys::FileHandle::ENCODING_UTF16_LITTLE_ENDIAN);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_WINDOWS);
            sizes.push_back(150);
            bom_sizes.push_back(arc::str::UTF16_BOM_SIZE);
            boms.push_back(arc::str::UTF16LE_BOM);
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
            arc::io::sys::Path p(base_path);
            p << "utf16be.linux.txt";
            paths.push_back(p);
            encodings.push_back(
                arc::io::sys::FileHandle::ENCODING_UTF16_BIG_ENDIAN);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_UNIX);
            sizes.push_back(136);
            bom_sizes.push_back(arc::str::UTF16_BOM_SIZE);
            boms.push_back(arc::str::UTF16BE_BOM);
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
            arc::io::sys::Path p(base_path);
            p << "utf16be.windows.txt";
            paths.push_back(p);
            encodings.push_back(
                arc::io::sys::FileHandle::ENCODING_UTF16_BIG_ENDIAN);
            newlines.push_back(arc::io::sys::FileHandle::NEWLINE_UNIX);
            sizes.push_back(150);
            bom_sizes.push_back(arc::str::UTF16_BOM_SIZE);
            boms.push_back(arc::str::UTF16BE_BOM);
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
        ARC_FOR_EACH(file_lines, lines)
        {
            ARC_FOR_EACH(line, (*file_lines))
            {
                delete[] *line;
            }
        }
    }

    void insert_ascii_line(
            const arc::str::UTF8String& line,
            std::vector<std::size_t>& _line_lengths,
            std::vector<const char*>& _lines)
    {
        _line_lengths.push_back(line.get_byte_length() - 1);
        char* copy = new char[line.get_byte_length()];
        memcpy(copy, line.get_raw(), line.get_byte_length());
        _lines.push_back(copy);
    }

    void insert_utf8_line(
            const arc::str::UTF8String& line,
            std::vector<std::size_t>& _line_lengths,
            std::vector<const char*>& _lines)
    {
        _line_lengths.push_back(line.get_byte_length() - 1);
        char* copy = new char[line.get_byte_length()];
        memcpy(copy, line.get_raw(), line.get_byte_length());
        _lines.push_back(copy);
    }

    void insert_utf16le_line(
            const arc::str::UTF8String& line,
            std::vector<std::size_t>& _line_lengths,
            std::vector<const char*>& _lines)
    {
        std::size_t r_length = 0;
        _lines.push_back(arc::str::utf8_to_utf16(
            line,
            r_length,
            arc::data::ENDIAN_LITTLE,
            false
        ));
        _line_lengths.push_back(r_length);
    }

    void insert_utf16be_line(
            const arc::str::UTF8String& line,
            std::vector<std::size_t>& _line_lengths,
            std::vector<const char*>& _lines)
    {
        std::size_t r_length = 0;
        _lines.push_back(arc::str::utf8_to_utf16(
            line,
            r_length,
            arc::data::ENDIAN_BIG,
            false
        ));
        _line_lengths.push_back(r_length);
    }

    void build_file_readers(std::vector<arc::io::sys::FileReader>& readers)
    {
        for(std::size_t i = 0; i < paths.size(); ++i)
        {
            arc::io::sys::FileReader r(paths[i], encodings[i], newlines[i]);
            readers.push_back(std::move(r));
        }
    }
};

//------------------------------------------------------------------------------
//                                    GET SIZE
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(detect_encoding, FileReaderFixture)
{
    // create readers
    std::vector<arc::io::sys::FileReader> file_readers;
    for(std::size_t i = 0; i < fixture->paths.size(); ++i)
    {
        arc::io::sys::FileReader r(
            fixture->paths[i],
            arc::io::sys::FileHandle::ENCODING_DETECT,
            fixture->newlines[i]
        );
        file_readers.push_back(std::move(r));
    }

    // check encodings
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        ARC_CHECK_EQUAL(
            file_readers[i].get_encoding(),
            fixture->encodings[i]
        );
    }
}

ARC_TEST_UNIT_FIXTURE(get_size, FileReaderFixture)
{
    // create readers
    std::vector<arc::io::sys::FileReader> file_readers;
    fixture->build_file_readers(file_readers);

    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        ARC_CHECK_EQUAL(file_readers[i].get_size(), fixture->sizes[i]);
    }
}

ARC_TEST_UNIT_FIXTURE(has_bom, FileReaderFixture)
{
    // create readers
    std::vector<arc::io::sys::FileReader> file_readers;
    fixture->build_file_readers(file_readers);

    ARC_TEST_MESSAGE("Checking files with correct BOMS");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        ARC_CHECK_EQUAL(
            file_readers[i].has_bom(),
            fixture->bom_sizes[i] != 0
        );
    }
    ARC_TEST_MESSAGE("Checking position is still 0");
    ARC_FOR_EACH(reader, file_readers)
    {
        ARC_CHECK_EQUAL(reader->tell(), 0);
    }

    ARC_TEST_MESSAGE("Checking position is retained");
    ARC_FOR_EACH(reader, file_readers)
    {
        arc::int64 position = reader->get_size() / 2;
        reader->seek(position);
        reader->has_bom();
        ARC_CHECK_EQUAL(reader->tell(), position);
    }
}

ARC_TEST_UNIT_FIXTURE(seek_to_data_start, FileReaderFixture)
{
    // create readers
    std::vector<arc::io::sys::FileReader> file_readers;
    fixture->build_file_readers(file_readers);

    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        file_readers[i].seek_to_data_start();
        ARC_CHECK_EQUAL(file_readers[i].tell(), fixture->bom_sizes[i]);
    }
}

ARC_TEST_UNIT_FIXTURE(read_char, FileReaderFixture)
{
    // create readers
    std::vector<arc::io::sys::FileReader> file_readers;
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

    ARC_TEST_MESSAGE("Checking reading the entire file");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        std::size_t byte_size = static_cast<std::size_t>(fixture->sizes[i]);

        //perform read
        char* read_data = new char[byte_size];
        file_readers[i].read(read_data, byte_size);
        // check
        ARC_CHECK_TRUE(memcmp(read_data, combined_lines[i], byte_size) == 0);

        // clean up
        delete[] read_data;
    }

    ARC_TEST_MESSAGE("Checking EOF");
    ARC_FOR_EACH(reader, file_readers)
    {
        ARC_CHECK_TRUE(reader->eof());
        // reset the file
        reader->close();
        reader->open();
    }

    ARC_TEST_MESSAGE("Checking reading the file in two parts");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        // don't check the empty file
        if(file_readers[i].get_size() == 0)
        {
            continue;
        }

        std::size_t byte_size = static_cast<std::size_t>(fixture->sizes[i]);
        std::size_t first_size = byte_size / 2;
        std::size_t second_size = byte_size - first_size;

        //perform first read
        char* read_data_1 = new char[first_size];
        file_readers[i].read(read_data_1, first_size);
        // check
        ARC_CHECK_TRUE(
            memcmp(read_data_1, combined_lines[i], first_size) == 0);

        // check position
        ARC_CHECK_EQUAL(file_readers[i].tell(), first_size);
        ARC_CHECK_FALSE(file_readers[i].eof());

        // perform second read
        char* read_data_2 = new char[second_size];
        file_readers[i].read(read_data_2, second_size);
        // check
        ARC_CHECK_TRUE(memcmp(
            read_data_2,
            combined_lines[i] + first_size,
            second_size
        ) == 0);

        // check eof
        ARC_CHECK_TRUE(file_readers[i].eof());

        // clean up
        delete[] read_data_1;
        delete[] read_data_2;
    }

    // clean up
    ARC_FOR_EACH(line, combined_lines)
    {
        delete[] *line;
    }
}

ARC_TEST_UNIT_FIXTURE(read_utf8, FileReaderFixture)
{
    // create readers
    std::vector<arc::io::sys::FileReader> file_readers;
    fixture->build_file_readers(file_readers);

    // combine lines
    std::vector<arc::str::UTF8String> combined_lines;
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        arc::str::UTF8String s;
        for(std::size_t j = 0; j < fixture->lines[i].size(); ++j)
        {
            if(fixture->encodings[i] ==
               arc::io::sys::FileHandle::ENCODING_UTF16_LITTLE_ENDIAN)
            {
                s += arc::str::utf16_to_utf8(
                    fixture->lines[i][j],
                    fixture->line_lengths[i][j],
                    arc::data::ENDIAN_LITTLE
                );
            }
            else if(fixture->encodings[i] ==
                    arc::io::sys::FileHandle::ENCODING_UTF16_BIG_ENDIAN)
            {
                s += arc::str::utf16_to_utf8(
                    fixture->lines[i][j],
                    fixture->line_lengths[i][j],
                    arc::data::ENDIAN_BIG
                );
            }
            else
            {
                s += arc::str::UTF8String(
                    fixture->lines[i][j],
                    fixture->line_lengths[i][j]
                );
            }
        }
        combined_lines.push_back(s);
    }

    ARC_TEST_MESSAGE("Checking reading the entire file");
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        //perform read
        arc::str::UTF8String read_data;
        file_readers[i].read(read_data);
        ARC_CHECK_EQUAL(read_data, combined_lines[i]);
    }

    ARC_TEST_MESSAGE("Checking EOF");
    ARC_FOR_EACH(reader, file_readers)
    {
        ARC_CHECK_TRUE(reader->eof());
    }

    ARC_TEST_MESSAGE("Checking EOF throws exception on read");
    ARC_FOR_EACH(reader, file_readers)
    {
        arc::str::UTF8String read_data;
        ARC_CHECK_THROW(
            reader->read(read_data),
            arc::ex::EOFError
        );
        // reset the file
        reader->close();
        reader->open();
    }
}

ARC_TEST_UNIT_FIXTURE(read_line_char, FileReaderFixture)
{
    // create readers
    std::vector<arc::io::sys::FileReader> file_readers;
    fixture->build_file_readers(file_readers);

    // read the file line by line
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        // skip the empty file
        if(file_readers[i].get_size() == 0)
        {
            continue;
        }

        // calculate the newline size for this file
        std::size_t newline_size = 1;
        if(file_readers[i].get_encoding() ==
           arc::io::sys::FileHandle::ENCODING_UTF16_LITTLE_ENDIAN
           ||
           file_readers[i].get_encoding() ==
           arc::io::sys::FileHandle::ENCODING_UTF16_BIG_ENDIAN)
        {
            newline_size = 2;
        }
        // apply os size
        if(file_readers[i].get_newline() ==
           arc::io::sys::FileHandle::NEWLINE_WINDOWS)
        {
            newline_size *= 2;
        }

        std::size_t l_n = 0;
        while(!file_readers[i].eof())
        {
            // skip the empty line
            if(l_n == fixture->lines[i].size())
            {
                break;
            }

            // read
            char* read_data = nullptr;
            file_readers[i].read_line(&read_data);

            // check
            ARC_CHECK_TRUE(
                memcmp(
                    read_data,
                    fixture->lines[i][l_n],
                    fixture->line_lengths[i][l_n] - newline_size
                ) == 0
            );

            // clean up
            delete[] read_data;
            ++l_n;
        }
    }
}

ARC_TEST_UNIT_FIXTURE(read_line_utf8, FileReaderFixture)
{
    // create readers
    std::vector<arc::io::sys::FileReader> file_readers;
    fixture->build_file_readers(file_readers);

    // read the file line by line
    for(std::size_t i = 0; i < file_readers.size(); ++i)
    {
        // skip the empty file
        if(file_readers[i].get_size() == 0)
        {
            continue;
        }

        // calculate the newline size for this file
        std::size_t newline_size = 1;
        if(file_readers[i].get_encoding() ==
           arc::io::sys::FileHandle::ENCODING_UTF16_LITTLE_ENDIAN
           ||
           file_readers[i].get_encoding() ==
           arc::io::sys::FileHandle::ENCODING_UTF16_BIG_ENDIAN)
        {
            newline_size = 2;
        }
        // apply os size
        if(file_readers[i].get_newline() ==
           arc::io::sys::FileHandle::NEWLINE_WINDOWS)
        {
            newline_size *= 2;
        }

        std::size_t l_n = 0;
        while(!file_readers[i].eof())
        {
            // skip the empty line
            if(l_n == fixture->lines[i].size())
            {
                break;
            }

            // get the fixture line as utf8
            arc::str::UTF8String line;
            if(fixture->encodings[i] ==
               arc::io::sys::FileHandle::ENCODING_UTF16_LITTLE_ENDIAN)
            {
                line = arc::str::utf16_to_utf8(
                    fixture->lines[i][l_n],
                    fixture->line_lengths[i][l_n] - newline_size,
                    arc::data::ENDIAN_LITTLE
                );
            }
            else if(fixture->encodings[i] ==
                    arc::io::sys::FileHandle::ENCODING_UTF16_BIG_ENDIAN)
            {
                line = arc::str::utf16_to_utf8(
                    fixture->lines[i][l_n],
                    fixture->line_lengths[i][l_n] - newline_size,
                    arc::data::ENDIAN_BIG
                );
            }
            else
            {
                line = arc::str::UTF8String(
                    fixture->lines[i][l_n],
                    fixture->line_lengths[i][l_n] - newline_size
                );
            }

            // read
            arc::str::UTF8String read_data;
            file_readers[i].read_line(read_data);

            // check
            ARC_CHECK_EQUAL(read_data, line);

            // clean up
            ++l_n;
        }
    }
}

} // namespace anonymous
