/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_LOGFORMATTER_XMLLOGFORMATTER_HPP_
#define CHAOSCORE_TEST_LOGFORMATTER_XMLLOGFORMATTER_HPP_

#include "chaoscore/test/log_formatter/AbstractTestLogFormatter.hpp"

namespace chaos
{
namespace test
{
namespace log_formatter
{

/*!
 * \brief Test Log Formatter that writes logs as XML.
 */
class XMLTestLogFormatter : public AbstractTestLogFormatter
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new XML Test Log Formatter.
     */
    XMLTestLogFormatter( std::ostream* stream );

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
