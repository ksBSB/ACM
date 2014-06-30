#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int N = 10005;

int main () {
	long long sum;
	char str[N];
	while (scanf("%s", str), str[0] != '0') {

		while (1) {
			int len = strlen(str);
			if (len > 1) {
				sum = 0;
				for (int i = 0; i < len; i++)
					sum = sum + str[i] - '0';
				sprintf(str, "%lld", sum);
			} else {
				printf("%s\n", str);
				break;
			}
		}
	}
	return 0;
}
