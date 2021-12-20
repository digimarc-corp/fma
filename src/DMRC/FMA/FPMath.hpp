#ifndef DMRC_FIXED_FPMATH_HPP
#define DMRC_FIXED_FPMATH_HPP

#include "Internal/ContainerType.hpp"
#include "Internal/FPTypeTraits.hpp"
#include "Internal/EnableIf.hpp"
#include "Internal/TypeTraits.hpp"
#include "Internal/Inline.h"

namespace DMRC {
namespace FMA {

template <int N1, int N2, typename T>
static dmrc_inline T promote_q(const T x) {
	return x << (N2 - N1);
}

template <int N1, int N2, typename T>
static dmrc_inline T demote_q(const T x) {
	return x >> (N1 - N2);
}

template <int N1, int N2, class T>
static dmrc_inline T round_and_demote_q(const T& x) {
	return (x + (1 << (N1 - N2 - 1))) >> (N1 - N2);
}

template <int N,
          typename T = typename Internal::ContainerType<N>::default_t>
struct FPMath : Internal::FPTypeTraits<N, T> {
	typedef typename DMRC::TypeTraits::get_container_after<T>::type larger_t;

	/** @brief Converts the given primitive value to a fixed-point value of type T.
	 * 
	 * @param T2 The type of the primitive from which to convert.
	 * @param x The value to convert to a QN fixed-point value of type T.
	 */
	template <typename T2,
	          typename DMRC::enable_if<DMRC::TypeTraits::is_integral<T2>::value, bool>::type = true>
	static dmrc_inline T to_fixed(const T2 x) {
		return static_cast<T>(x << N);
	}

	/** @brief Converts the given primitive value to a fixed-point value of type T.
	 * 
	 * @param T2 The type of the primitive from which to convert.
	 * @param x The value to convert to a QN fixed-point value of type T.
	 */
	template <typename T2,
	          typename DMRC::enable_if<DMRC::TypeTraits::is_floating_point<T2>::value, bool>::type = true>
	static dmrc_inline T to_fixed(const T2 x) {
		return static_cast<T>(x * (static_cast<typename TypeTraits::get_container_after<T>::type>(1) << N));
	}

	/** @brief Converts the given fixed-point primitive value to a new Q format of the same type.
	 * 
	 * @param N2 The new number of fractional bits to convert to.
	 * @param x The QN fixed-point value of type T from which to convert.
	 */
	template <int N2,
	          typename DMRC::enable_if<DMRC::is_lt<N2, N>::value, bool>::type = true>
	static dmrc_inline T to_q(const T x) {
		return demote_q<N, N2>(x);
	}

	/** @brief Converts the given fixed-point primitive value to a new Q format of the same type.
	 * 
	 * @param N2 The new number of fractional bits to convert to.
	 * @param x The QN fixed-point value of type T from which to convert.
	 */
	template <int N2,
	          typename DMRC::enable_if<DMRC::is_gt<N2, N>::value, bool>::type = true>
	static dmrc_inline T to_q(const T x) {
		return promote_q<N, N2>(x);
	}

	/** @brief Converts the given fixed-point primitive value to a new Q format of the same type.
	 * 
	 * @param N2 The new number of fractional bits to convert to.
	 * @param x The QN fixed-point value of type T from which to convert.
	 */
	template <int N2,
	          typename DMRC::enable_if<DMRC::is_eq<N2, N>::value, bool>::type = true>
	static dmrc_inline T to_q(const T x) {
		return x;  // No change
	}

	/** @brief Converts the given fixed-point primitive value to a new Q format of the same type,
	 *         rounding if needed (instead of truncating)
	 * 
	 * @param N2 The new number of fractional bits to convert to.
	 * @param x The QN fixed-point value of type T from which to convert.
	 */
	template <int N2,
	          typename DMRC::enable_if<DMRC::is_lt<N2, N>::value, bool>::type = true>
	static dmrc_inline T to_q_round(const T x) {
		return promote_q<N, N2>(x);
	}

