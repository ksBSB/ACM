#include<stdio.h>
#include<string.h>
#define N 1005
struct coor{
    int x;
    int y;
    int z;
    int value;
}que[N];
int n, cnt, max, vis[10];

void DFS(int k, int sum){
    vis[que[k].x] = vis[que[k].y] = vis[que[k].z] = 1;
    cnt += 3;
    sum += que[k].value;
    if (cnt == 9){
        if (max < sum)
           max = sum;
    }
    else{
        for (int i = k + 1; i < n; i++){
            if (vis[que[i].x] || vis[que[i].y] || vis[que[i].z])
                continue;
            DFS(i, sum);
        }
    }
    vis[que[k].x] = vis[que[k].y] = vis[que[k].z] = 0;
    cnt -= 3;
}   

int main(){
    int t = 1;
    while (scanf("%d", &n), n){
        // Init.
        memset(vis, 0, sizeof(vis));
        memset(que, 0, sizeof(vis));
        max = cnt = 0;

        // Read.
        for (int i = 0; i < n; i++)
            scanf("%d%d%d%d", &que[i].x, &que[i].y, &que[i].z, &que[i].value);

        for (int i = 0; i < n; i++)
            DFS(i, 0);

        if (max)
            printf("Case %d: %d\n", t++, max);
        else
            printf("Case %d: -1\n", t++);
    }
    return 0;}
