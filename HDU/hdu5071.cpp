#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 5005;
typedef long long ll;

map<int, ll> C;
int x, N, A[maxn], T, flag;
vector<int> vec;

int find(int a) {
	for (int i = 0; i < N; i++)
		if (A[i] == a)
			return i;
	return N;
}

void add ()  {
	scanf("%d", &x);
	if (C.count(x))
		printf("same priority");
	else {
		A[N++] = x;
		C[x] = 0;
		printf("success");
	}
}

void close() { 
	scanf("%d", &x);
	if (C.count(x)) {
		printf("close %d with %I64d", x, C[x]);
		C.erase(x);

		if (flag && T == x)
			flag = 0;

		int pos = find(x);
		for (int i = pos; i < N; i++)
			A[i] = A[i+1];
		N--;
	} else
		printf("invalid priority");
}

void chat() {
	scanf("%d", &x);
	if (N == 0)
		printf("empty");
	else {
		if (flag) {
			C[T] += x;
			vec.push_back(T);
		} else {
			C[A[0]] += x;
			vec.push_back(A[0]);
		}
		printf("success");
	}
}

void rotate() {
	scanf("%d", &x);
	if (x > N || x < 1)
		printf("out of range");
	else {
		int tmp = A[x-1];
		for (int i = x-1; i; i--)
			A[i] = A[i-1];
		A[0] = tmp;
		printf("success");
	}
}

void prior() {
	if (N == 0)
		printf("empty");
	else {
		int x = A[0], pos = 0;
		for (int i = 1; i < N; i++) {
			if (A[i] > x) {
				x = A[i];
				pos = i;
			}
		}

		int tmp = A[pos];
		for (int i = pos; i; i--)
			A[i] = A[i-1];
		A[0] = tmp;
		printf("success");
	}
}

void choose() {
	scanf("%d", &x);
	if (C.count(x)) {
		int pos = find(x);

		int tmp = A[pos];
		for (int i = pos; i; i--)
			A[i] = A[i-1];
		A[0] = tmp;
		printf("success");
	} else
		printf("invalid priority");
}

void top() {
	scanf("%d", &x);
	if (C.count(x)) {
		T = x;
		flag = 1;
		printf("success");
	} else
		printf("invalid priority");
}

void untop() {
	if (flag) {
		flag = 0;
		printf("success");
	} else 
		printf("no such person");
}

void solve() {
	if (N == 0)
		return;

	if (flag && C[T])
		printf("Bye %d: %I64d\n", T, C[T]);

	for (int i = 0; i < N; i++) {
		if (flag && A[i] == T)
			continue;
		if (C[A[i]])
			printf("Bye %d: %I64d\n", A[i], C[A[i]]);
	}

	/*
	   int t = flag ? T : A[0];
	   if (C[t])
	   printf("Bye %d: %I64d\n", t, C[t]);

	   for (int i = vec.size() - 1; i >= 0; i--) {
	   if (C.count(vec[i]) && t != vec[i]) {
	   printf("Bye %d: %I64d\n", vec[i], C[vec[i]]);
	   break;
	   }
	   }
	   */
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		N = T = flag = 0;
		vec.clear();
		C.clear();

		int Q;
		char op[10];
		scanf("%d", &Q);
		for (int i = 1; i <= Q; i++) {
			scanf("%s", op);
			printf("Operation #%d: ", i);
			if (strcmp(op, "Add") == 0)
				add();
			else if (strcmp(op, "Close") == 0)
				close();
			else if (strcmp(op, "Chat") == 0)
				chat();
			else if (strcmp(op, "Rotate") == 0)
				rotate();
			else if (strcmp(op, "Prior") == 0)
				prior();
			else if (strcmp(op, "Choose") == 0)
				choose();
			else if (strcmp(op, "Top") == 0)
				top();
			else if (strcmp(op, "Untop") == 0)
				untop();
			printf(".\n");
		}
		solve();
	}
	return 0;
}
