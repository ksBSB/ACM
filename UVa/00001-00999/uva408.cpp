#include<stdio.h>
int judge(int n, int m){
	for (int i = 2; i <= n && i <= m; i++){
		if (n % i == 0 && m % i == 0)
			return 0;
	}
	return 1;}
int main(){
	int n, m;
	while (scanf("%d%d", &n, &m) !=EOF){
		printf("%10d%10d", n, m);
		if (judge(n, m))
			printf("    Good Choice\n\n");
		else
			printf("    Bad Choice\n\n");
	}
	return 0;}
