#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 20
const int R = 4;

int n, vis[R][R], rec[N];
struct sque{
    int dir[N][2];
    int cnt;
}b[N];

void get_block(int cur){
    int r, c, t, ok = 0, p, q;
    char str[N];
    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; i++){
    scanf("%s", str);
    for (int j = 0; j < c; j++){
        if (str[j] - '0'){
        if (ok){
            b[cur].dir[b[cur].cnt][0] = i - p;
            b[cur].dir[b[cur].cnt][1] = j - q;
            b[cur].cnt++;
        }
        else{
            b[cur].dir[b[cur].cnt][0] = 0;
            b[cur].dir[b[cur].cnt][1] = 0;
            p = i;
            q = j;
            b[cur].cnt++;
            ok = 1;
        }
        }
    }
    }
}

bool judge(int x, int y, int cur){
    for (int i = 0; i < b[cur].cnt; i++){
    if (x + b[cur].dir[i][0] < 0 || x + b[cur].dir[i][0] >= 4)
        return false;
    if (y + b[cur].dir[i][1] < 0 || y + b[cur].dir[i][1] >= 4)
        return false;
    if (vis[x + b[cur].dir[i][0]][y + b[cur].dir[i][1]])
        return false;
    }
    return true;
}

bool dfs(int x, int y, int sum, int k){
    if (sum == 16){
    if (k == n)
        return true;
    else
        return false;
    }

    if (x == 4)
    return false;
    if (vis[x][y]){
    if (y == 3){
        if (dfs(x + 1, 0, sum, k))
        return true;
    }
    else{
        if (dfs(x, y + 1, sum, k))
        return true;
    }
    return false;
    }

    for (int i = 1; i <= n; i++){
    if (rec[i]) continue;
    if (judge(x, y, i)){
        rec[i] = 1;
        for (int j = 0; j < b[i].cnt; j++)
        vis[x + b[i].dir[j][0]][y + b[i].dir[j][1]] = i;

        if (y == 3){
        if (dfs(x + 1, 0, sum + b[i].cnt, k + 1))
            return true;
        }
        else{
        if (dfs(x, y + 1, sum + b[i].cnt, k + 1))
            return true;
        }

        rec[i] = 0;
        for (int j = 0; j < b[i].cnt; j++)
        vis[x + b[i].dir[j][0]][y + b[i].dir[j][1]] = 0;
    }
    }
    return false;
}

int main(){
    int text = 0;
    while (scanf("%d", &n), n){
    if (text++)
        printf("\n");
    // Init;
    memset(b, 0, sizeof(b));
    memset(vis, 0, sizeof(vis));
    memset(rec, 0, sizeof(rec));

    // Read;
    for (int i = 1; i <= n; i++)
        get_block(i);

    if(dfs(0, 0, 0, 0)){
        for (int i = 0; i < R; i++){
        for (int j = 0; j < R; j++)
            printf("%d", vis[i][j]);
        printf("\n");
        }
    }
    else
        printf("No solution possible\n");
    }
    return 0;
}
