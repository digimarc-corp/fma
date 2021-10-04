#include <gtest/gtest.h>

#include <FPMath.hpp>

using namespace DMRC::FMA;

#define abs_val(a) (((a) > 0) ? (a) : -(a))

TEST(Test_FPMath, round_trip_q1) {
	const int N = 1;
	float precision = 1 << N;  // 2^Q
	for (int i(0); i < 100; i++) {
		float expected = i / precision;
		float actual = FPMath<N>::to<float>(FPMath<N>::to_fixed(expected));
		ASSERT_FLOAT_EQ(actual, expected);
	}
}

TEST(Test_FPMath, round_trip_q2) {
	const int N = 2;
	float precision = 1 << N;  // 2^Q
	for (int i(0); i < 100; i++) {
		float expected = i / precision;
		float actual = FPMath<N>::to<float>(FPMath<N>::to_fixed(expected));
		ASSERT_FLOAT_EQ(actual, expected);
	}
}

TEST(Test_FPMath, round_trip_41) {
	const int N = 4;
	float precision = 1 << N;  // 2^Q
	for (int i(0); i < 100; i++) {
		float expected = i / precision;
		float actual = FPMath<N>::to<float>(FPMath<N>::to_fixed(expected));
		ASSERT_FLOAT_EQ(actual, expected);
	}
}

TEST(Test_FPMath, round_trip_q8) {
	const int N = 8;
	float precision = 1 << N;  // 2^Q
	for (int i(0); i < 100; i++) {
		float expected = i / precision;
		float actual = FPMath<N>::to<float>(FPMath<N>::to_fixed(expected));
		ASSERT_FLOAT_EQ(actual, expected);
	}
}

TEST(Test_FPMath, round_trip_q16) {
	const int N = 16;
	float precision = 1 << N;  // 2^Q
	for (int i(0); i < 100; i++) {
		float expected = i / precision;
		float actual = FPMath<N>::to<float>(FPMath<N>::to_fixed(expected));
		ASSERT_FLOAT_EQ(actual, expected);
	}
}

TEST(Test_FPMath, product_q2) {
	const int N = 2;
	float precision = 1 << (N / 2);  // 2^(N-1)
	for (int i(0); i < 100; i++) {
		float a = i / precision;
		for (int j(0); j < 100; j++) {
			float b = j / precision;
			float expected = a * b;
			float actual = FPMath<N>::to<float>(FPMath<N>::product(FPMath<N>::to_fixed(a), FPMath<N>::to_fixed(b)));
			ASSERT_FLOAT_EQ(expected, actual);
		}
	}
}

TEST(Test_FPMath, product_q4) {
	const int N = 4;
	float precision = 1 << (N / 2);  // 2^(N-1)
	for (int i(0); i < 100; i++) {
		float a = i / precision;
		for (int j(0); j < 100; j++) {
			float b = j / precision;
			float expected = a * b;
			float actual = FPMath<N>::to<float>(FPMath<N>::product(FPMath<N>::to_fixed(a), FPMath<N>::to_fixed(b)));
			ASSERT_FLOAT_EQ(expected, actual);
		}
	}
}

TEST(Test_FPMath, product_q8) {
	const int N = 8;
	float precision = 1 << (N / 2);  // 2^(N-1)
	for (int i(0); i < 100; i++) {
		float a = i / precision;
		for (int j(0); j < 100; j++) {
			float b = j / precision;
			float expected = a * b;
			float actual = FPMath<N>::to<float>(FPMath<N>::product(FPMath<N>::to_fixed(a), FPMath<N>::to_fixed(b)));
			ASSERT_FLOAT_EQ(expected, actual);
		}
	}
}

TEST(Test_FPMath, product_q16) {
	const int N = 16;
	float precision = 1 << (N / 2);  // 2^(N-1)
	for (int i(0); i < 100; i++) {
		float a = i / precision;
		for (int j(0); j < 100; j++) {
			float b = j / precision;
			float expected = a * b;
			float actual = FPMath<N>::to<float>(FPMath<N>::product(FPMath<N>::to_fixed(a), FPMath<N>::to_fixed(b)));
			ASSERT_FLOAT_EQ(expected, actual);
		}
	}
}

