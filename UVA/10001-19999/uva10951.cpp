#include <cstdio>
#include <cstring>

const int maxn = 105;
int M;

void gcd (int a, int b, int& d, int& x, int& y) {
	if (b == 0) {
		d = a;
		x = 1;
		y = 0;
	} else {
		gcd(b, a%b, d, y, x);
		y -= (a/b) * x;
	}
}

int inv (int a, int b) {
	int d, x, y;
	gcd(a, b, d, x, y);
	return (x + b) % b;
}

struct state {
	int d;
	int x[maxn];

	state() {
		d = 0;
		memset(x, 0, sizeof(x));
	}

	void get () {
		scanf("%d", &d);
		for (int i = d; i >= 0; i--)
			scanf("%d", &x[i]);
	}

	void put () {
		printf(" %d", d);
		for (int i = d; i >= 0; i--)
			printf(" %d", x[i]);
	}

	state operator * (const int& a) {
		state ans = *this;
		for (int i = 0; i <= d; i++)
			ans.x[i] = ans.x[i] * a % M;
		ans.del();
		return ans;
	}

	state operator - (const state& a) {

		state ans = *this;
		for (int i = 0; i <= a.d; i++)
			ans.x[d-i] = (ans.x[d-i] - a.x[a.d-i] + M) % M;
		ans.del();
		return ans;
	}

	void del () {
		for (int i = d; i >= 0; i--)
			x[d] = (x[d] + M) % M;

		while (d > 0 && x[d] == 0)
			d--;
	}

	bool empty() {
		return d <= 0 && x[0] == 0;
	}
};

state mod (state a, state b) {
	for (int i = a.d; i >= b.d; i--) {
		int p = a.x[i], q = b.x[b.d];

		state c = b * inv(q, M) * p;;
		a = a - c;
		/*
		a.put();
		printf("\n");
		*/
	}
	return a;
}

state sgcd (state a, state b) {
	return b.empty() ? a : sgcd(b, mod(a, b));
}

int main () {
	int cas = 1;
	while (scanf("%d", &M) == 1 && M) {
		state a, b;
		a.get();
		b.get();

		state c = sgcd(a, b);

		printf("Case %d:", cas++);
		c = c * inv(c.x[c.d], M);
		c.put();
		printf("\n");
	}
	return 0;
}
