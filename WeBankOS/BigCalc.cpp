#include <string>
#include <vector>
#include <algorithm>

std::string add(const std::string a, const std::string b) {
	std::vector<char> A(a.begin(), a.end()), B(b.begin(), b.end()), result;
	auto carry = 0;
	for (auto itA = A.rbegin(), itB = B.rbegin(); itA != A.rend() or itB != B.rend(); ) {
		const int tmpCalcA = itA == A.rend() ? '0' : *itA++;
		const int tmpCalcB = itB == B.rend() ? '0' : *itB++;

		const unsigned char tmpNum = tmpCalcA + tmpCalcB + carry - 2 * '0';
		carry = tmpNum / 10;
		result.push_back(tmpNum % 10 + '0');
	}
	if (carry) result.push_back(carry + '0');
	return *new std::string(result.rbegin(), result.rend());
}

std::string sub(const std::string a, const std::string b) {
	std::vector<char> A(a.begin(), a.end()), B(b.begin(), b.end()), result;
	if (a == b) return "0";
	auto carry = 0;
	for (auto itA = A.rbegin(), itB = B.rbegin(); itA != A.rend() or itB != B.rend(); ) {
		const int tmpCalcA = itA == A.rend() ? '0' : *itA++;
		const int tmpCalcB = itB == B.rend() ? '0' : *itB++;

		const char tmpNum = tmpCalcA - tmpCalcB + carry + 10;
		carry = tmpCalcA + carry < tmpCalcB ? -1 : 0;
		result.push_back(abs(tmpNum) % 10 + '0');
	}
	return std::string(find_if(result.rbegin(), result.rend(), [](const char x)->bool {return x > '0'; }), result.rend());
}