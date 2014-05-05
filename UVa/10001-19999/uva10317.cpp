#include <stdio.h>
#include <string.h>

const int N = 1605;
const int M = 20;
const int MAX = 1505;

int nb, nc, num[M], l, r, sum, vis[M];
char op[M];

void init(char str[]) {
	nb = nc  = l = r = sum = 0;
   	memset(num, 0, sizeof(num));
	memset(op, 0, sizeof(op));
	
	int len = strlen(str), k = 0;
	bool flag = true, isNum = true;
	for (int i = 0; i <= len; i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			k = k * 10 + str[i] - '0';
			isNum = true;
		} else if ((str[i] == ' ' || str[i] == '\0') && isNum) {
			sum += k, num[nb++] = k;
			k = 0, isNum = false;
		} else {
			if (str[i] != ' ')
				op[nc++] = str[i];

			if (str[i] == '+') {
				flag ? l++ : r++;
			} else if (str[i] == '-') {
				flag ? r++ : l++;
			} else if (str[i] == '=') {
				flag = false;
			}
		}
	}
	l++, r++;
}

bool dfs(int d, int s, int c) {
	if (d >= nb) {
		if (c == l && s == sum) return true;
		return false;
	}

	vis[d] = 0;
	if (dfs(d + 1, s, c)) return true;

	vis[d] = 1;
	if (s + num[d] > sum) return false;
	if (dfs(d + 1, s + num[d], c + vis[d])) return true;
	return false;
}

bool solve() {
	if (sum % 2) return false;
	else sum /= 2;

	int numl[M], numr[M];
	if (dfs(0, 0, 0) == false) return false;

	int p = 0, q = 0;

	for (int i = 0; i < nb; i++) {
		if (vis[i]) numl[p++] = num[i];
		else numr[q++] = num[i];
	}

	p = q = 0;
	bool flag = true;
	printf("%d", numl[p++]);
	for (int i = 0; i < nc; i++) {
		if (op[i] == '=') {

			printf(" %c %d", op[i], numr[q++]);
			flag = false;
		} else {

			printf(" %c", op[i]);
			if (flag) {
				printf(" %d", op[i] == '+' ? numl[p++] : numr[q++]);
			} else {
				printf(" %d", op[i] == '-' ? numl[p++] : numr[q++]);
			}
		}
	}
	printf("\n");
	return true;
}

int main () {
	char str[N];
	while (gets(str)) {
		init(str);
		if (solve() == false) printf("no solution\n");
	}
	return 0;
}
