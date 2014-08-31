#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int a, b, c;

ll f (int x) {
	ll ret = 1;
	for (int i = 0; i < a; i++)
		ret *= x;
	return ret * b + c;
}

bool judge (int s, int x) {
	int ret = 0;
	while (x) {
		ret += x % 10;
		x /= 10;
	}
	return ret == s;
}

int main () {
	vector<int> vec;
	scanf("%d%d%d", &a, &b, &c);
	for (int i = 1; i <= 81; i++) {
		ll u = f(i);
		if (u < 1e9 && judge(i, u))
			vec.push_back((int)u);
	}

	sort(vec.begin(), vec.end());
	printf("%lu\n", vec.size());
	for (int i = 0; i < vec.size(); i++)
		printf("%d%c", vec[i], i == vec.size() - 1 ? '\n' : ' ');
	return 0;
}
