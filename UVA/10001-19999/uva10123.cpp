#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

#define N 30

struct block{
    int x;
    int w;
}b[3][N], rec[N];

int L, M, n, cnt[3], vis[3][N];
int ok, pace[3];
double wr1, wr2, wl1, wl2;

bool cmp(const block &a, const block &b){
    return abs(a.x * a.w) < abs(b.x * b.w);
}

void DFS(int cur,int dir, int bo){
    if (cur >= n){
    ok = 1; 
    return;
    }
    int yes = 0;
    for (int i = pace[dir]; i < cnt[dir]; i++){
    if(dir == 0){
//      printf("L%.3lf %.3lf\n", wr2, wl2 + (-3 - b[dir][i].x) * b[dir][i].w);
        if(wr2 < (wl2 + (-3 - b[dir][i].x) * b[dir][i].w)){
        pace[dir] = i;
        break;
        }
        wl1 = wl1 + (3 - b[dir][i].x) * b[dir][i].w;
        wl2 = wl2 + (-3 - b[dir][i].x) * b[dir][i].w;
    }
    else{
//      printf("R%.3lf %.3lf\n", wr1 + (b[dir][i].x - 3) * b[dir][i].w, wl1);
        if((wr1 + (b[dir][i].x - 3) * b[dir][i].w) > wl1){
        pace[dir] = i;
        break;
        }
        wr1 = wr1 + (b[dir][i].x - 3) * b[dir][i].w;
        wr2 = wr2 + (b[dir][i].x + 3) * b[dir][i].w;
    }
    yes = 1;
    pace[dir] = i + 1;
    rec[cur++] = b[dir][i];
    }

    if (!bo && !yes){
    ok = -1;
    return;
    }
    DFS(cur, 2 - dir, yes);
    if (ok) return ;
}

int main(){
    int t = 1;
    while (scanf("%d%d%d", &L, &M, &n), L + M + n){
    // Init;
    memset(b, 0, sizeof(b));
    memset(cnt, 0, sizeof(cnt));
    memset(rec, 0, sizeof(rec));
    memset(pace, 0, sizeof(pace));
    wr1 = wl2 = (L - 3) * (L - 3) * M / (4.0 * L);
    wl1 = wr2 = (L + 3) * (L + 3) * M / (4.0 * L);
    ok = 0;

    // Read;
    int xi, wi;
    for (int i = 0; i < n; i++){
        scanf("%d%d", &xi, &wi);
        xi *= 2;
        if (xi > 3){
        b[2][cnt[2]].x = xi;
        b[2][cnt[2]].w = wi;
        cnt[2]++;
        }
        else if (xi < -3){
        b[0][cnt[0]].x = xi;
        b[0][cnt[0]].w = wi;
        cnt[0]++;
        }
        else{
        b[1][cnt[1]].x = xi;
        b[1][cnt[1]].w = wi;
        cnt[1]++;
        }
    }

    // Handle;
    for (int i = 0; i < 3; i++)
        sort(b[i], b[i] + cnt[i], cmp);
    memcpy(rec, b[1], sizeof(b[1]));
    for (int i = 0; i < cnt[1]; i++){
        wl1 += (3 - b[1][i].x) * b[1][i].w;
        wr2 += (b[1][i].x + 3) * b[1][i].w;
    }

    DFS(cnt[1], 0, 1);

    printf("Case %d:\n", t++);
    if(ok == 1){
        for (int i = n - 1; i >= 0; i--)
        printf("%d %d\n", rec[i].x / 2, rec[i].w);
    }
    else
        printf("Impossible\n");
    }
    return 0;}
