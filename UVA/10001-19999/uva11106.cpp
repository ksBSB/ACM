#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;
const int N = 100005;

struct point {
	int x, y, t, id;
	friend bool operator < (const point& a, const point& b) {
		return a.y > b.y;
	}
}p[N], s[N];

struct node {
	int t;
	node* link;
	node(int t) { 
		this->t = t;
		this->link = NULL; 
	}
};

int n, m, f[N];

int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

bool cmpX(const point& a, const point& b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

bool cmpY(const point& a, const point& b) {
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

void init() {
	m = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &p[i].x, &p[i].y);
		f[i] = p[i].id = i;
	}
	sort(p, p + n, cmpX);
}

void del(node* first, int x) {
	node* far = first;
	node* mov = first->link;
	while (mov != NULL) {
		if (mov->t == x) {
			far->link = mov->link;
			delete mov;
			return;
		}
		far = mov;
		mov = mov->link;
	}
}

int solve() {
	if (n&1) return -1;
	bool flag = false;
	int ans = 0;

	for (int i = 0; i < n; i += 2) {
		if (p[i].x != p[i+1].x) return -1;
		ans += p[i+1].y - p[i].y;
		s[m].x = p[i].y, s[m].y = p[i+1].y, s[m].t = p[i].x, m++;
		f[getfar(p[i].id)] = getfar(p[i+1].id);
	}
	int tmp = m, v = 0;
	sort(s, s + m, cmpX);
	sort(p, p + n, cmpY);
	priority_queue<point> que;
	node* first = new node(0);

	for (int i = 0; i < n; i+= 2) {
		if (p[i].y != p[i+1].y) {
			flag = true; break;
		}
	
		while (v < m) {
			if (s[v].x < p[i].y) {
				que.push(s[v]);
				node* p = new node(s[v].t);
				p->link = first->link; first->link = p;
			} else break;
			v++;
		}

		while (!que.empty()) {
			point c = que.top();
			if (c.y <= p[i].y) {
				del(first, c.t);
				que.pop();
			}
			else break;
		}

		node* mov = first->link;
		while (mov != NULL) {
			if (mov->t > p[i].x && mov->t < p[i+1].x) {
				flag = true; break;
			}
			mov = mov->link;	
		}

		if (flag) break;

		ans += p[i+1].x - p[i].x;
		if (getfar(p[i].id) != getfar(p[i+1].id)) {
			f[getfar(p[i].id)] = getfar(p[i+1].id);
			tmp--;
		}
	}
	while (first != NULL) {
		node* c = first->link;
		first = first->link;
		delete c;
	}
	return tmp > 1 || flag ? -1 : ans;
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
