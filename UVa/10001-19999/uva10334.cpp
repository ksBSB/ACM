#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
const int N = 1005;

struct bign {
	int len, sex;
	int s[N];

	bign() {
		this -> len = 1;
		this -> sex = 0;
		memset(s, 0, sizeof(s));
	}

	bign operator = (const char *number) {
		int begin = 0;
		len = 0;
		sex = 1;
		if (number[begin] == '-') {
			sex = -1;
			begin++;
		}
		else if (number[begin] == '+')
			begin++;

		for (int j = begin; number[j]; j++)
			s[len++] = number[j] - '0';
	}

	bign operator = (int number) {
		char string[N];
		sprintf(string, "%d", number);
		*this = string;
		return *this;
	}

	bign (int number) {*this = number;}
	bign (const char* number) {*this = number;}

	bool operator < (const bign& b) const {
		if (len != b.len)
			return len < b.len;
		for (int i = 0; i < len; i++)
			if (s[i] != b.s[i])
				return s[i] < b.s[i];
		return false;
	}
	bool operator > (const bign& b) const { return b < *this; }
	bool operator <= (const bign& b) const { return !(b < *this); }
	bool operator >= (const bign& b) const { return !(*this < b); }
	bool operator != (const bign& b) const { return b < *this || *this < b;}
	bool operator == (const bign& b) const { return !(b != *this); }

	bign change(bign cur) {
		bign now;
		now = cur;
		for (int i = 0; i < cur.len; i++)
			now.s[i] = cur.s[cur.len - i - 1];
		return now;
	}

	bign operator + (const bign &cur){  
		bign sum, a, b;  
		sum.len = 0;
		a = a.change(*this);
		b = b.change(cur);

		for (int i = 0, g = 0; g || i < a.len || i < b.len; i++){  
			int x = g;  
			if (i < a.len) x += a.s[i];  
			if (i < b.len) x += b.s[i];  
			sum.s[sum.len++] = x % 10;  
			g = x / 10;  
		}  
		return sum.change(sum);  
	} 

	void delZore() {	// 删除前导0.
		bign now = change(*this);
		while (now.s[now.len - 1] == 0 && now.len > 1) {
			now.len--;
		}
		*this = change(now);
	}

	void put() {    // 输出数值。
		delZore();
		if (sex < 0 && (len != 1 || s[0] != 0))
			cout << "-";
		for (int i = 0; i < len; i++)
			cout << s[i];
	}
};

int l, r;
char a[N], b[N];
bign f, s;
bign begin, end;

void solve() {
	int flag = 1;
	for (int i = 1; ; i++) {
		if (i % 2) {
			s = f + s;
			if (s >= begin && flag) {
				l = i;
				flag = 0;
			}
			if (s > end) {
				r = i;
				return ;
			}
		} else {
			f = f + s;	
			if (f >= begin && flag) {
				l = i;
				flag = 0;
			}
			if (f > end) {
				r = i;
				return ;
			}
		}
	}
}

bign num[N];

void init() {
	num[0] = 1;
	num[1] = 2;
	for (int i = 2; i < N; i++)
		num[i] = num[i - 1] + num[i - 2];
}
int main () {
	init();
	int n;
	while (scanf("%d", &n) == 1) {
		num[n].put();
		printf("\n");
	}
	return 0;
}
