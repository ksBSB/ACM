#include<stdio.h>
#include<string.h>

#define N 55

int main(){
	int n, t = 1;
	int num[N];
	while (scanf("%d", &n), n){

		// Init.
		memset(num, 0, sizeof(num));
		int sum = 0, aver;

		// Read.
		for (int i = 0; i < n; i++){
			scanf("%d", &num[i]);
			sum += num[i];
		}
		aver = sum / n;
		sum = 0;

		for (int i = 0; i < n; i++){
			if (num[i] < aver)
				sum = sum + aver - num[i];
		}

		printf("Set #%d\n", t++);
		printf("The minimum number of moves is %d.\n\n", sum);
	}
	return 0;}
