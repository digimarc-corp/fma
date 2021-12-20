#include <gtest/gtest.h>

#include <Internal/FPTypeTraits.hpp>
#include <Internal/TypeTraits.hpp>

using namespace DMRC::FMA::Internal;
using namespace DMRC::TypeTraits;

#ifndef NDEBUG
static const bool DEBUG_PRINT_TYPE_INFO = true;
#else
static const bool DEBUG_PRINT_TYPE_INFO = false;
#endif

template <int N_val,
          typename T,
          bool output = DEBUG_PRINT_TYPE_INFO,
          bool header = output>
struct FPTypeTraits_Expectations {
	static const int N = N_val;
	inline static void run() {

		if constexpr (header && output) {
			printf("[   INFO   ] Format, data_t, max_int, min_int, smallest_fraction\n");
		}

		using fptt = FPTypeTraits<N, T>;
		typedef typename fptt::data_t data_t;
		EXPECT_TRUE(static_cast<bool>(is_integral<data_t>::value));

		EXPECT_NE(static_cast<bool>(is_unsigned<data_t>::value),
		          static_cast<bool>(fptt::is_signed));

		EXPECT_EQ(fptt::data_sz, sizeof(typename fptt::data_t) * 8);

		// Because M is auto calculated based on N and the container size, check that if we have a
		// sign bit, it's accounted for in our M.N (integer.fraction bits) format.
		EXPECT_TRUE((is_unsigned<data_t>::value && (fptt::M + N == fptt::data_sz)) || fptt::M + N + 1 == fptt::data_sz);

		if constexpr (output) {
			printf("[   INFO   ] Q%02d.%02d, %s, %20llu, %20lld, %.64f\n",
			       fptt::M,
			       N,
			       typeid(data_t).name(),
			       fptt::max_int,
			       fptt::min_int,
			       fptt::smallest_fraction);
		}

		FPTypeTraits_Expectations<N - 1, T, output, false>::run();
	}
};

template <typename T,
          bool output,
          bool header>
struct FPTypeTraits_Expectations<-1, T, output, header> {
	inline static void run() {
		return;
	}
};

TEST(Test_Internal_FPTypeTraits, basic_expectations_char) {
	FPTypeTraits_Expectations<7, char>::run();
}

TEST(Test_Internal_FPTypeTraits, basic_expectations_unsigned_char) {
	FPTypeTraits_Expectations<8, unsigned char>::run();
}

TEST(Test_Internal_FPTypeTraits, basic_expectations_short) {
	FPTypeTraits_Expectations<15, short>::run();
}

TEST(Test_Internal_FPTypeTraits, basic_expectations_unsigned_short) {
	FPTypeTraits_Expectations<16, unsigned short>::run();
}

TEST(Test_Internal_FPTypeTraits, basic_expectations_int) {
	FPTypeTraits_Expectations<31, int>::run();
}

TEST(Test_Internal_FPTypeTraits, basic_expectations_unsigned_int) {
	FPTypeTraits_Expectations<32, unsigned int>::run();
}

TEST(Test_Internal_FPTypeTraits, basic_expectations_long) {
	FPTypeTraits_Expectations<63, long>::run();
}

TEST(Test_Internal_FPTypeTraits, basic_expectations_unsigned_long) {
	FPTypeTraits_Expectations<64, unsigned long>::run();
}
