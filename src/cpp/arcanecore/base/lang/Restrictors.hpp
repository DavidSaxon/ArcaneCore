/*!
 * \file
 * \brief Bases classes that can be inherited from to restrict an object's
 *        functionality.
 * \author David Saxon
 */
#ifndef ARCANECORE_BASE_LANG_RESTRICTORS_HPP_
#define ARCANECORE_BASE_LANG_RESTRICTORS_HPP_

namespace arc
{
namespace lang
{

/*!
 * \brief Classes the privately inherit from this class will not be copyable.
 */
class Noncopyable
{
public:

    Noncopyable() {}

private:

    // deleted
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
};

/*!
 * \brief Classes the privately inherit from this class will not be movable.
 */
class Nonmovable
{
public:

    Nonmovable() {}

private:

    // deleted
    Nonmovable(Nonmovable&&) = delete;
    Nonmovable& operator=(Nonmovable&) = delete;
};

/*!
 * \brief Classes the privately inherit from this class will not be comparable.
 */
class Noncomparable
{
public:

    Noncomparable() {}

private:

    // deleted
    bool operator==(const Noncomparable&) = delete;
};

} // namespace lang
} // namespace arc

#endif
