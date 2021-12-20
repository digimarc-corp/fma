#ifndef DMRC_FIXED_INTERNAL_FPTYPETRAITS_HPP
#define DMRC_FIXED_INTERNAL_FPTYPETRAITS_HPP

#include "EnableIf.hpp"
#include "Pow.hpp"
#include "TypeTraits.hpp"

namespace DMRC {
namespace FMA {
namespace Internal {

/** @brief Type traits for fixed-point
 */
template <int N_val,
          typename T>
struct FPTypeTraits {
	static_assert(DMRC::TypeTraits::is_integral<T>::value,
	              "Fixed-point type must use an integral storage type!");
	static_assert(DMRC::is_lte<N_val, DMRC::val_if<TypeTraits::is_unsigned<T>::value, sizeof(T) * 8, sizeof(T) * 8 - 1>::value>::value,
	              "N must be less than the size of the storage type!");
	static_assert(DMRC::is_gte<N_val, 0>::value,
	              "N must be greater than zero!");

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
          typename T>
const double FPTypeTraits<N_val, T>::smallest_fraction = 1.0 / _pow<2, N>::value;

}  // namespace Internal
}  // namespace FMA
}  // namespace DMRC

#endif  // DMRC_FIXED_INTERNAL_FPTYPETRAITS_HPP
