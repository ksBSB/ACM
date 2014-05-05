#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <string>
using namespace std;

const int N = 120005;
const int M = 30;
map<string, int> vec;

int main() {
    int n = 0;
    char str[N][M];

    while (gets(str[n]) != NULL) {
    vec[str[n++]] = 1;
    }

    for (int i = 0; i < n; i++) {
    int len = strlen(str[i]);
    for (int j = 0; j < len - 1; j++) {
        char p[M], q[M];
        strncpy(p, str[i], j);
        p[j] = '\0';
        for (int k = j; k < len; k++) 
        q[k - j] = str[i][k];
        q[len - j] = '\0';
        if (vec[p] + vec[q] == 2) {
        printf("%s\n", str[i]);
        break;
        }
    }
    }
    return 0;
}
