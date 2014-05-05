#include<stdio.h>
#include<string.h>
#define N 105
char str[N][N];
int n, m;
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void DFS(int a, int b){
	str[a][b] = '#';
	for (int i = 0; i < 4; i++){
		int p = a + dir[i][0], q = b + dir[i][1];
		if (p < 0 || p >= n)	continue;
		if (q < 0 || q >= m)	continue;
		if (str[p][q] == 'X')	continue;
		if (str[p][q] == '#')	continue;
		DFS(p, q);
	}
}
void find(){
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (str[i][j] == '*'){
				DFS(i, j);
				return ;
			}
}

int main(){
	int t;
	scanf("%d%*c", &t);
	while (t--){
		// Init.
		memset(str, 0, sizeof(str));
		n = 0;

		// Read.
		while (gets(str[n]) != NULL){
			if (strcmp(str[n], "_____") == 0)
				break;
			n++;
		}

		// Handle.
		m  = strlen(str[0]);
		find();

		// Printf.
		for (int i = 0; i < n; i++)
			puts(str[i]);
		puts("_____");
	}
	return 0;}
