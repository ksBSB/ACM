#include <stdio.h>
#include <string.h>
const int N = 105;

int cnt[N], answer[N];
const char sign[] = "TSW";
const char sen[][10] = {"BAI", "DONG", "NAN", " ",  "XI", "BEI", " ",  "ZHONG", "FA"};

int changeOne(char c) {
    if (c == 'T')   return 0;
    else if (c == 'S')  return 1;
    else if (c == 'W')  return 2;
}

int changeTwo(char a, char b) {
    if (a == 'D' && b == 'O')       return 31;
    else if (a == 'N' && b == 'A')  return 32;
    else if (a == 'X' && b == 'I')  return 34;
    else if (a == 'B' && b == 'E')  return 35;
    else if (a == 'Z' && b == 'H')  return 37;
    else if (a == 'F' && b == 'A')  return 38;
    else if (a == 'B' && b == 'A')  return 40;
    else    return -1;
}

void handle(char str[]) {
    memset(cnt, 0, sizeof(cnt));
    cnt[10] = cnt[20] = cnt[30] = cnt[33] = cnt[36] = cnt[39] = 5;
    int n = 0, len = strlen(str), cur;
    for (int i = 0; i < len - 1; i++) {
    if (str[i] > '0' && str[i] <= '9') {
        cur = 0;
        cur += str[i++] - '0';
        cur += changeOne(str[i++]) * 10;
        cnt[cur]++;
    }
    else {
        cur = changeTwo(str[i], str[i + 1]);
        if (cur > 0)
        cnt[cur]++;
    }
    }
}

bool dfs(int sum, int flag) {
    if (sum >= 14)  return true;

    for (int i = 1; i <= 40; i++) {
    if (cnt[i] >= 3 && cnt[i] < 5) {
        cnt[i] -= 3;
        if (dfs(sum + 3, flag)) {
        cnt[i] += 3;
        return true;
        }
        cnt[i] += 3;
    }
    if (!flag && cnt[i] >= 2 && cnt[i] < 5) {
        cnt[i] -= 2;
        if (dfs(sum + 2, 1)) {
        cnt[i] += 2;
        return true;
        }
        cnt[i] += 2;
    }

    if (cnt[i] && cnt[i + 1] && cnt[i + 2] && cnt[i] < 5 && cnt[i + 1] < 5 && cnt[i + 2] < 5) {
        cnt[i]--, cnt[i + 1]--, cnt[i + 2]--;
        if (dfs(sum + 3, flag)) {
        cnt[i]++, cnt[i + 1]++, cnt[i + 2]++;
        return true;
        }
        cnt[i]++, cnt[i + 1]++, cnt[i + 2]++;
    }
    }
    return false;
}

void put(int cur) {
    int a = cur / 10, b = cur % 10;
    if (a < 3)
    printf(" %d%c", b, sign[a]);
    else
    printf(" %s", sen[b]);
}

int main() {
    char str[N];
    int cas = 1;
    while (gets(str)) {
    if (strcmp(str, "0") == 0)
        break;
    memset(answer, 0, sizeof(answer));
    int t = 0;

    handle(str);

    for (int i = 1; i <= 40; i++) {
        if (cnt[i] >= 4)    continue;
        cnt[i]++;
        if (dfs(0, 0))
        answer[t++] = i;
        cnt[i]--;
    }
    printf("Case %d:", cas++);
    if (t)
        for (int i = 0; i < t; i++)
        put(answer[i]);
    else 
        printf(" Not ready");
    printf("\n");
    }
    return 0;
}
