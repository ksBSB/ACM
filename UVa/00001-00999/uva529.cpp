#include <stdio.h>
#include <string.h>
#define N 20
int order, num[N], ok;

void DFS(int cur, int sum){
    if (cur >= sum + 1){
    if (num[sum] == order){
        ok = 1;
        return ;
    }
    }
    else{
    if (num[cur - 1] << sum - cur + 1 < order)
        return;
    for (int i = cur - 1; i >= 0; i--)
        for (int j = cur - 1; j >= 0; j--){
        num[cur] = num[i] + num[j];
        DFS(cur + 1, sum);
        if (ok) return ;
        }
    }
}

int main(){
    while (scanf("%d", &order), order){
    int k, n;
    ok = 0;
    for (k = 0; ; k++)
        if (1 << k >= order)
        break;

    for (n = k; ; n++){
        memset(num, 0, sizeof(num));
        num[1] = 1;
        DFS(2, n);
        if (ok) break;
    }

    for (int i = 1; i < n; i++)
        printf("%d ", num[i]);
    printf("%d\n", num[n]);
    }
    return 0;}
