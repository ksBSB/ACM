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

	Fraction operator *= (const Fraction& u) { return *this = *this * u; }
	Fraction operator /= (const Fraction& u) { return *this = *this / u; }
	Fraction operator += (const Fraction& u) { return *this = *this + u; }
	Fraction operator -= (const Fraction& u) { return *this = *this - u; }

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
typedef Fraction Mat[maxn][maxn];

int N, M, f[maxn];
Mat G, A;

bool cmp (Fraction& a, Fraction& b) {
	return a.member * b.denominator < b.member * a.denominator;
}

inline int getfar (int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

inline void link (int u, int v) {
	int p = getfar(u);
	int q = getfar(v);
	f[p] = q;
}

void init () {
	scanf("%d%d", &N, &M);

	for (int i = 0; i < N; i++) {
		f[i] = i;
		for (int j = 0; j < N; j++)
			G[i][j] = 0;
	}

	int u, v;
	ll R;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%lld", &u, &v, &R);

		if (u == v)
			continue;

		link(u, v);
		G[u][v] += Fraction(1, R);
		G[v][u] += Fraction(1, R);
	}
}

Fraction gauss_elimin (int u, int v, int n) {

	/*
	printf("\n");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++)
			printf("%lld/%lld ", A[i][j].member,  A[i][j].denominator);
		printf("\n");
	}
	*/

	for (int i = 0; i < n; i++) {
		int r;

		for (int j = i; j < n; j++)
			if (A[j][i].member) {
				r = j;
				break;
			}

		if (r != i) {
			for (int j = 0; j <= n; j++)
				swap(A[i][j], A[r][j]);
		}

		if (A[i][i].member == 0)
			continue;

		for (int j = i + 1; j < n; j++) {
			Fraction t = A[j][i] / A[i][i];
			for (int k = 0; k <= n; k++)
				A[j][k] -= A[i][k] * t;
		}
	}

	for (int i = n-1; i >= 0; i--) {
		for (int j = i+1; j < n; j++) {
			if (A[j][j].member)
				A[i][n] -= A[i][j] * A[j][n] / A[j][j];
		}
	}

	/*
	   Fraction U = A[u][n] / A[u][u];
	   printf("%lld/%lld!\n", A[u][n].member, A[u][n].denominator);
	   printf("%lld/%lld!\n", A[u][u].member, A[u][u].denominator);
	   printf("%lld/%lld\n", U.member, U.denominator);

	   Fraction V = A[v][n] / A[v][v];
	   printf("%lld/%lld\n", V.member, V.denominator);
	   */

	return A[u][n] / A[u][u] - A[v][n] / A[v][v];
}

Fraction solve (int u, int v) {
	int n = 0, hash[maxn];
	int hu, hv;

	for (int i = 0; i < N; i++) {
		if (i == u)
			hu = u;

		if (i == v)
			hv = v;

		if (getfar(i) == getfar(u))
			hash[n++] = i;
	}

	n++;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++)
			A[i][j] = 0;
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (i == j)
				continue;

			int p = hash[i];
			int q = hash[j];

			A[i][i] += G[p][q];
			A[i][j] -= G[p][q];
		}
	}

	A[hu][n] = 1;
	A[hv][n] = -1;
	A[n-1][0] = 1;
	return gauss_elimin (hu, hv, n);
}

int main () {
	int cas;
	scanf("%d", &cas);

	for (int kcas = 1; kcas <= cas; kcas++) {
		init();

		int Q, u, v;
		scanf("%d", &Q);
		printf("Case #%d:\n", kcas);
		for (int i = 0; i < Q; i++) {
			scanf("%d%d", &u, &v);

			printf("Resistance between %d and %d is ", u, v);
			if (getfar(u) == getfar(v)) {
				Fraction ans = solve(u, v);
				printf("%lld/%lld\n", ans.member, ans.denominator);
			} else
				printf("1/0\n");
		}
		printf("\n");
	}
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

	if (denominator < 0) {
		denominator = -denominator;
		member = -member;
	}

	type tmp_d = gcd(member, denominator);
	this->member = member / tmp_d;
	this->denominator = denominator / tmp_d;
}
