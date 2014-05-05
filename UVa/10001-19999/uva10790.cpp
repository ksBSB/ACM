#include<stdio.h>
int main(){
	int n, m, t = 1;
	while (scanf("%d%d", &n, &m), n || m){
		long long num = 0, sum = 0;
		for (int i = 1; i < n; i++)
			num += i;
		for (int i = 1; i < m; i++)
			sum += num * i;
		printf("Case %d: %lld\n", t++, sum);
	}
	return 0;}
