#include <gtest/gtest.h>

#include <string>

#include <Internal/ContainerType.hpp>
#include <Internal/TypeTraits.hpp>

using namespace DMRC::FMA::Internal;

#ifndef NDEBUG
static const bool DEBUG_PRINT_TYPE_INFO = true;
#else
static const bool DEBUG_PRINT_TYPE_INFO = false;
#endif

static const int MAX_N = 64;
static const int MAX_N_SIGNED = MAX_N - 1;

template <int N, bool header = DEBUG_PRINT_TYPE_INFO, bool output = header>
inline void ContainerType_Expectations() {
	if constexpr (header && output) {
		printf("[   INFO   ] Format, Default Container, Min Unsigned, Min Signed, Larger, Smaller\n");
	}

	typedef ContainerType<N> c;

	typedef typename c::default_t container_t;
	container_t v = 0;
	++v;

	typedef typename c::min_unsigned_t min_unsigned_t;
	min_unsigned_t v2 = 0;
	++v2;

	typedef typename c::min_signed_t min_signed_t;
	min_signed_t v3 = 0;
	++v3;

	// Make sure we mark metatypes as "void" when we don't have a container for what was requested.
	// For example, if we're already using a 64-bit integer, we don't have a larger container to
	// use, and if we need a QM.64 container, we don't support signed types (because we don't have a
	// larger container!)

	std::string larger_t_name = typeid(typename c::larger_c).name();
	if constexpr (N > 32) {
		// We don't have a valid larger container, because the Q format is too high.
		EXPECT_EQ(typeid(void), typeid(typename c::larger_c));
	} else {
		// Since we DO have a valid larger container, make sure it is valid and usable
		EXPECT_NE(typeid(void), typeid(typename c::larger_c));
		typedef typename c::larger_c::default_t larger_t;
		EXPECT_TRUE(static_cast<bool>(DMRC::TypeTraits::is_integral<larger_t>::value));
		larger_t vLarge = 0;
		++vLarge;
		// Get the RTTI for our larger container type, for our printout below.
		larger_t_name = typeid(larger_t).name();
	}

	std::string smaller_t_name = typeid(typename c::smaller_c).name();
	if constexpr (N <= 8) {
		// We don't have a valid smaller container, because the Q format is too low.
		EXPECT_EQ(typeid(void), typeid(typename c::smaller_c));
	} else {
		// Since we DO have a valid smaller container, make sure it is valid and usable
		EXPECT_NE(typeid(void), typeid(typename c::smaller_c));
		typedef typename c::smaller_c::default_t smaller_t;
		EXPECT_TRUE(static_cast<bool>(DMRC::TypeTraits::is_integral<smaller_t>::value));
		smaller_t vSmall = 0;
		++vSmall;
		// Get the RTTI for our larger container type, for our printout below.
		smaller_t_name = typeid(smaller_t).name();
	}

	// All ContainerType instances should report they are valid
	EXPECT_TRUE(static_cast<bool>(c::is_valid));

	// All default container types should be signed
	EXPECT_FALSE(static_cast<bool>(DMRC::TypeTraits::is_unsigned<container_t>::value));

	// For our valid range of bit widths, everything should be a usable type.
	EXPECT_NE(typeid(void), typeid(container_t));
	EXPECT_NE(typeid(void), typeid(min_unsigned_t));
	EXPECT_NE(typeid(void), typeid(min_signed_t));

	// Print data if requested, after all tests for this case.
	if constexpr (output) {
		printf("[   INFO   ] QM.%02d, %s, %s, %s, %s, %s\n",
		       N,
		       typeid(container_t).name(),
		       typeid(min_unsigned_t).name(),
		       typeid(min_signed_t).name(),
		       larger_t_name.c_str(),
		       smaller_t_name.c_str());
	}

	// Compile-time recursive loop, which iterates us through other Q formats.
	ContainerType_Expectations<N - 1, false, output>();
}

template <>
inline void ContainerType_Expectations<-1, false, true>() {
	printf("[   INFO   ] KEY - unsigned char: %s, char: %s, unsigned short: %s, short: %s, unsigned int: %s, int: %s, unsigned long: %s, long: %s\n",
	       typeid(unsigned char).name(),
	       typeid(char).name(),
	       typeid(unsigned short).name(),
	       typeid(short).name(),
	       typeid(unsigned int).name(),
	       typeid(int).name(),
	       typeid(unsigned long long).name(),
	       typeid(long long).name());
	return;
}

template <>
inline void ContainerType_Expectations<-1, false, false>() {
	return;
}

TEST(Test_Internal_ContainerType, basic_expectations) {
	ContainerType_Expectations<MAX_N_SIGNED>();
}

TEST(Test_Internal_ContainerType, signed_t_void_for_Q64) {
	typedef typename ContainerType<64>::signed_t signed_t;
	ASSERT_EQ(typeid(void), typeid(signed_t));
}

TEST(Test_Internal_ContainerType, default_t_void_for_Q64) {
	typedef typename ContainerType<64>::default_t default_t;
	ASSERT_EQ(typeid(void), typeid(default_t));
}

TEST(Test_Internal_ContainerType, larger_c_void_for_Q64) {
	typedef typename ContainerType<64>::larger_c larger_c;
	ASSERT_EQ(typeid(void), typeid(larger_c));
}

TEST(Test_Internal_ContainerType, smaller_c_void_for_Q0) {
	typedef typename ContainerType<0>::smaller_c smaller_c;
	ASSERT_EQ(typeid(void), typeid(smaller_c));
}
