#include <arcanecore/test/ArcTest.hpp>

ARC_TEST_MODULE(config.Document)

#include <arcanecore/base/Exceptions.hpp>

#include <json/json.h>

#include <arcanecore/config/Document.hpp>

namespace
{

//------------------------------------------------------------------------------
//                                 LOAD FILE PATH
//------------------------------------------------------------------------------

class LoadFilePathFixture : public virtual arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<arc::io::sys::Path> valid_paths;
    std::vector<arc::io::sys::Path> invalid_paths;
    std::vector<arc::io::sys::Path> non_json_paths;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // valid paths
        {
            arc::io::sys::Path p;
            p << "tests" << "data" << "config" << "simple.json";
            valid_paths.push_back(p);
        }
        {
            arc::io::sys::Path p;
            p << "tests" << "data" << "config" << "hierarchy.json";
            valid_paths.push_back(p);
        }
        {
            arc::io::sys::Path p;
            p << "tests" << "data" << "config" << "sub" << "simple.json";
            valid_paths.push_back(p);
        }
        {
            arc::io::sys::Path p;
            p << "tests" << "data" << "config" << "sub" << "hierarchy.json";
            valid_paths.push_back(p);
        }

        // invalid paths
        {
            arc::io::sys::Path p;
            p << "tests" << "data" << "config" << "simple.txt";
            invalid_paths.push_back(p);
        }
        {
            arc::io::sys::Path p;
            p << "tests" << "data" << "config" << "does_not_exist.json";
            invalid_paths.push_back(p);
        }
        {
            arc::io::sys::Path p;
            p << "tests" << "does_not_exist" << "hierarchy.json";
            invalid_paths.push_back(p);
        }
        {
            arc::io::sys::Path p;
            p << "tests" << "data" << "config" << "does_not_exist"
              << "hierarchy.json";
            invalid_paths.push_back(p);
        }

        // non JSON paths
        {
            arc::io::sys::Path p;
            p << "tests" << "data" << "config" << "bad_1.json";
            non_json_paths.push_back(p);
        }
        {
            arc::io::sys::Path p;
            p << "tests" << "data" << "config" << "bad_2.txt";
            non_json_paths.push_back(p);
        }
        {
            arc::io::sys::Path p;
            p << "tests" << "data" << "config" << "sub" << "bad_3.csv";
            non_json_paths.push_back(p);
        }
        {
            arc::io::sys::Path p;
            p << "tests" << "data" << "config" << "sub" << "bad_4.json";
            non_json_paths.push_back(p);
        }
    }
};

ARC_TEST_UNIT_FIXTURE(load_file_path, LoadFilePathFixture)
{
    ARC_TEST_MESSAGE("Checking loading valid files");
    ARC_CONST_FOR_EACH(it, fixture->valid_paths)
    {
        arc::config::Document doc(*it);
        ARC_CHECK_TRUE(doc.is_using_file_path());
        ARC_CHECK_FALSE(doc.is_using_memory());
        ARC_CHECK_TRUE(doc.has_valid_file_data());
        ARC_CHECK_FALSE(doc.has_valid_memory_data());
    }

    ARC_TEST_MESSAGE("Checking loading invalid file paths");
    ARC_CONST_FOR_EACH(it, fixture->invalid_paths)
    {
        ARC_CHECK_THROW(arc::config::Document(*it), arc::ex::IOError);
    }

    ARC_TEST_MESSAGE("Checking loading non-JSON files");
    ARC_CONST_FOR_EACH(it, fixture->non_json_paths)
    {
        ARC_CHECK_THROW(arc::config::Document(*it), arc::ex::ParseError);
    }
}

//------------------------------------------------------------------------------
//                                  LOAD MEMORY
//------------------------------------------------------------------------------

