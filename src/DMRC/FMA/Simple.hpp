#ifndef DMRC_FIXED_SIMPLE_HPP
#define DMRC_FIXED_SIMPLE_HPP

#include "Container.hpp"
#include "FPMath.hpp"
#include "FPShift.hpp"
#include "Internal/EnableIf.hpp"
#include "Internal/TypeTraits.hpp"
#include "Internal/Inline.h"

namespace DMRC {
namespace FMA {

/** @brief A simple fixed-point type that uses a consistent container size, and no frills.
 * 
 * Simple always uses an int for its container, and a long for its overflow type. Math operations
 * are saturating, and always maintain Q value.
 * 
 * Simple does not implement operations with other types, nor different Q values of the Simple type.
 * This means the user is always required to explicitly cast, bit-shift, or otherwise convert to
 * uniform types, before doing a calculation. This minimizes the risk of user error.
 */
template <int N_val>
struct Simple : Container<N_val, int> {
	typedef Simple<N_val> this_t;
	typedef Container<N_val, int> base_t;
	typedef int data_t;
	typedef typename TypeTraits::get_container_after<data_t>::type overflow_t;
	typedef FPMath<N_val, data_t> math_t;
	typedef FPMath<N_val, overflow_t> overflow_math_t;

	static const int N = N_val;
	int n = base_t::traits::N;
	int m = base_t::traits::M;

	Simple()
	    : base_t() {
	}

	Simple(const this_t& rhs)
	    : base_t(rhs.data) {
	}

	template <int N2>
	explicit Simple(const Simple<N2>& rhs)
	    : base_t(FPMath<N2, data_t>::template to_q<N>(rhs.data)) {
	}

	template <typename T>
	explicit Simple(const T& primitive)
	    : base_t(math_t::template to_fixed<T>(primitive)) {
	}

	inline void set_raw(const data_t& fpval) {
		base_t::data = fpval;
	}

	inline void set_raw(const overflow_t& fpval) {
		base_t::data = static_cast<data_t>(fpval);
	}

	static dmrc_inline const Simple from_raw(const data_t& fpval) {
		Simple rtn;
		rtn.set_raw(fpval);
		return rtn;
	}

	static dmrc_inline const Simple from_raw(const overflow_t& fpval) {
		Simple rtn;
		rtn.set_raw(fpval);
		return rtn;
	}

	template <typename T>
	inline T as() const {
		return math_t::template to<T>(base_t::data);
	}

	template <typename T>
	explicit operator T() const {
		return as<T>();
	}

	template <int N2>
	explicit operator Simple<N2>() const {
		return Simple<N2>(*this);
	}

	template <typename T>
	inline Simple& operator+=(const T& rhs) {
		Simple<N> rhs_fp(rhs);
		overflow_t result = base_t::data + rhs_fp.data;
		base_t::data = static_cast<data_t>(result);
		return *this;
	}

	template <typename T>
	inline Simple& operator-=(const T& rhs) {
		Simple<N> rhs_fp(rhs);
		overflow_t result = base_t::data - rhs_fp.data;
		base_t::data = static_cast<data_t>(result);
		return *this;
	}

	template <typename T>
	inline Simple& operator*=(const T& rhs) {
		Simple<N> rhs_fp(rhs);
		overflow_t result =  overflow_math_t::product(base_t::data, rhs_fp.data);
		base_t::data = static_cast<data_t>(result);
		return *this;
	}

	template <typename T>
	inline Simple& operator/=(const T& rhs) {
		Simple<N> rhs_fp(rhs);
		overflow_t result = overflow_math_t::quotient(base_t::data, rhs_fp.data);
		base_t::data = static_cast<data_t>(result);
		return *this;
	}

};  // struct Simple

template <int N,
          typename T>
inline Simple<N> operator+(const Simple<N>& lhs, const T& rhs) {
	Simple<N> result(lhs);
	result += static_cast<Simple<N> >(rhs);
	return result;
}

template <int N,
          typename T>
inline Simple<N> operator-(const Simple<N>& lhs, const T& rhs) {
	Simple<N> result(lhs);
	result -= static_cast<Simple<N> >(rhs);
	return result;
}

template <int N>
inline Simple<N> operator*(const Simple<N>& lhs, const Simple<N>& rhs) {
	typedef typename Simple<N>::overflow_t overflow_t;
	typedef typename Simple<N>::overflow_math_t overflow_math_t;
	overflow_t tmp =  overflow_math_t::product(lhs.data, rhs.data);
	return Simple<N>::from_raw(tmp);
}

template <int N1, int N2>
inline Simple<N1> operator*(const Simple<N1>& lhs, const Simple<N2>& rhs) {
	static_assert(N1 == N2, "Simple fixed-point type does not support multiplying different Q sizes. Convert to same type or use a different container.");
}

template <int N,
          typename T>
inline Simple<N> operator*(const Simple<N>& lhs, const T& rhs) {
	typedef typename Simple<N>::overflow_t overflow_t;
	overflow_t tmp = lhs.data * rhs;
	return Simple<N>::from_raw(tmp);
}

template <int N>
inline Simple<N> operator/(const Simple<N>& lhs, const Simple<N>& rhs) {
	typedef typename Simple<N>::overflow_t overflow_t;
	typedef typename Simple<N>::overflow_math_t overflow_math_t;
	overflow_t tmp = overflow_math_t::quotient(lhs.data, rhs.data);
	return Simple<N>::from_raw(tmp);
}

template <int N1, int N2>
inline Simple<N1> operator/(const Simple<N1>& lhs, const Simple<N2>& rhs) {
	static_assert(N1 == N2, "Simple fixed-point type does not support dividing different Q sizes. Convert to same type or use a different container.");
}

template <int N,
          typename T>
inline Simple<N> operator/(const Simple<N>& lhs, const T& rhs) {
	typedef typename Simple<N>::overflow_t overflow_t;
	overflow_t tmp = static_cast<overflow_t>(lhs.data);
	tmp = tmp / rhs;
	return Simple<N>::from_raw(tmp);
}

template <int N, int N_rshift>
Simple<N - N_rshift> operator>>(Simple<N> v, _fpshift<N_rshift> shift) {
	const int N2 = N - N_rshift;
	return static_cast<Simple<N2> >(v);
}

template <int N, int N_lshift>
Simple<N + N_lshift> operator<<(Simple<N> v, _fpshift<N_lshift> shift) {
	const int N2 = N + N_lshift;
	return static_cast<Simple<N2> >(v);
}

}  // namespace FMA
}  // namespace DMRC

#endif  // DMRC_FIXED_SIMPLE_HPP
