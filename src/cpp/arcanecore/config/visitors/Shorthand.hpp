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
#define ME_PATHV arc::config::PathV::instance()
/*!
 * \brief Shorthand for arc::config::PathVectorV::instance()
 */
#define ME_PATHVECV arc::config::PathVectorV::instance()

/*!
 * \brief Shorthand for arc::config::BoolV::instance()
 */
#define ME_BOOLV arc::config::BoolV::instance()
/*!
 * \brief Shorthand for arc::config::BoolVectorV::instance()
 */
#define ME_BOOLVECV arc::config::BoolVectorV::instance()
/*!
 * \brief Shorthand for arc::config::IntV<IntType>::instance()
 */
#define ME_INTV(IntType) arc::config::IntV<IntType>::instance()
/*!
 * \brief Shorthand for arc::config::IntVectorV<IntType>::instance()
 */
#define ME_INTVECV(IntType) arc::config::IntVectorV<IntType>::instance()
/*!
 * \brief Shorthand for arc::config::FloatV<FloatType>::instance()
 */
#define ME_FLOATV(FloatType) arc::config::FloatV<FloatType>::instance()
/*!
 * \brief Shorthand for arc::config::FloatVectorV<FloatType>::instance()
 */
#define ME_FLOATVECV(FloatType) arc::config::FloatVectorV<FloatType>::instance()

/*!
 * \brief Shorthand for arc::config::UTF8StringV::instance()
 */
#define ME_U8STRV arc::config::UTF8StringV::instance()
/*!
 * \brief Shorthand for arc::config::UTF8StringVectorV::instance()
 */
#define ME_U8STRVECV arc::config::UTF8StringVectorV::instance()

#endif