class LoadMemoryFixture : public virtual arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<arc::str::UTF8String> valid;
    std::vector<arc::str::UTF8String> invalid;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        valid.push_back("{}");
        valid.push_back("{\"simple\": false}");
        valid.push_back(
            "{"
            "    \"value_1\": \"Hello world!\","
            "    \"value_2\": 175,"
            "    \"value_3\": 3.14"
            "}"
        );
        valid.push_back(
            "{"
            "    \"first_error\": 3,"
            "    \"resource_path\": [\"res\"],"
            "    \"g_resource_path\": [\"${resource_path}\", \"gui\"],"
            "    \"fonts_resource_path\": [\"${g_resource_path}\", \"fonts\"],"
            "    \"fonts\":"
            "    {"
            "        \"supported_formats\": [\"ttf\", \"otf\"]"
            "    },"
            "    \"bool_test\": true"
            "}"
        );

        invalid.push_back("");
        invalid.push_back("Hello World!");
        invalid.push_back("this,is,not,json\nnot,json,at,all");
        invalid.push_back(
            "{"
            "    \"first_error\": 3,"
            "    \"resource_path\": [\"res\"],"
            "    \"g_resource_path\": [\"${resource_path}\", \"gui\"],"
            "    \"fonts_resource_path\": [\"${g_resource_path}\", \"fonts\"],"
            "    \"fonts\":"
            "    {"
            "        \"supported_formats\":: [\"ttf\", \"otf\"]"
            "    },"
            "    \"bool_test\": true"
            "}"
        );
    }
};

ARC_TEST_UNIT_FIXTURE(load_memory, LoadMemoryFixture)
{
    ARC_TEST_MESSAGE("Checking loading valid JSON strings");
    ARC_CONST_FOR_EACH(it, fixture->valid)
    {
        arc::config::Document doc(&(*it));
        ARC_CHECK_FALSE(doc.is_using_file_path());
        ARC_CHECK_TRUE(doc.is_using_memory());
        ARC_CHECK_FALSE(doc.has_valid_file_data());
        ARC_CHECK_TRUE(doc.has_valid_memory_data());
    }

    ARC_TEST_MESSAGE("Checking loading invalid JSON strings");
    ARC_CONST_FOR_EACH(it, fixture->invalid)
    {
        ARC_CHECK_THROW(arc::config::Document(&(*it)), arc::ex::ParseError);
    }
}

//------------------------------------------------------------------------------
//                                 LOAD FALLBACK
//------------------------------------------------------------------------------

class LoadFallbackFixture : public LoadFilePathFixture, public LoadMemoryFixture
{
public:

    //-------------------------PUBLIC STATIC ATTRIBUTES-------------------------

    static bool report_callback;
    static arc::io::sys::Path report_file_path;
    static arc::str::UTF8String report_message;

    //----------------------------CALLBACK FUNCTIONS----------------------------

    static void reporter_func(
            const arc::io::sys::Path& file_path,
            const arc::str::UTF8String& message)
    {
        report_callback = true;
        report_file_path = file_path;
        report_message   = report_message;
    }

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super calls
        LoadFilePathFixture::setup();
        LoadMemoryFixture::setup();

        // hook up the callback
        arc::config::Document::set_load_fallback_reporter(reporter_func);
    }

    static void reset_state()
    {
        report_callback = false;
        report_file_path = arc::io::sys::Path();
        report_message = arc::str::UTF8String();
    }
};

bool LoadFallbackFixture::report_callback = false;
arc::io::sys::Path LoadFallbackFixture::report_file_path;
arc::str::UTF8String LoadFallbackFixture::report_message;

