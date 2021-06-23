#ifndef BIGINT_HPP

#define BIGINT_HPP

#include <string>
#include <cstring>
#include <iostream>

class BigInt
{
private:
	std::string v; //store value of the integer
	bool positive; //will be true if the number is non-negative
	/* internal stuff related function */
	static int charNumToInt (char digit); //convert '0', '1', '2', etc to 0, 1, 2, etc
	static char intToCharNum (int digit); //convert 0, 1, 2 etc to '0', '1', '2', etc
	static std::string oneDigitMult (std::string n, char d);

public:
	/* constructor */
	BigInt();
	BigInt(std::string n);
	/* assignment operator */
	void operator = (BigInt& a);
	void operator = (std::string n);
	void operator = (const char* n);
	void operator = (long long int n);

	//outstream for std::cout
	friend std::ostream& operator << (std::ostream& out, const BigInt& n);
	//instream for std::cin
	friend std::istream& operator >> (std::istream& in, BigInt& n);

	//comparison
	friend bool operator > (const BigInt& n1, const BigInt& n2);
	friend bool operator == (const BigInt& n1, const BigInt& n2);

	friend bool operator < (const BigInt& n1, const BigInt& n2);
	friend bool operator >= (const BigInt& n1, const BigInt& n2);
	friend bool operator <= (const BigInt& n1, const BigInt& n2);
	friend bool operator != (const BigInt& n1, const BigInt& n2);
	//addition
	friend std::string operator+ (const BigInt& n1, const BigInt& n2);

	bool isPositive(); //return true is number is non-negative

	~BigInt(); //deconstructor
};

#endif