#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxn = 20005;
const int maxm = 60005;
const int maxc = 500005;

// Union-Set
int f[maxn];
inline int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

// Treap;
struct Node {
	int val, rank, sum;
	Node* cid[2];

	Node (int val);
	void maintain();
	int cmp(int x);
};
Node* root[maxn];

void insert(Node* &o, int x);
void rotate(Node* &o, int d);
void remove(Node* &o, int x);

// Rank Tree;
void add_edge (int i);
void remove_tree(Node* &o);
void merge_tree(Node* &src, Node* & dest);
int rankth(Node* o, int k);

// Command;
struct Command {
	char type;
	int x, p;
}command[maxc];

bool flag[maxm];
ll tot, cnt;
int N, M, C, W[maxn], U[maxm], V[maxm];

void build () {
	for (int i = 1; i <= N; i++) {
		if (root[i] != NULL)
			remove_tree(root[i]);
		root[i] = new Node(W[i]);
	}

	for (int i = 1; i <= M; i++) {
		if (!flag[i])
			add_edge(i);
	}
}

void init () {
	C = 0;
	memset(flag, 0, sizeof(flag));
	for (int i = 1; i <= N; i++) {
		f[i] = i;
		scanf("%d", &W[i]);
	}

	for (int i = 1; i <= M; i++)
		scanf("%d%d", &U[i], &V[i]);

	int x, p;
	char str[5];
	while (scanf("%s", str) == 1 && str[0] != 'E') {
		scanf("%d", &x);

		if (str[0] == 'D') flag[x] = 1;
		else if (str[0] == 'Q') scanf("%d", &p);
		else if (str[0] == 'C') {
			scanf("%d", &p);
			swap(p, W[x]);
		}
		command[C++] = (Command){ str[0], x, p};
	}

	build();
}

void query (int x, int k) {
	cnt++;
	tot += rankth(root[getfar(x)], k);
}

void change (int x, int v) {
	int u = getfar(x);
	remove(root[u], W[x]);
	insert(root[u], v);
	W[x] = v;
}

int main () {
	int cas = 0;
	while (scanf("%d%d", &N, &M) == 2 && N) {
		init();
		tot = cnt = 0;

		for (int i = C - 1; i >= 0; i--) {
			char type = command[i].type;
			if (type == 'D')
				add_edge(command[i].x);
			else if (type == 'Q')
				query(command[i].x, command[i].p);
			else
				change(command[i].x, command[i].p);
		}
		printf("Case %d: %.6lf\n", ++cas, tot / (double) cnt);
	}
	return 0;
}

// Rank Tree;
int rankth(Node* o, int k) {
	if (o == NULL || k <= 0 || k > o->sum)
		return 0;
	int s = (o->cid[1] == NULL ? 0 : o->cid[1]->sum);

	if (k == s + 1) return o->val;
	else if (k <= s) return rankth(o->cid[1], k);
	else return rankth(o->cid[0], k - s - 1);
}

void remove_tree (Node* &o) {
	for (int i = 0; i < 2; i++) {
		if (o->cid[i] != NULL)
			remove_tree(o->cid[i]);
	}
	delete o;
	o = NULL;
}

void add_edge (int x) {
	int u = getfar(U[x]), v = getfar(V[x]);

	if (u != v) {
		if (root[u]->sum < root[v]->sum)
			swap(u, v);
		f[v] = u;
		merge_tree(root[v], root[u]);
	}
}

void merge_tree (Node* &src, Node* &dest) {
	for (int i = 0; i < 2; i++) {
		if (src->cid[i] != NULL)
			merge_tree(src->cid[i], dest);
	}
	insert(dest, src->val);
	delete src;
	src = NULL;
}

// Treap
Node::Node (int val) {
	sum = 1;
	rank = rand();
	this->val = val;
	cid[0] = cid[1] = NULL;
}

void Node::maintain() {
	sum = 1;
	if (cid[0] != NULL) sum += cid[0]->sum;
	if (cid[1] != NULL) sum += cid[1]->sum;
}

int Node::cmp(int x) {
	if (val == x)
		return -1;
	return val < x ? 1 : 0;
}

void remove(Node* &o, int x) {
	int d = o->cmp(x);
	if (d == -1) {
		Node* u = o;
		if (o->cid[0] != NULL && o->cid[1] != NULL) {
			int d2 = (o->cid[0]->rank > o->cid[1]->rank ? 1 : 0);
			rotate(o, d2);
			remove(o->cid[d2], x);
		} else {
			o = (o->cid[0] == NULL ? o->cid[1] : o->cid[0]);
			delete u;
		}
	} else
		remove(o->cid[d], x);

	if (o != NULL)
		o->maintain();
}

void rotate (Node* &o, int d) {
	Node* k = o->cid[d^1];
	o->cid[d^1] = k->cid[d];
	k->cid[d] = o;
	o->maintain();
	k->maintain();
	o = k;
}

void insert(Node* &o, int x) {
	if (o == NULL)
		o = new Node(x);
	else {
		int d = (x < o->val ? 0 : 1);
		insert(o->cid[d], x);
		if (o->cid[d]->rank > o->rank)
			rotate(o, d^1);
	}
	o->maintain();
}
