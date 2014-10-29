#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const char month[15][10] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov"};
const int day[15] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
typedef pair<int,int> pii;
typedef long long ll;

int N, M;
deque<pii> Q;
queue<pii> G;

inline int get_month(char* s) {
	for (int i = 1; i <= 11; i++)
		if (strcmp(s, month[i]) == 0)
			return i;
	return 12;
}

inline bool Leap_year(int x) {
	return (x % 4 == 0 && x % 100) || x % 400 == 0;
}

int get_time() {
	char mon[10];
	int y, d, h, m;
	scanf("%s%d%d%d", mon, &d, &y, &h);
	m = get_month(mon);

	int ret = 0;
	for (int i = 2000; i < y; i++)
		ret += Leap_year(i) ? 366 : 365;

	for (int i = 1; i < m; i++) {
		if (i == 2 && Leap_year(y))
			ret += 29;
		else
			ret += day[i];
	}
	ret += d - 1;
	return ret * 24 + h;
}

void init () {
	int ti, x;
	Q.clear();

	for (int i = 0; i < N; i++) {
		ti = get_time();
		scanf("%d", &x);
		G.push(make_pair(x, ti));
	}
}

ll solve () {
	int S, T, x;
	ll ret = 0;
	scanf("%d%d", &T, &S);
	for (int i = 0; i < M; i++) {
		scanf("%d", &x);
		while (!Q.empty() && x <= Q.back().first + (i - Q.back().second) * S)
			Q.pop_back();
		Q.push_back(make_pair(x, i));
		while (!G.empty() && i == G.front().second) {
			while (!Q.empty() && Q.front().second + T < i)
				Q.pop_front();
			ret += (Q.front().first + (i - Q.front().second) * S) * G.front().first;
			G.pop();
		}
	}
	return ret;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		printf("%I64d\n", solve());
	}
	return 0;
}
