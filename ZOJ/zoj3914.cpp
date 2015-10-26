#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
const int maxn = 100;

int P, N;
char a[maxn], b[maxn];
vector<string> A, B;

bool ischar(char ch) {
	if (ch >= 'a' && ch <= 'z') return true;
	if (ch >= 'A' && ch <= 'Z') return true;
	return false;
}
bool isnumber(char ch) { return ch >= '0' && ch <= '9'; }
void match(char c, char* s) { if (P < N && s[P] == c) P++; }
int getNumber (char* s) {
	int u = 0;
	while (P < N && isnumber(s[P]))
		u = u * 10 + s[P++] - '0';
	return u;
}

string get (char* s) {
	string ret = "";
	while (P < N && s[P] != '.' && s[P] != '-')
		ret = ret + s[P++];
	return ret;
}

void solve (vector<string>& u, char* s) {
	u.clear();
	P = 0;
	N = strlen(s);

	while (P < N) {
		u.push_back(get(s));
		if (s[P] == '.' || s[P] == '-') P++;
	}
}

int change(string& u) {
	int ret = 0;
	for (int i = 0; i < u.length(); i++)
		ret = ret * 10 + u[i];
	return ret;
}

bool judge () {
	for (int i = 0; i < A.size() || i < B.size(); i++) {
		if (i >= A.size()) return i != 3;
		if (i >= B.size()) return i == 3;

		if (isnumber(A[i][0]) && isnumber(B[i][0])) {
			int tmpa = change(A[i]), tmpb = change(B[i]);
			if (tmpa != tmpb) return tmpa < tmpb;
		} else if (A[i] != B[i]) return A[i] < B[i];
	}
	return false;
}

int main () {
	while (scanf("%s%s", a, b) == 2) {
		solve(A, a);
		solve(B, b);
		printf("%s\n", judge() ? "Wow! Such feature! Very smart! I'm excited!" : "I'm angry!");
	}
	return 0;
}
