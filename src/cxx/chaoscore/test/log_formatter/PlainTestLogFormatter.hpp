/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_LOGFORMATTER_PLAINTESTLOGFORMATTER_HPP_
#define CHAOSCORE_TEST_LOGFORMATTER_PLAINTESTLOGFORMATTER_HPP_

#include "chaoscore/test/log_formatter/AbstractTestLogFormatter.hpp"

namespace chaos
{
namespace test
{
namespace log_formatter
{

/*!
 * \brief Test Log Formatter that writes logs in plain text with no decorations
 *        and no formatting.
 */
class PlainTestLogFormatter : public AbstractTestLogFormatter
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new Plain Test Log Formatter.
     */
    PlainTestLogFormatter( std::ostream* stream );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void openLog();

    virtual void closeLog();

    virtual void open_test(
            const chaos::str::UTF8String& path,
            const chaos::str::UTF8String& id );

    virtual void close_test();
};

} // namespace log_formatter
} // namespace test
} // namespace chaos

#endif
