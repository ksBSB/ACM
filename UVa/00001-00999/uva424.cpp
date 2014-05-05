#include<iostream>
#include<string.h>
using namespace std;

#define N 400

struct bign{
	int len, s[N];

	bign(){
		memset(s, 0, sizeof(s));
		len = 1;
	}

	bign operator = (const char *num){
		len = strlen(num);
		for (int i = 0; i < len; i++)
			s[i] = num[len - i - 1] - '0';
		return *this;
	}

	bign operator + (const bign &c){
		bign sum;
		sum.len = 0;

		for (int i = 0, g = 0; g || i < len || i < c.len; i++){
			int x = g;
			if (i < len) x += s[i];
			if (i < c.len) x += c.s[i];
			sum.s[sum.len++] = x % 10;
			g = x / 10;
		}

		return sum;
	}
	
};

int main(){
	char str[N];
	bign sum;
	while (cin >> str){
		if (strcmp(str, "0") == 0)
			break;

		bign num;

		num = str;

		sum = sum + num;

	}

	for (int i = sum.len - 1; i >= 0; i--)
		cout << sum.s[i];
	cout << endl;

	return 0;
}
		
