#include<stdio.h>
#include<string.h>

#define N 55

int num[N];

int main(){
	int t, n, cnt, k;
	scanf("%d", &t);
	while (t--){
		// Init.
		memset(num, 0, sizeof(num));
		cnt = 0;

		// Read.
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &num[i]);

		// Count.
		for (int i = 1; i < n; i++){
			for (int j = 0; j < n - i; j++)
				if (num[j] > num[j + 1]){
					k = num[j];
					num[j] = num[j + 1];
					num[j + 1] = k;
					cnt++;
				}
		}

		printf("Optimal train swapping takes %d swaps.\n", cnt);

	}
	return 0;}
