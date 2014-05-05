#include<stdio.h>

int main(){
	int t, n, sum, i;
	scanf("%d", &t);
	while (t--){
		scanf("%d", &n);
		if (n < 0)
			n = -n;
		for (sum = 0, i = 1; ; i++){
			sum += i;
			if (sum >= n && (sum - n) % 2 == 0){
				printf("%d\n", i);
				break;
			}
		}
		if (t)
			printf("\n");
	}
	return 0;}	
