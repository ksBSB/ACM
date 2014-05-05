#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string.h>
using namespace std;

const int M = 155;
const int N = 105;
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

bign dp[M][M];

void init() {
	for (int i = 0; i <= 150; i++)
		dp[0][i] = 1;
	for (int i = 1; i <= 150; i++) {
		for (int j = 1; j <= 150; j++) {
			for (int k = 0; k < i; k++)
				dp[i][j] = dp[k][j - 1] * dp[i - k - 1][j] + dp[i][j];
		}
	}
}

int main () {
	init();
	int n, d;
	while (scanf("%d%d", &n, &d) == 2) {
		if (n % 2) {
			printf("0\n");
		} else {
			bign sum = dp[n/2][d] - dp[n/2][d - 1];
			sum.put();
			printf("\n");
		}
	}
	return 0;
}
