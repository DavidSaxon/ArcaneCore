#include <chaoscore/test/ChaosTest.hpp>

int main(int argc, char* argv[])
{
    // TODO: ensure the file system has been torn down
    //generate testing file system objects
    system("tests/util/generate_file_system_objects.sh");

    return chaos::test::deferred_main(argc, argv);
}
