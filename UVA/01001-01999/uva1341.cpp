#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 65536;
int n, vis[maxn+10];

struct state {
	int key, len, vec[maxn];
	state () {
		key = 0;
	}

	bool operator < (const state& a) {
		if (a.key == 0)
			return true;
		if (key == 0)
			return false;

		if (key != a.key)
			return key < a.key;

		if (len != a.len)
			return len < a.len;

		int l = len;
		for (int i = 0; i < l; i++)
			if (vec[i] != a.vec[i])
				return vec[i] < a.vec[i];
		return false;
	}
};

struct node {
	int mod, len, num;
	void set (int mod, int num, int len) {
		this->mod = mod;
		this->num = num;
		this->len = len;
	}
}que[maxn*2];

void put (int d, state& w, int x) {
	if (d < 0 || x < 0)
		return;
	w.vec[d] = que[x].num;
	put(d-1, w, vis[que[x].mod]);
}

state judge (int a, int b) {
	int head = 1, rear = 1;
	memset(vis, -1, sizeof(vis));

	state w;
	node u, v;
	w.key = (a==b?1:2);

	if (a) {
		que[rear++].set(a%n, a, 1);
		vis[a%n] = 0;
	}

	if (b) {
		que[rear++].set(b%n, b, 1);
		vis[b%n] = 0;
	}

	while (head < rear) {
		u = que[head++];

		if (u.mod == 0) {
			w.len = u.len;
			put(u.len-1, w, head-1);
			return w;
		}

		for (int i = 0; i < w.key; i++) {
			int t = (i?b:a);
			v.set((u.mod*10+t)%n, t, u.len+1);

			if (vis[v.mod] != -1)
				continue;

			vis[v.mod] = head-1;;
			que[rear++] = v;
		}
	}
	w.key = 0;
	return w;
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		state ans;

		for (int i = 1; i <= 9; i++) {
			state c = judge(i, i);
			if (c < ans)
				ans = c;
		}

		if (ans.key == 0) {
			for (int i = 0; i <= 9; i++) {
				for (int j = i+1; j <= 9; j++) {
					state c = judge(i, j);
					if (c < ans)
						ans = c;
				}
			}
		}
		for (int i = 0; i < ans.len; i++)
			printf("%d", ans.vec[i]);
		printf("\n");
	}	
	return 0;
}
