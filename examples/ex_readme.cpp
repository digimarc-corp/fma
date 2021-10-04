#include <iostream>
#include <DMRC/FMA/Core>
#include <DMRC/FMA/Typedefs>

using namespace std;
using namespace DMRC::FMA::Typedefs;

int main(int argc, char** argv) {
	// Two ways to initialize. Implicit assignment from primitives is not allowed.
	sQ15_t x(12);
	sQ15_t y = static_cast<sQ15_t>(3);

	// Basic arithmetic
	sQ15_t z1 = x + y;
	sQ15_t z2 = x - y;
	sQ15_t z3 = x * y; // Multiplication maintains Q value
	sQ15_t z4 = x / y; // Division maintains Q value

	cout << "x + y = " << z1.as<double>() << endl;
	cout << "x - y = " << z2.as<double>() << endl;
	cout << "x * y = " << z3.as<double>() << endl;
	cout << "x / y = " << z4.as<double>() << endl;

	// Two basic conversion techniques: casting and bit shifting
	sQ12_t a = static_cast<sQ12_t>(x);
	sQ12_t b = y  >> fpshift(3); // operator>> is demotion: 15-3=12
	sQ17_t c = (a + b) << fpshift(5); // operator<< is promotion: 12+5=17

	cout << "a + b = " << c.as<double>() << endl;
}