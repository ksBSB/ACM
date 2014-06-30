#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define N 55
char map[N][N];
int n, m, num[N], cnt;
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void DFS(int a, int b){
	map[a][b] = '*';
	for (int i = 0; i < 4; i++){
		int p = a + dir[i][0], q = b + dir[i][1];
		if (p < 0 || p >= n)	continue;
		if (q < 0 || q >= m)	continue;
		if (map[p][q] != 'X')	continue;
		DFS(p, q);
	}
}

int find(int a, int b){
	int sum = 0;
	if (map[a][b] == 'X'){
		DFS(a, b);
		sum++;
		sum += find(a, b);
	}
	else{
		map[a][b] = '.';
		for (int i = 0; i < 4; i++){
			int p = a + dir[i][0], q = b + dir[i][1];
			if (p < 0 || p >= n)	continue;
			if (q < 0 || q >= m)	continue;
			if (map[p][q] == '.')	continue;
			sum += find(p, q);
		}
	}
	return sum;
}

int main(){
	int t = 1;
	while (scanf("%d%d%*c", &m, &n), n || m){
		// Init.
		memset(map, 0, sizeof(map));
		memset(num, 0, sizeof(num));
		cnt = 0;

		// Read.
		for (int i = 0; i < n; i++)
			gets(map[i]);

		// Handle.
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++){
				if (map[i][j] == '*' || map[i][j] == 'X'){
					num[cnt++] = find(i, j);
				}
			}

		// Printf.
		printf("Throw %d\n", t++);
		sort(num, num + cnt);
		for (int i = 0; i < cnt - 1; i++)
			printf("%d ", num[i]);
		printf("%d\n\n", num[cnt - 1]);
	}
	return 0;}