ARC_TEST_UNIT_FIXTURE(load_fallback, LoadFallbackFixture)
{
    ARC_TEST_MESSAGE("Checking all valid");
    for(std::size_t i = 0; i < fixture->valid_paths.size(); ++i)
    {
        arc::config::Document doc(fixture->valid_paths[i], &fixture->valid[i]);
        ARC_CHECK_FALSE(LoadFallbackFixture::report_callback);
        ARC_CHECK_TRUE(doc.is_using_file_path());
        ARC_CHECK_TRUE(doc.is_using_memory());
        ARC_CHECK_TRUE(doc.has_valid_file_data());
        ARC_CHECK_TRUE(doc.has_valid_memory_data());
    }
    LoadFallbackFixture::reset_state();

    ARC_TEST_MESSAGE("Checking valid path, invalid memory");
    for(std::size_t i = 0; i < fixture->valid_paths.size(); ++i)
    {
        arc::config::Document doc(fixture->valid_paths[i], &fixture->invalid[i]);
        ARC_CHECK_TRUE(LoadFallbackFixture::report_callback);
        ARC_CHECK_EQUAL(
            LoadFallbackFixture::report_file_path,
            fixture->valid_paths[i]
        );
        ARC_CHECK_TRUE(doc.is_using_file_path());
        ARC_CHECK_TRUE(doc.is_using_memory());
        ARC_CHECK_TRUE(doc.has_valid_file_data());
        ARC_CHECK_FALSE(doc.has_valid_memory_data());
    }
    LoadFallbackFixture::reset_state();

    ARC_TEST_MESSAGE("Checking invalid path, valid memory");
    for(std::size_t i = 0; i < fixture->invalid_paths.size(); ++i)
    {
        arc::config::Document doc(fixture->invalid_paths[i], &fixture->valid[i]);
        ARC_CHECK_TRUE(LoadFallbackFixture::report_callback);
        ARC_CHECK_EQUAL(
            LoadFallbackFixture::report_file_path,
            fixture->invalid_paths[i]
        );
        ARC_CHECK_TRUE(doc.is_using_file_path());
        ARC_CHECK_TRUE(doc.is_using_memory());
        ARC_CHECK_FALSE(doc.has_valid_file_data());
        ARC_CHECK_TRUE(doc.has_valid_memory_data());
    }
    LoadFallbackFixture::reset_state();

    ARC_TEST_MESSAGE("Checking invalid path, invalid memory");
    for(std::size_t i = 0; i < fixture->invalid_paths.size(); ++i)
    {
        ARC_CHECK_THROW(
            arc::config::Document(
                    fixture->invalid_paths[i],
                    &fixture->invalid[i]
            ),
            arc::ex::ParseError
        );
        ARC_CHECK_TRUE(LoadFallbackFixture::report_callback);
        ARC_CHECK_EQUAL(
            LoadFallbackFixture::report_file_path,
            fixture->invalid_paths[i]
        );
    }
    LoadFallbackFixture::reset_state();

    ARC_TEST_MESSAGE("Checking non-JSON path, valid memory");
    for(std::size_t i = 0; i < fixture->non_json_paths.size(); ++i)
    {
        arc::config::Document doc(
            fixture->non_json_paths[i],
            &fixture->valid[i]
        );
        ARC_CHECK_TRUE(LoadFallbackFixture::report_callback);
        ARC_CHECK_EQUAL(
            LoadFallbackFixture::report_file_path,
            fixture->non_json_paths[i]
        );
        ARC_CHECK_TRUE(doc.is_using_file_path());
        ARC_CHECK_TRUE(doc.is_using_memory());
        ARC_CHECK_FALSE(doc.has_valid_file_data());
        ARC_CHECK_TRUE(doc.has_valid_memory_data());
    }
    LoadFallbackFixture::reset_state();

    ARC_TEST_MESSAGE("Checking non-JSON path, invalid memory");
    for(std::size_t i = 0; i < fixture->non_json_paths.size(); ++i)
    {
        ARC_CHECK_THROW(
            arc::config::Document(
                    fixture->non_json_paths[i],
                    &fixture->invalid[i]
            ),
            arc::ex::ParseError
        );
        ARC_CHECK_TRUE(LoadFallbackFixture::report_callback);
        ARC_CHECK_EQUAL(
            LoadFallbackFixture::report_file_path,
            fixture->non_json_paths[i]
        );
    }
    LoadFallbackFixture::reset_state();
}

//------------------------------------------------------------------------------
//                             VISITOR IMPLEMENTATION
//------------------------------------------------------------------------------

class TestVisitor : public arc::config::Visitor<arc::str::UTF8String>
{
public:

    static TestVisitor& instance()
    {
        static TestVisitor v;
        return v;
    }

    virtual bool retrieve(
            const Json::Value* value,
            const arc::str::UTF8String& key,
            arc::config::Document* requester,
            arc::str::UTF8String& error_message)
    {
        // check type
        if(!value->isString())
        {
            return false;
        }

        m_value = arc::str::UTF8String(value->asCString());
        return true;
    }
};

//------------------------------------------------------------------------------
//                                      GET
//------------------------------------------------------------------------------

class GetFixture : public virtual arc::test::Fixture
{
public:

    //-------------------------PUBLIC STATIC ATTRIBUTES-------------------------

    static bool report_callback;
    static arc::io::sys::Path report_file_path;
    static arc::str::UTF8String report_message;

    //----------------------------CALLBACK FUNCTIONS----------------------------

    static void reporter_func(
            const arc::io::sys::Path& file_path,
            const arc::str::UTF8String& message)
    {
        report_callback = true;
        report_file_path = file_path;
        report_message   = report_message;
    }

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    arc::str::UTF8String key;
    arc::str::UTF8String expected;

    arc::io::sys::Path correct_path;
    arc::io::sys::Path missing_path;
    arc::io::sys::Path incorrect_type_path;
    arc::io::sys::Path invalid_path;

