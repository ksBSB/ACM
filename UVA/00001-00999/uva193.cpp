#include <stdio.h> 
#include <string.h> 
#define N 105
int g[N][N], vis[N], rec[N];
int n, n_rec, m;

int judge(int k, int sum){
    for (int i = 0; i <= sum; i++)
	if (g[k][vis[i]])
	    return 1;
    return 0;
}

void DFS(int k, int cnt){
    vis[cnt] = k;
    for (int i = k + 1; i <= n; i++){
	if (judge(i, cnt))  continue;
	DFS(i, cnt + 1);
    }

    if (cnt >= n_rec){
	n_rec = cnt;
	memcpy(rec, vis, sizeof(vis));
    }
}

int main(){
    int t;
    scanf("%d", &t);
    while (t--){
	// Init;
	memset(g, 0, sizeof(g));
	memset(rec, 0, sizeof(rec));
	n_rec = 0;

	// Read;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++){
	    int a, b;
	    scanf("%d%d", &a, &b);
	    g[a][b] = g[b][a] = 1;
	}

	for (int i = 1; i <= n; i++){
	    memset(vis, 0, sizeof(vis));
	    DFS(i, 0);
	}

	printf("%d\n", n_rec + 1);
	for (int i = 0; i < n_rec; i++)
	    printf("%d ", rec[i]);
	printf("%d\n", rec[n_rec]);
    }
    return 0;
}
