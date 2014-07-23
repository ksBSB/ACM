#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
typedef long long ll;
ll k, p;

int main () {
	while (cin >> k >> p) {
		ll t = k / (p-1);	
		if (t&1)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}
