#ifndef DMRC_CORE_COMPARISON_HPP
#define DMRC_CORE_COMPARISON_HPP

namespace DMRC {

template <int lhs, int rhs>
struct is_lt {
	enum {
		value = lhs < rhs
	};
};

template <int lhs, int rhs>
struct is_lte {
	enum {
		value = lhs <= rhs
	};
};

template <int lhs, int rhs>
struct is_gt {
	enum {
		value = lhs > rhs
	};
};

template <int lhs, int rhs>
struct is_gte {
	enum {
		value = lhs >= rhs
	};
};

template <int lhs, int rhs>
struct is_eq {
	enum {
		value = lhs == rhs
	};
};

template <int lhs, int rhs>
struct is_neq {
	enum {
		value = lhs != rhs
	};
};

template <int a, int b>
struct max2 {
	enum { value = a > b ? a : b };
};

template <int a, int b, int c>
struct max3 {
	enum { value = max2<max2<a, b>::value, c>::value };
};

template <int a, int b, int c, int d>
struct max4 {
	enum { value = max2<max3<a, b, c>::value, d>::value };
};

template <int a, int b, int c, int d, int e>
struct max5 {
	enum { value = max2<max4<a, b, c, d>::value, e>::value };
};

template <int a, int b, int c, int d, int e, int f>
struct max6 {
	enum { value = max2<max5<a, b, c, d, e>::value, f>::value };
};

template <int a, int b, int c, int d, int e, int f, int g>
struct max7 {
	enum { value = max2<max6<a, b, c, d, e, f>::value, g>::value };
};

template <int a, int b, int c, int d, int e, int f, int g, int h>
struct max8 {
	enum { value = max2<max7<a, b, c, d, e, f, g>::value, h>::value };
};

template <int a, int b, int c, int d, int e, int f, int g, int h, int i>
struct max9 {
	enum { value = max2<max8<a, b, c, d, e, f, g, h>::value, i>::value };
};

template <int a, int b, int c, int d, int e, int f, int g, int h, int i, int j>
struct max10 {
	enum { value = max2<max9<a, b, c, d, e, f, g, h, i>::value, j>::value };
};

template <int a, int b>
struct min2 {
	enum { value = a > b ? b : a };
};

template <int a, int b, int c>
struct min3 {
	enum { value = min2<min2<a, b>::value, c>::value };
};

template <int a, int b, int c, int d>
struct min4 {
	enum { value = min2<min3<a, b, c>::value, d>::value };
};

template <int a, int b, int c, int d, int e>
struct min5 {
	enum { value = min2<min4<a, b, c, d>::value, e>::value };
};

template <int a, int b, int c, int d, int e, int f>
struct min6 {
	enum { value = min2<min5<a, b, c, d, e>::value, f>::value };
};

template <int a, int b, int c, int d, int e, int f, int g>
struct min7 {
	enum { value = min2<min6<a, b, c, d, e, f>::value, g>::value };
};

template <int a, int b, int c, int d, int e, int f, int g, int h>
struct min8 {
	enum { value = min2<min7<a, b, c, d, e, f, g>::value, h>::value };
};

template <int a, int b, int c, int d, int e, int f, int g, int h, int i>
struct min9 {
	enum { value = min2<min8<a, b, c, d, e, f, g, h>::value, i>::value };
};

template <int a, int b, int c, int d, int e, int f, int g, int h, int i, int j>
struct min10 {
	enum { value = min2<min9<a, b, c, d, e, f, g, h, i>::value, j>::value };
};

template <bool expression, int val_if_true, int val_if_false>
struct val_if {
	enum { value = expression ? val_if_true : val_if_false };
};

}  // namespace DMRC

#endif  // DMRC_CORE_COMPARISON_HPP
