#include <stdio.h>
#include <string.h>

const int N = 1005;
const int M = 2;
typedef long long ll;

ll g[M][M*2];
struct rNum {
	ll son, mom;
	bool sign;
	rNum () {
		son = mom = 0;
		sign = false;
	}

	void put () {
		if (son == 0)
			printf("0");
		else {
			if (sign) printf("-");
			printf("%lld", son);
			if (mom != 1) printf("/%lld", mom);
		}
		printf("\n");
	}

	bool operator == (const rNum& c) {
		if (son == 0 && c.son == 0) return true;

		return (sign == c.sign)
			&& (son == c.son)
			&& (mom == c.mom);
	}
};

void cat (char* s, ll* u) {
	int len = strlen(s);
	ll flag = 1, sign = 1, num = 0;
	for (int i = 0; i <= len; i++) {
		if (s[i] == '-') {
			sign *= -1;
		} else if (s[i] == '=') {
			flag *= -1;
		} else if (s[i] == '+') {
			sign = 1;
		} else if (s[i] == 'x') {

			if (num == 0) num = 1;
			u[0] += (num * flag * sign);
			num = 0;
			sign = 1;
		} else if (s[i] == 'y') {

			if (num == 0) num = 1;
			u[1] += (num * flag * sign);
			num = 0;
			sign = 1;
		} else if (s[i] >= '0' && s[i] <= '9') {

			num = num * 10 + s[i] - '0';
		} else if (num) {

			u[2] += (num * flag * sign);
			num = 0;
			sign = 1;
		}
	}
}

void init () {
	memset(g, 0, sizeof(g));

	getchar();

	char str[N];
	for (int i = 0; i < 2; i++) {
		gets(str);
		cat (str, g[i]);
	}

	/*
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++)
			printf("%lld ", g[i][j]);
		printf("\n");
	}
	printf("\n");
	*/
}

ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b, a%b);
}

rNum get (ll a, ll b) {
	rNum ans;
	ans.sign = (a * b < 0);

	if (a < 0) a = -a;
	if (b < 0) b = -b;

	ans.son = b;
	ans.mom = a;

	if (b == 0) return ans;
	ll d = gcd(a, b);
	ans.son /= d;
	ans.mom /= d;
	return ans;
}

void solve () {
	ll a1 = g[0][0], a2 = g[1][0];
	ll b1 = g[0][1], b2 = g[1][1];
	ll c1 = g[0][2], c2 = g[1][2];

	ll a = a1 * b2 - a2 * b1;

	if (a == 0) {

		if (a1 == 0 && a2 == 0) {

			printf("don't know\n");
			if (b1 && b2 == 0 && c2 == 0) {

				rNum x = get(b1, -c1);
				x.put();
			} else if (b1 == 0 && c1 == 0 && b2) {

				rNum x = get(b2, -c2);
				x.put();
			} else if (b1 && b2) {
				rNum x1 = get(b1, -c1);
				rNum x2 = get(b2, -c2);

				if (x1 == x2)
					x1.put();
				else
					printf("don't know\n");
			} else
				printf("don't know\n");

		} else if (b1 == 0 && b2 == 0) {

			if (a1 && a2 == 0 && c2 == 0) {

				rNum x = get(a1, -c1);
				x.put();
			} else if (a1 == 0 && c1 == 0 && a2) {

				rNum x = get(a2, -c2);
				x.put();
			} else if (a1 && a2) {
				rNum x1 = get(a1, -c1);
				rNum x2 = get(a2, -c2);

				if (x1 == x2)
					x1.put();
				else
					printf("don't know\n");

			} else
				printf("don't know\n");
			printf("don't know\n");

		} else 
			printf("don't know\ndon't know\n");
		return;
	}

	ll b = c1 * b2 - c2 * b1;
	ll c = g[0][2] * g[1][0] - g[1][2] * g[0][0];
	//printf("%d %d %d\n", a, b, c);
	rNum x = get(a, b*(-1)); 
	rNum y = get(-a, -c);
	x.put();
	y.put();
}

int main () {
	int cas;	
	scanf("%d", &cas);
	while (cas--) {
		init ();
		solve ();
		if (cas) printf("\n");
	}
	return 0;
}
