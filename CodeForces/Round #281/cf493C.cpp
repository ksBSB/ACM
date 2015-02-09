#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int inf = 0x3f3f3f3f;
struct state {
	int t, s;
	state(int t = 0, int s = 0) {
		this->t = t;
		this->s = s;
	}
};

int N, M, c[2], L, R, ans = -inf;
vector<state> vec;

inline bool cmp (const state& a, const state& b) {
	return a.t < b.t;
}

inline void judge () {
	int tL = c[0] * 2 + (N - c[0]) * 3;
	int tR = c[1] * 2 + (M - c[1]) * 3;
	if (tL - tR > ans || (tL - tR == ans && tL > L)) {
		L = tL;
		R = tR;
		ans = tL - tR;
	}
}

int main () {

	int a;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &a);
		vec.push_back(state(a, 0));
	}
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d", &a);
		vec.push_back(state(a, 1));
	}
	sort(vec.begin(), vec.end(), cmp);

	judge();
	for (int i = 0; i < vec.size(); i++) {
		c[vec[i].s]++;

		if (i != vec.size() - 1 && vec[i].t == vec[i+1].t)
			continue;
		judge();
	}

	printf("%d:%d\n", L, R);

	return 0;
}
