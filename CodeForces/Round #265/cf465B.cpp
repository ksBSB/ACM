#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> vec;

int main () {
	int n, x;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		if (x&1)
			vec.push_back(i);
	}

	int ret = vec.size() ? 1 : 0;
	for (int i = 1; i < vec.size(); i++)
		ret += (vec[i] != vec[i-1] + 1 ? 2 : 1);
	printf("%d\n", ret);
	return 0;
}
