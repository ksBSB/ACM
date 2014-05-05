
#include <stdio.h>
#include <string.h>
#include <math.h>


#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)

const int MAXSIZE = 10000;

struct bign {
	int s[MAXSIZE];
	bign ()	{memset(s, 0, sizeof(s));}
	bign (int number) {*this = number;}
	bign (const char* number) {*this = number;}
    
	void put();
	bign mul(int d);
	void del();
	void init() { memset(s, 0, sizeof(s)); }
    
	bign operator =  (char *num);
	bign operator =  (int num);

	bool operator <  (const bign& b) const;
	bool operator >  (const bign& b) const { return b < *this; }
	bool operator <= (const bign& b) const { return !(b < *this); }
	bool operator >= (const bign& b) const { return !(*this < b); }
	bool operator != (const bign& b) const { return b < *this || *this < b;}
	bool operator == (const bign& b) const { return !(b != *this); }
    
	bign operator + (const bign& c);
	bign operator * (const bign& c);
	bign operator - (const bign& c);
	int  operator / (const bign& c);
	bign operator / (int k);
	bign operator % (const bign &c);
	int  operator % (int k);
	void operator ++ ();
	bool operator -- ();
};

const int N = 22;
int node[N][N];
bign ans[N][N];

bign C(int x, int y) {
	y = min(y, x - y);
	bign c = 1, d;
	for (int i = 0; i < y; i++) {
		d = x - i;
		c = c * d;
		c = c / (i + 1);
	}

	return c;
}

void solve(int x, int y) {

	ans[x][y] = 1;
	int m = node[x][y - 1];
	for (int i = 0; i < x; i++) {
		ans[x][y] = ans[x][y] * C(node[x][y] - i * m - 1, m) * ans[x][y - 1];
	}
}

void init() {
	for (int i = 1; i <= 21; i++)
		ans[1][i] = 1;
	
	for (int i = 2; i <= 21; i++) {
		int top = 21 / i;
		ans[i][0] = node[i][0] = 1;
		node[i][0] = 1;
		for (int j = 1; j <= top; j++) {
			node[i][j] = node[i][j - 1] * i + 1;
			solve(i, j);
		}
	}
}

int main () {
	init();

	int k, d;
	while (scanf("%d%d", &k, &d) == 2) {
		ans[k][d].put();
		printf("\n");
	}
	/*
	int a, b;
	while (scanf("%d%d", &a, &b) == 2) {
		bign t = C(a, b);
		t.put();
		printf("!\n");
	}
	*/
	return 0;
}

bign bign::operator = (char *num) {
	init();
	s[0] = strlen(num);
	for (int i = 1; i <= s[0]; i++)
		s[i] = num[s[0] - i] - '0';
	return *this;
}

bign bign::operator = (int num) {
	char str[MAXSIZE];
	sprintf(str, "%d", num);
	return *this = str;
}

bool bign::operator < (const bign& b) const {
	if (s[0] != b.s[0])
		return s[0] < b.s[0];
	for (int i = s[0]; i; i--)
		if (s[i] != b.s[i])
			return s[i] < b.s[i];
	return false;
}

bign bign::operator + (const bign& c) {
	int sum = 0;
	bign ans;
	ans.s[0] = max(s[0], c.s[0]);

	for (int i = 1; i <= ans.s[0]; i++) {
		if (i <= s[0]) sum += s[i];
		if (i <= c.s[0]) sum += c.s[i];
		ans.s[i] = sum % 10;
		sum /= 10;
	}
	return ans;
}

bign bign::operator * (const bign& c) {
	bign ans;
	ans.s[0] = 0; 

	for (int i = 1; i <= c.s[0]; i++){  
		int g = 0;  

		for (int j = 1; j <= s[0]; j++){  
			int x = s[j] * c.s[i] + g + ans.s[i + j - 1];  
			ans.s[i + j - 1] = x % 10;  
			g = x / 10;  
		}  
		int t = i + s[0] - 1;

		while (g){  
			++t;
			g += ans.s[t];
			ans.s[t] = g % 10;
			g = g / 10;  
		}  

		ans.s[0] = max(ans.s[0], t);
	}  
	ans.del();
	return ans;
}

bign bign::operator - (const bign& c) {
	bign ans = *this;
	for (int i = 1; i <= c.s[0]; i++) {
		if (ans.s[i] < c.s[i]) {
			ans.s[i] += 10;
			ans.s[i + 1]--;;
		}
		ans.s[i] -= c.s[i];
	}

	for (int i = 1; i <= ans.s[0]; i++) {
		if (ans.s[i] < 0) {
			ans.s[i] += 10;
			ans.s[i + 1]--;
		}
	}

	ans.del();
	return ans;
}

int bign::operator / (const bign& c) {
	int ans = 0;
	bign d = *this;
	while (d >= c) {
		d = d - c;
		ans++;
	}
	return ans;
}

bign bign::operator / (int k) {
	bign ans; 
	ans.s[0] = s[0];
	int num = 0;  
	for (int i = s[0]; i; i--) {  
		num = num * 10 + s[i];  
		ans.s[i] = num / k;  
		num = num % k;  
	}  
	ans.del();
	return ans;
}

int bign:: operator % (int k){  
	int sum = 0;  
	for (int i = s[0]; i; i--){  
		sum = sum * 10 + s[i];  
		sum = sum % k;  
	}  
	return sum;  
} 

bign bign::operator % (const bign &c) {
	bign now = *this;
	while (now >= c) {
		now = now - c;
		now.del();
	}
	return now;
}

void bign::operator ++ () {
	s[1]++;
	for (int i = 1; s[i] == 10; i++) {
		s[i] = 0;
		s[i + 1]++;
		s[0] = max(s[0], i + 1);
	}
}

bool bign::operator -- () {
	del();
	if (s[0] == 1 && s[1] == 0) return false;

	int i;
	for (i = 1; s[i] == 0; i++)
		s[i] = 9;
	s[i]--;
	del();
	return true;
}

void bign::put() {
	if (s[0] == 0)
		printf("0");
	else
		for (int i = s[0]; i; i--)
			printf("%d", s[i]);
}

bign bign::mul(int d) {
	s[0] += d;
	for (int i = s[0]; i > d; i--)
		s[i] = s[i - d];
	for (int i = d; i; i--)
		s[i] = 0;
	return *this;
}

void bign::del() {
	while (s[s[0]] == 0) {
		s[0]--;
		if (s[0] == 0) break;
	}
}
