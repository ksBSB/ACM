#include<iostream>
#include<string.h>
#include<stdlib.h>
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
	char str1[N], str2[N], str3[N], c;
	double tem = 2147483647;
	while (cin >> str1 >> c >> str2){
        
		bign num1, num2, sum;
        
		num1 = str1;
		num2 = str2;

		if (c == '*')
			sum = num1 * num2;
		else if (c == '+')
			sum = num1 + num2;

		cout << str1 << " " << c << " " << str2 << endl;

		double t;

		t = atof(str1);

		if (t > tem)
			cout << "first number too big" << endl;

		t = atof(str2);

		if (t > tem)
			cout << "second number too big" << endl;

		for (int i = 0; i < sum.len; i++)
			str3[i] = sum.s[sum.len - i - 1] + '0';

		t = atof(str3);

		if (t > tem)
			cout << "result too big" << endl;
		
		memset(str1, 0, sizeof(str1));
		memset(str2, 0, sizeof(str2));
		memset(str3, 0, sizeof(str3));
	}
	return 0;
}
