#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int cpfix[maxn], extand[maxn];

void getCPfix(char* str) {
	memset(cpfix, 0, sizeof(cpfix));

	int n = strlen(str + 1), tmp = 1;
	cpfix[1] = n;

	while (tmp < n && str[tmp] == str[tmp+1])
		tmp++;
	cpfix[2] = tmp-1;

	int p = 2;
	for (int k = 3; k <= n; k++) {
		// e 为目前匹配过的最末位置, l 为对应的偏移;
		int e = p + cpfix[p] - 1, l = cpfix[k-p+1];

		if (k + l - 1 >= e) {
			int j = e - k > 0 ? e - k : 0;
			while (k + j <= n && str[k+j] == str[j+1])
				j++;
			cpfix[k] = j, p = k;
		} else
			cpfix[k] = l;
	}
	/*
	for (int i = 1; i <= n; i++)
		printf("%d%c", cpfix[i], i == n ? '\n' : ' ');
		*/
}

void getExtand(char* s, char* t) {
	getCPfix(t);

	int sn = strlen(s+1), tn = strlen(t+1);
	int n = min(sn, tn), tmp = 1;

	while (tmp <= n && s[tmp] == t[tmp])
		tmp++;
	extand[1] = tmp-1;

	int p = 1;
	for (int k = 2; k <= sn; k++) {
		int e = p + extand[p] - 1, l = cpfix[k-p+1];

		if (k + l - 1 >= e) {
			int j = e - k > 0 ? e - k : 0;
			while (k + j <= sn && j < tn && s[k+j] == t[j+1])
				j++;
			extand[k] = j, p = k;

		} else
			extand[k] = l;
	}

	/*
	for (int i = 1; i <= sn; i++) 
		printf("%d%c", extand[i], i == sn ? '\n' : ' ');
		*/
}

int fail[maxn];
int KMP (char* str) {
	int n = strlen(str+1);
	int p = fail[0] = fail[1] = 0;

	for (int i = 2; i <= n; i++) {
		while (p && str[p+1] != str[i])
			p = fail[p];

		if (str[p+1] == str[i])
			p++;
		fail[i] = p;
	}
	return n - fail[n];
}

char S[maxn * 2], T[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%s", T+1);
		strcpy(S+1, T+1);
		strcat(S+1, T+1);
		int n = KMP(S);
		getExtand(S, T);

		int ans[3], tn = strlen(T+1);
		memset(ans, 0, sizeof(ans));
		for (int i = 1; i <= n; i++) {
			if (extand[i] >= tn)
				ans[1]++;
			else {
				int g = extand[i];
				if (S[1+g] < S[i+g])
					ans[2]++;
				else
					ans[0]++;
			}
		}
		printf("Case %d: %d %d %d\n", kcas, ans[0], ans[1], ans[2]);
	}
	return 0;
}
