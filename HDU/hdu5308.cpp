#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;

int main() {
    while (~scanf("%d", &n)) {
        if (n == 1 || n == 2 || n == 3) printf("-1\n");
        else if (n == 4) {
            printf("1 * 2\n");
            printf("5 + 3\n");
            printf("6 + 4\n");
        } else if (n == 5) {
			printf("1 * 2\n");
			printf("3 * 6\n");
			printf("7 - 4\n");
			printf("8 / 5\n");
        } else if (n == 6) {
            printf("1 + 2\n");
            printf("3 + 4\n");
            printf("5 / 6\n");
            printf("7 + 8\n");
            printf("9 * 10\n");
        } else if (n == 7) {
            printf("1 + 2\n");
            printf("3 + 4\n");
            printf("5 + 8\n");
            printf("6 + 9\n");
            printf("10 / 7\n");
            printf("11 + 12\n");
        } else if (n == 8) {
            printf("1 - 2\n");
            printf("3 - 4\n");
            printf("5 + 6\n");
            printf("7 * 9\n");
            printf("8 + 11\n");
            printf("10 + 13\n");
            printf("12 + 14\n");
        } else if (n == 9) {
            printf("1 + 2\n");
            printf("3 + 4\n");
            printf("5 - 6\n");
            printf("7 + 10\n");
            printf("8 + 11\n");
            printf("13 / 9\n");
            printf("14 - 15\n");
            printf("16 + 12\n");
        } else if (n == 10) {
            printf("1 + 2\n");
            printf("3 / 4\n");
            printf("5 / 6\n");
            printf("7 / 8\n");
            printf("9 / 10\n");
            printf("11 + 12\n");
            printf("13 + 16\n");
            printf("14 + 17\n");
            printf("15 + 18\n");
        } else if (n == 11) {
            printf("1 + 2\n");
            printf("3 - 4\n");
            printf("5 - 6\n");
            printf("7 / 8\n");
            printf("9 / 10\n");
            printf("12 + 15\n");
            printf("11 * 13\n");
            printf("14 * 18\n");
            printf("16 + 17\n");
            printf("19 + 20\n");
        } else if (n >= 12) {
            if (n == 13) {
                printf("1 + 2\n");
                printf("14 / 3\n");
                printf("4 + 5\n");
                printf("16 / 6\n");
                printf("7 + 8\n");
                printf("18 / 9\n");
                printf("10 + 11\n");
                printf("20 + 12\n");
                printf("21 / 13\n");
                printf("15 * 17\n");
                printf("23 * 19\n");
                printf("24 * 22\n");
            } else {
                printf("1 + 2\n");
                printf("%d + 3\n", n + 1);
                printf("%d + 4\n", n + 2);
                printf("%d / 5\n", n + 3);
                printf("6 + 7\n");
                printf("%d + 8\n", n + 5);
                printf("%d + 9\n", n + 6);
                printf("%d + 10\n", n + 7);
                printf("%d + 11\n", n + 8);
                printf("%d / 12\n", n + 9);
                printf("%d * %d\n", n + 4, n + 10);
                if (n > 12) {
                    printf("14 - 13\n");
                    for (int i = 15; i <= n; i++) {
                        printf("%d * %d\n", n + i - 3, i);
                    }
                    printf("%d + %d\n", n + 11, 2 * n - 2);
                }
            }
        }
    }
    return 0;
}
