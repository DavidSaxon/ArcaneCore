/*!
 * \file
 * \brief Documents the arc::col namespace.
 * \author David Saxon
 */
#ifndef ARCANECOLLATE_HPP_
#define ARCANECOLLATE_HPP_

namespace arc
{

/*!
 \brief The global module of ArcaneCore's collate API.
 *
 * ArcaneCore's collate provides functionality for writing and reading
 * application resource files into collated files that contain multiple or all
 * of the application's resources. An API is provided for both writing and
 * reading from from collated files and for convenience a command line tool is
 * supplied to write collated files.
 *
 * \par Technical Overview
 *
 * Collate works by collating resources (files on disk) into a single collated
 * file. This file may be broken into smaller subfiles referred to as pages,
 * however these pages still make a contiguous block of data, so these multiple
 * pages are still considered to be a single collated file. In order to locate
 * resources in collated files a separate file called the Table of Contents
 * exists that stores a mapping from resources to their location in a collated
 * file. A Table of Contents may contain resources that are from multiple
 * collated files.
 *
 * \par Using the Command Line Tool to Write Collated Files.
 *
 * The command line tool can be used to write one or more collated files
 * from existing resources on disk, and generate a Table of Contents denoting
 * the location of resources in the collated files.
 *
 * A path to the Table of Contents to generate must be specified using
 * the ```--table_of_contents``` argument, and at least one collated file must
 * be defined using the ```--collate_begin``` and ```--collate_end``` arguments.
 *
 * Example usage:
 *
 * \code
 * arc_collate_tool --table_of_contents res/locations.toc --collate_begin
       res/images.arccol res/images/logo.png res/images/textures/ --collate_end
       --collate_begin res/fonts.arccol res/fonts/font_1.ttf
       res/fonts/font_2.ttf --collate_end
 * \endcode
 *
 * The above command will generate 3 new files: ```res/locations.toc``` the
 * Table of Contents which describes where resources are located in collated
 * files, ```res/images.arccol.0``` a collated file containing
 * images, and ```res/fonts.arccol.0``` a collated file containing fonts. The
 * other file paths in the command are the paths of resources to write to the
 * related collated files. If a file is specified here,
 * i.e. ```res/images/logo.png``` that exact file is written to the collated
 * file. If a directory is specified i.e. ``` res/images/textures/``` all files
 * within the directory are written to the collated file.
 *
 * Note that collated files produced by this command ```res/images.arccol.0```
 * and ```res/fonts.arccol.0``` have ```.0``` appended to the end of the path
 * that was specified for them: this is the page number. By default, collated
 * files have no size limit on them, but using the ```--page_size``` argument a
 * size limit on collated files can be enforced. The size limit is implemented
 * by splitting the collated file across sub files, each with their page number
 * appended to the end of the collated path, i.e. ```.0```, ```.1```, ```.2```
 * and so on. In the example command no page limit is set, but by a matter of
 * convention the page number is still appended to the end of the collated file
 * path.
 *
 * \par Writing using the API
 *
 * Writing collated files using the API requires at least two objects:
 * arc::col::TableOfContents and one or more arc::col::Collator.
 *
 * The first step is to create the arc::col::TableOfContents which will store
 * the resource locations, and eventually generate the Table of Contents file on
 * disk. First we will create the arc::col::TableOfContents with the file path
 * we want the Table of Contents file to be written to:
 *
 * \code
 * arc::io::sys::Path toc_path;
 * toc_path << "res" << "locations.toc";
 * arc::col::TableOfContents toc(toc_path);
 * \endcode
 *
 * Like the command line tool example, in this example we will write two
 * collated files, one for images and one for fonts. To do this we will need to
 * generate arc::col::Collator objects for each. These objects take at least the
 * pointer to the arc::col::TableOfContents to record the locations of
 * resources, and the path to the collated file to write (this should not
 * include the page index extension).
 *
 * \code
 * arc::io::sys::Path images_path;
 * images_path << "res" << "images.arccol";
 * arc::col::Collator images_collator(&toc, images_path);
 *
 * arc::io::sys::Path fonts_path;
 * fonts_path << "res" << "fonts.arccol";
 * arc::col::Collator fonts_collator(&toc, fonts_path);
 * \endcode
 *
 * The next step is to add the resources to each arc::col::Collator:
 *
 * \code
 * arc::io::sys::Path logo_path;
 * logo_path << "res" << "images" << "logo.png";
 * images_collator.add_resource(logo_path);
 *
 * arc::io::sys::Path textures_path;
 * textures_path << "res" << "images" << "textures";
 * images_collator.add_resource(textures_path);
 *
 * arc::io::sys::Path font_1_path;
 * font_1_path << "res" << "fonts" << "font_1.ttf";
 * fonts_collator.add_resource(font_1_path);
 *
 * arc::io::sys::Path font_2_path;
 * font_2_path << "res" << "fonts" << "font_2.ttf";
 * fonts_collator.add_resource(font_2_path);
 * \endcode
 *
 * The final step is to actually performing the writing of the collated files
 * and the Table of Contents. Note that the arc::col::Collator::execute()
 * functions should be called before the arc::col::TableOfContents::write()
 * function.
 *
 * \code
 * images_collator.execute();
 * fonts_collator.execute();
 *
 * toc.write();
 * \endcode
 *
 * \par Reading using the API
 *
 * In order to read from collated files we must use a arc::col::Accessor to load
 * the Table of Contents file and access the locations of resources in collated
 * files:
 *
 * \code
 * arc::io::sys::Path toc_path;
 * toc_path << "res" << "locations.toc";
 * arc::col::Accessor accessor(toc_path);
 * \endcode
 *
 * Here we could use the arc::col::Accessor::get_resource() function to find
 * information about where to find the resource in a collated file and manually
 * read the subsection of the collated file to get the resource data.
 * However this proccess can be quite complicated since if a collated file is
 * broken into smaller pages a resource's data may exist in more than one file
 * on disk (however the resource's data is always contiguous within the pages).
 *
 * Collate provides the arc::col::Reader object to handle reading resources from
 * collated files. arc::col::Reader inherits from arc::io::sys::FileReader so
 * provides a familiar interface, and can be treated like any other reader. In
 * order to open an arc::col::Reader to a resource we must provide it with an
 * arc::col::Accessor object which represents the Table of Contents and the path
 * to the resource to read:
 *
 * \code
 * arc::io::sys::Path logo_path;
 * logo_path << "res" << "images" << "logo.png";
 * arc::col::Reader image_reader(logo_path, &accessor);
 * \endcode
 *
 * If the resource does not exist in the accessor's Table of Contents the
 * resource will simply be read from its real file path. From here we can use
 * any of the common file reader functions to access the data in the resource.
 * i.e. tell, seek, eof, read() etc.
 */
namespace col
{
} // namespace col

} // namespace arc

#endif
