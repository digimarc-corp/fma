#ifndef DMRC_TYPETRAITS_TYPETRAITS_HPP
#define DMRC_TYPETRAITS_TYPETRAITS_HPP

#include "Comparison.hpp"
#include "EnableIf.hpp"

namespace DMRC {
namespace TypeTraits {

template <class T, T v>
struct integral_constant {
	static const T value = v;
	using value_type = T;
	using type = integral_constant;  // using injected-class-name
	inline operator value_type() const {
		return value;
	}
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

namespace internal {

template <class T>
struct remove_cv { typedef T type; };
template <class T>
struct remove_cv<const T> { typedef T type; };
template <class T>
struct remove_cv<volatile T> { typedef T type; };
template <class T>
struct remove_cv<const volatile T> { typedef T type; };
template <class T>
struct remove_const { typedef T type; };
template <class T>
struct remove_const<const T> { typedef T type; };
template <class T>
struct remove_volatile { typedef T type; };
template <class T>
struct remove_volatile<volatile T> { typedef T type; };

template <typename>
struct is_numeric_primitive_base : public false_type {};
template <>
struct is_numeric_primitive_base<bool> : public true_type {};
template <>
struct is_numeric_primitive_base<char> : public true_type {};
template <>
struct is_numeric_primitive_base<short> : public true_type {};
template <>
struct is_numeric_primitive_base<int> : public true_type {};
template <>
struct is_numeric_primitive_base<long> : public true_type {};
template <>
struct is_numeric_primitive_base<long long> : public true_type {};
template <>
struct is_numeric_primitive_base<unsigned char> : public true_type {};
template <>
struct is_numeric_primitive_base<unsigned short> : public true_type {};
template <>
struct is_numeric_primitive_base<unsigned int> : public true_type {};
template <>
struct is_numeric_primitive_base<unsigned long> : public true_type {};
template <>
struct is_numeric_primitive_base<unsigned long long> : public true_type {};
template <>
struct is_numeric_primitive_base<float> : public true_type {};
template <>
struct is_numeric_primitive_base<double> : public true_type {};

template <typename>
struct is_integral_base : public false_type {};

template <>
struct is_integral_base<bool> : public true_type {};
template <>
struct is_integral_base<char> : public true_type {};
template <>
struct is_integral_base<short> : public true_type {};
template <>
struct is_integral_base<int> : public true_type {};
template <>
struct is_integral_base<long> : public true_type {};
template <>
struct is_integral_base<long long> : public true_type {};
template <>
struct is_integral_base<unsigned char> : public true_type {};
template <>
struct is_integral_base<unsigned short> : public true_type {};
template <>
struct is_integral_base<unsigned int> : public true_type {};
template <>
struct is_integral_base<unsigned long> : public true_type {};
template <>
struct is_integral_base<unsigned long long> : public true_type {};

template <typename>
struct is_unsigned_base : public false_type {};

template <>
struct is_unsigned_base<bool> : public true_type {};
template <>
struct is_unsigned_base<unsigned char> : public true_type {};
template <>
struct is_unsigned_base<unsigned short> : public true_type {};
template <>
struct is_unsigned_base<unsigned int> : public true_type {};
template <>
struct is_unsigned_base<unsigned long> : public true_type {};
template <>
struct is_unsigned_base<unsigned long long> : public true_type {};

template <typename>
struct is_floating_point_base : public false_type {};

template <>
struct is_floating_point_base<float> : public true_type {};
template <>
struct is_floating_point_base<double> : public true_type {};

}  // namespace internal

template <typename T>
struct is_numeric_primitive : public internal::is_numeric_primitive_base<typename internal::remove_cv<T>::type> {};

template <typename T>
struct is_integral : public internal::is_integral_base<typename internal::remove_cv<T>::type> {};

template <typename T>
struct is_unsigned : public internal::is_unsigned_base<typename internal::remove_cv<T>::type> {};

template <typename T>
struct is_floating_point : public internal::is_floating_point_base<typename internal::remove_cv<T>::type> {};

template <class T>
struct get_unsigned {};
template <>
struct get_unsigned<char> { typedef unsigned char type; };
template <>
struct get_unsigned<short> { typedef unsigned short type; };
template <>
struct get_unsigned<int> { typedef unsigned int type; };
template <>
struct get_unsigned<long> { typedef unsigned long type; };
template <>
struct get_unsigned<long long> { typedef unsigned long long type; };
template <>
struct get_unsigned<unsigned char> { typedef unsigned char type; };
template <>
struct get_unsigned<unsigned short> { typedef unsigned short type; };
template <>
struct get_unsigned<unsigned int> { typedef unsigned int type; };
template <>
struct get_unsigned<unsigned long> { typedef unsigned long type; };
template <>
struct get_unsigned<unsigned long long> { typedef unsigned long long type; };

template <class T>
struct get_signed {};
template <>
struct get_signed<char> { typedef char type; };
template <>
struct get_signed<short> { typedef short type; };
template <>
struct get_signed<int> { typedef int type; };
template <>
struct get_signed<long> { typedef long type; };
template <>
struct get_signed<long long> { typedef long long type; };
template <>
struct get_signed<unsigned char> { typedef char type; };
template <>
struct get_signed<unsigned short> { typedef short type; };
template <>
struct get_signed<unsigned int> { typedef int type; };
template <>
struct get_signed<unsigned long> { typedef long type; };
template <>
struct get_signed<unsigned long long> { typedef long long type; };

template <class T>
struct get_container_after { typedef void type; };
template <>
struct get_container_after<char> { typedef short type; };
template <>
struct get_container_after<short> { typedef int type; };
template <>
struct get_container_after<int> { typedef long type; };
template <>
struct get_container_after<unsigned char> { typedef unsigned short type; };
template <>
struct get_container_after<unsigned short> { typedef unsigned int type; };
template <>
struct get_container_after<unsigned int> { typedef unsigned long type; };

}  // namespace TypeTraits
}  // namespace DMRC

#endif  // DMRC_TYPETRAITS_TYPETRAITS_HPP
