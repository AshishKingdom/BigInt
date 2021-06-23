#include "bigint.hpp"

BigInt::BigInt() { //constructor
	v = "0";
	positive = true;
}
BigInt::BigInt(std::string n) {
	try {
		positive = true; //assuming number is positive
		std::string tmp;
		int i = 0;
		for (char d : n) //for each character in string n
		{
			int x = static_cast<int>(d);
			if (x < 48 || x > 57) { //found a non-numeric character... that's illegal. :)
				if (x == 45 || x == 43) {
					if (i == 0) { //it simply means unary - or unary + was used. ;)
						positive = (x == 43);
						i++; continue; //prevent '-' from storing in the number
					} else {
						throw n;
					}
				} else {
					throw n;
				}
			}
			tmp += d;
			i++;
		}
		v = tmp; //no non-numeric characters.. so its safe to assign the values.
	} catch (std::string s) {
		std::cerr << "ERROR: string literal contains non-numeric character(s) - " << s << '\n';
	}
}

void BigInt::operator=(BigInt& a) { //copy values from object a
	v = a.v;
	positive = a.isPositive();
}

void BigInt::operator=(std::string n) {
	try {
		int i = 0;
		positive = true; //assuming number is positive
		std::string tmp;
		for (char d : n) { //again making sure that there is no non-numeric character
			int x = static_cast<int>(d);
			if (x < 48 || x > 57) {
				if (d == 45 || d == 43) { //it just mean unary - or unary + was used
					if (i == 0) {
						positive = (d == 43);
						i++; continue;
					} else {
						throw n;
					}
				} else {
					throw n;
				}
			};
			tmp += d;
			i++;
		}
		v = tmp;
	} catch (std::string s) {
		std::cerr << "ERROR in operator=: string literal contains non-numeric character(s) - " << s << '\n';
	}
}

void BigInt::operator=(const char* n) { //similar to above one, but now its for const  char*
	try {
		int i = 0;
		positive = true;
		std::string num;
		num = "";
		char d = *(n + i);
		while (d != 0) {
			if (d < 48 || d > 57) {
				if (d == 45 || d == 43) {
					if (i == 0) { //it simply means unary - or unary + was put there;
						positive = (d = 43);
						//skip the '-' from getting stored in num variable
						i++; d = *(n + i);
						continue;
					} else {
						throw d;
					}
				} else {
					throw d;
				}
			}
			num += d;
			i++;
			d = *(n + i);
		}
		v = num;
	} catch (char d) {
		std::cerr << "ERROR in operator=: char* contains non-numeric literal - " << d;
	}
}

void BigInt::operator=(long long int n) {
	bool p = n >= 0 ? true : false; //know if n is non-negative or not
	positive = p;
	if (!p)n *= -1; //if n is negative, we will make it positive as we are only interested in its magnitude
	std::string tmp, final;
	int d = 0;
	while (n > 0) {
		d = n % 10;
		n /= 10;
		tmp += intToCharNum(d); //storing the digits
	}
	for (int i = tmp.size() - 1; i >= 0; --i)final += tmp[i]; //we need to reverse it.. so that numbers gets correclty represented in string
	v = final;
}

BigInt::~BigInt() { //deconstructor

}

std::string BigInt::oneDigitMult (std::string n, char d) { //multipy a string number to a string numeric digit. example oneDigitMult("23",'5') returns "115"
	std::string final = "";
	if (d == '0') {
		final = "0"; //digit is 0, so multiplication results in 0. :)
	}
	else if (d == '1') {
		final = n; //multiplication with 1 result in number itself... no change
	}
	else if (n == "1") {
		final = d; //multiplication with 1 result in number itself... no change
	}
	else {
		int total = n.size(); //total no. of digits in n
		int carry = 0; //will store carry when as we mulitply d with each digit of n
		int int_d = charNumToInt(d); //convert character d into numerical d;
		int a = 0;
		std::string product = ""; //will store product but in reverse way... we will fixed it in final variable in the next 2nd for loop.
		for (int i = total - 1; i >= 0; i--) {
			a = charNumToInt(n[i]) * int_d + carry; //multiply digits and add carry
			carry = a / 10; //if a>10, dividing by 10 will give tenth place (note that carry is an int variable so it will not contain decimal part)
			product += intToCharNum(a % 10); //we will only store the digit at ones place because tenth place digit is used in carry
			if (i == 0 && a > 10)product += intToCharNum(a / 10); //for i=0 or for the last digit (one placed at extreme left), we don't need to pass the carry if a>10
		}
		//we need to reverse the string product to get correct result of the multiplication
		total = product.size();
		for (int i = total - 1; i >= 0; i--)final += product[i];
	}
	return final;

}
int BigInt::charNumToInt (char digit) {
	return static_cast<int>(digit) - 48; //convert '0', '1', '2', etc to 0, 1, 2, etc
}
char BigInt::intToCharNum (int digit) {
	return (static_cast<char>(digit + 48)); //convert 0, 1, 2 etc to '0', '1', '2', etc
}

