/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_LOGFORMATTER_HTMLLOGFORMATTER_HPP_
#define CHAOSCORE_TEST_LOGFORMATTER_HTMLLOGFORMATTER_HPP_

#include "chaoscore/test/log_formatter/AbstractTestLogFormatter.hpp"

namespace chaos
{
namespace test
{
namespace log_formatter
{

/*!
 * \brief Test Log Formatter that writes logs as HTML.
 */
class HTMLTestLogFormatter : public AbstractTestLogFormatter
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new HTML Test Log Formatter.
     */
    HTMLTestLogFormatter( std::ostream* stream );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void openLog();

    virtual void closeLog();
};

} // namespace log_formatter
} // namespace test
} // namespace chaos

#endif
