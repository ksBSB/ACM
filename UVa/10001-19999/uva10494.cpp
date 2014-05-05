#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

#define N 1005

struct bign{
	int len, s[N];
    
	bign(){
		memset(s, 0, sizeof(s));
		len = 1;
	}
    
	bign operator = (const char *num){
		len = strlen(num);
		for (int i = 0; i < len; i++)
			s[i] = num[i] - '0';
		return *this;
	}
    
	long long operator % (int k){
		long long sum = 0;
		for (int i = 0; i < len; i++){
			sum = sum * 10 + s[i];
			sum = sum % k;
		}
        
		return sum;
	}
    
    bign operator / (int k){
		bign sum;
		sum.len = 0;
		long long num = 0;
		for (int i = 0; i < len; i++) {
			num = num * 10 + s[i];
			sum.s[sum.len++] = num / k;
			num = num % k;
		}
		return sum;
	}
    
};

int main(){
	char str1[N], c;
	long long num2;
	while (cin >> str1 >> c >> num2){
        
		bign num1;
        
		num1 = str1;
        
		if (c == '/'){
			bign sum = num1 / num2;
			int bo = 0;
			for (int i = 0; i < sum.len; i++){
				if (bo || sum.s[i]){
					bo = 1;
					cout << sum.s[i];
				}
			}
			if (bo ==0)
				cout << bo;
			cout << endl;
		}
		else if (c == '%'){
			long long sum = num1 % num2;
			cout << sum << endl;
		}
        
		memset(str1, 0, sizeof(str1));
	}
	return 0;
}
