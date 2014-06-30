#include <stdio.h>
#include <string.h>

const int N = 50;
int begin, endin, flag;
int num[N];

bool judge(int cur) {
    int sum = 0;
    for (int i = 1; i <= cur; i++) {
    sum = sum * 10 + num[i];
    sum = sum % cur;
    }
    return sum?false:true;
}    

void dfs(int cur) {
    if (cur > endin) {
    flag = 1;
    return ;
    }

    for (num[cur] = 0; num[cur] < 10; num[cur]++) {
    if (cur >= begin) {
        if (judge(cur))
        dfs(cur + 1);
    }
    else
        dfs(cur + 1);
    if  (flag)  return;
    }
}

int main() {
    int cas, t = 1;
    scanf("%d", &cas);
    while (cas--) {
    // Init;
    memset(num, 0, sizeof(num));
    flag = 0;
    scanf("%d%d", &begin, &endin);

    int cur = 1;
    for (num[cur] = 1; num[cur] < 10; num[cur]++) {
        dfs(cur + 1);
        if (flag)
        break;
    }

    printf("Case %d: ", t++);
    if (flag) {
        for (int i = 1; i <= endin; i++)
        printf("%d", num[i]);
        printf("\n");
    }
    else
        printf("-1\n");
    }
    return 0;
}
