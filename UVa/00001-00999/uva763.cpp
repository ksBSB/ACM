#include <stdio.h>
#include <string.h>
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
const int N = 105;
const int MAXBIGN = 305;


struct bign {
	int s[MAXBIGN];
	int len;
	bign() {
		len = 1;
		memset(s, 0, sizeof(s));
	}

	bign operator = (const char *number) {
		len = strlen(number);
		for (int i = 0; i < len; i++)
			s[len - i - 1] = number[i] - '0';
		return *this;
	}
	bign operator = (const int num) {
		char number[N];
		sprintf(number, "%d", num);
		*this = number;
		return *this;
	}

	bign (int number) {*this = number;}
	bign (const char* number) {*this = number;}

	bign operator + (const bign &c){  
		bign sum;
		int t = 0;
		sum.len = max(this->len, c.len);
		for (int i = 0; i < sum.len; i++) {
			if (i < this->len) t += this->s[i];
			if (i < c.len) t += c.s[i];
			sum.s[i] = t % 10;
			t /= 10;
		}

		while (t) {
			sum.s[sum.len++] = t % 10;
			t /= 10;
		}
		
		return sum;  
	}
	
	bign operator - (const bign &c) {
		bign ans;
		ans.len = max(this->len, c.len);
		int i;
		
		for (i = 0; i < c.len; i++) {
			if (this->s[i] < c.s[i]) {
				this->s[i] += 10;
				this->s[i + 1]--;
			}
			ans.s[i] = this->s[i] - c.s[i];
		}

	
		
		for (; i < this->len; i++) {
			if (this->s[i] < 0) {
				this->s[i] += 10;
				this->s[i + 1]--;
			}
			ans.s[i] = this->s[i];
		}
		while (ans.s[ans.len - 1] == 0) {
			ans.len--;
		}
		if (ans.len == 0) ans.len = 1;
		return ans;
	}

	void put() {
		if (len == 1 && s[0] == 0) {
			printf("0");
		} else {
			for (int i = len - 1; i >= 0; i--)
				printf("%d", s[i]);
		}
	}

	bool operator < (const bign& b) const {
		if (len != b.len)
			return len < b.len;

		for (int i = len - 1; i >= 0; i--)
			if (s[i] != b.s[i])
				return s[i] < b.s[i];
		return false;
    }
    bool operator > (const bign& b) const { return b < *this; }
    bool operator <= (const bign& b) const { return !(b < *this); }
    bool operator >= (const bign& b) const { return !(*this < b); }
    bool operator != (const bign& b) const { return b < *this || *this < b;}
    bool operator == (const bign& b) const { return !(b != *this); }
};
bign f[N];
void init() {
	f[0] = f[1] = 1;
	for (int i = 2; i < N; i++)
		f[i] = f[i - 1]  + f[i - 2];
}

bign change (char vis[]) {
	int cnt = strlen(vis);
	bign c = 0;
	for (int i = 1; i <= cnt; i++)
		if (vis[cnt - i] == '1')
			c = c + f[i];

	memset(vis, 0, sizeof(vis));
	return c;
}
bign tmp = 0;
void solve(bign sum) {
	if (sum == tmp) {
		printf("0\n");
		return;
	}
	int i;
	for (i = 1; i < N; i++)
		if (f[i] > sum) 
			break;
	int flag = 1;
	for (i--; i; i--) {
		if (f[i] <= sum && flag) {
			sum = sum - f[i];
			printf("1");
			flag = 0;
		} else {	
			printf("0");
			flag = 1;
		}
	}
	printf("\n");
}

int main () {
	init();
	int flag = 0;
	char s1[N], s2[N];
	while (scanf("%s%s", s1, s2) == 2) {
		if (flag) printf("\n");
		else flag = 1;

		bign num1 = change(s1);
		bign num2 = change(s2);

		bign sum = num1 + num2;
		solve(sum);
	}
	return 0;
}
