#include <gtest/gtest.h>

#include <Simple.hpp>

using namespace DMRC::FMA;

TEST(Test_Simple, ctor_noparams) {
	Simple<15> x;
	ASSERT_EQ(0, x.data);
}

TEST(Test_Simple, ctor_primitive_int) {
	Simple<15> x(10);
	ASSERT_EQ(327680, x.data);
}

TEST(Test_Simple, ctor_primitive_float) {
	Simple<15> x(10.5);
	ASSERT_EQ(344064, x.data);
}

TEST(Test_Simple, ctor_other_Simple) {
	Simple<15> x;
	x.data = 1212416;  // 37 << 15
	Simple<12> y(x);
	auto expected = x.data >> 3;
	ASSERT_EQ(expected, y.data);
}

TEST(Test_Simple, set_raw) {
	Simple<15> x;
	x.set_raw(1212416);
	ASSERT_EQ(1212416, x.data);
}

TEST(Test_Simple, from_raw) {
	auto x = Simple<15>::from_raw(1212416);
	ASSERT_EQ(37, x.as<int>());
}

TEST(Test_Simple, as_int) {
	Simple<15> x;
	x.data = 327680;
	ASSERT_EQ(10, x.as<int>());
}

TEST(Test_Simple, as_float) {
	Simple<15> x;
	x.data = 344064;
	ASSERT_EQ(10.5, x.as<float>());
}

TEST(Test_Simple, explicit_operator_int) {
	Simple<15> x;
	x.data = 327680;
	ASSERT_EQ(10, static_cast<int>(x));
}

TEST(Test_Simple, explicit_operator_float) {
	Simple<15> x;
	x.data = 344064;
	ASSERT_EQ(10.5, static_cast<float>(x));
}

TEST(Test_Simple, c_cast_int) {
	Simple<15> x;
	x.data = 327680;
	ASSERT_EQ(10, (int)x);
}

TEST(Test_Simple, c_cast_float) {
	Simple<15> x;
	x.data = 344064;
	ASSERT_EQ(10.5, (float)x);
}

TEST(Test_Simple, operator_plus_equals_Simple) {
	Simple<15> x(10);
	Simple<15> y(12);
	x += y;
	ASSERT_EQ(22, x.as<int>());
}

TEST(Test_Simple, operator_plus_equals_primitive_int) {
	Simple<15> x(10);
	x += 12;
	ASSERT_EQ(22, x.as<int>());
}

TEST(Test_Simple, operator_plus_equals_primitive_float) {
	Simple<15> x(10);
	float y = 12.5;
	x += y;
	;
	ASSERT_EQ(22.5, x.as<float>());
}

TEST(Test_Simple, operator_minus_equals_Simple) {
	Simple<15> x(12);
	Simple<15> y(10);
	x -= y;
	ASSERT_EQ(2, x.as<int>());
}

TEST(Test_Simple, operator_minus_equals_primitive_int) {
	Simple<15> x(12);
	int y = 10;
	x -= y;
	ASSERT_EQ(2, x.as<int>());
}

TEST(Test_Simple, operator_minus_equals_primitive_float) {
	Simple<15> x(12);
	float y = 10.5;
	x -= y;
	ASSERT_EQ(1.5, x.as<float>());
}

TEST(Test_Simple, operator_times_equals_Simple) {
	Simple<15> x(0.125);
	Simple<15> y(1.125);
	x *= y;
	ASSERT_EQ(15, x.n);
	auto expected = 0.140625;
	ASSERT_EQ(expected, x.as<double>());
	auto expected_raw = FPMath<15, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, x.data);
}

TEST(Test_Simple, operator_times_equals_int) {
	Simple<15> x(0.125);
	int y = 5;
	x *= y;
	ASSERT_EQ(15, x.n);
	auto expected = 0.625;
	ASSERT_EQ(expected, x.as<double>());
	auto expected_raw = FPMath<15, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, x.data);
}

TEST(Test_Simple, operator_times_equals_float) {
	Simple<15> x(0.125);
	float y = 1.125;
	x *= y;
	ASSERT_EQ(15, x.n);
	auto expected = 0.140625;
	ASSERT_EQ(expected, x.as<double>());
	auto expected_raw = FPMath<15, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, x.data);
}

