#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = (1<<10) + 5;

int N, s[maxn][maxn], f[maxn][maxn];
int c, v[maxn];

const char sign[maxn][10] = {"id", "id-", "rot", "rot-", "sym", "sym-", "bhsym", "bhsym-", "bvsym",
	"bvsym-", "div", "div-", "mix", "mix-" };

inline int get_sign (char* word) {
	for (int i = 0; i < 14; i++)
		if (strcmp(word, sign[i]) == 0)
			return i;
	return -1;
}

// 逆时针90
void rot (bool flag) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (flag)
				f[i][j] = s[N-1-j][i];
			else
				f[N-1-j][i] = s[i][j];
		}
	}
	memcpy(s, f, sizeof(f));
}

// 水平翻转
void sym () {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			f[i][j] = s[i][N-1-j];
	}
	memcpy(s, f, sizeof(f));
}

// 下一半水平翻转
void bhsym () {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i >= N/2)
				f[i][j] = s[i][N-1-j];
			else
				f[i][j] = s[i][j];
		}
	}
	memcpy(s, f, sizeof(f));
}

// 下一半垂直翻转
void bvsym () {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i >= N/2)
				f[i][j] = s[3 * N / 2 - i - 1][j];
			else
				f[i][j] = s[i][j];
		}
	}
	memcpy(s, f, sizeof(f));
}

// 分成两份
void div (bool flag) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (flag) {
				if (i&1)
					f[i/2 + N/2][j] = s[i][j];
				else
					f[i/2][j] = s[i][j];
			} else {
				if (i&1)
					f[i][j] = s[i/2 + N/2][j];
				else
					f[i][j] = s[i/2][j];
			}
		}
	}
	memcpy(s, f, sizeof(f));
}

void mix (bool flag) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i&1) {

				if (flag) {
					if (j&1)
						f[i][j] = s[i][N/2 + j/2];
					else
						f[i][j] = s[i-1][N/2 + j/2];
				} else {
					if (j&1)
						f[i][N/2+j/2] = s[i][j];
					else
						f[i-1][N/2+j/2] = s[i][j];
				}
			} else {

				if (flag) {
					if (j&1)
						f[i][j] = s[i+1][j/2];
					else
						f[i][j] = s[i][j/2];
				} else {
					if (j&1)
						f[i+1][j/2] = s[i][j];
					else
						f[i][j/2] = s[i][j];
				}
			}
		}
	}

	/*
	if (N&1) {
		for (int i = 0; i < N; i++) {
			f[i][n] = s[i][n];
			f[n][i] = s[n][i];
		}
	}
	*/
	memcpy(s, f, sizeof(f));
}

void put () {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%d ", s[i][j]);
		printf("\n");
	}
}

void handle () {
	for (int i = c-1; i >= 0; i--) {
		switch (v[i]) {
			case 0:
			case 1:
				break;
			case 2:
				rot(true);
				break;
			case 3:
				rot(false);
				break;
			case 4:
			case 5:
				sym();
				break;;
			case 6:
			case 7:
				bhsym();
				break;
			case 8:
			case 9:
				bvsym();
				break;
			case 10:
				div(true);
				break;
			case 11:
				div(false);
				break;
			case 12:
				mix(true);
				break;
			case 13:
				mix(false);
				break;
		}
	}
}

ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

ll lcm (ll a, ll b) {
	return a / gcd (a, b) * b;
}

ll solve () {
	char str[maxn], word[maxn];
	gets(str);
	int len = strlen(str), mv = 0;

	c = 0;
	for (int i = 0; i <= len; i++) {
		if ((str[i] >= 'a' && str[i] <= 'z') || str[i] == '-')
			word[mv++] = str[i];
		else {
			word[mv] = '\0';
			v[c++] = get_sign(word);
			mv = 0;
		}
	}

	handle();

	ll ret = 1;
	memset(f, 0, sizeof(f));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (f[i][j])
				continue;

			int x = s[i][j] / N;
			int y = s[i][j] % N;
			ll cnt = 0;

			while (f[x][y] == 0) {
				f[x][y] = 1;
				cnt++;

				int tmp = s[x][y];
				x = tmp / N;
				y = tmp % N;
			}

			ret = lcm(ret, cnt);
		}
	}

	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%*c", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				s[i][j] = i * N + j;
		printf("%lld\n", solve());
		if (cas)
			printf("\n");
	}
	return 0;
}
