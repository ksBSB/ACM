#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Node {
	int val, sum, flip;
	Node* cid[2];

	Node(int val = 0);
	int cmp (int v);
	void maintain();
	void pushdown();
};

void rotate (Node* &o, int d);

void build(Node* &o, int l, int r);
void put(Node* &o);
void split (Node* o, int k, Node* &l, Node* & r);
Node* merge (Node* l, Node* r);
void splay(Node* &o, int k);

int main () {
	int n, m, x, y;
	while (scanf("%d%d", &n, &m) == 2) {
		Node* root = NULL;
		Node *l, *mid, *r, *o;

		build(root, 0, n);

		for (int i = 0; i < m; i++) {
			scanf("%d%d", &x, &y);

			split(root, x, l, o);
			split(o, y - x + 1, mid, r);

			mid->flip ^= 1;
			root = merge(merge(l, r), mid);
		}
		put(root);
	}
	return 0;
}

void splay(Node* &o, int k) {

	o->pushdown();
	int d = o->cmp(k);

	if (d == 1) k -= (o->cid[0] == NULL ? 0 : o->cid[0]->sum) + 1;

	if (d != -1) {
		Node* p = o->cid[d];
		p->pushdown();

		int d2 = p->cmp(k);
		int k2 = (d2 == 0 ? k : k - (p->cid[0] == NULL ? 0 : p->cid[0]->sum) - 1);
		if (d2 != -1) {
			splay(p->cid[d2], k2);
			if (d == d2)
				rotate(o, d^1);
			else
				rotate(o->cid[d], d);
		}
		rotate(o, d^1);
	}
}

Node* merge (Node* l, Node* r) {
	splay(l, l->sum);
	l->cid[1] = r;
	l->maintain();
	return l;
}

void split (Node* o, int k, Node* &l, Node* & r) {
	splay(o, k);
	l = o;
	r = o->cid[1];
	o->cid[1] = NULL;
	l->maintain();
}

void build(Node* &o, int l, int r) {
	if (l > r)
		return;

	int mid = (l + r) / 2;
	o = new Node(mid);
	build(o->cid[0], l, mid - 1);
	build(o->cid[1], mid + 1, r);
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

void put(Node* &o) {
	o->pushdown();
	if (o->cid[0] != NULL) put(o->cid[0]);
	if (o->val)
		printf("%d\n", o->val);
	if (o->cid[1] != NULL) put(o->cid[1]);

	delete o;
	o = NULL;
}

Node::Node (int val) {
	sum = 1;
	flip = 0;
	this->val = val;
	cid[0] = cid[1] = NULL;
}

int Node::cmp (int v) {
	int d = v - (cid[0] == NULL ? 0 : cid[0]->sum);
	if (d == 1) return -1;
	return d <= 0 ? 0 : 1;
}

void Node::pushdown() {
	if (flip) {
		flip = 0;
		swap(cid[0], cid[1]);
		if (cid[0] != NULL)
			cid[0]->flip = !cid[0]->flip;
		if (cid[1] != NULL)
			cid[1]->flip = !cid[1]->flip;
	}
}

void Node::maintain () {
	sum = 1;
	if (cid[0] != NULL) sum += cid[0]->sum;
	if (cid[1] != NULL) sum += cid[1]->sum;
}

void remove (Node* &o) {
	if (o->cid[0] != NULL) remove(o->cid[0]);
	if (o->cid[1] != NULL) remove(o->cid[1]);
	delete o;
	o = NULL;
}
