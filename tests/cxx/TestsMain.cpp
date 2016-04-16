#include <cstdio>

#include <chaoscore/test/ChaosTest.hpp>

#include <Python.h>

//------------------------------------------------------------------------------
//                                GLOBAL FIXTURES
//------------------------------------------------------------------------------

void init_py_runtime()
{
    Py_Initialize();
}

void end_py_runtime()
{
    Py_Finalize();
}

void generate_file_system_objects()
{
    // get a handle to the generate script
    chaos::uni::UTF8String generate_path(
        "tests/util/generate_file_system_objects.py");
    PyObject* py_generate_path = Py_BuildValue("s", generate_path.get_raw());
    FILE* generate_script = _Py_fopen_obj(py_generate_path, "r+");

    // generate file system objects
    if (generate_script != NULL)
    {
        PyRun_SimpleFile(generate_script, generate_path.get_raw());
    }
}

void destroy_file_system_objects()
{
    // get a handle to the destroy script
    chaos::uni::UTF8String destroy_path(
        "tests/util/destroy_file_system_objects.py");
    PyObject* py_destroy_path = Py_BuildValue("s", destroy_path.get_raw());
    FILE* destroy_script = _Py_fopen_obj(py_destroy_path, "r+");

    // destroy file system objects
    if (destroy_script != NULL)
    {
        PyRun_SimpleFile(destroy_script, destroy_path.get_raw());
    }
}

//------------------------------------------------------------------------------
//                                 MAIN FUNCTION
//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // register the global fixtures
    chaos::test::register_global_fixture(init_py_runtime, end_py_runtime);
    chaos::test::register_global_fixture(destroy_file_system_objects, NULL);
    chaos::test::register_global_fixture(
        generate_file_system_objects,
        destroy_file_system_objects
    );

    // run tests
    return chaos::test::deferred_main(argc, argv);
}
