#include <stdio.h>
#include <string.h>
#define N 50
#define M 10

int n, m, ok, vis[N];
int list[M][N], cnt[M], map[M][M];
int rec[M][M];
struct puzzle{
    int top;
    int right;
    int bottom;
    int lift;
}block[N];

int change_char(char c){
    if (c == 'F')
    return 0;
    else if (c == 'O')
    return 1;
    else if (c == 'I')
    return 2;
}

bool judge(){
    rec[0][3] = m;
    rec[1][3] = n;
    for (int i = 0; i < 2; i++){
    if (rec[i][0] != rec[3 - i][0] || rec[i][0] != rec[i][3])
        return false;
//  if (rec[i][1] + rec[i][2] != rec[i][3])
//      return false;
    for (int j = 1; j <= 2; j++)
        if (rec[i][j] != rec[3 - i][3 - j])
        return false;
    }
//    printf("!\n");
    return true;
}

void handle(int cur, char str[]){
    int p, q, k, t;
    p = block[cur].top = change_char(str[0]);
    rec[0][p]++;
    k = block[cur].right = change_char(str[1]);
    rec[1][k]++;
    t = block[cur].bottom = change_char(str[2]);
    rec[3][t]++;
    q = block[cur].lift = change_char(str[3]);
    rec[2][q]++;
    list [p * 3 + q][cnt[p * 3 + q]++] = cur;
}

int change_num(int x, int y){
    int k = 0;
    if (x == 2)
    k += 1;
    else if (x == 1)
    k += 2;

    if (y == 2)
    k += 3;
    else if (y == 1)
    k += 6;
    return k;
}

void dfs(int x, int y){
    int cur = change_num(block[map[x][y - 1]].right, block[map[x - 1][y]].bottom);
    for (int i = 0; i < cnt[cur]; i++){
    if (vis[list[cur][i]])  continue;

    if (x == n && y == m){
        if (block[list[cur][i]].right + block[list[cur][i]].bottom)
        continue;
        ok = 1;
        return;
    }
    else if (x == n){
        if (block[list[cur][i]].right  == 0 || block[list[cur][i]].bottom)
        continue;
        vis[list[cur][i]] = 1;
        map[x][y] = list[cur][i];
        dfs(x, y + 1);
    }
    else if (y == m){
        if (block[list[cur][i]].right || block[list[cur][i]].bottom == 0)
        continue;
        vis[list[cur][i]] = 1;
        map[x][y] = list[cur][i];
        dfs(x + 1, 1);
    }
    else{
        if (block[list[cur][i]].right == 0 || block[list[cur][i]].bottom == 0)
        continue;
        vis[list[cur][i]] = 1;
        map[x][y] = list[cur][i];
        dfs(x, y + 1);
    }

    vis[list[cur][i]] = 0;
    if (ok) return;
    }
}

int main(){
    char str[M];
    while (scanf("%d%d", &n, &m), n + m){
    // Init.
    memset(block, 0, sizeof(block));
    memset(list, 0, sizeof(list));
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    memset(map, 0, sizeof(map));
    memset(rec, 0, sizeof(rec));
    ok = 0;

    // Read.
    for (int i = 1; i <= n * m; i++){
        scanf("%s", str);
        handle(i, str);
    }

    if (judge())
        dfs(1, 1);

    printf("%s\n", ok?"YES":"NO");
    }
    return 0;}
