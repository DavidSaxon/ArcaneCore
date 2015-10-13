/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_TESTLOGGER_HPP_
#define CHAOSCORE_TEST_TESTLOGGER_HPP_

#include <iosfwd>
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
     * \brief Adds a standard output for writing.
     *
     * \warning Currently writing to only one standard output is supported.
     *          Calling this function multiple times will result in an
     *          exception. TODO:
     *
     * \param format The format to write standard output in.
     */
    void addStdOut( OutFormat format );

    /*!
     * \brief Adds a file output for writing.
     *
     * \param path Full path to the file to write to. This path does not need to
     *             exist beforehand.
     * \param format The format to write to the file in.
     */
    void addFileOutput( const chaos::str::UTF8String& path, OutFormat format );

    /*!
     * \brief Opening statement of the log.
     */
    void openLog();

    /*!
     * \brief Closing statement of the log.
     */
    void closeLog();

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief List of TestLogFormatters being used by this logger.
     */
    std::vector< log_formatter::AbstractTestLogFormatter* > m_formatters;
    /*!
     * \brief Whether the logger is using the standard output stream.
     */
    bool m_usingStdout;
    /*!
     * \brief List of open file streams so they can be deleted at destruction
     *        time.
     */
    std::vector< std::ostream* > m_fileStreams;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Internal function for creating and storing a formatter for the
     *        given stream and format.
     */
    void createFormatter( std::ostream* stream, OutFormat format );
};

} // namespace test
} // namespace chaos

#endif
