#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
const int N = 1005;
const int M = 2005;

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

	bign change(bign cur) {
		bign now;
		now = cur;
		for (int i = 0; i < cur.len; i++)
			now.s[i] = cur.s[cur.len - i - 1];
		return now;
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

	bign operator * (const bign &cur){  
		bign sum, a, b;
		sum.len = 0; 
		a = a.change(*this);
		b = b.change(cur);

		for (int i = 0; i < a.len; i++){  
			int g = 0;  

			for (int j = 0; j < b.len; j++){  
				int x = a.s[i] * b.s[j] + g + sum.s[i + j];  
				sum.s[i + j] = x % 10;  
				g = x / 10;  
			}  
			sum.len = i + b.len;  

			while (g){  
				sum.s[sum.len++] = g % 10;  
				g = g / 10;  
			}  
		}  
		return sum.change(sum);  
	}  

	bign operator - (const bign &cur) {
		bign sum, a, b;
		sum.len = len;
		a = a.change(*this);
		b = b.change(cur);

		for (int i = 0; i < b.len; i++) {
			sum.s[i] = a.s[i] - b.s[i] + sum.s[i];
			if (sum.s[i] < 0) {
				sum.s[i] += 10;
				sum.s[i + 1]--;
			}
		}
		for (int i = b.len; i < a.len; i++) {
			sum.s[i] += a.s[i];
			if (sum.s[i] < 0) {
				sum.s[i] += 10;
				sum.s[i + 1]--;
			}
		}
		return sum.change(sum);
	}
};

bign c[M];

void init() {
	bign tmp = 3;
	c[1] = 1;
	c[2] = 3;
	for (int i = 3; i < M; i++)
		c[i] = c[i - 1] * tmp - c[i - 2];
}

int main () {
	int n;
	init();
	while (scanf("%d", &n), n) {
		c[n].put();
		printf("\n");
	}
	return 0;
}
