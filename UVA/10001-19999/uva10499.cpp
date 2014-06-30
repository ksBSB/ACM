#include<stdio.h>
int main(){
	long long n;
	char c = '%';
	while (scanf("%lld", &n), n > 0){
		if (n == 1)
			printf("0%c\n", c);
		else
			printf("%lld%c\n", 25 * n, c);
	}
	return 0;}
