#include <stdio.h>
#include <string.h>

const int N = 1010;

struct File{
    char sen_ori[N];
    char sen_exp[N];
}del[N], ret[N];
int cnt_del, cnt_ret;
int min_ori, min_exp;
int max_ori, max_exp;
char ans_ori[N], ans_exp[N];

void handle(char str[], char c) {
    int len = strlen(str), move = 1;
    if (c == '-') {
        for (int i = 0; move < len; move++) {
            if (str[move] == '.') {
                if (i > max_ori)    max_ori = i;
                if (i < min_ori)    min_ori = i;
                del[cnt_del].sen_ori[i] = '\0';
                break;
            }
            del[cnt_del].sen_ori[i++] = str[move];
            if (move == len - 1) {
                if (i > max_ori)    max_ori = i;
                if (i < min_ori)    min_ori = i;
                del[cnt_del].sen_ori[i] = '\0';
        break;
            }
        }
        
        move++;
    if (move >= len) {
        min_exp = 0;
    }
    else {
        for (int i = 0; move < len; move++) {
        del[cnt_del].sen_exp[i++] = str[move];
        if (move == len - 1) {
            if (i > max_exp)    max_exp = i;
            if (i < min_exp)    min_exp = i;
            del[cnt_del].sen_exp[i] = '\0';
        }
        }
    }
    del[cnt_del].sen_exp[min_exp] = '\0';
    cnt_del++;
    }
    else {
    for (int i = 0; move < len; move++) {
        if (str[move] == '.') {
        ret[cnt_ret].sen_ori[i] = '\0';
        break;
        }
        ret[cnt_ret].sen_ori[i++] = str[move];
        if (move == len - 1) {
        ret[cnt_ret].sen_ori[i] = '\0';
        break;
        }
    }

    move++;

    for (int i = 0; move < len; move++) {
        ret[cnt_ret].sen_exp[i++] = str[move];
        if (move == len - 1) {
        ret[cnt_ret].sen_exp[i] = '\0';
        }
    }
    ret[cnt_ret].sen_exp[move] = '\0';
    cnt_ret++;
    }
}

void slove() {
    // Init.
    memset(ans_ori, 0, sizeof(ans_ori));
    memset(ans_exp, 0, sizeof(ans_exp));

    for (int i = 0; i < min_ori; i++) {
    int flag = 1;
    for (int j = 1; j < cnt_del; j++) {
        if (del[j].sen_ori[i] != del[0].sen_ori[i]) {
        flag = 0;
        break;
        }
    }

    if (flag)
        ans_ori[i] = del[0].sen_ori[i];
    else
        ans_ori[i] = '?';
    }

    if (min_ori != max_ori) {
    ans_ori[min_ori] = '*';
    ans_ori[min_ori + 1] = '\0';
    }
    else
    ans_ori[min_ori] = '\0';

    for (int i = 0; i < min_exp; i++) {
    int flag = 1;
    for (int j = 1; j < cnt_del; j++) {
        if (del[j].sen_exp[i] != del[0].sen_exp[i]) {
        flag = 0;
        break;
        }
    }

    if (flag)
        ans_exp[i] = del[0].sen_exp[i];
    else
        ans_exp[i] = '?';
    }

    if (min_exp != max_exp) {
    ans_exp[min_exp] = '*';
    ans_exp[min_exp + 1] = '\0';
    }
    else
    ans_exp[min_exp] = '\0';
}

bool judge() {
    int len1 = strlen(ans_ori), len2 = strlen(ans_exp);
    if (ans_ori[len1 - 1] == '*')   len1--;
    if (ans_exp[len2 - 1] == '*')   len2--;

    for (int i = 0; i < cnt_ret; i++) {
    int flag = 1, dis1 = strlen(ret[i].sen_ori), dis2 = strlen(ret[i].sen_exp);

    for (int j = 0; j < len1; j++) {
        if (ans_ori[j] == '?')  continue;
        if (ans_ori[j] != ret[i].sen_ori[j]) {
        flag = 0;
        break;
        }
    }

    if (flag) {
        if (ans_ori[len1] == '*') {
        if (dis1 < len1)
            flag = 0;
        }
        else if (len1 != dis1)
        flag = 0;
    }

    if (flag) {
        for (int j = 0; j < len2; j++) {
        if (ans_exp[j] == '?')  continue;
        if (ans_exp[j] != ret[i].sen_exp[j]) {
            flag = 0;
            break;
        }
        }
    }

    if (flag) {
        if (ans_exp[len2] == '*') {
        if (dis2 < len2)
            flag = 0;
        }
        else if (len2 != dis2)
        flag = 0;
    }

    if (flag)   return false;
    }
    return true;
}

int main() {
    int cas;
    scanf("%d%*c%*c", &cas);
    char str[N];

    while (cas--) {
    // Init.
    memset(del, 0, sizeof(del));
    memset(ret, 0, sizeof(ret));
    cnt_del = cnt_ret = 0;
    min_ori = min_exp = N;
    max_ori = max_exp = 0;

    // Read.
    while (gets(str) != NULL && str[0] != '\0') {
        handle(str, str[0]);
    }
    slove();

    if(judge())
        printf("DEL %s.%s\n", ans_ori, ans_exp);
    else
        printf("IMPOSSIBLE\n");

    if (cas)
        printf("\n");
    }
    return 0;}
