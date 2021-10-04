#ifndef DMRC_FIXED_INTERNAL_FPTYPETRAITS_HPP
#define DMRC_FIXED_INTERNAL_FPTYPETRAITS_HPP

#include "Pow.hpp"
#include <EnableIf.hpp>
#include <TypeTraits.hpp>

namespace DMRC {
namespace FMA {
namespace Internal {

/** @brief Type traits for fixed-point
 */
template <int N_val,
          typename T,
          // Ensure the container type given is a primitive integral type
          typename DMRC::enable_if<DMRC::TypeTraits::is_integral<T>::value, bool>::type = true,
          // Ensure the container type can hold the fractional bits given. Signed containers can hold
          //one less bit due to the sign bit
          typename DMRC::enable_if<DMRC::is_lte<N_val, DMRC::val_if<TypeTraits::is_unsigned<T>::value, sizeof(T) * 8, sizeof(T) * 8 - 1>::value>::value && DMRC::is_gte<N_val, 0>::value, bool>::type = true>
struct FPTypeTraits {
	typedef T data_t;
	static const bool is_signed = !TypeTraits::is_unsigned<T>::value;

	enum {
		data_sz = sizeof(T) * 8,                    ///< The total number of bits in this type's data container
		fp_sz = is_signed ? data_sz - 1 : data_sz,  ///< The number of bits available to store fixed-point data
		N = N_val,                                  ///< The number of bits used to store the fractional part of the value
		M = fp_sz - N,                              ///< The number of bits used to store the integer part of the value
	};

	static const double smallest_fraction;
	static const unsigned long long max_int = static_cast<long long>((_pow<2, M>::value) - 1);  ///< The largest whole number stored by this type
	static const long long min_int = is_signed ? 0 - max_int - 1 : 0;                           ///< The smallest whole number stored by this type
};

template <int N_val,
          typename T,
          typename DMRC::enable_if<DMRC::TypeTraits::is_integral<T>::value, bool>::type a,
          typename DMRC::enable_if<DMRC::is_lte<N_val, DMRC::val_if<TypeTraits::is_unsigned<T>::value, sizeof(T) * 8, sizeof(T) * 8 - 1>::value>::value && DMRC::is_gte<N_val, 0>::value, bool>::type b>
const double FPTypeTraits<N_val, T, a, b>::smallest_fraction = 1.0 / _pow<2, N>::value;

}  // namespace Internal
}  // namespace FMA
}  // namespace DMRC

#endif  // DMRC_FIXED_INTERNAL_FPTYPETRAITS_HPP
