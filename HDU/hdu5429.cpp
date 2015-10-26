#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int maxn = 10005;

struct bign {
	int len, num[maxn];

	bign () {
		len = 0;
		memset(num, 0, sizeof(num));
	}
	bign (int number) {*this = number;}
	bign (const char* number) {*this = number;}

	void delzero ();
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
	bign operator * (const int& b);
	bign operator * (const bign& b);
	bign operator / (const int& b);
	//bign operator / (const bign& b);
	int operator % (const int& b);
};

const int maxm = 105;

int N;
char s[maxm];
bign A[maxm], zero = 0;

bool judge () {
	int c = 0;
	for (int i = 0; i < N; i++) if (A[i] == zero) c++;
	if (c) return c == N;
	for (int i = 1; i < N-1; i++)
		if (A[i-1] * A[i+1] != A[i] * A[i]) return false;
	return true;
}

/*Code*/
int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%s", s);
			A[i] = s;
		}
		printf("%s\n", judge() ? "Yes" : "No");
	}
	return 0;
}

void bign::delzero () {
	while (len && num[len-1] == 0)
		len--;

	if (len == 0) {
		num[len++] = 0;
	}
}

void bign::Put () {
	for (int i = len-1; i >= 0; i--) 
		printf("%d", num[i]);
}

void bign::operator = (char* number) {
	len = strlen (number);
	for (int i = 0; i < len; i++)
		num[i] = number[len-i-1] - '0';

	delzero ();
}

void bign::operator = (int number) {

	len = 0;
	while (number) {
		num[len++] = number%10;
		number /= 10;
	}

	delzero ();
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
	delzero ();
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
	ans.delzero ();
	return ans;
}

bign bign::operator * (const int& b) {
	int bignSum = 0;
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
	ans.delzero ();
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
