#include <cstdio>

#include <chaoscore/test/ChaosTest.hpp>

#include <Python.h>

int main(int argc, char* argv[])
{
    // we're going to use python to do setup and teardown
    Py_Initialize();

    // get a handle to the generate script
    chaos::uni::UTF8String generate_path(
        "tests/util/generate_file_system_objects.py");
    PyObject* py_generate_path = Py_BuildValue("s", generate_path.get_raw());
    FILE* generate_script = _Py_fopen_obj(py_generate_path, "r+");

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
    // generate file system objects
    if (generate_script != NULL)
    {
        PyRun_SimpleFile(generate_script, generate_path.get_raw());
    }

    // run tests
    int rc = chaos::test::deferred_main(argc, argv);

    // regain the handle to the destroy script
    py_destroy_path = Py_BuildValue("s", destroy_path.get_raw());
    destroy_script = _Py_fopen_obj(py_destroy_path, "r+");

    // destroy file system objects
    if (destroy_script != NULL)
    {
        PyRun_SimpleFile(destroy_script, destroy_path.get_raw());
    }

    // cleanup Python runtime
    Py_Finalize();

    return rc;
}
