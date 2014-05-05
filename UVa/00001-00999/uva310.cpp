#include <stdio.h>
#include <string.h>

const int N = 1 << 16;
const int M = 16;

int vis[N], end;
char a[M], b[M], begin[M], over[M];
char que[N][M], pdn[200];

int hash(char str[]) {
    int sum = 0, cnt = strlen(str);
    for (int i = 0; i < cnt; i++)
    sum = sum * 2 + str[i] - 'a' + 1;
    return sum % N;
}

void inInit() {
    memset(que, 0, sizeof(que));
    memset(vis, 0, sizeof(vis));
    scanf("%s%s%s", b, begin, over);
    end = hash(over);
}

bool bfs() {
    inInit();
    int t, i, j, k;
    int front = 0, rear = 0;
    for(i = 0; begin[i]; i++) {
    for(k = 0,j = i; begin[j] && over[k]; k++, j++)
        que[rear][k] = begin[j];
    que[rear][k] = '\0';
    t = hash(que[rear]);

    if(t == end)
        return 1;

    if(!vis[t]) {
        vis[t]=1;
        rear++;
    }
    }
    
    while(rear > front) {
    for(i = 0,k = 0; que[front][i]; i++) {
        if(que[front][i] == 'a')
        for(j = 0; a[j]; j++)
            pdn[k++] = a[j];
        else 
        for(j = 0; b[j]; j++)
            pdn[k++] = b[j];
    }
    pdn[k] = '\0';
    for(i = 0; pdn[i]; i++) {
        for(k = 0,j = i; pdn[j] && over[k]; j++, k++)
        que[rear][k] = pdn[j];
        que[rear][k] = '\0';
        t = hash(que[rear]);
        if(t == end)
        return true;
        if(!vis[t]) {
        vis[t] = 1;
        rear++;
        }
    }
    front++;
    }
    return false;
}

int main() {
    while (scanf("%s", a) == 1) {
    printf("%s\n", bfs() ? "YES" : "NO");
    }
    return 0;
}
