#include <stdio.h>
#include <string.h>
#include <math.h>
#define N 1000

int n, ok, con[2][N], bo[N];
int Max = (1 << 16) - 1;

int handle(char str[]){
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++){
    if (str[i] == '+')
        con[1][n] += 1 << (str[++i] - 'A');
    else
        con[0][n] += 1 << (str[++i] - 'A');
    }
}

bool judge(int k){
    for (int i = 0; i < n; i++){
    if (((k^Max) & con[0][i]) || (k & con[1][i]))
        continue;
    else
        return false;
    }
    return true;
}

int main(){
    char str[N];
    memset(con, 0, sizeof(con));
    n = ok = 0;
    while (gets(str)){
    if (strcmp(str, ".") != 0){
        handle(str);
        n++;
        continue;
    }

    for (int i = 0; i <= Max; i++){
        if (judge(i)){
        ok = 1;
        n = i;
        break;
        }
    }

    if (ok){
        printf("Toppings: ");
        for (int i = 0; i <= 15; i++){
        if (n & (1 << i))
            printf("%c", 'A' + i); 
        }
        printf("\n");
    }
    else
        printf("No pizza can satisfy these requests.\n");

    // Init;
    memset(con, 0, sizeof(con));
    n = ok = 0;
    }
    return 0;}
