#include <climits>
#include <iostream>

using namespace std;

void Sum(int64_t a, int64_t b) {
	if (a > 0 && b > 0) {
		if (INT64_MAX - a >= b) cout << a + b;
		else cout << "Overflow!";
	}
	else if (a < 0 && b < 0) {
		if (a - INT64_MIN + b >= 0) cout << a + b;
		else cout << "Overflow!";
	}
	else cout << a + b;
}

int main() {
	int64_t a, b;
	cin >> a >> b;
	Sum(a, b);
	return 0;
}