#include <stdio.h>
#include <string.h>
#define N 200

int h, k, Max,maxvalue[N];
int nowvalue[N], recvalue[N];
bool vis[N];
void count(int n,int cur, int sum){
    vis[sum] = true;
    if (n >= h)
	return ;
    for (int i = 0; i <= cur; i++)
	count(n + 1, cur, sum + nowvalue[i]);
}

void find(int cur){
    if (cur >= k){
	if (maxvalue[cur - 1] > Max){
	    Max = maxvalue[cur - 1];
	    memcpy(recvalue, nowvalue, sizeof(nowvalue));
	}
	return;
    }
    for (int i = nowvalue[cur - 1]; i <= maxvalue[cur - 1] + 1; i++){
	memset(vis, 0, sizeof(vis));
	nowvalue[cur] = i;
	count(0, cur, 0);

	int t = 1, num = 0;
	while(vis[t++])num++;

	maxvalue[cur] = num;
	find(cur + 1);	
    }
}

int main(){
    while (scanf("%d%d", &h, &k), h && k){
	// Init.
	memset(vis, 0, sizeof(vis));
	memset(maxvalue, 0, sizeof(maxvalue));
	memset(nowvalue, 0, sizeof(nowvalue));
	memset(recvalue, 0, sizeof(recvalue));

	maxvalue[0] = h;
	nowvalue[0] = 1;
	Max = 0;
	find(1);

	for (int i = 0; i < k; i++)
	    printf("%3d", recvalue[i]);
	printf(" ->%3d\n", Max);
    }
    return 0;
}
