#include "bigint.hpp"

void bigint::trim() {
	while (d.size() > 1 && d[d.size() - 1] == '0')
		d.erase(d.size() - 1, 1);
}

bigint::bigint() : d("0") {}

bigint::bigint(int n) {
	if (n == 0) { d = "0"; return; }
	while (n > 0) {
		d += (char)('0' + n % 10);
		n /= 10;
	}
}

bigint::bigint(const bigint &o) : d(o.d) {}

bigint &bigint::operator=(const bigint &o) {
	d = o.d;
	return *this;
}

bigint bigint::operator+(const bigint &o) const {
	bigint res;
	res.d = "";
	size_t len = d.size() > o.d.size() ? d.size() : o.d.size();
	int carry = 0;
	for (size_t i = 0; i < len || carry; i++) {
		int sum = carry;
		if (i < d.size()) sum += d[i] - '0';
		if (i < o.d.size()) sum += o.d[i] - '0';
		res.d += (char)('0' + sum % 10);
		carry = sum / 10;
	}
	return res;
}

static int toInt(const std::string &s) {
	int r = 0;
	for (size_t i = s.size(); i > 0; i--)
		r = r * 10 + (s[i - 1] - '0');
	return r;
}

bigint bigint::operator<<(const bigint &o) const {
	int n = toInt(o.d);
	bigint res(*this);
	if (res.d == "0") return res;
	res.d.insert(0, std::string(n, '0'));
	return res;
}

bigint bigint::operator>>(const bigint &o) const {
	int n = toInt(o.d);
	bigint res(*this);
	if ((size_t)n >= res.d.size()) { res.d = "0"; return res; }
	res.d.erase(0, n);
	res.trim();
	return res;
}

bool bigint::operator==(const bigint &o) const {
	return d == o.d;
}

bool bigint::operator<(const bigint &o) const {
	if (d.size() != o.d.size()) return d.size() < o.d.size();
	for (size_t i = d.size(); i > 0; i--) {
		if (d[i - 1] != o.d[i - 1])
			return d[i - 1] < o.d[i - 1];
	}
	return false;
}

std::ostream &operator<<(std::ostream &os, const bigint &b) {
	for (size_t i = b.d.size(); i > 0; i--)
		os << b.d[i - 1];
	return os;
}