    arc::str::UTF8String correct_mem;
    arc::str::UTF8String missing_mem;
    arc::str::UTF8String incorrect_type_mem;
    arc::str::UTF8String invalid_mem;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        key = "value_1";
        expected = "Hello world!";

        // paths
        correct_path
            << "tests" << "data" << "config" << "get" << "correct.json";
        missing_path
            << "tests" << "data" << "config" << "get" << "missing.json";
        incorrect_type_path
            << "tests" << "data" << "config" << "get" << "incorrect_type.json";
        invalid_path
            << "tests" << "data" << "config" << "get" << "invalid.json";

        // strings
        correct_mem =
            "{"
            "    \"value_1\": \"Hello world!\","
            "    \"value_2\": 175"
            "}";
        missing_mem =
            "{"
            "    \"value_2\": 175"
            "}";
        incorrect_type_mem =
            "{"
            "    \"value_1\": 12,"
            "    \"value_2\": 175"
            "}";
        invalid_mem = "not JSON at all";

        // connect callback
        arc::config::Document::set_get_fallback_reporter(reporter_func);
    }

    static void reset_state()
    {
        report_callback = false;
        report_file_path = arc::io::sys::Path();
        report_message = arc::str::UTF8String();
    }
};

bool GetFixture::report_callback = false;
arc::io::sys::Path GetFixture::report_file_path;
arc::str::UTF8String GetFixture::report_message;

