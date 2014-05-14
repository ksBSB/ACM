#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
typedef unsigned long long ll;

ll n, m;
int main () {
	while (cin >> n >> m) {
		if (!(n + m))
			break;

		if (m < n)
			swap(n, m);

		cout << n * m * (n+m-2) + 2 * n * (n-1)*(3*m-n-1)/3 << endl;
	}
	return 0;
}
