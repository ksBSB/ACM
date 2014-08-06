#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int Y = 105;
const int D = 15;
const int M = 35;
const int month[D] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int dp[Y][D][M];

bool is_year (int y) {
	if (y % 100 == 0 && y % 400 == 0)
		return true;
	if (y % 4 == 0 && y % 100)
		return true;
	return false;
}

int get_day (int y, int m) {
	if (y == 2001 && m == 11)
		return 4;

	if (m == 2 && is_year(y))
		return 29;
	return month[m];
}

bool judge_day (int y, int m, int d) {
	if (y > 101)
		return false;
	if (y == 101 && m > 11)
		return false;
	if (y == 101 && m == 11 && d > 4)
		return false;
	return true;
}

bool getnext_day (int& yy, int& mm, int& dd, int y, int m, int d, int type) {
	if (type) {
		dd = d;
		mm = m + 1;

		if (mm > 12) {
			yy = y + 1;
			mm = 1;
		} else
			yy = y;

		if (dd > get_day(yy + 1900, m))
			return false;

	} else {
		dd = d + 1;

		if (dd > get_day(y + 1900, m)) {
			dd = 1;
			mm = m + 1;
		} else
			mm = m;

		if (mm > 12) {
			yy = y + 1;
			mm = 1;
		} else
			yy = y;
	}
	return judge_day(yy, mm, dd);
}

int SG (int y, int m, int d) {
	if (dp[y][m][d] != -1)
		return dp[y][m][d];

	dp[y][m][d] = 0;
	int yy, mm, dd;

	if (getnext_day(yy, mm, dd, y, m, d, 0)) {
		if (SG(yy, mm, dd) == false)
			dp[y][m][d] = 1;
	}

	if (getnext_day(yy, mm, dd, y, m, d, 1)) {
		if (SG(yy, mm, dd) == false)
			dp[y][m][d] = 1;
	}
	return dp[y][m][d];
}

void init () {
	memset(dp, -1, sizeof(dp));
	dp[101][11][4] = 0;

	for (int i = 0; i <= 101; i++) {
		int limit_month = (i == 101 ? 11 : 12);
		for (int j = 1; j <= limit_month; j++) {
			int limit_day = get_day(1900+i, j);

			for (int d = 1; d <= limit_day; d++)
				SG(i, j, d);
		}
	}
}

int main () {
	init();
	int cas, y, m, d;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%d", &y, &m, &d);
		printf("%s\n", dp[y-1900][m][d] ? "YES" : "NO");
	}
	return 0;
}
