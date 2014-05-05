#include<stdio.h>

int main(){
	long long a, b, t, n, sum, k;
	scanf("%lld", &t);
	while (t--){
		scanf("%lld%lld", &a, &b);
		n = b - a;
		sum =  0;
		if (n == 0){
			printf("%lld\n", n);
			continue;}

		for (long long i = 0; ; i++){
			sum += 2 * i;
			k = sum - n;
			if (k >= 0 && k < i){
				printf("%lld\n", 2 * i);
				break;
			}
			else if(k >= i){
				printf("%lld\n", 2 * i - 1);
				break;
			}
		}
	}
	return 0;}
