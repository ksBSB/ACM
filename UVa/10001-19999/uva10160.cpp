#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define N 40
int n, m, Min, rec[N];
int g[N][N], son[N];

int cmp(const int &a, const int &b){
    return a > b;
}

void DFS(int cur, int cnt, int sum){
    if (sum >= Min)  // 剪枝2：当放得服务站数量大于前面计算的最小值时。
    return;
    if (cnt == n)
    Min = sum;

    for (int i = 1; i < cur; i++)   //剪枝3：出现已经遍历的点无法被覆盖，这条路继续收索是无用功。
    if (!rec[i] && g[i][0] < cur)
        return;
    DFS(cur + 1, cnt, sum);

    int k = 0, vis[N];
    for (int i = 0; i < son[cur]; i++)
    if (rec[g[cur][i]] == 0){
        vis[k++] = g[cur][i];
        rec[g[cur][i]] = 1;
    }
    if (!k)     // 剪枝1：增加覆盖点为0。
    return ;

    DFS(cur + 1, cnt + k, sum + 1);

    for (int i = 0; i < k; i++) // 回溯要将点还原，不然答案会错。
    rec[vis[i]] = 0;
}

int main(){
    int a, b;
    while (scanf("%d%d", &n, &m), n + m){
    // Init;
    memset(g, 0, sizeof(g));
    memset(son, 0, sizeof(son));
    memset(rec, 0, sizeof(rec));
    Min = n + 1;

    // Read;
    for (int i = 0; i < m; i++){
        scanf("%d%d", &a, &b);
        g[a][son[a]++] = b;
        g[b][son[b]++] = a;
    }

    // Handle;
    for (int i = 1; i <= n; i++){
        g[i][son[i]++] = i;
        sort(g[i], g[i] + son[i], cmp); // 优化3的优化，具体看解释。
    }
    DFS(1, 0, 0);

    printf("%d\n", Min);
    }
    return 0;
}
