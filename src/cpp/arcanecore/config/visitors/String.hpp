/*!
 * \file
 * \brief Visitor objects for retrieving string types from Documents.
 * \author David Saxon
 */
#ifndef ARCANECORE_CONFIG_VISITORS_STRING_HPP_
#define ARCANECORE_CONFIG_VISITORS_STRING_HPP_

#include "arcanecore/config/Document.hpp"
#include "arcanecore/config/Visitor.hpp"


namespace arc
{
namespace config
{

//------------------------------------------------------------------------------
//                               UTF8STRING VISITOR
//------------------------------------------------------------------------------

/*!
 * \brief Visitor object used to retrieve a arc::str::UTF8String from a
 *        arc::config::Document.
 */
class UTF8StringV : public arc::config::Visitor<arc::str::UTF8String>
{
public:

    /*!
     * \brief Provides an existing static instance of this object.
     */
    static UTF8StringV& instance();

    // override
    virtual bool retrieve(
            const Json::Value* data,
            const arc::str::UTF8String& key,
            Document* requester,
            arc::str::UTF8String& error_message);
};

//------------------------------------------------------------------------------
//                           UTF8STRING VECTOR VISITOR
//------------------------------------------------------------------------------

/*!
 * \brief Visitor object used to retrieve a vector of arc::str::UTF8String
 *        objects from a arc::config::Document.
 */
class UTF8StringVectorV :
    public arc::config::Visitor<std::vector<arc::str::UTF8String>>
{
public:

    /*!
     * \brief Provides an existing static instance of this object.
     */
    static UTF8StringVectorV& instance();

    // override
    virtual bool retrieve(
            const Json::Value* data,
            const arc::str::UTF8String& key,
            Document* requester,
            arc::str::UTF8String& error_message);
};

} // namespace config
} // namespace arc

#endif
