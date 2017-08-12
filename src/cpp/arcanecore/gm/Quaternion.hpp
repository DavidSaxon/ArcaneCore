/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_GM_QUATERNION_HPP_
#define ARCANECORE_GM_QUATERNION_HPP_

#include "arcanecore/gm/Vector.hpp"


namespace arc
{
namespace gm
{

/*!
 * \brief TODO: comment
 */
template<typename T_scalar, bool T_use_simd = false>
class Quaternion
    : public arc::memory::AlignedBase<Quaternion<T_scalar, T_use_simd>>
{
public:

    //--------------------------------------------------------------------------
    //                            TYPEDEF DEFINITIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief The storage object this quaternion is using.
     */
    typedef VectorStorage<T_scalar, 4, T_use_simd> Storage;
    /*!
     * \brief The simd data of this object (if valid).
     */
    typedef typename VectorStorage<T_scalar, 4, T_use_simd>::SimdData SimdType;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new Quaternion initialised to [0, 0, 0, 1].
     */
    Quaternion()
    {
        x() = 0;
        y() = 0;
        z() = 0;
        w() = 1;
    }

    /*!
     * \brief Creates a new Quaternion initialised with the four given x, y, z,
     *        and w values.
     */
    Quaternion(T_scalar x_, T_scalar y_, T_scalar z_, T_scalar w_)
    {
        x() = x_;
        y() = y_;
        z() = z_;
        w() = w_;
    }

    // TODO: implement this properly if it's ever needed - needs to take
    //       rotation order into account
    //       - could be useful for "compressing" quaternions into 3 floats
    // /*!
    //  * \brief Creates a new quaternion from the given euler angle (in radians)
    //  */
    // template<bool T_other_use_simd>
    // Quaternion(const arc::gm::Vector<T_scalar, 3, T_other_use_simd>& euler)
    // {
    //     T_scalar t0 = std::cos(euler[1] * static_cast<T_scalar>(0.5));
    //     T_scalar t1 = std::sin(euler[1] * static_cast<T_scalar>(0.5));
    //     T_scalar t2 = std::cos(euler[2] * static_cast<T_scalar>(0.5));
    //     T_scalar t3 = std::sin(euler[2] * static_cast<T_scalar>(0.5));
    //     T_scalar t4 = std::cos(euler[0] * static_cast<T_scalar>(0.5));
    //     T_scalar t5 = std::sin(euler[0] * static_cast<T_scalar>(0.5));

    //     x() = t0 * t3 * t4 - t1 * t2 * t5;
    //     y() = t0 * t2 * t5 + t1 * t3 * t4;
    //     z() = t1 * t2 * t4 - t0 * t3 * t5;
    //     w() = t0 * t2 * t4 + t1 * t3 * t5;
    // }

    /*!
     * \brief Creates a new quaternion from the given rotation angle (in
     *        radians) and rotation axis.
     */
    template<bool T_other_use_simd>
    Quaternion(
        T_scalar angle,
        const arc::gm::Vector<T_scalar, 3, T_other_use_simd>& axis)
    {
        x() = axis.x() * std::sin(angle / static_cast<T_scalar>(2));
        y() = axis.y() * std::sin(angle / static_cast<T_scalar>(2));
        z() = axis.z() * std::sin(angle / static_cast<T_scalar>(2));
        w() = std::cos(angle / static_cast<T_scalar>(2));
    }

    /*!
     * \brief Copies the values of the other given Quaternion of the same scalar
     *        type to this Quaternion.
     */
    template<bool T_other_use_simd>
    Quaternion(const Quaternion<T_scalar, T_other_use_simd>& q)
    {
        x() = q.x();
        y() = q.y();
        z() = q.z();
        w() = q.w();
    }

    /*!
     * \brief Tag that is used to provided a unique typed argument to the simd
     *        direct assignment constructor.
     */
    enum SimdAssign
    {
        kSimdAssignTag
    };

    /*!
     * \brief Optimisation constructor which directly assigns the internal simd
     *        data of the Quaternion to the given data.
     *
     * \param data The simd data the will be assigned to the internal data of
     *             this Quaternion.
     * \param dummy A dummy parameter which differentiates this constructor.
     */
    Quaternion(SimdType data, SimdAssign tag)
        : m_simd_data(data)
    {
    }

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assigns the components of this Quaternion to be a copy of the
     *        other Quaternion's components.
     */
    template<bool T_other_use_simd>
    Quaternion<T_scalar, T_use_simd>& operator=(
            const Quaternion<T_scalar, T_other_use_simd>& q)
    {
        x() = q.x();
        w() = q.y();
        y() = q.z();
        z() = q.w();
        return *this;
    }

    /*!
     * \brief Compares whether the given Quaternions are considered equal.
     *
     * \warning This performs a standard equality check of the individual
     *          components of the Quaternions, so beware of comparing floating
     *          point Quaternion types.
     */
    template<bool T_other_use_simd>
    bool operator==(
            const Quaternion<T_scalar, T_other_use_simd>& q) const
    {
        return x() == q.x() && y() == q.y() && z() == q.z() && w() == q.w();
    }

    /*!
     * \brief Compares whether the given Quaternions are considered not equal.
     *
     * \warning This performs a standard equality check of the individual
     *          components of the Quaternions, so beware of comparing floating
     *          point Quaternion types.
     */
    template<bool T_other_use_simd>
    bool operator!=(
            const Quaternion<T_scalar, T_other_use_simd>& q) const
    {
        return !((*this) == q);
    }

    /*!
     * \brief Addition operator.
     *
     * Adds each component of the given Quaternion to each component of this
     * Quaternion and returns the result as a new Quaternion.
     */
    template<bool T_other_use_simd>
    Quaternion<T_scalar, T_use_simd> operator+(
        const Quaternion<T_scalar, T_other_use_simd>& q) const
    {
        return Quaternion<T_scalar, T_use_simd>(
            x() + q.x(),
            y() + q.y(),
            z() + q.z(),
            w() + q.w()
        );
    }

    /*!
     * \brief Compound assignment addition operator.
     *
     * Adds each component of the given Quaternion to each component of this
     * Quaternion.
     */
    template<bool T_other_use_simd>
    Quaternion<T_scalar, T_use_simd>& operator+=(
        const Quaternion<T_scalar, T_other_use_simd>& q)
    {
        x() += q.x();
        y() += q.y();
        z() += q.z();
        w() += q.w();

        return *this;
    }

    /*!
     * \brief Subtraction operator.
     *
     * Subtracts each component of the given Quaternion from each component of
     * this Quaternion and returns the result as a new Quaternion.
     */
    template<bool T_other_use_simd>
    Quaternion<T_scalar, T_use_simd> operator-(
        const Quaternion<T_scalar, T_other_use_simd>& q) const
    {
        return Quaternion<T_scalar, T_use_simd>(
            x() - q.x(),
            y() - q.y(),
            z() - q.z(),
            w() - q.w()
        );
    }

    /*!
     * \brief Compound assignment subtraction operator.
     *
     * Subtracts each component of the given Quaternion from each component of
     * this Quaternion.
     */
    template<bool T_other_use_simd>
    Quaternion<T_scalar, T_use_simd>& operator-=(
        const Quaternion<T_scalar, T_other_use_simd>& q)
    {
        x() -= q.x();
        y() -= q.y();
        z() -= q.z();
        w() -= q.w();

        return *this;
    }

    /*!
     * \brief Multiplication operator.
     *
     * Multiplies this Quaternion by the given Quaternion and returns the result
     * as a new Quaternion.
     */
    template<bool T_other_use_simd>
    Quaternion<T_scalar, T_use_simd> operator*(
        const Quaternion<T_scalar, T_other_use_simd>& q) const
    {
        return Quaternion<T_scalar, T_use_simd>(
            (w() * q.x()) + (x() * q.w()) + (y() * q.z()) - (z() * q.y()),
            (w() * q.y()) - (x() * q.z()) + (y() * q.w()) + (z() * q.x()),
            (w() * q.z()) + (x() * q.y()) - (y() * q.x()) + (z() * q.w()),
            (w() * q.w()) - (x() * q.x()) - (y() * q.y()) - (z() * q.z())
        );
    }

    /*!
     * \brief Compound assignment multiplication operator.
     *
     * Multiplies this Quaternion by the given Quaternion.
     */
    template<bool T_other_use_simd>
    Quaternion<T_scalar, T_use_simd>& operator*=(
        const Quaternion<T_scalar, T_other_use_simd>& q)
    {
        x() *= q.x();
        y() *= q.y();
        z() *= q.z();
        w() *= q.w();

        return *this;
    }

    //--------------------------------------------------------------------------
    //                           PUBLC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Provides access the x component of this Quaternion.
     */
    T_scalar& x()
    {
        return m_storage.data[0];
    }

    /*!
     * \brief Provides const access the x component of this Quaternion.
     */
    const T_scalar& x() const
    {
        return m_storage.data[0];
    }

    /*!
     * \brief Provides access the y component of this Quaternion.
     */
    T_scalar& y()
    {
        return m_storage.data[1];
    }

    /*!
     * \brief Provides const access the y component of this Quaternion.
     */
    const T_scalar& y() const
    {
        return m_storage.data[1];
    }

    /*!
     * \brief Provides access the z component of this Quaternion.
     */
    T_scalar& z()
    {
        return m_storage.data[2];
    }

    /*!
     * \brief Provides const access the z component of this Quaternion.
     */
    const T_scalar& z() const
    {
        return m_storage.data[2];
    }

    /*!
     * \brief Provides access the w component of this Quaternion.
     */
    T_scalar& w()
    {
        return m_storage.data[3];
    }

    /*!
     * \brief Provides const access the w component of this Quaternion.
     */
    const T_scalar& w() const
    {
        return m_storage.data[3];
    }

    // TODO: magnitude (math?)

    // TODO: normalise (math?)

    // TODO: to euler

    // TODO: to axis angle

    // TODO: to matrix??

    /*!
     * \brief Returns whether this Quaternion has a valid simd data
     *        representation.
     */
    bool has_simd() const
    {
        return T_use_simd;
    }

    /*!
     * \brief Returns the simd representation of this Quaternions's data.
     *
     * \note This should only be used on Quaternions that are using simd.
     */
    SimdType& get_simd()
    {
        static_assert(
            T_use_simd == true,
            "Quaternion does not have simd data"
        );

        return m_simd_data;
    }

    /*!
     * \brief Returns the const simd representation of this Quaternion's data.
     *
     * \note This should only be used on Quaternions that are using simd.
     */
    const SimdType& get_simd() const
    {
        static_assert(
            T_use_simd == true,
            "Quaternion does not have simd data"
        );

        return m_simd_data;
    }

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The storage of this quaternion, union-ed with the simd type so it
     *        can be used interchangeably.
     */
    union
    {
        Storage m_storage;
        typename Storage::SimdData m_simd_data;
    };
};

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

template<typename T_scalar, bool T_use_simd>
inline arc::str::UTF8String& operator<<(
        arc::str::UTF8String& s,
        const Quaternion<T_scalar, T_use_simd>& q)
{
    s << "(" << q.x() << "i, " << q.y() << "j, " << q.z() << "k, " << q.w()
      << ")";
    return s;
}

template<typename T_scalar, bool T_use_simd>
inline std::ostream& operator<<(
        std::ostream& s,
        const Quaternion<T_scalar, T_use_simd>& q)
{
    s << "(" << q.x() << "i, " << q.y() << "j, " << q.z() << "k, " << q.w()
      << ")";
    return s;
}

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

typedef Quaternion<float> Quaternionf;
typedef Quaternion<double> Quaterniond;

// define the Simd types whether or not it's enabled, since we want to be able
// turn it off and on easily without having to update the vector types
// everywhere in the code.
#undef ARC_GM_USE_SIMD
#ifndef ARC_GM_DISABLE_SSE
    #define ARC_GM_USE_SIMD true
#else
    #define ARC_GM_USE_SIMD false
#endif

typedef Quaternion<float, ARC_GM_USE_SIMD> SimdQuaternionf;

} // namespace gm
} // namespace arc

#endif