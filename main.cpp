#include "bigint.hpp"
#include <iostream>
//#include <string>


int main(int argc, char** argv)
{

	BigInt a, b, c;

	std::cout << "Enter number 1 : ";
	std::cin >> a;
	std::cout << "\n Enter number 2 : ";
	std::cin >> b;

	// std::cout << '\n' << a << '>' << b << '=' << (a > b);
	// std::cout << '\n' << a << '<' << b << '=' << (a < b);
	// std::cout << '\n' << a << ">=" << b << '=' << (a >= b);
	// std::cout << '\n' << a << "<=" << b << '=' << (a <= b);
	// std::cout << '\n' << a << "==" << b << '=' << (a == b);
	// std::cout << '\n' << a << "!=" << b << '=' << (a != b);

	c = a + b;
	std::cout << "\n(" << a << ") + (" << b << ") = " << c;


	return 0;
}