bool BigInt::isPositive() {
	return positive;
}


//I/O
std::ostream& operator << (std::ostream& out, const BigInt& n) {
	out << (n.positive ? '+' : '-') << (n.v);
	return out;
}

std::istream& operator >> ( std::istream& in, BigInt& n) {
	std::string tmp;
	in >> tmp; //take value
	n = tmp; //set value
	return in;
}

//comparison
bool operator > (const BigInt& n1, const BigInt& n2) {
	if (n1.positive && !n2.positive)return true; //n2 is negative & n1 is non-negative
	else if (n1.positive && n2.positive) { //if both int have same sign '+'
		int s1, s2; //gets number of digits it has
		s1 = n1.v.size(); s2 = n2.v.size();
		if (s1 > s2)return true;
		else if (s1 == s2)return (n1.v[0] > n2.v[0]); //if the first digit from left is greater, then of course whole number is greater than n2
		else return false; //means n2 has more no. of digits than n1. so, n1 is not greater than n2.
	} else if (!n1.positive && !n2.positive) { //if both int have same sign '-'
		int s1, s2; //gets number of digits it has
		s1 = n1.v.size(); s2 = n2.v.size();
		if (s1 < s2)return true;
		else if (s1 == s2)return (n1.v[0] < n2.v[0]); //if the first digit from left is greater, then of course whole number is smaller than n1 (as both are negative)
		else return false; //means n1 has more no. of digits than n2. so, n2 is greater than n1. (as both are negative)
	}
	else return false;
}

bool operator == (const BigInt& n1, const BigInt& n2) {
	bool x = true;
	if ((n1.v.size() == n2.v.size()) && (n1.positive + n2.positive != 1)) { //make sure that both int have same sign & same no. of digits
		for (int i = 0; i < n1.v.size(); ++i) {
			if (n1.v[i] != n2.v[i]) { //if they differ at any place
				x = false;
				break;
			}
		}
	} else {
		x = false;
	}
	return x;
}

bool operator < (const BigInt& n1, const BigInt& n2) {
	return (n2 > n1);
}

bool operator >= (const BigInt& n1, const BigInt& n2) {
	return ((n1 > n2) || (n1 == n2));
}

bool operator <= (const BigInt& n1, const BigInt& n2) {
	return ((n2 > n1) || (n1 == n2));
}

bool operator != (const BigInt& n1, const BigInt& n2) {
	return ( !(n1 == n2) );
}

//addition
std::string operator+(const BigInt& n1, const BigInt& n2) {
	//this function is only valid if n1 & n2 are both either positive or negative.
	if (!(n1.positive ^ n2.positive)) {
		int  s1, s2; //no. of digits in n1 & n2.
		std::string tmp, final;
		s1 = n1.v.size(); s2 = n2.v.size();
		if (s1 >= s2) {
			int d1, d2, diff, carry, digit; //d1 & d2 -> digit of n1 & n1 when index is given. carry and digit is used in loop
			carry = 0;
			digit = 0;
			diff = s1 - s2;
			for (int i = s1 - 1; i >= 0; --i)
			{
				d1 = n1.charNumToInt(n1.v[i]);
				d2 = (i - diff >= 0) ? n1.charNumToInt(n2.v[i - diff]) : 0; //return zero if index become -ve, else return the digit at that position. Its just like converting 123+3 to 123+003
				digit = (d1 + d2) + carry;
				carry = digit / 10;
				tmp += n1.intToCharNum(digit % 10);
				if (i == 0 && digit >= 10)tmp += n1.intToCharNum(digit / 10);
			}
		} else {
			return (n2 + n1); //just call this function but with swaped arguments
		}
		for (int i = tmp.size() - 1; i >= 0; --i)final += tmp[i];
		char p = n1.positive ? '+' : '-';
		final = p + final;
		return final;
	}
}