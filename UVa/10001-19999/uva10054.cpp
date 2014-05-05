#include<stdio.h>
#include<string.h>
#define M 52
int num[M];
int map[M][M];
int n;

int get_fa(int x){
	return num[x] != x?get_fa(num[x]):x;}

void print(int k){
	for (int i = 0; i < M; i++)
		if (map[k][i]){
			map[k][i]--;
			map[i][k]--;
			print(i);
			printf("%d %d\n", i , k);
		}
}

int main(){
	int t, bo, k = 1;
	int f[M];
	scanf("%d" ,&t);
	while (t--){
		// Init.
		memset(f, 0, sizeof(f));
		memset(map, 0, sizeof(map));
		bo = 0;
		for (int i = 0; i < M; i++)
			num[i] = i;
        
		// Read.
		scanf("%d", &n);
		for (int i = 0; i < n; i++){
			int a, b;
			scanf("%d%d", &a, &b);
			f[a]++;
			f[b]++;
			map[a][b]++;
			map[b][a]++;
            num[get_fa(a)] = get_fa(b);
		}
        
		// Find.
		int god = 0;
    	for (int i = 0; i < M; i++)
			if (f[i] && get_fa(i) == i)
			{
				god = i;
				break;
			}
        
		// Judge.
		for (int i = 0; i < M; i++){
			bo += f[i] % 2;
			if (f[i] && god != get_fa(i))
					bo++;
		}
        
		// Printf.
		printf("Case #%d\n", k++);
		if (bo > 0)
			printf("some beads may be lost\n");
		else
			print(god);
		if (t)
			printf("\n");
	}
	return 0;}
