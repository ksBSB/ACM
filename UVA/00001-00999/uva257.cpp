#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

const int maxn = 500;

char word[maxn];

int get_hash(int l, int r) {
	int ret = 0;
	for (int i = l; i <= r; i++)
		ret = ret * 26 + word[i] - 'A';
	return ret;
}

bool judge (char* s) {
	int n = strlen(s), c = 0;
	set<int> vec;

	for (int i = 1; i < n - 1; i++) {
		if (s[i-1] == s[i+1]) {
			int tmp = get_hash(i-1, i+1);
			if (vec.find(tmp) == vec.end()) {
				vec.insert(tmp);
				c++;
			}
		}
	}

	for (int i = 0; i < n - 3; i++) {
		if (s[i] == s[i+3] && s[i+1] == s[i+2]) {
			int a = get_hash(i, i + 3);
			int b = get_hash(i + 1, i + 3);
			int d = get_hash(i, i + 2);

			if (vec.find(a) == vec.end() && vec.find(b) == vec.end() && vec.find(d) == vec.end()) {
				vec.insert(a);
				vec.insert(b);
				vec.insert(d);
				c++;
			}
		}
	}

	return c >= 2;
}

int main () {
	while (scanf("%s", word) == 1) {
		if (judge(word))
			printf("%s\n", word);
	}
	return 0;
}
