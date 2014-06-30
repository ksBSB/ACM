#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

#define N 105

void change(int num[], int n){
	int t;
	for (int i = 1; i <= n / 2; i++){
		t = num[i];
		num[i] = num[n - i + 1];
		num[n - i + 1] = t;
	}
}
 
int main(){
	int n;
	char c;
	int num[N];
	int tem[N];

	while (1){

		// Init.
		memset(num, 0, sizeof(num));
		memset(tem, 0, sizeof(tem));
		n = 0;

		// Read.
		while (1){
			if (scanf("%d%c", &num[++n], &c) != 2)
				goto out;
			tem[n] = num[n];
			if (c == '\n')
				break;
		}

		// Ready.
		sort(tem, tem + n + 1);

		// Printf.
		for (int i = 1; i < n; i++)
			printf("%d ", num[i]);
		printf("%d\n", num[n]);	

		// Count.
		for (int i = n; i >= 0; i--){
			if (num[i] == tem[i])
				continue;
			for (int j = i - 1; j > 0; j--){
				if (num[j] == tem[i]){
					if (j != 1){
						printf("%d ", n + 1 - j);
						change(num, j);
					}
					printf("%d ", n - i + 1);
					change(num, i);
					break;
				}
			}
		}
		printf("0\n");
	}
out:
	return 0;}