TEST(Test_FPMath, quotient_q1) {
	const int N = 1;
	float precision = 1 << N;
	for (int i(0); i < 100; i++) {
		float a = i / precision;
		for (int j(1); j < 100; j++) {
			float b = j / precision;
			float expected = a / b;
			float actual = FPMath<N>::to<float>(FPMath<N>::quotient(FPMath<N>::to_fixed(a), FPMath<N>::to_fixed(b)));
			ASSERT_TRUE(abs_val(expected - actual) < (1 / precision));
		}
	}
}

TEST(Test_FPMath, quotient_q2) {
	const int N = 2;
	float precision = 1 << N;
	for (int i(0); i < 100; i++) {
		float a = i / precision;
		for (int j(1); j < 100; j++) {
			float b = j / precision;
			float expected = a / b;
			float actual = FPMath<N>::to<float>(FPMath<N>::quotient(FPMath<N>::to_fixed(a), FPMath<N>::to_fixed(b)));
			ASSERT_TRUE(abs_val(expected - actual) < (1 / precision));
		}
	}
}

TEST(Test_FPMath, quotient_q4) {
	const int N = 4;
	float precision = 1 << N;
	for (int i(0); i < 100; i++) {
		float a = i / precision;
		for (int j(1); j < 100; j++) {
			float b = j / precision;
			float expected = a / b;
			float actual = FPMath<N>::to<float>(FPMath<N>::quotient(FPMath<N>::to_fixed(a), FPMath<N>::to_fixed(b)));
			ASSERT_TRUE(abs_val(expected - actual) < (1 / precision));
		}
	}
}

TEST(Test_FPMath, quotient_q8) {
	const int N = 8;
	float precision = 1 << N;
	for (int i(0); i < 100; i++) {
		float a = i / precision;
		for (int j(1); j < 100; j++) {
			float b = j / precision;
			float expected = a / b;
			float actual = FPMath<N>::to<float>(FPMath<N>::quotient(FPMath<N>::to_fixed(a), FPMath<N>::to_fixed(b)));
			ASSERT_TRUE(abs_val(expected - actual) < (1 / precision));
		}
	}
}

TEST(Test_FPMath, quotient_q16) {
	const int N = 16;
	float precision = 1 << N;
	for (int i(0); i < 100; i++) {
		float a = i / precision;
		for (int j(1); j < 100; j++) {
			float b = j / precision;
			float expected = a / b;
			float actual = FPMath<N>::to<float>(FPMath<N>::quotient(FPMath<N>::to_fixed(a), FPMath<N>::to_fixed(b)));
			ASSERT_TRUE(abs_val(expected - actual) < (1 / precision));
		}
	}
}

TEST(Test_FPMath, reciprocal_vs_division_q2) {
	const int N = 2;
	float precision = 1 << N;
	for (int j(1); j < 100; j++) {
		float a = j / precision;
		float expected = FPMath<N>::to<float>(FPMath<N>::quotient(FPMath<N>::to_fixed(1.0), FPMath<N>::to_fixed(a)));
		float actual = FPMath<N>::to<float>(FPMath<N>::reciprocal(a));
		ASSERT_EQ(expected, actual);
	}
}

TEST(Test_FPMath, reciprocal_vs_division_q4) {
	const int N = 4;
	float precision = 1 << N;
	for (int j(1); j < 100; j++) {
		float a = j / precision;
		float expected = FPMath<N>::to<float>(FPMath<N>::quotient(FPMath<N>::to_fixed(1.0), FPMath<N>::to_fixed(a)));
		float actual = FPMath<N>::to<float>(FPMath<N>::reciprocal(a));
		ASSERT_EQ(expected, actual);
	}
}

TEST(Test_FPMath, reciprocal_vs_division_q8) {
	const int N = 8;
	float precision = 1 << N;
	for (int j(1); j < 100; j++) {
		float a = j / precision;
		float expected = FPMath<N>::to<float>(FPMath<N>::quotient(FPMath<N>::to_fixed(1.0), FPMath<N>::to_fixed(a)));
		float actual = FPMath<N>::to<float>(FPMath<N>::reciprocal(a));
		ASSERT_EQ(expected, actual);
	}
}