	/** @brief Converts the given fixed-point primitive value to a new Q format of the same type,
	 *         rounding if needed (instead of truncating)
	 * 
	 * @param N2 The new number of fractional bits to convert to.
	 * @param x The QN fixed-point value of type T from which to convert.
	 */
	template <int N2,
	          typename DMRC::enable_if<DMRC::is_gt<N2, N>::value, bool>::type = true>
	static dmrc_inline T to_q_round(const T x) {
		return round_and_demote_q<N, N2>(x);
	}

	/** @brief Converts the given fixed-point primitive value to a new Q format of the same type,
	 *         rounding if needed (instead of truncating)
	 * 
	 * @param N2 The new number of fractional bits to convert to.
	 * @param x The QN fixed-point value of type T from which to convert.
	 */
	template <int N2,
	          typename DMRC::enable_if<DMRC::is_eq<N2, N>::value, bool>::type = true>
	static dmrc_inline T to_q_round(const T x) {
		return x;  // No change
	}

	/** @brief Converts the given fixed-point value from one container type to another.
	 */
	template <typename T2,
	          typename DMRC::enable_if<DMRC::TypeTraits::is_integral<T2>::value, bool>::type = true>
	static dmrc_inline T2 fp_to(const T x) {
		return static_cast<T2>(x);
	}

	/** @brief Converts the given fixed-point value to the requested primitive type, rounding
	 *         appropriately.
	 * 
	 * @param T2 The target type to convert to.
	 * @param x The fixed-point value to convert to a T2.
	 */
	template <typename T2,
	          typename DMRC::enable_if<DMRC::TypeTraits::is_integral<T2>::value, bool>::type = true>
	static dmrc_inline T2 to(const T x) {
		T2 result = static_cast<T2>(x);
		if (x < 0) {
			result = FPMath<N, T2>::ceil(x);
		} else {
			result = FPMath<N, T2>::floor(x);
		}
		return FPMath<N, T2>::template to_q<0>(result);
	}

	/** @brief Converts the given fixed-point value to the requested primitive type, rounding
	 *         appropriately.
	 * 
	 * @param T2 The target type to convert to.
	 * @param x The fixed-point value to convert to a T2.
	 */
	template <typename T2,
	          typename DMRC::enable_if<DMRC::TypeTraits::is_floating_point<T2>::value, bool>::type = true>
	static dmrc_inline T2 to(const T x) {
		return static_cast<T2>(x / static_cast<T2>(1 << N));
	}

	template <typename T2>
	static dmrc_inline T from(const T2 x) {
		// This is dependent on a template parameter, so kindly remind the compiler
		return FPMath<N, T2>::template to<T>(x);
	}

	static dmrc_inline T floor(const T x) {
		return (x >> N) << N;
	}

	static dmrc_inline T ceil(const T x) {
		return -floor(-x);
	}

	static dmrc_inline T round(const T x) {
		return floor(x + (1 << (N - 1)));
	}

	static dmrc_inline bool is_integer(const T x) {
		return x == floor(x);
	}

	static dmrc_inline T product(T a, T b) {
		return (a * b) >> N;
	}

	static dmrc_inline larger_t product_safe(T a, T b) {
		return static_cast<larger_t>(a) * b;
	}

	static dmrc_inline T quotient(T a, T b) {
		return (a << N) / b;
	}

	static dmrc_inline T quotient_safe(T a, T b) {
		return static_cast<T>((static_cast<larger_t>(a) << N) / b);
	}

	static dmrc_inline T reciprocal_fixed(const T x) {
		return to_fixed(1.0 / to_double(x));
	}

	template <typename T2,
	          typename DMRC::enable_if<DMRC::TypeTraits::is_floating_point<T2>::value, bool>::type = true>
	static dmrc_inline T reciprocal(const T2 x) {
		return to_fixed(1.0 / x);
	}
};

}  // namespace FMA
}  // namespace DMRC

#endif  // DMRC_FIXED_FPMATH_HPP
