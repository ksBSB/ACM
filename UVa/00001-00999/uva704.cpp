#include <stdio.h>
#include <string.h>

typedef int State[24];
const int MAXN = 100008;
const State begin = {0, 3, 4, 3, 0, 5, 6, 5, 0, 1, 2, 1, 0, 7, 8, 7, 0, 9, 10, 9, 0, 1, 2, 1};
const int dir[4][2] = {{0, 0}, {12, 1}, {0, 1}, {12, 0}};
const int chan[5] = {0, 3, 4, 1, 2};

struct coor {
    State total;
    char order[10];
}que[2][MAXN];
int head[2][MAXN], next[2][MAXN], dist[2][MAXN];
int flag, aid, over;
State gohead;

void turn(int x, int id, int k, int sex) {
    coor& end = que[sex][k];
    if (id) {
        int t1 = end.total[x], t2 = end.total[x + 1];
        for (int i = 0; i < 10; i++)
            end.total[i + x] = end.total[x + i + 2];
        end.total[x + 10] = t1;
    end.total[x + 11] = t2;
    }
    else {
        int t1 = end.total[x + 10], t2 = end.total[x + 11];
        for (int i = x + 11; i > x + 1; i--) {
            end.total[i] = end.total[i - 2];
        }
        end.total[x] = t1;
    end.total[x + 1] = t2;
    }
    
    if (x) {
        for (int i = 0; i < 3; i++)
            end.total[9 + i] = end.total[21 + i];
    }
    else {
        for (int i = 0; i < 3; i++)
            end.total[21 + i] = end.total[9 + i];
    }
}

int hash(coor now) {
    int sum = 0;
    for (int i = 0; i < 24; i++)
    sum = sum * 5 + now.total[i];
    return sum % MAXN;
}

bool tryInsert(int cur, int sex, int k) {
    int h = hash(que[k][cur]);
    int u = head[sex][h];
    while (u) {
    if (memcmp(que[sex][u].total, que[k][cur].total, sizeof(que[k][cur].total)) == 0) {
        if (k + sex == 1) {
        flag = 1;
        aid = u;
        return true;
        }
        else
        return false;
    }
       u = next[sex][u];    
    }
    if (sex == k) {
    next[sex][cur] = head[sex][h];
    head[sex][h] = cur;
    return true;
    }
    return false;
}

void bfs(int sex) {
    int front = 1, rear = 2;
    memset(head[sex], 0, sizeof(head[sex]));
    memcpy(que[sex][front].total, gohead, sizeof(begin));
    dist[sex][front] = 0;

    tryInsert(front, sex, sex);

    while (front < rear) {
    coor& now = que[sex][front];
    if (dist[sex][front] > 8)   return;

    if (tryInsert(front, 1 - sex, sex)) {
        over = front;
        return;
    }

    for (int i = 0; i < 4; i++) {
        coor& net = que[sex][rear];
        net = now;
        dist[sex][rear] = dist[sex][front] + 1;
        turn(dir[i][0], dir[i][1], rear, sex);
        net.order[dist[sex][front]] = i + 1;

        if (tryInsert(rear, 1 - sex, sex)) {
        over = rear;
        return;
        }

        if (tryInsert(rear, sex, sex))
        rear++;
    }
    front++;
    }
}

int main() {

    memcpy(gohead, begin, sizeof(begin));
    bfs(0);
    int cas;
    scanf("%d", &cas);
    while (cas--) {
    // Init;
    flag = aid = over = 0;
    for (int i = 0; i < 24; i++)
        scanf("%d", &gohead[i]);

    bfs(1);

    if (flag && dist[0][aid] + dist[1][over] <= 16) {
        if (dist[0][aid] + dist[1][over]){
        for (int i = 0; i < dist[1][over]; i++)
            printf("%d", que[1][over].order[i]);
        for (int i = dist[0][aid] - 1; i >= 0; i--)
            printf("%d", chan[que[0][aid].order[i]]);
        printf("\n");
        }
        else
        printf("PUZZLE ALREADY SOLVED\n");
    }
    else
        printf("NO SOLUTION WAS FOUND IN 16 STEPS\n");
    }
    return 0;
}
