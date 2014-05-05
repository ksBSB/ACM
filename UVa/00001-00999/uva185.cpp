#include <stdio.h>
#include <string.h>
#define N 1005

struct number{
    int val;
    char ch;
}tem[N];

int n, ok, cnt[3];
char S[3][N];

int change(char c){
    switch(c){
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    default:
        return 0;
    }
}

bool judge(char str[]){
    int num[3] ={0}, len = strlen(str), t = 0, bo = 0;
    memset(cnt, 0, sizeof(cnt));
    memset(S, 0, sizeof(S));

    for (int i = 0; i <len; i++){
    if (str[i] != '+' && str[i] != '='){
        num[bo] += change(str[i]);
        if (t < change(str[i]))
        num[bo] -= 2 * t;
        S[bo][cnt[bo]++] = str[i];
        t = change(str[i]);
    }
    else{
        t = 0;
        bo++;
    }
    }

    return num[0] + num[1] == num[2]?true:false;
}

bool thesome(char c){
    for (int i = 0; i < n; i++)
    if (tem[i].ch == c)
        return true;
    return false;
}

void handle(){
    for (int i = 0; i < 3; i++){
    for (int j = 0; j < cnt[i]; j++){
        if (thesome(S[i][j]))   continue;
        tem[n++].ch = S[i][j];
    }
    }
}

bool rep(int cur){
    for (int i = 0; i < cur; i++)
    if (tem[cur].val == tem[i].val)
        return true;
    return false;
}

int find(char c){
    for (int i = 0; i < n; i++)
    if (tem[i].ch == c)
        return tem[i].val;
    return 0;
}

int build(int cur){
    int sum = 0;
    for (int i = 0; i < cnt[cur]; i++)
       sum = sum * 10 + find(S[cur][i]);    
    return sum;
}

void dfs(int cur){

    if (cur == n){
    int num[3];
    for (int i = 0; i < 3; i++)
        num[i] = build(i);
    if (num[0] + num[1] == num[2])
        ok++;
    }
    else{
    int k = 0;
    for (int i = 0; i < 3; i++)
        if (tem[cur].ch == S[i][0])
        k = 1;

    for (tem[cur].val = k; tem[cur].val <= 9; tem[cur].val++){
        if (rep(cur))    continue;
        dfs(cur + 1);
    }
    }
}

int main(){
    char str[N];
    while (scanf("%s", str)){
    if (strcmp(str, "#") == 0)  break;

    if (judge(str))
        printf("Correct ");
    else
        printf("Incorrect ");

    memset(tem, 0, sizeof(tem));
    n = ok = 0;

    for (int i = 0; i < 2; i++)
        if (cnt[i] == cnt[2] || cnt[i] == cnt[2] - 1)
        ok = 1;

    if (ok){
        ok = 0;

        handle();

        dfs(0);

        if (ok > 1 )
        printf("ambiguous\n");
        else if (ok == 1)
        printf("valid\n");
        else
        printf("impossible\n");
    }
    else
        printf("impossible\n");
    }
    return 0;
}
