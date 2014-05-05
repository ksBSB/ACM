#include <stdio.h>
#include <string.h>
#include <string>
#include <set>
#include <iostream>
using namespace std;

const int N = 1505;
const int M = 105;
char p[N][M], q[N][M], str[N];

int main(){
    set<string> vec;
    int cas = 1, n, m, sum, t;
    scanf("%d", &sum);
    while (sum--) {
    memset(p, 0, sizeof(p));
    memset(q, 0, sizeof(q));

    scanf("%d%d%*c", &n, &m);
    vec.clear();
    for (int i = 0; i < n; i++)
        gets(p[i]);
    for (int i = 0; i < m; i++)
        gets(q[i]);

    for (int i = 0; i < n; i++) {
        t = strlen(p[i]);
        for (int j = 0; j < m; j++) {
        strcpy(str, p[i]);
        strcpy(str + t, q[j]);
        vec.insert(str);
        }
    }
    cout << "Case " << cas++ << ": " << vec.size() << endl;
    }
    return 0;
}
