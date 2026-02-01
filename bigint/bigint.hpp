#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>

class bigint {
private:
	std::string d; // digits stored in reverse order (units first)
	void trim();

public:
	bigint();
	bigint(int n);
	bigint(const bigint &o);
	bigint &operator=(const bigint &o);

	bigint operator+(const bigint &o) const;
	bigint &operator+=(const bigint &o) { *this = *this + o; return *this; }
	bigint &operator++() { *this += 1; return *this; }
	bigint operator++(int) { bigint tmp(*this); ++(*this); return tmp; }

	bigint operator<<(const bigint &o) const;
	bigint operator>>(const bigint &o) const;
	bigint &operator<<=(const bigint &o) { *this = *this << o; return *this; }
	bigint &operator>>=(const bigint &o) { *this = *this >> o; return *this; }

	bool operator==(const bigint &o) const;
	bool operator<(const bigint &o) const;
	bool operator!=(const bigint &o) const { return !(*this == o); }
	bool operator>(const bigint &o) const { return o < *this; }
	bool operator<=(const bigint &o) const { return !(o < *this); }
	bool operator>=(const bigint &o) const { return !(*this < o); }

	friend std::ostream &operator<<(std::ostream &os, const bigint &b);
};

#endif
