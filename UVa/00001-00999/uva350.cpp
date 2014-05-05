#include<stdio.h>
#include<string.h>
#define N 100000
int num[N];
int main(){
	int z, i, m, l, k;
	int cnt, ti = 1;
	while (scanf("%d%d%d%d", &z, &i, &m, &l) != EOF && z && i && m && l){
		cnt = 1;
		memset(num, 0, sizeof(num));
		num[l] = 1;
		do{
		 l = (z * l + i) % m;
		 if (num[l] != 0)
			 break;
		 else
			 num[l] = ++cnt;
		 }while (1);
		printf("Case %d: %d\n", ti++, ++cnt - num[l]);
	}
	return 0;
}
