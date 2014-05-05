#include<stdio.h>
#include<string.h>
#include<math.h>
#define N 1000
#define M 10

int main(){
	int t = 1, n, m;
	char str[N], tem[M], q[M];
	int num[M];

	while (scanf("%d", &n), n){
		// Init.
		memset(str, 0, sizeof(str));
		memset(tem, 0, sizeof(tem));
		memset(q, 0, sizeof(q));
		memset(num, 0, sizeof(num));

		// Read.
		for (int i = 0; i < n; i++){
			scanf("%s", tem);
			num[i] = tem[1] - '0';
		}
		scanf("%s", str);
		scanf("%d", &m);

		// Handle.
		int f = pow(2, n);
		for (int i = 0; i < m; i++){
			scanf("%s", tem);
			int k = 1;
			for (int j = 0; j < n; j++){
				if (tem[num[j] - 1] == '1')
					k = k * 2 + 1;
				else
					k = k * 2;
			}
			q[i] = str[k - f];
		}
		q[m] = '\0';
		printf("S-Tree #%d:\n%s\n\n", t++, q);
	}
	return 0;}
