#ifndef DMRC_FIXED_CONTAINER_HPP
#define DMRC_FIXED_CONTAINER_HPP

#include "FPMath.hpp"
#include "Internal/ContainerType.hpp"
#include "Internal/FPTypeTraits.hpp"
#include <EnableIf.hpp>
#include <TypeTraits.hpp>

namespace DMRC {
namespace FMA {

template <int N_val,
          typename T = typename Internal::ContainerType<N_val>::default_t>
struct Container {
	typedef Internal::FPTypeTraits<N_val, T> traits;
	typedef T data_t;

	data_t data;

	inline Container()
	    : data(0) {
	}

	inline Container(data_t v)
	    : data(v) {
	}
};  // struct Container

}  // namespace FMA
}  // namespace DMRC

#endif  // DMRC_FIXED_CONTAINER_HPP
