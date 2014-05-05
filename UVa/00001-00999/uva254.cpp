#include <stdio.h>
#include <string.h>
#include <math.h>
#define max(a,b) (a)>(b)?(a):(b)
const int N = 1005;

struct bign {
	int s[N];
	bign () {
		memset(s, 0, sizeof(s));
	}
	bign (int number) {*this = number;}
	bign (const char* number) {*this = number;}

	void put();
	void del();

	bign operator = (char *num) {
		s[0] = strlen(num);
		for (int i = 1; i <= s[0]; i++)
			s[i] = num[s[0] - i] - '0';
		return *this;
	}

	bign operator = (int num) {
		char str[N];
		sprintf(str, "%d", num);
		return *this = str;
	}

	bool operator < (const bign& b) const {
		if (s[0] != b.s[0])
			return s[0] < b.s[0];
		for (int i = s[0]; i; i--)
			if (s[i] != b.s[i])
				return s[i] < b.s[i];
		return false;
	}
	bool operator > (const bign& b) const { return b < *this; }
	bool operator <= (const bign& b) const { return !(b < *this); }
	bool operator >= (const bign& b) const { return !(*this < b); }
	bool operator != (const bign& b) const { return b < *this || *this < b;}
	bool operator == (const bign& b) const { return !(b != *this); }

	bign operator + (const bign& c) {
		int sum = 0;
		bign ans;
		ans.s[0] = max(s[0], c.s[0]);

		for (int i = 1; i <= ans.s[0]; i++) {
			if (i <= s[0]) sum += s[i];
			if (i <= c.s[0]) sum += c.s[i];
			ans.s[i] = sum % 10;
			sum /= 10;
		}

		while (sum) {
			ans.s[++ans.s[0]] = sum % 10;
			sum /= 10;
		}
		return ans;
	}

	bign operator - (bign& c) {
		bign ans = *this;
		for (int i = 1; i <= c.s[0]; i++) {
			if (ans.s[i] < c.s[i]) {
				ans.s[i] += 10;
				ans.s[i + 1] -= 1;
			}
			ans.s[i] -= c.s[i];
		}

		ans.del();
		return ans;
	}
};

bign cnt[105], tmp = 1, over = 0;

void init() {
	cnt[0] = 0;
	for (int i = 1; i <= 100; i++)
		cnt[i] = cnt[i - 1] + cnt[i - 1] + tmp;
}

void hanoi(int n, bign k, int& a, int& b, int& c) {
	if (k == over) {
		a += n;
		return;
	}

	for (int i = 1; i <= n; i++) {
		if (cnt[i] == k) {
			a += n - i;
			if (n % 2 == i % 2)
				c += i;
			else
				b += i;
			return;
		} else if (cnt[i] > k) {
			a += n - i;
			if (n % 2 == i % 2) {
				c += 1;
				hanoi(i - 1, k - cnt[i - 1] - tmp, b, a, c);
			} else {
				b += 1;
				hanoi(i - 1, k - cnt[i - 1] - tmp, c, a, b);
			}
			return;	
		}
	}
}

int main () {
	init();
	int n, a, b, c;
	bign k;
	char str[N];
	while (scanf("%d%s", &n, str), n || strcmp(str, "0")) {
		a = b = c = 0;
		k = str;

		if (n % 2)
			hanoi(n, k, a, c, b);
		else
			hanoi(n, k, a, b, c);
		printf("%d %d %d\n", a, b, c);
	}
	return 0;
}

void bign::put() {
	if (s[0] == 0)
		printf("0");
	else
		for (int i = s[0]; i; i--)
			printf("%d", s[i]);
}

void bign::del() {
	while (s[s[0]] == 0) {
		s[0]--;
		if (s[0] == 0) break;
	}
	if (s[0] == 0) {
		s[0] = 1;
		s[1] = 0;
	}
}
