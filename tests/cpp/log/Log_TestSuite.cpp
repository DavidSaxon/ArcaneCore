#include <arcanecore/test/ArcTest.hpp>

ARC_TEST_MODULE(log)

#include <arcanecore/log/LogHandler.hpp>
#include <arcanecore/log/Input.hpp>
#include <arcanecore/log/outputs/FileOutput.hpp>
#include <arcanecore/log/outputs/StdOutput.hpp>

namespace
{

static arc::log::LogHandler test_handler;

static arc::log::Profile log_profile("ArcaneLog", "0.0.1");
static arc::log::Input* logger = test_handler.vend_input(log_profile);

static arc::log::Profile log_profile2("ValgrindPlugin", "1.4.27");
static arc::log::Input* logger2 =
    test_handler.vend_input(log_profile2);


ARC_TEST_UNIT(logging)
{
    // set up the logger
    test_handler.add_output(
        new arc::log::StdOutput(arc::log::VERBOSITY_DEBUG));
    arc::io::sys::Path log_path;
    log_path << "logs" << "log.txt";
    arc::log::FileOutput* file_output =
        new arc::log::FileOutput(log_path, false, arc::log::VERBOSITY_DEBUG);
    test_handler.add_output(file_output);

    logger->critical << "Hello" << std::endl;
    logger2->error << "World" << std::endl;
    logger->warning << 1337 << std::endl;

    file_output->set_enabled(true);

    logger->notice << arc::str::UTF8String("aל∑") << std::endl;
    logger2->info << 12.4F << std::endl;
    logger->debug << "<EOF>" << std::endl;

    file_output->set_enabled(false);

    logger2->critical << "Hello" << std::endl;
    logger->error << "World" << std::endl;
    logger->warning << 1337 << std::endl;

    file_output->set_enabled(true);

    logger->notice << arc::str::UTF8String("aל∑") << std::endl;
    logger->info << 12.4F << std::endl;
    logger2->debug << "<EOF>" << std::endl;

    ARC_CHECK_TRUE(true);
}

} // namespace
