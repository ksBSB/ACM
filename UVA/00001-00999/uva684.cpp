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
	return b == 0 ? (a > 0 ? a : -a) : gcd(b, a % b);
}

inline type lcm (type a, type b) {
	return a / gcd(a, b) * b;
}

/*Code*/
/////////////////////////////////////////////////////
const int maxn = 105;
typedef long long ll;

int N;
Fraction A[maxn][maxn];;

/*
bool cmp (const Fraction& a, const Fraction& b) {
	ll p = a.member * b.denominator;
	ll q = a.denominator * b.member;

	if (p < 0)
		p = -p;
	if (q < 0)
		q = -q;
	return p > q;
}
*/

inline void self_swap (Fraction& a, Fraction& b) {
	Fraction tmp = a;
	a = b;
	b = tmp;
}

ll solve () {
	int sign = 1;
	Fraction ret = 1;

	for (int i = 0; i < N; i++) {
//		printf("%d!\n", i);
		int r = i;

		for (int j = i+1; j < N; j++)
			if (A[j][i].member)
				r = j;

		if (r != i) {
			for (int j = 0; j < N; j++)
				self_swap(A[i][j], A[r][j]);
			sign *= -1;
		}

		if (A[i][i].member == 0 || A[i][i].denominator == 0)
			return 0;

		for (int j = i + 1; j < N; j++) {
			Fraction f = A[j][i] / A[i][i];

			for (int k = N-1; k >= 0; k--) {
				A[j][k] = A[j][k] - (A[i][k] * f);
			}
		}
		ret = ret * A[i][i];
	}

	/*
	   for (int i = 0; i < N; i++) {
	   for (int j = 0; j < N; j++)
	   printf("%lld/%lld ", A[i][j].member, A[i][j].denominator);
	   printf("\n");
	   }
	   */
	if (ret.denominator < 0)
		sign *= -1;
	return ret.member * sign;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		ll x;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%lld", &x);
				A[i][j] = x;
			}
		}
		printf("%lld\n", solve());
	}
	printf("*\n");
	return 0;
}

/////////////////////////////////////////////////////

Fraction::Fraction (type member, type denominator) {
	this->set(member, denominator);
}

Fraction Fraction::operator * (const Fraction& u) {
	type tmp_p = gcd(member, u.denominator);
	type tmp_q = gcd(u.member, denominator);
	return Fraction( (member / tmp_p) * (u.member / tmp_q), (denominator / tmp_q) * (u.denominator / tmp_p) );
}

Fraction Fraction::operator / (const Fraction& u) {
	type tmp_p = gcd(member, u.member);
	type tmp_q = gcd(denominator, u.denominator);
	return Fraction( (member / tmp_p) * (u.denominator / tmp_q), (denominator / tmp_q) * (u.member / tmp_p));
}

Fraction Fraction::operator + (const Fraction& u) {
	type tmp_l = lcm (denominator, u.denominator);
	return Fraction(tmp_l / denominator * member + tmp_l / u.denominator * u.member, tmp_l);
}

Fraction Fraction::operator - (const Fraction& u) {
	type tmp_l = lcm (denominator, u.denominator);
	return Fraction(tmp_l / denominator * member - tmp_l / u.denominator * u.member, tmp_l);
}

void Fraction::set (type member, type denominator) {

	if (denominator == 0) {
		denominator = 1;
		member = 0;
	}

	type tmp_d = gcd(member, denominator);
	this->member = member / tmp_d;
	this->denominator = denominator / tmp_d;
}
