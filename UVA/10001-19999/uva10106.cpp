#include <iostream>
#include <string.h>

using namespace std;

#define N 62505

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
    
	bign operator * (const bign &c){
		bign sum;
		sum.len = 0;
        
		for (int i = 0; i < len; i++){

			int g = 0;
			for (int j = 0; j < c.len; j++){

				int x = s[i] * c.s[j] + g + sum.s[i + j];

				sum.s[i + j] = x % 10;

				g = x / 10;
			}

			sum.len = i + c.len;

			while (g){
				sum.s[sum.len++] = g % 10;
				g = g / 10;
				
			}
		}

		return sum;
	}

};

int main(){
	char str1[N], str2[N];
	while (cin >> str1 >> str2){

		bign num1, num2, sum;

		num1 = str1;
		num2 = str2;
		sum = num1 * num2;

		int bo = 0;
		for (int i = sum.len - 1; i >= 0; i--){

			if (sum.s[i] || bo){
				
				bo = 1;
				cout << sum.s[i];
			}
		}

		if (bo == 0)
			cout << bo;	
		cout << endl;
		
		memset(str1, 0, sizeof(str1));
		memset(str2, 0, sizeof(str2));
	}
	return 0;
}
