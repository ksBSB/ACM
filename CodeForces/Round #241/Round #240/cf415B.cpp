#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
const int N =1e5+5;
typedef long long ll;

int main () {
	ll n, a, b, c, w, ans[N];
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i++) {
		cin >> w;
		ans[i] = (w * a % b)/a;
	}	
	for (int i = 1; i < n; i++)
		cout << ans[i] << " ";
	cout << ans[n] << endl;
	return 0;
}
