#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 50010;
#define lowbit(x) ((x)&(-x))
struct Node {
	Node* ch[2];
	int key, len, idx, val;
	int mlen, midx;

	Node () {}
	Node (int key, int len, int idx):key(key), len(len), idx(idx), mlen(len), midx(idx) {
		val = rand();
		ch[0] = ch[1] = NULL;
	}

	void maintain() {
		mlen = len;
		midx = idx;

		for (int i = 0; i < 2; i++) {
			if (ch[i] != NULL && (ch[i]->mlen > mlen || (ch[i]->mlen == mlen && ch[i]->midx < midx))) {
				mlen = ch[i]->mlen;
				midx = ch[i]->midx;
			}
		}
	}

	int cmp (int v) {
		if (v == key)
			return -1;
		return v < key ? 0 : 1;
	}
};

void findMax(Node* a, Node* b) {
	if (a->mlen < b->mlen || (a->mlen == b->mlen && a->midx > b->midx))
		*a = *b;
}

namespace Treap {
	int cntNode;
	Node nd[maxn * 10];

	void init () {
		cntNode = 0;
	}

	Node* newNode (int key, int len, int idx) {
		nd[++cntNode] = Node(key, len, idx);
		return &nd[cntNode];
	}

	void rotate(Node* &o, int d) {
		Node* k = o->ch[d^1];
		o->ch[d^1] = k->ch[d];
		k->ch[d] = o;
		o->maintain();
		k->maintain();
		o = k;
	}

	void insert(Node* &o, int key, int len, int idx) {
		if (o == NULL)
			o = newNode(key, len, idx);
		else {
			int d = o->cmp(key);
			if (d != -1) {
				insert(o->ch[d], key, len, idx);
				if (o->val < o->ch[d]->val)
					rotate(o, d^1);
			} else if (len >= o->len) {
				o->len = len;
				o->idx = idx;
			}
		}
		o->maintain();
	}

	Node query(Node* o, int key) {
		if (o == NULL)
			return Node(-1, 0, -1);
		else {
			Node ret, tmp;
			if (o->key == key) {
				ret = Node(o->key, o->len, o->idx);
				if (o->ch[1])
					findMax(&ret, o->ch[1]);
			} else if (o->key > key) {
				ret = Node(o->key, o->len, o->idx);
				if (o->ch[1])
					findMax(&ret, o->ch[1]);

				tmp = query(o->ch[0], key);
				findMax(&ret, &tmp);
			} else {
				ret = query(o->ch[1], key);
			}
			return ret;
		}
	}
}

namespace Bit {

	int n;
	Node* fenw[maxn];

	void init (int k) {
		n = k;
		memset(fenw, 0, sizeof(fenw));
	}

	void add (int x, int key, int len, int idx) {
		while (x < n) {
			Treap::insert(fenw[x], key, len, idx);
			x += lowbit(x);
		}
	}

	Node search(int x, int level) {
		Node ret, tmp;
		ret = Node(-1, 0, -1);
		while (x > 0) {
			tmp = Treap::query(fenw[x], level);
			findMax(&ret, &tmp);
			x -= lowbit(x);
		}
		return ret;
	}
}

struct Pi {
	int L, R, id;
	bool operator < (const Pi& u) const {
		return L < u.L;
	}
}P[maxn];

bool cmp(const Pi& a, const Pi& b) {
	return a.id < b.id;
}
int N, M, Idx[maxn], Pre[maxn];

void print (Node& ans) {
	int mv = ans.midx;
	printf("%d\n", ans.mlen);
	while (true) {
		printf("%d", mv);
		if (Pre[mv] == -1)
			break;
		printf(" ");
		mv = Pre[mv];
	}
	printf("\n");
}

int main () {
	while (scanf("%d", &N) == 1) {
		for (int i = 1; i <= N; i++) {
			scanf("%d", &P[i].L);
			P[i].id = i;
		}
		for (int i = 1; i <= N; i++)
			scanf("%d", &P[i].R);
		sort(P + 1, P + N + 1);

		M = 0;
		Idx[1] = ++M;
		for (int i = 2; i <= N; i++) {
			if (P[i].L != P[i-1].L)
				Idx[i] = ++M;
			else
				Idx[i] = Idx[i-1];
		}
		for (int i = 1; i <= N; i++)
			P[i].L = Idx[i];
		sort(P + 1, P + N + 1, cmp);

		Bit::init(M + 1);
		Treap::init();

		Node ans = Node(-1, 0, -1), tmp;
		for (int i = N; i > 0; i--) {
			tmp = Bit::search(P[i].L, P[i].R);
			Pre[i] = tmp.midx;
			tmp.mlen = tmp.mlen + 1;
			tmp.midx = i;
			Bit::add(P[i].L, P[i].R, tmp.mlen, tmp.midx);
			findMax(&ans, &tmp);
		}
		print(ans);
	}
	return 0;
}
