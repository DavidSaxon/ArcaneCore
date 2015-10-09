/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_TESTLOGGER_HPP_
#define CHAOSCORE_TEST_TESTLOGGER_HPP_

#include <fstream>
#include <vector>

#include "chaoscore/base/string/UTF8String.hpp"

namespace chaos
{
namespace test
{

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
        PLAIN_TEXT,
        /// Output plain text with decoration and formatting.
        PRETTY_TEXT,
        /// Output in XML format.
        XML,
        /// Output in HTML format for viewing in a web browser.
        HTML
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

private:

    //--------------------------------------------------------------------------
    //                            PRIVATE INNER STRUCT
    //--------------------------------------------------------------------------

    /*!
     * \brief Internal structure for storing file streams and the format to
     *        write to them in.
     */
    struct FileStreamInfo
    {
        //--------------------------PUBLIC ATTRIBUTES---------------------------

        std::ofstream* stream;
        OutFormat format;

        //------------------------------CONSTRUTOR------------------------------

        FileStreamInfo( std::ofstream* a_stream, OutFormat a_format )
            :
            stream( a_stream ),
            format( a_format )
        {
        }

        //------------------------------DESTRUCTOR------------------------------

        ~FileStreamInfo()
        {
            delete stream;
        }
    };

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief Whether the logger is using the standard output stream.
     */
    bool m_usingStdout;
    /*!
     * \brief the format of the standard stream output.
     */
    OutFormat m_stdoutFormat;

    /*!
     * \brief List of the file streams being used by this logger.
     */
    std::vector< FileStreamInfo* > m_fileStreams;
};

} // namespace test
} // namespace chaos

#endif
