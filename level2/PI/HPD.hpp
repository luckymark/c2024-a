#pragma once
#include <algorithm>
#include <string>
#include <iostream>
bool StrRefToNumGreater(const std::string a, const std::string b) noexcept {
	if(a[0] == b[0] && a[0] == '-') {
		std::string suba = a.substr(1, a.size() - 1);
		std::string subb = b.substr(1, b.size() - 1);
		return (StrRefToNumGreater(subb, suba));
	}
	if(a[0] == '-') return false;
	if(b[0] == '-') return true;
	if(a.size() > b.size()) return true;
	if(a.size() < b.size()) return false;
	int n = a.size();
	for(int i = 0; i < n; i++) {
		if(a[i] > b[i]) return true;
		if(a[i] < b[i]) return false;
	}
	return false;//they are equal
}
void RevStr(std::string &str) {
	std::reverse(str.begin(), str.end());
}
std::string StrMinus(const std::string a, const std::string b) noexcept;
std::string StrAdd(const std::string a, const std::string b) noexcept {
	if(a[0] == '-' && b[0] == '-') {
		std::string suba = a.substr(1, a.size() - 1);
		std::string subb = b.substr(1, b.size() - 1);
		return ("-" + StrAdd(suba, subb));
	}
	if(a[0] == '-') {
		std::string suba = a.substr(1, a.size() - 1);
		return StrMinus(b, suba);
	}
	if(b[0] == '-') {
		std::string subb = b.substr(1, b.size() - 1);
		return StrMinus(a, subb);
	}
	if(a.size() < b.size()) return StrAdd(b, a);
	std::string ans;
	std::string stra = a, strb = b;
	RevStr(stra);
	RevStr(strb);
	int s = stra.size();
	int carry = 0;
	for(int i = 0; i < s; i++) {
		if(i < strb.size()) {
			int m = (int)(stra[i] - '0'), n = (int)(strb[i] - '0');
			int p = m + n + carry;
			carry = 0;
			if(p < 10) ans.push_back((char)(p + '0'));
			else {
				ans.push_back((char)(p - 10 + '0'));
				carry = 1;
			}
		}
		else {
			int m = (int)(stra[i] - '0') + carry;
			carry = 0;
			if(m < 10) ans.push_back((char)(m + '0'));
			else {
				ans.push_back((char)('0'));
				carry = 1;
			}
		}
	}
	if(carry == 1) ans.push_back('1');
	RevStr(ans);
	return ans;
}
std::string StrMinus(const std::string a, const std::string b) noexcept {
	if(a == b) return "0";
	if(b[0] == '-') {
		std::string str = b.substr(1, b.size() - 1);
		return StrAdd(a, str);
	}
	if(a[0] == '-') {
		std::string str = a.substr(1, a.size() - 1);
		std::string ans = "-" + StrAdd(str, b);
		return ans;
	}
	if(!StrRefToNumGreater(a, b)) {
		return "-" + StrMinus(b, a);
	}
	std::string ans = "", stra = a, strb = b;
	RevStr(stra);
	RevStr(strb);
	int s = stra.size();
	int subtract = 0;
	for(int i = 0; i < s; i++) {
		if(i < strb.size()) {
			int k = stra[i] - strb[i] - subtract;
			subtract = 0;
			if(k < 0) {
				subtract = 1;
				k += 10;
			}
			ans.push_back((char)(k + '0'));
		}
		else {
			int k = stra[i] - subtract - '0';
			subtract = 0;
			if(k < 0) {
				subtract = 1;
				k += 10;
			}
			ans.push_back((char)(k + '0'));
		}
	}
	RevStr(ans);
	ans.erase(0, ans.find_first_not_of('0'));
	return ans;
}
#include <vector>
std::string StrMultiply(const std::string &a, const std::string &b) noexcept {
	if(a == "0" || b == "0") return "0";
	if(a == "1") return b;
	if(b == "1") return a;

	bool negative = (a[0] == '-') ^ (b[0] == '-');
	std::string absA = (a[0] == '-') ? a.substr(1) : a;
	std::string absB = (b[0] == '-') ? b.substr(1) : b;

	int n = absA.size();
	int m = absB.size();
	std::vector<int> result(n + m, 0);

	for(int i = n - 1; i >= 0; --i) {
		for(int j = m - 1; j >= 0; --j) {
			int mul = (absA[i] - '0') * (absB[j] - '0');
			int sum = mul + result[i + j + 1];
			result[i + j + 1] = sum % 10;
			result[i + j] += sum / 10;
		}
	}

	std::string ans;
	for(int num : result) {
		if(!(ans.empty() && num == 0)) {
			ans.push_back(num + '0');
		}
	}

	return negative ? "-" + ans : ans;
}
std::string StrDivide(const std::string &a, const std::string &b) {
	if(b == "0") {
		throw std::runtime_error("Division by zero");
	}
	bool negative = (a[0] == '-') ^ (b[0] == '-');
	std::string absA = (a[0] == '-') ? a.substr(1) : a;
	std::string absB = (b[0] == '-') ? b.substr(1) : b;
	if(StrRefToNumGreater(absB, absA)) {
		return "0";
	}
	std::string result;
	std::string current;
	for(char digit : absA) {
		current.push_back(digit);
		int count = 0;
		while(!StrRefToNumGreater(absB, current) && StrRefToNumGreater(current, "0")) {
			current = StrMinus(current, absB);
			count++;
		}
		result.push_back(count + '0');
	}
	result.erase(0, result.find_first_not_of('0'));
	if(result.empty()) {
		return "0";
	}
	return negative ? "-" + result : result;
}
class HPD {
public:
	unsigned long long precision;
	std::string demical;
	int integer;
	static unsigned long long def_precision;
public:
	bool operator==(const HPD &other) const {
		return integer == other.integer && demical == other.demical;
	}
	static void set_defprec(unsigned long long newprec) {
		def_precision = newprec;
	}
	HPD(unsigned long long prec = def_precision) :precision(prec), integer(0), demical(precision, '0') {}
	HPD(unsigned long long num, unsigned long long den, unsigned long long prec = def_precision) : precision(prec), demical(prec, '0') {
		integer = num / den;
		num %= den;
		for(int i = 0; i < precision; ++i) {
			num *= 10;
			demical[i] = num / den + '0';
			num %= den;
		}
	}
	HPD &operator+=(const HPD &hpd) {
		int carry = 0;
		for(int i = precision - 1; i >= 0; --i) {
			int sum = demical[i] - '0' + hpd.demical[i] - '0' + carry;
			demical[i] = sum % 10 + '0';
			carry = sum / 10;
		}
		integer += hpd.integer + carry;
		return *this;
	}
	HPD operator+(const HPD &hpd) {
		HPD ret = *this;
		ret += hpd;
		return ret;
	}
	HPD &operator-=(const HPD &hpd) {
		std::string thisfull = std::to_string(integer) + demical;
		std::string hpdfull = std::to_string(hpd.integer) + hpd.demical;
		std::string resultfull = StrMinus(thisfull, hpdfull);
		int n = resultfull.size();
		if(n > def_precision) {
			integer = std::stoull(resultfull.substr(0, n - def_precision));
			demical = resultfull.substr(n - precision);
		}
		else {
			integer = 0;
			demical = resultfull;
		}
		if(demical.size() < def_precision) {
			std::string temp(def_precision - demical.size(), '0');
			demical = temp + demical;
		}
		return *this;
	}
	HPD operator-(const HPD &hpd) {
		HPD ret = *this;
		ret -= hpd;
		return ret;
	}
	HPD operator*(const HPD &b) const {
		unsigned long long ret_prec = def_precision;
		HPD ret(ret_prec);
		std::string a_full = std::to_string(integer) + demical;
		a_full.erase(0, a_full.find_first_not_of('0'));
		std::string b_full = std::to_string(b.integer) + b.demical;
		b_full.erase(0, b_full.find_first_not_of('0'));
		std::string ret_full = StrMultiply(a_full, b_full);
		int len = ret_full.size() - ret_prec * 2;
		ret.integer = (len > 0) ? std::stoull(ret_full.substr(0, len)) : 0;
		ret.demical = ret_full.substr(((len > 0) ? len : 0), ret_prec + (len > 0 ? 0 : len));
		if(ret.demical.size() < def_precision) {
			std::string temp(def_precision - ret.demical.size(), '0');
			ret.demical = temp + ret.demical;
		}
		return ret;
	}

	HPD operator/(const HPD &b) const {
		unsigned long long result_precision = def_precision;
		HPD result(result_precision);
		std::string a_full = std::to_string(integer) + demical;
		a_full.append(def_precision, '0');
		a_full.erase(0, a_full.find_first_not_of('0'));
		std::string b_full = std::to_string(b.integer) + b.demical;
		b_full.erase(0, b_full.find_first_not_of('0'));
		std::string result_full = StrDivide(a_full, b_full);
		int ret_int_size = result_full.size() - result_precision;
		result.integer = (ret_int_size > 0) ? std::stoull(result_full.substr(0, ret_int_size)) : 0;
		result.demical = result_full.substr(((ret_int_size > 0) ? ret_int_size : 0), result_precision);
		if(result.demical.size() < result_precision) {
			std::string temp(result_precision - result.demical.size(), '0');
			result.demical = temp + result.demical;
		}
		return result;
	}
	friend std::ostream &operator<<(std::ostream &os, const HPD &hpd) {
		os << hpd.integer << '.' << hpd.demical;
		return os;
	}
};
unsigned long long HPD::def_precision = 10000;
