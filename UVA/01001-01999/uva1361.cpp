#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int maxn = 2 * 1e5 + 5;

int N, M, cnt[maxn], C[maxn], vis[maxn];
bool flag;
int cntlock, cntbcc, pre[maxn], iscut[maxn], bccno[maxn];
vector<int> BCC[maxn], G[maxn];
stack<pii> S;

int dfs (int u, int fa) {
	int lowu = pre[u] = ++cntlock, child = 0;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		pii e = make_pair(u, v);
		if (!pre[v]) {
			S.push(e);
			child++;
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);
			if (lowv >= pre[u]) {
				iscut[u] = 1;
				BCC[++cntbcc].clear();
				while (true) {
					pii x = S.top(); S.pop();
					if (bccno[x.first] != cntbcc) {
						bccno[x.first] = cntbcc;
						BCC[cntbcc].push_back(x.first);
					}
					if (bccno[x.second] != cntbcc) {
						bccno[x.second] = cntbcc;
						BCC[cntbcc].push_back(x.second);
					}
					if (u == x.first && v == x.second) break;
				}
			}
		} else if (pre[v] < pre[u] && v != fa) {
			S.push(e);
			lowu = min(lowu, pre[v]);
		}
	}
	if (fa < 0 && child == 1) iscut[u] = 0;
	return lowu;
}

bool findBCC() {
	cntlock = cntbcc = 0;
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	memset(bccno, 0, sizeof(bccno));
	dfs(1, -1);
	for (int i = 1; i <= N; i++)
		if (!pre[i]) return false;
	return true;
}

void init () {
	for (int i = 1; i <= N; i++) G[i].clear();

	int k, x, y;
	while (M--) {
		scanf("%d%d", &k, &x);
		for (int i = 1; i < k; i++) {
			scanf("%d", &y);
			G[x].push_back(y);
			G[y].push_back(x);
			x = y;
		}
	}
	flag = findBCC();
}

int isSimpleCircle(const vector<int>& g) {
	int ret = 0;
	for (int i = 0; i < g.size(); i++) {
		int u = g[i];
		for (int j = 0; j < G[u].size(); j++) {
			int v = G[u][j];
			if (bccno[v] == bccno[u]) ret++;
		}
	}
	return ret / 2;
}

bool judge () {
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= cntbcc; i++) {
		for (int j = 0; j < BCC[i].size(); j++) bccno[BCC[i][j]] = i;
		int n = isSimpleCircle(BCC[i]);
		if (n > BCC[i].size()) return false;

		if (n == BCC[i].size()) {
			for (int j = 0; j < BCC[i].size(); j++) vis[BCC[i][j]]++;
			C[i] = BCC[i].size() + 1;
		} else
			C[i] = 1;
	}
//	for (int i = 1; i <= N; i++)
//		if (vis[i] >= 2) return false;
	return true;
}

/******* BidInter **********/
const int MAXN = 1e4;

struct bign {
	int len, num[MAXN];

	bign () {
		len = 0;
		memset(num, 0, sizeof(num));
	}
	bign (int number) {*this = number;}
	bign (const char* number) {*this = number;}

	void DelZero ();
	void Put ();

	void operator = (int number);
	void operator = (char* number);

	bool operator <  (const bign& b) const;
	bool operator >  (const bign& b) const { return b < *this; }
	bool operator <= (const bign& b) const { return !(b < *this); }
	bool operator >= (const bign& b) const { return !(*this < b); }
	bool operator != (const bign& b) const { return b < *this || *this < b;}
	bool operator == (const bign& b) const { return !(b != *this); }

	void operator ++ ();
	void operator -- ();
	bign operator + (const int& b);
	bign operator + (const bign& b);
	bign operator - (const int& b);
	bign operator - (const bign& b);
	bign operator * (const ll& b);
	bign operator * (const bign& b);
	bign operator / (const int& b);
	//bign operator / (const bign& b);
	int operator % (const int& b);
}ans;
/***************************/

