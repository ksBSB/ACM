#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define N 220

const char x[] = "AUEOI";
const char y[] = "JSBKTCLDMVNWFXGPYHQZR";

int main(){
	int t, n;
	char p[N], q[N];
	scanf("%d", &t);

	for (int k = 1; k <= t; k++){
		// Init.
		memset(p, 0, sizeof(p));
		memset(q, 0, sizeof(q));

		// Read.
		scanf("%d", &n);
		int xi = (n + 1) / 2, yi = n / 2;
		// 奇数位>=偶数位。 
		for (int i = 0; i < xi; i++){
			p[i] = x[i / 21];
			if (i < yi)
				q[i] = y[i / 5];
		}
		p[xi] = '\0';
		q[yi] = '\0';

		sort(p, p + xi);
		sort(q, q + yi);

		printf("Case %d: ", k);
		for (int i = 0; i < xi; i++){
			printf("%c", p[i]);
			if (i < yi)
				printf("%c", q[i]);
		}
		printf("\n");
	}
	return 0;}
