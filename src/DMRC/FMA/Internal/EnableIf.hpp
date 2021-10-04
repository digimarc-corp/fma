///////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: EnableIf.hpp
//
// Description: Internal port of std::enable_if, to minimize external dependencies
//
// Remarks: Implementation sourced from https://en.cppreference.com/w/cpp/types/enable_if
//
// Remarks: The simple example below shows how you can coerce compilers to select certain
//          specializations based on compile-time constant information, such as STL type traits, or
//          constants of your own. This can be used to more cleanly handle special cases, such as
//          un-supported operations, or operations requiring special conversions, etc.
//
// Example:
//
// 	/** @brief Default implementation for dividing floating-point values */
// 	template<typename T, typename enable_if<std::is_floating_point<T>::value, bool>::type = true >
// 	double divide(T val1, T val2) {
// 		return val1 / val2; // No special implementation needed
// 	}
//
// 	/** @brief Our special implementation for internal fixed-point values */
// 	template<typename T, typename enable_if<dmrc::is_fixed_point<T>::value, bool>::type = true >
// 	double divide(T val1, T val2) {
// 		// implementation here that divides the fixed-point values, and converts to a double.
// 	}
//
// 	/** @brief Our special implementation for handling integral values */
// 	template<typename T, typename enable_if<std::is_integral<T>::value, bool>::type = true >
// 	double divide(T val1, T val2) {
// 		double v1 = static_cast<double>(val1);
// 		double v2 = static_cast<double>(val2);
// 		return v1 / v2;
// 	}
//
// 	int main() {
// 		int a = 10;
// 		int b = 6;
// 		my_fixedPt<5> c = 3.14159;
// 		my_fixedPt<5> d = 2.00000;
// 		float e = 1.141;
// 		float f = 1.1;
//
// 		double r1 = divide(a, b); // Unambiguously selects the first implementation. Returns 1.66667
// 		double r2 = divide(c, d); // Unambiguously selects the second implementation. Returns 1.57080
// 		double r3 = divide(e, f); // Unambiguously selects the third implementation. Returns 1.03727
// 	}
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef DMRC_CORE_ENABLEIF_HPP
#define DMRC_CORE_ENABLEIF_HPP

namespace DMRC {

/** @brief Conditionally resolves to T, if B is true. Used to coerce a substitution error,
 *         leveraging SFINAE to force the compiler to select one implementation.
 * 
 * @remark When B is false, this implementation will be used, and T will not be represented by
 *         enable_if<false, T>::type, causing a substitution error. See the true specialization
 *         for more information.
 */
template <bool B, class T = void>
struct enable_if {};

/** @brief Conditionally resolves to T, if B is true. Used to coerce a substitution error,
 *         leveraging SFINAE to force the compiler to select one implementation.
 * 
 * @remark When B is true, this specialization will be used, and T will be represented by
 *         enable_if<true, T>::type, which does NOT cause a substitution error.
 */
template <class T>
struct enable_if<true, T> { typedef T type; };

}  // namespace DMRC

#endif  // DMRC_CORE_ENABLEIF_HPP
