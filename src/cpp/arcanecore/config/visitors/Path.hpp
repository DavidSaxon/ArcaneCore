/*!
 * \file
 * \brief Visitor objects for retrieving file system path types from Documents.
 * \author David Saxon
 */
#ifndef ARCANECORE_CONFIG_VISITORS_PATH_HPP_
#define ARCANECORE_CONFIG_VISITORS_PATH_HPP_

#include <arcanecore/io/sys/Path.hpp>

#include "arcanecore/config/Document.hpp"
#include "arcanecore/config/Visitor.hpp"


namespace arc
{
namespace config
{

/*!
 * \brief Visitor object used to retrieve an arc::io::sys::Path from a
 *        arc::config::Document.
 *
 * Paths must be expressed as an array of UTF-8 compatible strings in the
 * document. Paths may references other paths or strings in the same Document
 * using the \@{<other_key>} syntax.
 *
 * Example:
 *
 * \code
 * {
 *     "my_path": ["example", "path", "@{other_path}"],
 *     "other_path": ["another", "path"]
 * }
 * \endcode
 *
 * There is also some extended functionality to reference keys from an external
 * document. Where the external document must be provided to the Visitor and
 * the ```#{<other_ley>}``` syntax is used.
 *
 * Example:
 *
 * \code
 * {
 *     "my_path":  ["example", "path", "#{key_in_another_document}"]
 * }
 * \endcode
 */
class PathV : public arc::config::Visitor<arc::io::sys::Path>
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Constructs a new Path Visitor.
     *
     * \param external_document Pointer to a arc::config::Document to resolve
     *                          external references from.
     */
    PathV(arc::config::Document* external_document = nullptr);

    //--------------------------------------------------------------------------
    //                          PUBLIC STATIC FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Provides an existing static instance of this object.
     *
     * \param external_document Pointer to a arc::config::Document which the
     *                          returned Visitor will use to resolve external
     *                          references.
     */
    static PathV& instance(arc::config::Document* external_document = nullptr);

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    // override
    virtual bool retrieve(
            const Json::Value* data,
            const arc::str::UTF8String& key,
            Document* requester,
            arc::str::UTF8String& error_message);

    /*!
     * \brief Returns a pointer to the arc::config::Document which this Visitor
     *        is using to resolve external references.
     */
    arc::config::Document* get_external_document() const;

    /*!
     * \brief Sets the arc::config::Document that will be used by this Visitor
     *        to resolve external references.
     */
    void set_external_document(arc::config::Document* external_document);

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief Pointer to a Document that can be used to resolve external
     *        references.
     */
    arc::config::Document* m_external;

    /*!
     * \brief Whether this Document is created as part of recursive path
     *        expansion
     */
    bool m_is_recursive;
    /*!
     * \brief List of the keys used as references already as part of the
     *        recursive path expansion.
     */
    std::vector<arc::str::UTF8String> m_visited_refs;
};

//------------------------------------------------------------------------------
//                              PATH VECTOR VISITOR
//------------------------------------------------------------------------------

/*!
 * \brief Visitor object used to retrieve a vector of arc::io::sys::Path objects
 *        from arc::config::Document.
 *
 * See PathV for details.
 */
class PathVectorV : public arc::config::Visitor<std::vector<arc::io::sys::Path>>
{
public:

    /*!
     * \brief Provides an existing static instance of this object.
     */
    static PathVectorV& instance();

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
