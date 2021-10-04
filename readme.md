# Fixed Martial Arts (`DMRC::FMA`)
A small, fixed-point math library relying on no external libraries, and designed to work with various compilers.

It does not depend on external libraries such as STL. The only external code used is Google Test, for unit-test purposes.

# About FMA
[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-2.1-4baaaa.svg?style=flat)](./code_of_conduct.md)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg?style=flat)](./license.txt)

The goal of FMA is to provide an elementary set of math operations for fixed-point math, and a number of container types with behavior that suits your use case.

FMA uses Q notation as defined by Texas Instruments ($Q_{m.n}$), usually omitting the number of numerical bits (i.e. $Q_n$). That is, `FMA::Simple<10>` is a fixed-point type with 10 fractional bits, since it is $Q_{10}$. Most containers default to the signed 32-bit `int` type to store raw data, meaning $Q_{10}$ is most likely shorthand for $Q_{21.10}$. 

## Supported Containers
* [`DMRC::FMA::Simple`](src/DMRC/FMA/Simple.hpp) - A simple fixed-point type that uses a consistent container size, and no frills.

## Upcoming Containers
* `DMRC::FMA::Flexible` - A container with user-configured containers, anything from a `uint8_t` to an `int64_t`.
* `DMRC::FMA::Adaptable` - A container with user-configured containers, entirely templatized math operations, and providing implementations of those operations for NEON Intrinsics and AVX512 container types
* `DMRC::FMA::Static` - A container providing compile-time values and calculations

## Main Features
### 1. Minimal run-time overhead
FMA inlines nearly its entire library, so most of the structures and function calls compile away back down the raw multiplying and bit-shifting. That way, you get the compile-time safety checks of explicit types, and convenience features offered in FMA, without the overhead. FMA can be used in algorithm code—and is designed to be.
### 2. No implicit conversions
FMA is designed to be dropped into code bases that use raw fixed-point math. To prevent unintended behavior, no primitives can be implicitly converted to any FMA type, or vice versa, and no FMA types implicitly convert to other FMA types. This may not be the most convenient, but it prevents math bugs, even when integrating FMA into algorithm code.
### 3. Convenience
Container types in FMA implement operator overloads to act just like their underlying type, but without the risk of mis-using it, or losing its Q-value due to bad symbol naming. In addition, they have several convenience features, such as:
* Rounding, floor, and ceiling
* Promotion/demotion (function calls, static casts, and bit-shifting styles)
* Conversion to/from any primitive numerical type
* Type traits to access container size, data size, $m$ and $n$ values, etc.