ARC_TEST_UNIT_FIXTURE(get, GetFixture)
{
    ARC_TEST_MESSAGE("Checking get using files only");

    ARC_TEST_MESSAGE("Checking correct data");
    GetFixture::reset_state();
    {
        arc::config::Document doc(fixture->correct_path);
        ARC_CHECK_EQUAL(
            *doc.get(fixture->key, TestVisitor::instance()),
            fixture->expected
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }

    ARC_TEST_MESSAGE("Checking missing key");
    GetFixture::reset_state();
    {
        arc::config::Document doc(fixture->missing_path);
        ARC_CHECK_THROW(
            (*doc.get(fixture->key, TestVisitor::instance())),
            arc::ex::KeyError
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }

    ARC_TEST_MESSAGE("Checking incorrect type");
    GetFixture::reset_state();
    {
        arc::config::Document doc(fixture->incorrect_type_path);
        ARC_CHECK_THROW(
            (*doc.get(fixture->key, TestVisitor::instance())),
            arc::ex::TypeError
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }

    ARC_TEST_MESSAGE("Checking get using memory only");

    ARC_TEST_MESSAGE("Checking correct data");
    GetFixture::reset_state();
    {
        arc::config::Document doc(&fixture->correct_mem);
        ARC_CHECK_EQUAL(
            *doc.get(fixture->key, TestVisitor::instance()),
            fixture->expected
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }

    ARC_TEST_MESSAGE("Checking missing key");
    GetFixture::reset_state();
    {
        arc::config::Document doc(&fixture->missing_mem);
        ARC_CHECK_THROW(
            (*doc.get(fixture->key, TestVisitor::instance())),
            arc::ex::KeyError
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }

    ARC_TEST_MESSAGE("Checking incorrect type");
    GetFixture::reset_state();
    {
        arc::config::Document doc(&fixture->incorrect_type_mem);
        ARC_CHECK_THROW(
            (*doc.get(fixture->key, TestVisitor::instance())),
            arc::ex::TypeError
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }



    ARC_TEST_MESSAGE("Checking valid file and valid memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->correct_path,
            &fixture->correct_mem
        );
        ARC_CHECK_EQUAL(
            *doc.get(fixture->key, TestVisitor::instance()),
            fixture->expected
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }

    ARC_TEST_MESSAGE("Checking valid file and missing memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->correct_path,
            &fixture->missing_mem
        );
        ARC_CHECK_EQUAL(
            *doc.get(fixture->key, TestVisitor::instance()),
            fixture->expected
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }

    ARC_TEST_MESSAGE("Checking valid file and incorrect type memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->correct_path,
            &fixture->incorrect_type_mem
        );
        ARC_CHECK_EQUAL(
            *doc.get(fixture->key, TestVisitor::instance()),
            fixture->expected
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }

    ARC_TEST_MESSAGE("Checking valid file and invalid memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->correct_path,
            &fixture->invalid_mem
        );
        ARC_CHECK_EQUAL(
            *doc.get(fixture->key, TestVisitor::instance()),
            fixture->expected
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }


    ARC_TEST_MESSAGE("Checking missing file and valid memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->missing_path,
            &fixture->correct_mem
        );
        ARC_CHECK_EQUAL(
            *doc.get(fixture->key, TestVisitor::instance()),
            fixture->expected
        );
        ARC_CHECK_TRUE(GetFixture::report_callback);
        ARC_CHECK_EQUAL(GetFixture::report_file_path, fixture->missing_path);
    }

    ARC_TEST_MESSAGE("Checking missing file and missing memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->missing_path,
            &fixture->missing_mem
        );
        ARC_CHECK_THROW(
            (*doc.get(fixture->key, TestVisitor::instance())),
            arc::ex::KeyError
        );
        ARC_CHECK_TRUE(GetFixture::report_callback);
        ARC_CHECK_EQUAL(GetFixture::report_file_path, fixture->missing_path);
    }

    ARC_TEST_MESSAGE("Checking missing file and incorrect type memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->missing_path,
            &fixture->incorrect_type_mem
        );
        ARC_CHECK_THROW(
            (*doc.get(fixture->key, TestVisitor::instance())),
            arc::ex::TypeError
        );
        ARC_CHECK_TRUE(GetFixture::report_callback);
        ARC_CHECK_EQUAL(GetFixture::report_file_path, fixture->missing_path);
    }

    ARC_TEST_MESSAGE("Checking missing file and invalid memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->missing_path,
            &fixture->invalid_mem
        );
        ARC_CHECK_THROW(
            (*doc.get(fixture->key, TestVisitor::instance())),
            arc::ex::KeyError
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }


    ARC_TEST_MESSAGE("Checking incorrect type file and valid memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->incorrect_type_path,
            &fixture->correct_mem
        );
        ARC_CHECK_EQUAL(
            *doc.get(fixture->key, TestVisitor::instance()),
            fixture->expected
        );
        ARC_CHECK_TRUE(GetFixture::report_callback);
        ARC_CHECK_EQUAL(
            GetFixture::report_file_path,
            fixture->incorrect_type_path
        );
    }

    ARC_TEST_MESSAGE("Checking incorrect type file and missing memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->incorrect_type_path,
            &fixture->missing_mem
        );
        ARC_CHECK_THROW(
            (*doc.get(fixture->key, TestVisitor::instance())),
            arc::ex::KeyError
        );
        ARC_CHECK_TRUE(GetFixture::report_callback);
        ARC_CHECK_EQUAL(
            GetFixture::report_file_path,
            fixture->incorrect_type_path
        );
    }

    ARC_TEST_MESSAGE("Checking incorrect type file and incorrect type memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->incorrect_type_path,
            &fixture->incorrect_type_mem
        );
        ARC_CHECK_THROW(
            (*doc.get(fixture->key, TestVisitor::instance())),
            arc::ex::TypeError
        );
        ARC_CHECK_TRUE(GetFixture::report_callback);
        ARC_CHECK_EQUAL(
            GetFixture::report_file_path,
            fixture->incorrect_type_path
        );
    }

    ARC_TEST_MESSAGE("Checking incorrect type file and invalid_mem memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->incorrect_type_path,
            &fixture->invalid_mem
        );
        ARC_CHECK_THROW(
            (*doc.get(fixture->key, TestVisitor::instance())),
            arc::ex::TypeError
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }


    ARC_TEST_MESSAGE("Checking invalid file and valid memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->invalid_path,
            &fixture->correct_mem
        );
        ARC_CHECK_EQUAL(
            *doc.get(fixture->key, TestVisitor::instance()),
            fixture->expected
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }

    ARC_TEST_MESSAGE("Checking invalid file and missing memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->invalid_path,
            &fixture->missing_mem
        );
        ARC_CHECK_THROW(
            (*doc.get(fixture->key, TestVisitor::instance())),
            arc::ex::KeyError
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }

    ARC_TEST_MESSAGE("Checking invalid file and incorrect type memory");
    GetFixture::reset_state();
    {
        arc::config::Document doc(
            fixture->invalid_path,
            &fixture->incorrect_type_mem
        );
        ARC_CHECK_THROW(
            (*doc.get(fixture->key, TestVisitor::instance())),
            arc::ex::TypeError
        );
        ARC_CHECK_FALSE(GetFixture::report_callback);
    }
}

// TODO: check null callback functions

} // namespace anonymous
