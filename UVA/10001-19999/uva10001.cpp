#include <stdio.h>
#include <string.h>
#define N 35
int ok, vis[N], state[N], solve[N];
int dir[8][3]= {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};
char str[N];

void to_base(int k){
    for (int i = 0; i < 8; i++){
	state[i] = k %2;
	k = k / 2;
    }
}

void dfs(int n, int cur){
    if (ok) return;
    if (cur == n){
	if (vis[0] == vis[n] && vis[1] == vis[n + 1])
	    ok = 1;
	    return;
    }
    for (int i = 0; i < 8; i++){
	if (solve[cur] == state[i] && (!cur || (vis[cur] == dir[i][0] && vis[cur + 1] == dir[i][1]))){
	    if (!cur){
		vis[0] = dir[i][0];
		vis[1] = dir[i][1];
	    }
	    vis[cur + 2] = dir[i][2];
	    dfs(n, cur + 1);
	}
    }
}

int main(){
    int k, n;
    while (scanf("%d%d%s", &k, &n, str) != EOF){
	// Init.
	memset(vis, 0, sizeof(vis));
	memset(state, 0, sizeof(state));
	memset(solve, 0, sizeof(solve));
	ok = 0;

	// Handle.
	to_base(k);
	for (int i = 0; i < n; i++)
	    solve[i] = str[i] - '0';
	dfs(n, 0);
	if(ok)
	    puts("REACHABLE");
	else
	    puts("GARDEN OF EDEN");
    }
    return 0;
}
