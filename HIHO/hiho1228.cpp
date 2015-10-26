#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e4 + 5;

struct Stack {
	int n;
	char s[maxn];

	void push(char ch) { s[n++] = ch; }
	void pop() { n--; }
	bool empty() { return n == 0; }
}L, R;

int N, M, P, E;
bool rewrite, iscopy;
char order[maxn], text[maxn];

void init () {
	E = L.n = R.n = 0;
	rewrite = iscopy = false;
	scanf("%d%s", &M, order);
	N = strlen(order);
}

void moveLeft () { 
	if (!L.empty()) {
		R.push(L.s[--L.n]);
		if (iscopy) P++;
	}
}

void moveRight () { 
	if (!R.empty()) {
		L.push(R.s[--R.n]);
		if (iscopy) P--;
	}
}

void deleteBlock() {
	if (P < 0) {
		P = -P;
		for (int i = 1; i <= P; i++)
			L.pop();
	} else
		for (int i = 1; i <= P; i++)
			R.pop();
}

void deleteLeft () {
	if (!L.empty()) L.pop();
	iscopy = false;
}

void deleteRight () {
	if (iscopy) deleteBlock();
	else if (!R.empty()) R.pop();
	iscopy = false;
}

void select () {
	if (iscopy) {
		E = 0;
		if (P < 0) {
			P = -P;
			for (int i = 0; i < P; i++)
				text[E++] = L.s[L.n-P+i];
		} else {
			for (int i = 1; i <= P; i++)
				text[E++] = R.s[R.n-i];
		}
	//	printf("%d %d!\n", P, E);
		iscopy = false;
	} else {
		iscopy = true;
		P = 0;
	}
}

void write (char ch) {
	if (rewrite && !R.empty()) R.pop();
	if (L.n + R.n + 1 > M) return;
	L.push(ch);
	iscopy = false;
}

void copy () {
	int pos = L.n + R.n + E;
	if (rewrite) pos -= R.n;
	if (pos > M) return;
	for (int i = 0; i < E; i++)
		write(text[i]);
	iscopy = false;
}

void solve () {
	for (int i = 0; i < N; i++) {
		char& ch = order[i];
		if (ch == 'L')
			moveLeft();
		else if (ch == 'R')
			moveRight();
		else if (ch == 'S') {
			rewrite ^= true; 
			iscopy = false;
		} else if (ch == 'B')
			deleteLeft();
		else if (ch == 'D')
			deleteRight();
		else if (ch == 'C') {
			select();
		} else if (ch == 'V')
			copy();
		else if (ch >= 'a' && ch <= 'z')
			write(ch);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
		if (L.empty() && R.empty()) printf("NOTHING\n");
		else {
			for (int i = 0; i < L.n; i++) printf("%c", L.s[i]);
			for (int i = R.n-1; i >= 0; i--) printf("%c", R.s[i]);
			printf("\n");
		}
	}
	return 0;
}