TEST(Test_Simple, operator_divide_equals_Simple) {
	Simple<15> x(10);
	Simple<15> y(16);
	x /= y;
	ASSERT_EQ(15, x.n);
	auto expected = 0.625;
	ASSERT_EQ(expected, x.as<double>());
	auto expected_raw = FPMath<15, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, x.data);
}

TEST(Test_Simple, operator_divide_equals_int) {
	Simple<15> x(10);
	int y = 16;
	x /= y;
	ASSERT_EQ(15, x.n);
	auto expected = 0.625;
	ASSERT_EQ(expected, x.as<double>());
	auto expected_raw = FPMath<15, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, x.data);
}

TEST(Test_Simple, operator_divide_equals_float) {
	Simple<15> x(2.1875);
	float y = 3.5;
	x /= y;
	ASSERT_EQ(15, x.n);
	auto expected = 0.625;
	ASSERT_EQ(expected, x.as<double>());
	auto expected_raw = FPMath<15, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, x.data);
}

TEST(Test_Simple, operator_plus_Simple) {
	Simple<15> x(10);
	Simple<15> y(12);
	auto z = x + y;
	ASSERT_EQ(22, z.as<int>());
}

TEST(Test_Simple, operator_plus_primitive_int) {
	Simple<15> x(10);
	int y = 12;
	auto z = x + y;
	ASSERT_EQ(22, z.as<int>());
}

TEST(Test_Simple, operator_plus_primitive_float) {
	Simple<15> x(10);
	float y = 12.5;
	auto z = x + y;
	ASSERT_EQ(22.5, z.as<float>());
}

TEST(Test_Simple, operator_minus_Simple) {
	Simple<15> x(12);
	Simple<15> y(10);
	auto z = x - y;
	ASSERT_EQ(2, z.as<int>());
}

TEST(Test_Simple, operator_minus_primitive_int) {
	Simple<15> x(12);
	int y = 10;
	auto z = x - y;
	ASSERT_EQ(2, z.as<int>());
}

TEST(Test_Simple, operator_minus_primitive_float) {
	Simple<15> x(12);
	float y = 10.5;
	auto z = x - y;
	ASSERT_EQ(1.5, z.as<float>());
}

TEST(Test_Simple, operator_times_Simple) {
	Simple<15> x(0.125);
	Simple<15> y(1.125);
	auto z = x * y;
	const auto expected_n = 15;
	ASSERT_EQ(expected_n, z.n);
	auto expected = 0.140625;
	ASSERT_EQ(expected, z.as<double>());
	auto expected_raw = FPMath<expected_n, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, z.data);
}

TEST(Test_Simple, operator_times_Simple_2) {
	Simple<15> x(12);
	Simple<15> y(0.125);
	auto z = x * y;
	const auto expected_n = 15;
	ASSERT_EQ(expected_n, z.n);
	auto expected = 1.5;
	ASSERT_EQ(expected, z.as<double>());
	auto expected_raw = FPMath<expected_n, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, z.data);
}

TEST(Test_Simple, operator_times_Simple_3) {
	Simple<15> x(12.125);
	Simple<15> y(0.125);
	auto z = x * y;
	const auto expected_n = 15;
	ASSERT_EQ(expected_n, z.n);
	auto expected = 1.515625;
	ASSERT_EQ(expected, z.as<double>());
	auto expected_raw = FPMath<expected_n, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, z.data);
}

TEST(Test_Simple, operator_times_primitive_int) {
	Simple<15> x(3);
	int y = 12;
	auto z = x * y;
	const auto expected_n = 15;
	ASSERT_EQ(expected_n, z.n);
	auto expected = 36.0;
	ASSERT_EQ(expected, z.as<double>());
	auto expected_raw = FPMath<expected_n, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, z.data);
}

TEST(Test_Simple, operator_times_primitive_int_2) {
	Simple<15> x(0.125);
	int y = 12;
	auto z = x * y;
	const auto expected_n = 15;
	ASSERT_EQ(expected_n, z.n);
	auto expected = 1.5;
	ASSERT_EQ(expected, z.as<double>());
	auto expected_raw = FPMath<expected_n, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, z.data);
}

TEST(Test_Simple, operator_times_primitive_float) {
	Simple<15> x(12);
	float y = 0.125;
	auto z = x * y;
	const auto expected_n = 15;
	ASSERT_EQ(expected_n, z.n);
	auto expected = 1.5;
	ASSERT_EQ(expected, z.as<double>());
	auto expected_raw = FPMath<expected_n, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, z.data);
}