TEST(Test_FPMath, is_integer) {
	ASSERT_TRUE(FPMath<4>::is_integer(FPMath<4>::to_fixed(3.0)));
}

TEST(Test_FPMath, is_integer_NOT) {
	ASSERT_FALSE(FPMath<4>::is_integer(FPMath<4>::to_fixed(3.1415926)));
}

TEST(Test_FPMath, round_UP) {
	const int actual = FPMath<8>::round(FPMath<8>::to_fixed(1.678));
	const int expected = FPMath<8>::to_fixed(2);
	ASSERT_EQ(expected, actual);
}

TEST(Test_FPMath, round_DOWN) {
	const int actual = FPMath<8>::round(FPMath<8>::to_fixed(1.432));
	const int expected = FPMath<8>::to_fixed(1);
	ASSERT_EQ(expected, actual);
}

TEST(Test_FPMath, round_NEGUP) {
	const int actual = FPMath<8>::round(FPMath<8>::to_fixed(-1.678));
	const int expected = FPMath<8>::to_fixed(-2);
	ASSERT_EQ(expected, actual);
}

TEST(Test_FPMath, round_NEGDOWN) {
	const int actual = FPMath<8>::round(FPMath<8>::to_fixed(-1.432));
	const int expected = FPMath<8>::to_fixed(-1);
	ASSERT_EQ(expected, actual);
}

TEST(Test_FPMath, to_fixed_POS_int) {
	const int actual = FPMath<8>::to_fixed(2);
	ASSERT_EQ(512, actual);
}

TEST(Test_FPMath, to_fixed_POS_float) {
	const int actual = FPMath<8>::to_fixed(2.0);
	ASSERT_EQ(512, actual);
}

TEST(Test_FPMath, to_fixed_NEG_int) {
	const int actual = FPMath<8>::to_fixed(-2);
	ASSERT_EQ(-512, actual);
}

TEST(Test_FPMath, to_fixed_NEG_float) {
	const int actual = FPMath<8>::to_fixed(-2.0);
	ASSERT_EQ(-512, actual);
}

TEST(Test_FPMath, floor_POSITIVE) {
	const int actual = FPMath<8>::floor(FPMath<8>::to_fixed(1.567));
	const int expected = FPMath<8>::to_fixed(1.0);
	ASSERT_EQ(expected, actual);
}

TEST(Test_FPMath, floor_NEGATIVE) {
	const int actual = FPMath<8>::floor(FPMath<8>::to_fixed(-1.123));
	const int expected = FPMath<8>::to_fixed(-2.0);
	ASSERT_EQ(expected, actual);
}

TEST(Test_FPMath, ceil_POSITIVE) {
	const int actual = FPMath<8>::ceil(FPMath<8>::to_fixed(1.123));
	const int expected = FPMath<8>::to_fixed(2.0);
	ASSERT_EQ(expected, actual);
}

TEST(Test_FPMath, ceil_NEGATIVE) {
	const int actual = FPMath<8>::ceil(FPMath<8>::to_fixed(-1.789));
	const int expected = FPMath<8>::to_fixed(-1.0);
	ASSERT_EQ(expected, actual);
}

TEST(Test_FPMath, to_int_POSITIVE) {
	float f = 1.678f;
	int actual = FPMath<8>::to<int>(FPMath<8>::to_fixed(f));
	int expected = static_cast<int>(f);
	ASSERT_EQ(expected, actual);

	f = 1.378f;
	actual = FPMath<8>::to<int>(FPMath<8>::to_fixed(f));
	expected = static_cast<int>(f);
	ASSERT_EQ(expected, actual);
}

TEST(Test_FPMath, to_int_NEGATIVE) {
	float f = -1.678f;
	int actual = FPMath<8>::to<int>(FPMath<8>::to_fixed(f));
	int expected = static_cast<int>(f);
	ASSERT_EQ(expected, actual);

	f = -1.378f;
	actual = FPMath<8>::to<int>(FPMath<8>::to_fixed(f));
	expected = static_cast<int>(f);
	ASSERT_EQ(expected, actual);
}