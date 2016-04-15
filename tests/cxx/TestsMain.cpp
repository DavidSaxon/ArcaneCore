#include <chaoscore/test/ChaosTest.hpp>

int main(int argc, char* argv[])
{
    // make sure there are no file system test objects to start with
    system("tests/util/destroy_file_system_objects.sh");
    //generate testing file system objects
    system("tests/util/generate_file_system_objects.sh");

    int rc = chaos::test::deferred_main(argc, argv);

    // clean up file system test objects
    system("tests/util/destroy_file_system_objects.sh");

    return rc;
}
