#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef int State[8];
const int MAXN = 1000005;
const int prime[20] = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1};

State order, rec, g[50000];
int head[MAXN], next[MAXN], dist[MAXN];

int cmp(const int &a, const int &b) {
    return abs(a) < abs(b);
}

void inInit() {
    memset(head, 0, sizeof(head));
    dist[0] = 0;
    memcpy(g[1], rec, sizeof(rec));
}

void inSert(State& s, int u, int v, int dir) {
    if(dir == 1){ //左边  
    if(u == v - 1) return;  // 如果本来就在他的左边，不移动  
    if(u == v + 1){ // 如果再它右边，直接交换  
        int tmp = s[u];  s[u]=s[v]; s[v] = tmp;  
    }  
    int t = s[u];  
    if(u > v){  
        for(int i = u; i > v; --i) s[i] = s[i-1];  
        s[v] = t;  
    }  
    else{  
        for(int i = u; i < v - 1; ++i) s[i] = s[i+1];  
        s[v-1] = t;  
    }   
    }  
    else{ // 右边  
    if(u == v + 1) return ; //如果本来就在他右边， 不移动  
    if(u == v - 1){   
        int tmp = s[u];  s[u]=s[v]; s[v] = tmp;  
    }  
    int t = s[u];  
    if(u > v){  
        for(int i = u; i > v + 1; --i) s[i] = s[i - 1];  
        s[v+1] = t;  
    }  
    else{  
        for(int i = u; i < v; ++i) s[i] = s[i + 1];  
        s[v] = t;  
    }   
    }  
}

int hash(State now) {
    int sum = 0; 
    for (int i = 0; i < 8; i++)
    sum = sum * 10 + now[i];
    return (sum & 0x7FFFFFFF) % MAXN;
}


bool tryInsert(int cur) {
    int h = hash(g[cur]);
    int u = head[h];
    while (u) {
    if(memcmp(g[u], g[cur], sizeof(g[cur])) == 0)
        return false;
    u = next[u];
    }
    next[cur] = head[h];
    head[h] = cur;
    return true;
}

int bfs() {
    inInit();
    int front = 1, rear = 2;

    while (front < rear) {
    State& now = g[front];
    if (memcmp(now, order, sizeof(order)) == 0) 
        return dist[front];

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
        if (i != j && prime[abs(now[i]) + abs(now[j])] && now[i] * now[j] < 0){
            for (int dir = 1; dir <= 2; dir++) {
            State& next = g[rear];
            memcpy(&next, &now, sizeof(now));
            inSert(next, i, j, dir);
            if (tryInsert(rear))
                dist[rear++] = dist[front] + 1;
            }
        }
        }
    }
    front++;
    }
    return -1;
}

int main(){
    int cas = 1;
    while (scanf("%d", &rec[0]) == 1 && rec[0]) {
    // Read;
    for (int i = 1; i < 8; i++)
        scanf("%d", &rec[i]);
    memcpy(order, rec, sizeof(rec));

    sort(order, order + 8, cmp);

    int flag = bfs();

    printf("Case %d: %d\n", cas++, flag);
    }
    return 0;
}
