#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 25

int g[N][N], vis[N], rou[N], son[N], num[N];
int order, cnt, n = 21;

int get(int x){
    return x != num[x]?num[x] = get(num[x]):x;
}

void print(int sum){
    cnt++;
    for (int i = 0; i <= sum; i++)
        printf("%d ", rou[i]);
    printf("%d\n", order);
}

void DFS(int k, int sum){
    vis[k] = 1;
    rou[sum] = k;
    for (int i = 0; i < son[k]; i++){
        if (vis[g[k][i]]) continue;
        else if (g[k][i] == order)
            print(sum);
        else
            DFS(g[k][i], sum + 1);
    }
    vis[k] = 0;
}

int main(){
    int t = 1;
    while (~scanf("%d", &order)){
        memset(g, 0, sizeof(g));
        memset(vis, 0, sizeof(vis));
        memset(rou, 0, sizeof(rou));
        memset(son, 0, sizeof(son));
        for (int i = 1; i <= n; i++)
            num[i] = i;
        cnt = 0;
        
        int a, b;
        while (scanf("%d%d", &a, &b), a && b){
            g[a][son[a]++] = b;
            g[b][son[b]++] = a;
            num[get(a)] = get(b);
        }
        
        printf("CASE %d:\n", t++);
	if (get(1) == get(order)){
	    for (int i = 1; i <= 21; i++){
		sort(g[i], g[i] + son[i]);
	    }
	    DFS(1, 0);
	}
	printf("There are %d routes from the firestation to streetcorner %d.\n", cnt, order);
    }
    return 0;
}
