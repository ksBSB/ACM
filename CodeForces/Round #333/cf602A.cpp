#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll getnumber () {
	int n, k, a;
	ll ret = 0;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		ret = ret * k + a;
	}
	return ret;
}

int main () {
	ll a = getnumber();
	ll b = getnumber();
	printf("%c\n", a == b ? '=' : (a < b ? '<' : '>'));
	return 0;
}
