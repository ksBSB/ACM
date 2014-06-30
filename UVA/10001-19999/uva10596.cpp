#include<stdio.h>
#include<string.h>
#define M 205
int num[M], cnt[M];
int n, m, bo;

int get_fa(int x){
	return num[x] != x?get_fa(num[x]):x;}

int main(){
	while (scanf("%d%d", &n, &m) != EOF){
		// Init.
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; i++)
			num[i] = i;
		bo = 0;
        
		// Read.
		for (int i = 0; i < m; i++){
			int a, b;
			scanf("%d%d", &a, &b);
			cnt[a]++;
			cnt[b]++;
            num[get_fa(a)] = get_fa(b);
		}
        
		// Find.
		int god = 0;
		for (int i = 0; i < M; i++)
			if (cnt[i] && get_fa(i) == i)
			{
				god = i;
				break;
			}

		// Judge.
		for (int i = 0; i < n; i++){
			bo += cnt[i] % 2;
			if (cnt && god != get_fa(i))
				bo++;
		}

		// Printf.
		if (bo > 0)
			printf("Not Possible\n");
		else
			printf("Possible\n");
	}
	return 0;}
