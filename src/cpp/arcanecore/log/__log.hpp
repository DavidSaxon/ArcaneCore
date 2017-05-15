#ifndef ARCANECORE_LOG_HPP_
#define ARCANECORE_LOG_HPP_

namespace arc
{

/*!
 * \brief Global namespace that contains all ArcaneCore logging functionality.
 *
 * ArcaneCore's logging is designed to be a generic log facility which provides
 * for support multiple inputs connected to multiple outputs.
 *
 * \par Overview
 *
 * ArcaneCore's logging uses the arc::log::LogHandler object to connect
 * arc::log::Input objects and arc::log::AbstractOutput objects. An input will
 * write to all outputs connected to the same arc::log::LogHandler. A
 * pre-existing arc::log::LogHandler is provided with ArcaneCore's logging:
 * arc::log::shared_handler. This handler initially has no inputs or outputs
 * connected. Providing a default handler means that multiple libraries or
 * sections of an application can link against ArcaneCore logging and share the
 * same logging facility and add their own inputs and outputs.
 *
 * \par Example Usage
 *
 * In this example we have an application that requires two logging inputs, one
 * for the application core, and one for the GUI. In this example will use a
 * global pointer for each input and set up the logging facilities in a function
 * called ```init_logging```.
 *
 * The first step is to vend pointers to the input objects using two different
 * arc::log::Profile objects.
 *
 * \code
 * #include <arcanecore/log/Shared.hpp>
 *
 * arc::log::Input* core_logger;
 * arc::log::Input* gui_logger;
 *
 * void init_logging()
 * {
 *     // add an input for the core application
 *     arc::log::Profile core_profile("MyApp::core");
 *     core_logger = arc::log::shared_handler.vend_input(core_profile);
 *
 *     // add an input for the application's GUI
 *     arc::log::Profile gui_profile("MyApp::gui");
 *     gui_logger = arc::log::shared_handler.vend_input(gui_profile);
 * }
 * \endcode
 *
 * At this stage we could write to our newly created inputs, but it would have
 * no effect since there are no outputs connected. So next two logging outputs
 * will be connected. The first is an arc::log::StdOutput which outputs logging
 * messages to ```stdout``` (notice, info, and debug) and to ```stderr```
 * (critical, error, and warning). The second will be an arc::log::FileOutput
 * which writes logging messages to a file on disk.
 *
 * \code
 * #include <arcanecore/log/Shared.hpp>
 * #include <arcanecore/log/outputs/StdOutput.hpp>
 * #include <arcanecore/log/outputs/StdOutput.hpp>
 *
 * ...
 *
 * void init_logging()
 * {
 *     ...
 *
 *     // add a library provided output that will write messages to std::cout
 *     // and std::cerr. The log handler will handle deleting the stdout_writer.
 *     arc::log::StdOutput* stdout_writer = new arc::log::StdOutput();
 *     arc::log::shared_handler.add_output(stdout_writer);
 *
 *     // create the path the FileOutput will write to
 *     arc::io::sys::Path log_path;
 *     log_path << "logs" << "example.log";
 *     // add a library provided output that will write messages to a file on
 *     // disk.
 *     arc::log::FileOutput* file_writer =
 *         new arc::log::FileOutput(log_path, false, arc::log::VERBOSITY_DEBUG);
 *     arc::log::shared_handler.add_output(file_writer);
 *
 *     // will write the following message to std::cout and disk:
 *     // {MyApp::core} - [NOTICE]: Hello world!
 *     core_logger->notice << "Hello world!" << std::endl;
 *
 *     // will write the following message to std::cerr and disk:
 *     // {MyApp::gui} - [ERROR]: Example error.
 *     gui_logger->error << "Example error." << std::endl;
 * }
 * \endcode
 *
 * Output writers can individually have their verbosity changed or be completely
 * disabled:
 *
 * \code
 *
 * ...
 *
 * void init_logging()
 * {
 *     ...
 *
 *     stdout_writer.set_verbosity_level(arc::log::VERBOSITY_INFO);
 *
 *     // this message will be output to std::cout
 *     core_logger->info << "Hello world!" << std::endl;
 *
 *     // this message will not be output std::cout
 *     gui_logger->debug << "Some debug information." << std::endl;
 *
 *     // turn off all output
 *     stdout_writer.set_enabled(false);
 * }
 * \endcode
 */
namespace log
{
} // namespace log

} // namespace arc

#endif
