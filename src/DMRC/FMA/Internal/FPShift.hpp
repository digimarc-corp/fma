#ifndef DMRC_FMA_FPSHIFT_HPP
#define DMRC_FMA_FPSHIFT_HPP

namespace DMRC {
namespace FMA {

/** @brief A structure used only to coerce templatized bit-shifting whenever
 *         bit-shift values are known at compile time
 */
template <int N>
struct _fpshift {};

/** @brief Shorthand to construct an empty _fpshift structure of a given value
 */
#define fpshift(N) ::DMRC::FMA::_fpshift<N>()

}  // namespace FMA
}  // namespace DMRC

#endif  // DMRC_FMA_FPSHIFT_HPP