TEST(Test_Simple, operator_times_primitive_float_2) {
	Simple<15> x(12.125);
	float y = 0.125;
	auto z = x * y;
	const auto expected_n = 15;
	ASSERT_EQ(expected_n, z.n);
	auto expected = 1.515625;
	ASSERT_EQ(expected, z.as<double>());
	auto expected_raw = FPMath<expected_n, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, z.data);
}

TEST(Test_Simple, operator_divide_Simple) {
	Simple<15> x(10);
	Simple<15> y(5);
	auto z = x / y;
	const auto expected_n = 15;
	ASSERT_EQ(expected_n, z.n);
	auto expected = 2.0;
	ASSERT_EQ(expected, z.as<double>());
	auto expected_raw = FPMath<expected_n, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, z.data);
}

TEST(Test_Simple, operator_divide_Simple_2) {
	Simple<15> x(1.5);
	Simple<15> y(0.125);
	auto z = x / y;
	const auto expected_n = 15;
	ASSERT_EQ(expected_n, z.n);
	auto expected = 12.0;
	ASSERT_EQ(expected, z.as<double>());
	auto expected_raw = FPMath<expected_n, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, z.data);
}

TEST(Test_Simple, operator_divide_Simple_3) {
	Simple<15> x(.75);
	Simple<15> y(1.125);
	auto z = x / y;
	const auto expected_n = 15;
	ASSERT_EQ(expected_n, z.n);
	auto expected = 0.6666;
	ASSERT_NEAR(expected, z.as<double>(), 0.0001);
	auto expected_raw = FPMath<expected_n, int>::to_fixed(expected);
	ASSERT_NEAR(expected_raw, z.data, 3);  // 3 = 0.0001 << 15
}

TEST(Test_Simple, operator_divide_primitive_int) {
	Simple<15> x(36);
	int y = 3;
	auto z = x / y;
	const auto expected_n = 15;
	ASSERT_EQ(expected_n, z.n);
	auto expected = 12;
	ASSERT_EQ(expected, z.as<int>());
	auto expected_raw = FPMath<expected_n, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, z.data);
}

TEST(Test_Simple, operator_divide_primitive_float) {
	Simple<15> x(36);
	float y = 4.5;
	auto z = x / y;
	const auto expected_n = 15;
	ASSERT_EQ(expected_n, z.n);
	auto expected = 8.0;
	ASSERT_EQ(expected, z.as<double>());
	auto expected_raw = FPMath<expected_n, int>::to_fixed(expected);
	ASSERT_EQ(expected_raw, z.data);
}

TEST(Test_Simple, bit_shift_right) {
	Simple<15> x(12.125);
	auto y = x >> fpshift(5);
	ASSERT_EQ(10, y.n);
	ASSERT_EQ(12.125, y.as<double>());
}

TEST(Test_Simple, bit_shift_right_with_multiply) {
	Simple<15> x(12);
	Simple<15> y(0.125);
	auto z = (x * y) >> fpshift(10);
	ASSERT_EQ(5, z.n);
	ASSERT_EQ(1.5, z.as<double>());
}

TEST(Test_Simple, bit_shift_right_with_divide) {
	Simple<15> x(12);
	Simple<15> y(0.125);
	auto z = (x / y) >> fpshift(10);
	ASSERT_EQ(5, z.n);
	ASSERT_EQ(96.0, z.as<double>());
}

TEST(Test_Simple, bit_shift_left) {
	Simple<15> x(12.125);
	auto y = x << fpshift(5);
	ASSERT_EQ(20, y.n);
	ASSERT_EQ(12.125, y.as<double>());
}

TEST(Test_Simple, bit_shift_left_with_multiply) {
	Simple<5> x(12);
	Simple<5> y(0.125);
	auto z = (x * y) << fpshift(10);
	ASSERT_EQ(15, z.n);
	ASSERT_EQ(1.5, z.as<double>());
}

TEST(Test_Simple, bit_shift_left_with_divide) {
	Simple<5> x(12);
	Simple<5> y(0.125);
	auto z = (x / y) << fpshift(10);
	ASSERT_EQ(15, z.n);
	ASSERT_EQ(96.0, z.as<double>());
}