int main () {
	int cas = 0;
	while (scanf("%d%d", &N, &M) == 2) {
		if (cas++) printf("\n");
		init();
		if (flag && judge()) {
			ans = 1;
			for (int i = 1; i <= cntbcc; i++) if (C[i] != 1)
				ans = ans * C[i];
			ans.Put();
			printf("\n");

		} else
			printf("0\n");
	}
	return 0;
}

/**********************/

void bign::DelZero () {
	while (len && num[len-1] == 0)
		len--;

	if (len == 0)
		num[len++] = 0;
}

void bign::Put () {
	for (int i = len-1; i >= 0; i--) 
		printf("%d", num[i]);
}

void bign::operator = (char* number) {
	len = strlen (number);
	for (int i = 0; i < len; i++)
		num[i] = number[len-i-1] - '0';

	DelZero ();
}

void bign::operator = (int number) {

	len = 0;
	while (number) {
		num[len++] = number%10;
		number /= 10;
	}

	DelZero ();
}

bool bign::operator < (const bign& b) const {
	if (len != b.len)
		return len < b.len;
	for (int i = len-1; i >= 0; i--)
		if (num[i] != b.num[i])
			return num[i] < b.num[i];
	return false;
}

void bign::operator ++ () {
	int s = 1;

	for (int i = 0; i < len; i++) {
		s = s + num[i];
		num[i] = s % 10;
		s /= 10;
		if (!s) break;
	}

	while (s) {
		num[len++] = s%10;
		s /= 10;
	}
}

void bign::operator -- () {
	if (num[0] == 0 && len == 1) return;

	int s = -1;
	for (int i = 0; i < len; i++) {
		s = s + num[i];
		num[i] = (s + 10) % 10;
		if (s >= 0) break;
	}
	DelZero ();
}

bign bign::operator + (const int& b) {
	bign a = b;
	return *this + a;
}

bign bign::operator + (const bign& b) {
	int bignSum = 0;
	bign ans;

	for (int i = 0; i < len || i < b.len; i++) {
		if (i < len) bignSum += num[i];
		if (i < b.len) bignSum += b.num[i];

		ans.num[ans.len++] = bignSum % 10;
		bignSum /= 10;
	}

	while (bignSum) {
		ans.num[ans.len++] = bignSum % 10;
		bignSum /= 10;
	}

	return ans;
}

bign bign::operator - (const int& b) {
	bign a = b;
	return *this - a;
}


bign bign::operator - (const bign& b) {
	int bignSub = 0;
	bign ans;
	for (int i = 0; i < len || i < b.len; i++) {
		bignSub += num[i];
		bignSub -= b.num[i];
		ans.num[ans.len++] = (bignSub + 10) % 10;
		if (bignSub < 0) bignSub = -1;
		else bignSub = 0;
	}
	ans.DelZero ();
	return ans;
}

bign bign::operator * (const ll& b) {
	ll bignSum = 0;
	bign ans;

	ans.len = len;
	for (int i = 0; i < len; i++) {
		bignSum += num[i] * b;
		ans.num[i] = bignSum % 10;
		bignSum /= 10;
	}

	while (bignSum) {
		ans.num[ans.len++] = bignSum % 10;
		bignSum /= 10;
	}

	return ans;
}

bign bign::operator * (const bign& b) {
	bign ans;
	ans.len = 0; 

	for (int i = 0; i < len; i++){  
		int bignSum = 0;  

		for (int j = 0; j < b.len; j++){  
			bignSum += num[i] * b.num[j] + ans.num[i+j];  
			ans.num[i+j] = bignSum % 10;  
			bignSum /= 10;
		}  
		ans.len = i + b.len;  

		while (bignSum){  
			ans.num[ans.len++] = bignSum % 10;  
			bignSum /= 10;
		}  
	}  
	return ans;
}

bign bign::operator / (const int& b) {

	bign ans;

	int s = 0;
	for (int i = len-1; i >= 0; i--) {
		s = s * 10 + num[i];
		ans.num[i] = s/b;
		s %= b;
	}

	ans.len = len;
	ans.DelZero ();
	return ans;
}

int bign::operator % (const int& b) {

	bign ans;

	int s = 0;
	for (int i = len-1; i >= 0; i--) {
		s = s * 10 + num[i];
		ans.num[i] = s/b;
		s %= b;
	}

	return s;
}
