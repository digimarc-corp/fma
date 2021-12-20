#ifndef DMRC_FIXED_INTERNAL_CONTAINERTYPE_HPP
#define DMRC_FIXED_INTERNAL_CONTAINERTYPE_HPP

#include "Comparison.hpp"
#include "EnableIf.hpp"

namespace DMRC {
namespace FMA {
namespace Internal {

template <int N>
struct _container_q {
	static const bool is_valid = false;
	typedef _container_q<min8<val_if<(7 > N), 7, 64>::value,
	                          val_if<(8 > N), 8, 64>::value,
	                          val_if<(15 > N), 15, 64>::value,
	                          val_if<(16 > N), 16, 64>::value,
	                          val_if<(31 > N), 31, 64>::value,
	                          val_if<(32 > N), 32, 64>::value,
	                          val_if<(63 > N), 63, 64>::value,
	                          val_if<(64 > N), 64, 64>::value>::value>
	    valid_c;
};

template <>
struct _container_q<64> {
	static const bool is_valid = true;
	typedef _container_q<64> valid_c;

	typedef unsigned long min_unsigned_t;
	typedef void min_signed_t;

	typedef min_unsigned_t unsigned_t;
	typedef min_signed_t signed_t;

	typedef signed_t default_t;

	typedef void larger_c;
	typedef _container_q<32> smaller_c;
};

template <>
struct _container_q<63> {
	static const bool is_valid = true;
	typedef _container_q<63> valid_c;

	typedef unsigned long min_unsigned_t;
	typedef long min_signed_t;

	typedef min_unsigned_t unsigned_t;
	typedef min_signed_t signed_t;

	typedef signed_t default_t;

	typedef void larger_c;
	typedef _container_q<31> smaller_c;
};

template <>
struct _container_q<32> {
	static const bool is_valid = true;
	typedef _container_q<32> valid_c;

	typedef unsigned int min_unsigned_t;
	typedef long min_signed_t;

	typedef unsigned int unsigned_t;
	typedef long signed_t;

	typedef signed_t default_t;

	typedef _container_q<63> larger_c;
	typedef _container_q<16> smaller_c;
};

template <>
struct _container_q<31> {
	static const bool is_valid = true;
	typedef _container_q<31> valid_c;

	typedef unsigned int min_unsigned_t;
	typedef int min_signed_t;

	typedef unsigned int unsigned_t;
	typedef int signed_t;

	typedef signed_t default_t;

	typedef _container_q<63> larger_c;
	typedef _container_q<15> smaller_c;
};

template <>
struct _container_q<16> {
	static const bool is_valid = true;
	typedef _container_q<16> valid_c;

	typedef unsigned short min_unsigned_t;
	typedef int min_signed_t;

	typedef unsigned int unsigned_t;
	typedef int signed_t;

	typedef signed_t default_t;

	typedef _container_q<31> larger_c;
	typedef _container_q<8> smaller_c;
};

template <>
struct _container_q<15> {
	static const bool is_valid = true;
	typedef _container_q<15> valid_c;

	typedef unsigned short min_unsigned_t;
	typedef short min_signed_t;

	typedef unsigned int unsigned_t;
	typedef int signed_t;

	typedef signed_t default_t;

	typedef _container_q<31> larger_c;
	typedef _container_q<7> smaller_c;
};

template <>
struct _container_q<8> {
	static const bool is_valid = true;
	typedef _container_q<8> valid_c;

	typedef unsigned char min_unsigned_t;
	typedef short min_signed_t;

	typedef unsigned int unsigned_t;
	typedef int signed_t;

	typedef signed_t default_t;

	typedef _container_q<15> larger_c;
	typedef void smaller_c;
};

template <>
struct _container_q<7> {
	static const bool is_valid = true;
	typedef _container_q<7> valid_c;

	typedef unsigned char min_unsigned_t;
	typedef char min_signed_t;

	typedef unsigned int unsigned_t;
	typedef int signed_t;

	typedef signed_t default_t;

	typedef _container_q<15> larger_c;
	typedef void smaller_c;
};

template <int N>
struct ContainerType : _container_q<N>::valid_c {};

}  // namespace Internal
}  // namespace FMA
}  // namespace DMRC

#endif  // DMRC_FIXED_INTERNAL_CONTAINERTYPE_HPP
