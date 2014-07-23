#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;
const int maxn = 16;

struct Trian {
	int x, y, z;
	Trian () {};
	Trian (int x, int y, int z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Trian add (int type) {
		int mv = (x+y+z == 0 ? 1 : -1);
		if (type == 0)
			return Trian(x, y+mv, z+mv);
		else if (type == 1)
			return Trian(x+mv, y, z+mv);
		else
			return Trian(x+mv, y+mv, z);
	}

	void rotate () {
		int tmp = x;
		x = y;
		y = z;
		z = tmp;
	}

	void overturn () {
		x = 1 - x;
		y = 1 - y;
		z = -z;
	}

	void move (int x, int y, int z) {
		this->x += x;
		this->y += y;
		this->z += z;
	}
};

bool operator == (const Trian& a, const Trian& b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool operator < (const Trian& a, const Trian& b) {
	if (a.x != b.x)
		return a.x < b.x;
	else if (a.y != b.y)
		return a.y < b.y;
	else
		return a.z < b.z;
}

struct Hash {
	int cnt, key[maxn+5];
};

bool operator < (const Hash& a, const Hash& b) {
	if (a.cnt != b.cnt)
		return a.cnt < b.cnt;
	for (int i = 0; i < a.cnt; i++)
		if (a.key[i] != b.key[i])
			return a.key[i] < b.key[i];
	return false;
}

struct Pizz {
	int cnt;
	Trian arr[maxn+5];
	Pizz () { cnt = 0; }

	bool add (const Trian& u) {

		for (int i = 0; i < cnt; i++)
			if (arr[i] == u)
				return false;
		arr[cnt++] = u;
		return true;
	}

	void remove () { cnt--; }

	Hash getKey () {
		Hash u;
		u.cnt = cnt;

		for (int i = 0; i < cnt; i++) {
			u.key[i] = arr[i].x + 8;
			u.key[i] <<= 4;
			u.key[i] += arr[i].y + 8;
			u.key[i] <<= 4;
			u.key[i] += arr[i].z + 8;
		}
		return u;
	}
};

set<Hash> vis;
int ans[maxn+5] = {0};

bool find (Pizz v) {
	for (int i = 0; i < 3; i++) {
		sort(v.arr, v.arr+v.cnt);
		if (vis.find(v.getKey()) != vis.end())
			return true;

		for (int j = 0; j < v.cnt; j++)
			v.arr[j].rotate();
	}
	return false;
}

bool search (Pizz u) {
	for (int i = 0; i < u.cnt; i++) {
		int x = u.arr[i].x;
		int y = u.arr[i].y;
		int z = u.arr[i].z;

		Pizz v = u;
		if (x + y + z == 0) {

			for (int j = 0; j < v.cnt; j++)
				v.arr[j].move(-x, -y, -z);

			if (find(v))
				return true;
		} else {

			for (int j = 0; j < v.cnt; j++) {
				v.arr[j].overturn();
				v.arr[j].move(x-1, y-1, z);
			}

			if (find(v))
				return true;
		}
	}
	return false;
}

void insert (Pizz u) {
	for (int i = 0; i < 3; i++) {
		sort(u.arr, u.arr+u.cnt);	
		vis.insert(u.getKey());

		for (int j = 0; j < u.cnt; j++)
			u.arr[j].rotate();
	}
}

void dfs (Pizz u) {
	if (u.cnt == maxn+1)
		return;

	if (search(u))
		return;

	insert(u);
	ans[u.cnt]++;

	for (int i = 0; i < u.cnt; i++) {
		for (int j = 0; j < 3; j++) {
			Trian v = u.arr[i].add(j);
			if (u.add(v)) {
				dfs(u);
				u.remove();
			}
		}
	}
}
int rec[maxn+5] = {0, 1, 1, 1, 4, 6, 19, 43, 120, 307, 866, 2336, 6588, 18373, 52119, 147700, 422016};

int main () {
	/*
	Pizz u;
	u.add(Trian(0, 0, 0));
	dfs(u);

	for (int i = 0; i <= maxn; i++)
		printf("%d\n", ans[i]);
	*/

	int cas, n;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%d", &n);
		printf("Case #%d: %d\n", i, rec[n]);
	}
	return 0;
}
