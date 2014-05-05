#include<stdio.h>

int main(){
	int n;
	while (scanf("%d", &n) != EOF){
		int sum = 1;
		for (int i = 1; i <= n; i++){
			sum = sum * i;
			while (sum % 10 == 0){
				sum /= 10;
			}
			sum %= 100000;
		}
		printf("%5d -> %d\n", n, sum % 10);
	}
	return 0;
}
