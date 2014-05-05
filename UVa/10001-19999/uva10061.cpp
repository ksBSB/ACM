#include<stdio.h>
#include<string.h>
#include<math.h>

#define N 10000
int num[N];

int count_digit(int n, int bas){
	double sum = 0;
	for (int i = 1; i <= n; i++)
		sum += log10(i);
	sum = sum / log10(bas);
	return floor(sum + 1e-9) + 1;
}

int count_zore(int n, int bas){
	memset(num, 0, sizeof(num));

	for (int i = 2; i <= n; i++){
		int g = i;
		for (int j = 2; j <= g && j <= bas; j++){
			while (g % j == 0){
				num[j]++;
				g = g / j;
			}
		}
	}

	int cnt = 0;

	while (1){
		int g = bas;

		for (int j = 2; j <= bas; j++){
			while (g % j == 0){
				if (num[j] > 0)
					num[j]--;
				else
					goto out;
				g = g / j;
			}
		}
		cnt++;
	}
out:
	return cnt;
}

int main(){
	int n, bas;
	while (scanf("%d%d", &n, &bas) != EOF){
		int ndigit = count_digit(n, bas);
		int nzore = count_zore(n, bas);
		printf("%d %d\n", nzore, ndigit);
	}
	return 0;
}
