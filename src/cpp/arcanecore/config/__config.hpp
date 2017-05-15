#ifndef ARCANECORE_CONFIG_HPP_
#define ARCANECORE_CONFIG_HPP_

namespace arc
{

/*!
 * \brief the global namespace for ArcaneCore's config API.
 *
 * ArcaneCore's config is a JSON wrapper for loading and accessing configuration
 * data using the Visitor Pattern.
 *
 * \par Purpose of ArcaneCore Config
 *
 * ArcaneCore Config is designed for storing program runtime configuration data
 * that can be stored outside of the source code, therefore program behavior can
 * be modified without requiring recompilation.
 * By default Config reads JSON data from the file system, but provides methods
 * for sourcing "fallback" JSON data stored within program memory. This means
 * applications using Config can be fail safe since if there is an unexpected
 * error with the file system data, access will fallback to the data in memory,
 * and provide handlers to report the failure.
 * Some applications may not desire to expose the editable file system data in
 * production releases, for which Config can be initialised to only use the
 * in-memory data.
 *
 * TODO: using the ArcaneCore Config inliner script
 *
 * \par Loading Data
 *
 * For the following examples we will assume there is a file
 * called ```config/resources.json``` and an ```arc::str::UTF8String``` in the
 * runtime called ```resources_inline``` that both contain this JSON data:
 *
 * \code
 * {
 *     "app_name": "ArcaneCore Config Example",
 *     "resource_path": ["res"],
 *     "gui_resource_path": ["@{resource_path}", "gui"],
 *     "fonts":
 *     {
 *         "resource_path": ["@{gui_resource_path}", "fonts"],
 *         "default_font": "Roboto Th",
 *         "default_size": 10,
 *         "default_colour": [255, 120, 0]
 *     }
 * }
 * \endcode
 *
 * We will also assume the ArcaneCore Config setup is done in a function
 * called ```init_config```.
 *
 * Loading and storing the data is done by constructing a arc::config::Document:
 *
 * \code
 * void init_config()
 * {
 *     arc::io::sys::Path resource_path;
 *     resource_path << "config" << "resources.json";
 *
 *     // loads the Document from the file on disk
 *     arc::config::Document file_doc(resource_path);
 *
 *     // loads the Document from application memory
 *     arc::config::Document mem_doc(&resources_inline);
 *
 *     // loads the Document from both the file system and application memory
 *     arc::config::Document fallback_doc(resource_path, &resources_inline);
 * }
 * \endcode
 *
 * In the above example, if either the ```file_doc``` or the ```mem_doc``` fail
 * to load their data, an exception will be raised immediately. However if
 * the ```fallback_doc``` fails to load its data from the file or memory a
 * failure callback will be triggered, and only if loading from both sources
 * fails then an exception will be raised.
 *
 * The following example shows connecting a failure reporter to report if
 * loading from one of the sources fails:
 *
 * \code
 * #include <iostream>
 *
 * void config_load_reporter(
 *         const arc::io::sys::Path& file_path,
 *         const arc::str::UTF8String& message)
 * {
 *     std::cerr << message << std::endl;
 * }
 *
 * void init_config()
 * {
 *     // connect the load failure function
 *     arc::config::Document::set_load_fallback_reporter(config_load_reporter);
 *
 *     arc::io::sys::Path resource_path;
 *     resource_path << "config" << "resources.json";
 *
 *     // loads the Document from both the file system and application memory
 *     arc::config::Document fallback_doc(resource_path, &resources_inline);
 * }
 * \endcode
 *
 * Now if loading the data from the file or from memory fails,
 * the ```config_load_reporter``` function will be called and will print the
 * reason for failure to stderr.
 *
 * \par Accessing Data
 *
 * To access data from the document, the Visitor pattern is used to retrieve
 * values as useful types. ArcaneCore Config comes with a built-in set of
 * Visitors, but the arc::config::Visitor type can be derived from to implement
 * the retrieval of other types.
 * All Visitors should provide a static ```instance()``` function (although it
 * is not required for user-implemented Visitors) which can be used to get an
 * existing static instance of the Visitor type. All visitors provide a ```*```
 * operator which can be used to extract the Visitor's value as the expected
 * type.
 *
 * In the following example we will use built-in Visitors to retrieve some
 * values:
 *
 * \code
 * void init_config()
 * {
 *     ...
 *
 *     // app will contain "ArcaneCore Config Example"
 *     arc::str::UTF8String app(
 *         *fallback_doc.get("app_name", arc::config::UTF8StringV::instance()));
 *
 *     // font_size will contain 10. Notice the . symbol is used to retrieve
 *     // nested values, and the IntV visitor expects a template type to define
 *     // the integral type
 *     arc::uint32 font_size = *fallback_doc.get(
 *         "fonts.default_size",
 *         arc::config::IntV<arc::uint32>::instance()
 *     );
 *
 *     // font_colour will contain [255, 120, 0]
 *     std::vector<arc::uint8> font_colour(*fallback_doc.get(
 *         "fonts.default_colour",
 *         arc::config::IntVectorV<arc::uint8>::instance()
 *     ));
 *
 *     // The PathV visitor provides it's own syntax, in which elements with the
 *     // patten: @{<key>} will be resolved to other valid paths or strings in
 *     // the same Document with the key. Therefore gui_resource_path will
 *     // contain: "res/gui/fonts"
 *     arc::io::sys::Path gui_resource_path(*fallback_doc.get(
 *          "fonts.gui_resource_path",
 *          arc::config::PathV::instance()
 *     ));
 * }
 * \endcode
 *
 * If the arc::config::Document is using data from both the file system and from
 * memory the fall-back protocol will be used when retrieving values. This
 * means if a value is requested from the Document, but there is no entry with
 * the key, or the data cannot be converted by the provided Visitor, the
 * Document will trigger a reporter callback, and then proceed to retrieve the
 * value from memory instead. Only if both of these operations fail will an
 * exception be raised.
 *
 * The following example shows connecting a failure reporter to report if
 * retrieving a value from data loaded from the file system fails:
 *
 * \code
 * #include <iostream>
 *
 * void config_get_reporter(
 *         const arc::io::sys::Path& file_path,
 *         const arc::str::UTF8String& message)
 * {
 *     std::cerr << message << std::endl;
 * }
 *
 * void init_config()
 * {
 *     // connect the get failure function
 *     arc::config::Document::set_get_fallback_reporter(config_get_reporter);
 *
 *     ...
 * }
 * \endcode
 *
 * ArcaneCore Config also supports an extended implementation of the
 * arc::config::Document object: arc::config::Variant. Variants work much the
 * same way as Documents except they take a base file path, and variants of this
 * file path are used to access data. The arc::config::Variant has a default
 * variant which is always loaded, and a current variant which may or may not be
 * the default variant. Data will first be attempted to be retrieved from the
 * current file path variant, if this fails it will try access the data from the
 * default variant, and finally if this fails and the arc::config::Variant has
 * data loaded from memory it will attempt to access it from here. Variants are
 * intended to be used to support multiple language representations of string
 * data, but can be used for any other relevant use.
 *
 * For example we have a file called ```config/lang.uk.json``` which contains
 * the data:
 *
 * \code
 * {
 *     "string": "hello_world",
 *     "sentence": "This is a language variant."
 * }
 * \endcode
 *
 * And another file called ```config/lang.de.json``` which contains the data:
 *
 * \code
 * {
 *     "string": "hallo_welt"
 * }
 * \endcode
 *
 *
 * We will use the uk variant as the default which will cause it to be loaded
 * initially:
 *
 * \code
 * // we leave uk and de out of the file path since these are variants
 * arc::io::sys::Path base_path;
 * base_path << "config" << "lang.json";
 *
 * // using uk as the default variant which will load from config/lang.uk.json
 * arc::config::Variant lang_var(base_path, "uk");
 *
 * // returns "hello_world"
 * *lang_var.get("string", arc::config::UTF8StringV::instance()));
 * // returns "This is a language variant."
 * *lang_var.get("sentence", arc::config::UTF8StringV::instance()));
 * \endcode
 *
 * The arc::config::Variant::set_variant function can be used to change the
 * current variant (which is currently the default variant: "uk"). Changing the
 * current variant will cause the new file variant to be loaded, however the
 * default variant will remain loaded and will be used to fallback to if data
 * cannot be accessed from the current variant:
 *
 * \code
 * // changing to the de variant will load data from config/lang.de.json
 * lang_var.set_variant("de");
 *
 * // returns "hallo_welt"
 * *lang_var.get("string", arc::config::UTF8StringV::instance()));
 * // returns "This is a language variant." from the uk variant since the
 * // "sentence" key doesn't exist in the de variant file.
 * *lang_var.get("sentence", arc::config::UTF8StringV::instance()));
 * \endcode
 */
namespace config
{
} // namespace config

} // namespace arc

#endif
