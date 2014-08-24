#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;
typedef set<int> sint;
typedef set<int>::iterator iter;

int hn;
stack<sint> stak;
map<sint, int> g;

void hashadd (sint u) {
	if (g.count(u))
		return;
	g[u] = hn++;
}

void putsize () {
	if (stak.empty())
		return;
	printf("%d\n", (int)stak.top().size());
}

void sf_push () {
	sint u;
	hashadd(u);
	stak.push(u);
}

void sf_dup () {
	sint u = stak.top();
	stak.push(u);
}

void sf_union () {
	sint f = stak.top();
	stak.pop();
	sint u = stak.top();
	stak.pop();

	for (iter i = f.begin(); i != f.end(); i++)
		u.insert(*i);
	hashadd(u);
	stak.push(u);
}

void sf_inct () {
	sint u;
	sint f = stak.top();
	stak.pop();
	sint s = stak.top();
	stak.pop();

	for (iter i = f.begin(); i != f.end(); i++) {
		if (s.count(*i))
			u.insert(*i);
	}

	hashadd(u);
	stak.push(u);
}

void sf_add () {
	sint f = stak.top();
	stak.pop();
	sint s = stak.top();
	stak.pop();

	s.insert(g[f]);
	hashadd(s);
	stak.push(s);
}

void solve () {
	char order[10];
	scanf("%s", order);
	switch (order[0]) {
		case 'P':
			sf_push();
			break;
		case 'D':
			sf_dup();
			break;
		case 'U':
			sf_union();
			break;
		case 'I':
			sf_inct();
			break;
		case 'A':
			sf_add();
			break;
	}
	putsize();
}

int main () {
	int cas, n;
	scanf("%d", &cas);

	while (cas--) {
		hn = 0;
		g.clear();
		while (!stak.empty())
			stak.pop();

		scanf("%d", &n);
		while (n--)
			solve();
		printf("***\n");
	}
	return 0;
}
