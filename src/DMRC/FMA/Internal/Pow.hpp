#ifndef DMRC_FMA_INTERNAL_POW_HPP
#define DMRC_FMA_INTERNAL_POW_HPP

namespace DMRC {
namespace FMA {
namespace Internal {

/* @brief Compile-time power for positive exponents only */
template <int b, int e>
struct _pow {
	static const unsigned long long value = static_cast<long long>(b * _pow<b, e - 1>::value);
};

/* @brief Compile-time power for positive exponents only */
template <int b>
struct _pow<b, 0> {
	static const long long value = 1;
};

}  // namespace Internal
}  // namespace FMA
}  // namespace DMRC

#endif  // DMRC_FMA_INTERNAL_POW_HPP
