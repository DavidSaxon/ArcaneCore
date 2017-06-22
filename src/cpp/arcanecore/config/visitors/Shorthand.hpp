/*!
 * \file
 * \brief Convience defines for including and accessing visitor instances.
 * \author David Saxon
 */
#ifndef ARCANECORE_CONFIG_VISITORS_SHORTHAND_HPP_
#define ARCANECORE_CONFIG_VISITORS_SHORTHAND_HPP_

#include "arcanecore/config/visitors/Path.hpp"
#include "arcanecore/config/visitors/Primitive.hpp"
#include "arcanecore/config/visitors/String.hpp"


/*!
 * \brief Shorthand for arc::config::PathV::instance()
 */
#define AC_PATHV arc::config::PathV::instance()
/*!
 * \brief Shorthand for arc::config::PathVectorV::instance()
 */
#define AC_PATHVECV arc::config::PathVectorV::instance()

/*!
 * \brief Shorthand for arc::config::BoolV::instance()
 */
#define AC_BOOLV arc::config::BoolV::instance()
/*!
 * \brief Shorthand for arc::config::BoolVectorV::instance()
 */
#define AC_BOOLVECV arc::config::BoolVectorV::instance()
/*!
 * \brief Shorthand for arc::config::IntV<IntType>::instance()
 */
#define AC_INTV(IntType) arc::config::IntV<IntType>::instance()
/*!
 * \brief Shorthand for arc::config::IntVectorV<IntType>::instance()
 */
#define AC_INTVECV(IntType) arc::config::IntVectorV<IntType>::instance()
/*!
 * \brief Shorthand for arc::config::FloatV<FloatType>::instance()
 */
#define AC_FLOATV(FloatType) arc::config::FloatV<FloatType>::instance()
/*!
 * \brief Shorthand for arc::config::FloatVectorV<FloatType>::instance()
 */
#define AC_FLOATVECV(FloatType) arc::config::FloatVectorV<FloatType>::instance()

/*!
 * \brief Shorthand for arc::config::UTF8StringV::instance()
 */
#define AC_U8STRV arc::config::UTF8StringV::instance()
/*!
 * \brief Shorthand for arc::config::UTF8StringVectorV::instance()
 */
#define AC_U8STRVECV arc::config::UTF8StringVectorV::instance()

#endif
