#include<stdio.h>
#include<string.h>
#include<math.h>

int main(){
	long long n, s[3], q[3];
	while (scanf("%lld", &n) != EOF){
		// Init.
		memset(s, 0, sizeof(s));
		memset(q, 0, sizeof(q));
		long long k = n * ( n + 1 ) / 2;

		for (int i = 1; i <= n; i++)
			for (int j = 0; j < 3; j++)
				s[j] += pow(i, j + 2);
			
		for (int i = 0; i < 3; i++)
			q[i] = pow(k, i + 2) - s[i];

		for (int i = 0;i < 2; i++)
			printf("%lld %lld ", s[i], q[i]);
		printf("%lld %lld\n", s[2], q[2]);
	}
return 0;}	
