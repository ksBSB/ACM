#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long type;

struct Fraction {
	type member; // 分子；
	type denominator; // 分母；

	Fraction (type member = 0, type denominator = 1);
	void operator = (type x) { this->set(x, 1); }
	Fraction operator * (const Fraction& u);
	Fraction operator / (const Fraction& u);
	Fraction operator + (const Fraction& u);
	Fraction operator - (const Fraction& u);

	void set(type member, type denominator);
};

inline type gcd (type a, type b) {
	return b == 0 ? a : gcd(b, a % b);
}

/*Code*/
/////////////////////////////////////////////////////
const int maxn = 33;
typedef long long ll;

Fraction dp[maxn+5][maxn+5];

void init () {
	for (int i = 1; i <= maxn; i++) {
		dp[i][0] = 0;
		for (int j = 1; j <= i; j++)
			//dp[i][j] = (dp[i][j-1] * Fraction(j, i) + Fraction(1, 1)) / Fraction(j, i);
			dp[i][j] = dp[i][j-1] + Fraction(i, j);
	}
}

inline int countbit (ll u) {
	int ret = 0;
	while (u) {
		ret++;
		u /= 10;
	}
	return ret;
}


void put_ans (Fraction u) {

	type d = u.member / u.denominator;
	type member = u.member % u.denominator;

	int cn = countbit(d);
	int cd = countbit(u.denominator);

	int n = cn + (cn == 0 ? 0 : 1);
	if (member) {
		for (int i = 0; i < n; i++) printf(" ");
		printf("%lld\n", member);
	}

	printf("%lld", d);
	if (member) {
		if (d)
			printf(" ");
		for (int i = 0; i < cd; i++) printf("-");
		printf("\n");

		for (int i = 0; i < n; i++) printf(" ");
		printf("%lld", u.denominator);
	}
	printf("\n");
}

int main () {
	int n;
	init();
	while (scanf("%d", &n) == 1) {
		put_ans(dp[n][n]);
	}
	return 0;
}

/////////////////////////////////////////////////////

Fraction::Fraction (type member, type denominator) {
	this->set(member, denominator);
}

Fraction Fraction::operator * (const Fraction& u) {
	return Fraction(member * u.member, denominator * u.denominator);
}

Fraction Fraction::operator / (const Fraction& u) {
	return Fraction(member * u.denominator, denominator * u.member);
}

Fraction Fraction::operator + (const Fraction& u) {
	return Fraction(member * u.denominator + denominator * u.member, denominator * u.denominator);
}

Fraction Fraction::operator - (const Fraction& u) {
	return Fraction(member * u.denominator - denominator * u.member, denominator * u.denominator);
}

void Fraction::set (type member, type denominator) {
	type tmp_d = gcd(member, denominator);
	this->member = member / tmp_d;
	this->denominator = denominator / tmp_d;
}
