#include <stdio.h>
#include <string.h>

const int N = 30;
const int number[8] = {0, 4, 3, 4, 4, 4, 4, 4}; // 各个block的木块组成。
int p[N][N];    // 24面序列储存。

struct coor {
    int x[20];
    int y[20];
    int z[20];
    coor() {
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
        memset(z, 0, sizeof(z));
    }
};

struct block {
    int cnt;
    coor dir[20];
}blo[10];

////////////////////////////////////////////////////////////////////////////
//////                数据处理                    //////

void get_seq(int cur, int now, int a, int b, int c) {   //打印单一面的序列。
    for (int k = 0; k < 3; k++)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                p[cur][k * 9 + i * 3 + j] = now + c * k + b * i + j * a - 1;
}

void build_seq() {  // 打印24面的序列。
    int top[8] = {1, 3, 7, 9, 19, 21, 25, 27};
    int num[8][3] = { {1, 3, 9}, {3, -1, 9}, {-3, 1, 9}, {-1, -3, 9}, {3, 1, -9}, {-1, 3,-9}, {1, -3, -9}, {-3, -1, -9}};
    
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 3; j++)
            get_seq(i * 3 + j, top[i], num[i][j % 3], num[i][(j + 1) % 3], num[i][(j + 2) % 3]);
}

bool is_some_dir(int cur, int a, int b) {
    int bo[5] = {0};
    for (int i = 0; i < number[cur]; i++) {
        int k = 0;
        for (int j = 0; j < number[cur]; j++) {
            if (bo[j])  continue;
            if (blo[cur].dir[a].x[i] == blo[cur].dir[b].x[j] && blo[cur].dir[a].y[i] == blo[cur].dir[b].y[j] && blo[cur].dir[a].z[i] == blo[cur].dir[b].z[j] ) {
                bo[j] = 1;
                k = 1;
        break;
            }
        }
        if (!k)
            return false;
    }
    return true;
}

bool is_some_blo(int cur, int cas) {
    for (int i = 0; i < cas; i++)
        if (is_some_dir(cur, i, cas))
            return true;
    return false;
}

int get_block(int num[], int cur) { // 对于一个block进行24面转向判断。
    int cas = 0, f = 1;
    for (int t  = 0; t < 24; t++) {
    int ok = 0, a, b, c;
    for (int k = 0; k < 3; k++)
        for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (num[p[t][k * 9 + i * 3 + j]]) {
            if (ok) {
                blo[cur].dir[cas].x[f] = i - a;
                blo[cur].dir[cas].y[f] = j - b;
                blo[cur].dir[cas].z[f] = k - c;
                f++;
            }
            else {
                ok = f = 1;
                a = i, b = j, c = k;
            }
            }
        }
    if (is_some_blo(cur, cas))  continue;
    cas++;
    }
    blo[cur].cnt = cas;
}

void build_block() {    // 获得除了1以外的所有block的转向值。
    int num[8][27] = { {0}, {0}, {1, 1, 0, 0, 1}, {1, 1, 1, 0, 1}, {1, 0, 0,1, 1, 0, 0, 1}, {1, 1, 0, 1, 0, 0, 0, 0, 0, 1}, {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 }, {1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1} };

    for (int i = 2; i < 8; i++)
    get_block(num[i], i);
}

////////////////////////////////////////////////////////////////////////////

const int MANX = 1000;
const int R = 3;
int vis[N];
char str[MANX];

void handle(char str[]) {
    int ok = 0, cas = 1, a, b, c;
    for (int k = 0; k < R; k++)
    for (int i = 0; i < R; i++)
        for (int j = 0; j < R; j++)
        if (str[k * 9 + i * 3 + j] == 'a') {
            if (ok) {
            blo[1].dir[0].x[cas] = i - a;
            blo[1].dir[0].y[cas] = j - b;
            blo[1].dir[0].z[cas] = k - c;
            cas++;
            }
            else {
            ok = cas = 1;
            a = i, b = j, c = k;
            }
        }
    blo[1].cnt = 1;
}

bool judge_take(coor cur, int x, int y, int z, int n) {
    for (int i = 0; i < n; i++) {
    if (cur.x[i] + x < 0 || cur.x[i] + x >= R)  return true;
    if (cur.y[i] + y < 0 || cur.y[i] + y >= R)  return true;
    if (cur.z[i] + z < 0 || cur.z[i] + z >= R)  return true;
    if (str[(cur.z[i] + z) * 9 + (cur.x[i] + x) * 3 + cur.y[i] + y] != '\0')
        return true;
    }
    return false;
}

void take(coor cur, int x, int y, int z, int n) {
    for (int i = 0; i < number[n]; i++)
    str[(cur.z[i] + z) * 9 + (cur.x[i] + x) * 3 + cur.y[i] + y] = n + 'a' - 1;
}

void clear(coor cur, int x, int y, int z, int n) {
    for (int i = 0; i < n; i++)
    str[(cur.z[i] + z) * 9 + (cur.x[i] + x) * 3 + cur.y[i] + y] = '\0';
}

void dfs(int x, int y, int z, int sum) {
    if (sum == 7) {
    puts(str);
    return ;
    }

    while (1) {
    if (y >= 3) {
        x++;
        y = 0;
    }

    if (x >= 3) {
        z++;
        x = 0;
    }

    if (str[z * 9 + x * 3 + y] != '\0')
        y++;
    else
        break;
    }

    for (int cur = 1; cur < 8; cur++) {
    if (vis[cur])   continue;
    vis[cur] = 1;

    for (int now = 0; now < blo[cur].cnt; now++) {
        if (judge_take(blo[cur].dir[now], x, y, z, number[cur]))    continue;
        take(blo[cur].dir[now], x, y, z, cur);
        dfs(x, y + 1, z, sum + 1);
        clear(blo[cur].dir[now], x, y, z, number[cur]);
    }

    vis[cur] = 0;
    }
}

int main() {
    // 数据准备。
    memset(blo, 0, sizeof(blo));
    build_seq();
    build_block();

    while (gets(str) != NULL) {
    handle(str);
    memset(vis, 0, sizeof(vis));
    memset(str, 0, sizeof(str));

    dfs(0, 0, 0, 0);

    printf("\n");
    }
    return 0;}
