#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6 + 5;

int N, P, C;
char word[maxn], text[maxn];

bool idx(char ch) { return ch == 32 || ch == 9 || ch == 10; }

bool getLine() {
	if (gets(text)) {
		P = 0;
		N = strlen(text);
		return true;
	}
	return false;
}

bool clear () {
	while (P < N && idx(text[P])) P++;
	if (P >= N) return getLine();
	return true;
}

bool match(char ch) {
	if (!clear()) return false;
	if (text[P] == ch) {
		word[C++] = text[P++];
		return true;
	}
	return false;
}

void add() { if (C && word[C-1] != ' ') word[C++] = ' '; }

int getTerm () {
	if (P >= N) getLine();

	C = 0;
	bool istag = match('<');
	bool isend = match('/');

	if (istag) {
		bool space = false;
		while (text[P] != '>') {
			if (P == 0 && space) word[C++] = ' ';
			word[C++] = text[P++];
			if (P >= N && !getLine()) break;
			space = true;
		}
	} else {
		bool space = false;
		while (text[P] != '<') {
			if (P == 0 && space) add();
			if (idx(text[P])) add();
			else word[C++] = text[P];
			P++;
			if (P >= N && !getLine()) break;
			space = true;
		}
		while (C && word[C-1] == ' ') C--;
	}

	bool bo = word[C-1] == '/';
	match('>');
	word[C] = '\0';

	if (istag && isend && !bo) return -1;
	if (istag && !bo) return 1;
	return 0;
}

int main () {
	int cas, cnt;
	scanf("%d%*c", &cas);
	P = N = 0;
	for (int kcas = 1; kcas <= cas; kcas++) {
		printf("Case #%d:\n", kcas);

		cnt = 0;
		cnt = getTerm();
		puts(word);
		while (cnt) {
			int tmp = getTerm();
			if (word[0] == '\0') continue;
			if (tmp < 0)
				for (int i = 0; i < cnt-1; i++) printf(" ");
			else
				for (int i = 0; i < cnt; i++) printf(" ");
			cnt += tmp;
			puts(word);
		}
	}
	return 0;
}
