#include <stdio.h>
#include <algorithm>
using namespace std;
const int N = 1005;
int answer, a, b, c, d, n;
int num[N];

bool find() {
    for (a = n - 1; a >= 0; a--) {
    for (b = n - 1; b > 0; b--) {
        if (a == b) continue;
        answer = num[a] - num[b];
        for (c = 0, d = b - 1; c < d; ) {
        if (num[c] + num[d] == answer)
            return true;
        else if (num[c] + num[d] < answer)
            c++;
        else
            d--;
        }
    }
    }
    return false;
}

int main() {
    while (scanf("%d",&n) == 1 && n) {
    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);
    sort(num, num + n);
    if (find())
        printf("%d\n", num[a]);
    else
        printf("no solution\n");
    }
    return 0;}
