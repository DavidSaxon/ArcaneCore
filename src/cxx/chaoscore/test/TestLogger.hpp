/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_TESTLOGGER_HPP_
#define CHAOSCORE_TEST_TESTLOGGER_HPP_

#include <iosfwd>
#include <map>
#include <vector>

#include "chaoscore/base/string/UTF8String.hpp"

namespace chaos
{
namespace test
{

//------------------------------------------------------------------------------
//                             FORWARD DECELERATIONS
//------------------------------------------------------------------------------

namespace log_formatter
{
    class AbstractTestLogFormatter;
} // namespace log_formatter

/*!
 * \internal
 *
 * \brief Interface used for managing the different loggers being used.
 */
class TestLogger
{
private:

    CHAOS_DISALLOW_COPY_AND_ASSIGN( TestLogger );

public:

    //--------------------------------------------------------------------------
    //                                ENUMERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief The different possible log outputs
     */
    enum OutFormat
    {
        /// Output plain text with no decoration or formatting.
        OUT_PLAIN_TEXT,
        /// Output plain text with decoration and formatting.
        OUT_PRETTY_TEXT,
        /// Output in XML format.
        OUT_XML,
        /// Output in HTML format for viewing in a web browser.
        OUT_HTML
    };

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Constructs a test logger interface.
     *
     * By default the logger has no defined outputs.
     */
    TestLogger();

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~TestLogger();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Sets this logger as the parent logger.
     *
     * There should be only one parent  logger. The parent logger will merge in
     * any sub logs made child processes and will also handle actions like
     * opening and closing the log.
     */
    void set_as_parent( bool state );

    /*!
     * \brief Adds a standard output for writing.
     *
     * \warning Currently writing to only one standard output is supported.
     *          Calling this function multiple times will result in an
     *          exception. TODO:
     *
     * \param verbosity The verbosity level of standard output.
     * \param format The format to write standard output in.
     */
    void add_stdout( chaos::uint16 verbosity, OutFormat format );

    /*!
     * \brief Adds a file output for writing.
     *
     * \param path Full path to the file to write to. This path does not need to
     *             exist beforehand.
     * \param verbosity The verbosity level of the file output.
     * \param format The format to write to the file in.
     */
    void add_file_output(
            const chaos::str::UTF8String& path,
                  chaos::uint16           verbosity,
                  OutFormat               format );

    /*!
     * \brief Opening statement of the log.
     */
    void open_log();

    /*!
     * \brief Closing statement of the log.
     */
    void close_log();

    /*!
     * \brief Opening statement of a unit test.
     *
     * \param path The Path of this test
     * \param id The unique id of this test.
     */
    void open_test(
            const chaos::str::UTF8String& path,
            const chaos::str::UTF8String& id );

    /*!
     * \brief Closing of a unit test.
     *
     * \param id The unique id of this test.
     */
    void close_test( const chaos::str::UTF8String& id );

    /*!
     * \brief Reports a test success.
     *
     * \param type the Type of test that succeed.
     * \param file The source file that the success occurred in.
     * \param line The line in the file that success occurred at.
     */
    void report_success(
            const chaos::str::UTF8String& type,
            const chaos::str::UTF8String& file,
                  chaos::int32            line );

    /*!
     * \brief Reports a test failure.
     *
     * \param type the Type of test that failed.
     * \param file The source file that the failure occurred in.
     * \param line The line in the file that failure occurred at.
     * \param message A message that was provided with the failure.
     */
    void report_failure(
            const chaos::str::UTF8String& type,
            const chaos::str::UTF8String& file,
                  chaos::int32            line,
            const chaos::str::UTF8String& message );

    /*!
     * \brief Finalises reports for a unit test
     */
    void finialise_test_report();

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief Whether this is the parent logger or not.
     */
    bool m_is_parent;

    /*!
     * \brief List of TestLogFormatters being used by this logger.
     */
    std::vector< log_formatter::AbstractTestLogFormatter* > m_formatters;
    /*!
     * \brief Whether the logger is using the standard output stream.
     */
    bool m_using_stdout;
    /*!
     * \brief Mapping from filenames to the streams writing to them.
     */
    std::map< chaos::str::UTF8String, std::ostream* > m_file_streams;

    /*!
     * \brief The number of test successes in the current unit.
     */
    chaos::uint64 m_success_count;
    /*!
     * \brief The number of test failures in the current unit.
     */
    chaos::uint64 m_failure_count;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Internal function for creating and storing a formatter for the
     *        given stream and format.
     */
    void create_formatter(
            std::ostream* stream,
            chaos::uint8  verbosity,
            OutFormat     format,
            bool          is_stdout = false );
};

} // namespace test
} // namespace chaos

#endif
