#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 105

int n, ans, sum, stick[N], vis[N];
int cmp(const int &a, const int &b){
    return a > b;
}
bool dfs(int cnt, int pos, int sum){
    if (cnt == n)   return true;
    for (int i = pos; i < n; i++){
    if (vis[i]) continue;
    if (sum + stick[i] < ans){
        vis[i] = 1;
        if (dfs(cnt + 1, i + 1, sum + stick[i]))
        return true;
        vis[i] = 0;
        while (stick[i] == stick[i + 1] && i + 1 < n){
        i++;
        }
    }
    else if (sum + stick[i] == ans){
        vis[i] = 1;
        if (dfs(cnt + 1, 0, 0))
        return true;
        vis[i] = 0;
        return false;
    }

    if (sum == 0)
        return false;
    }
    return false;
}

int main(){

    while (scanf("%d", &n), n){
    // Init;
    memset(stick, 0, sizeof(stick));
    sum = 0;

    // Read.
    for (int i = 0; i < n; i++){
        scanf("%d", &stick[i]);
        sum += stick[i];
    }

    sort(stick, stick + n, cmp);

    // Handle.
    for (int i = n; i > 0; --i){
        if (sum % i == 0 && (sum / i) >= stick[0]){
        ans = sum / i;
        memset(vis, 0, sizeof(vis));

        if (dfs(0, 0, 0)){
            printf("%d\n", ans);
            break;
        }
        }
    }
    }
    return 0;
}
