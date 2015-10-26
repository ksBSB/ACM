#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 400040;
typedef long long ll;

/***************** FFT ************************/
const double pi = acos(-1.0);

struct Complex {
    double r,i;
    Complex(double r = 0,double i = 0): r(r), i(i) { }
    Complex operator + (const Complex &u) { return Complex(r+u.r,i+u.i); }
    Complex operator - (const Complex &u) { return Complex(r-u.r,i-u.i); }
    Complex operator * (const Complex &u) { return Complex(r*u.r-i*u.i,r*u.i+i*u.r); }
};
Complex X[maxn];

void change(Complex* y, int n) {
    int k;
    for(int i = 1, j = n/2; i < n-1; i++) {
        if(i < j)swap(y[i],y[j]);
        k = n/2;
        while(j >= k) {
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}

void dft(Complex* y, int n, int sign) {

    change(y,n);

    for (int h = 2; h <= n; h <<= 1) {

        Complex wn(cos(-sign*2*pi/h),sin(-sign*2*pi/h));
        for(int j = 0; j < n; j += h) {
            Complex w(1,0);
            for(int k = j; k < j+h/2; k++) {
                Complex u = y[k];
                Complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }

    if (sign == -1)
        for(int i = 0;i < n;i++)
            y[i].r /= n;
}

void fft (ll* cnt, int n) {
	int m = 1;
	while (m < 2 * n) m <<= 1;


	for (int i = 0; i < n; i++)
		X[i] = Complex(cnt[i], 0);
	for (int i = n; i < m; i++)
		X[i] = Complex(0, 0);

	dft(X, m, 1);
	for (int i = 0; i < m; i++)
		X[i] = X[i] * X[i];
	dft(X, m, -1);
	for (int i = 0; i < m; i++)
		cnt[i] = (ll)(X[i].r + 0.5);
}

/***********************************************/

int N, M, A[maxn>>2];
ll cnt[maxn], sum[maxn];

void init () {
	scanf("%d", &N);
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
		cnt[A[i]]++;
	}
	sort(A, A + N);
}

double solve () {
	fft(cnt, A[N-1]+1);
	int n = A[N-1] + 1;
	for (int i = 0; i < N; i++)
		cnt[A[i]+A[i]]--;
	for (int i = 0; i < 2 * n; i++)
		cnt[i] /= 2;
	sum[0] = 0;
	for (int i = 1; i < 2 * n; i++)
		sum[i] = sum[i-1] + cnt[i];

	double tot = 1.0 * N * (N-1) * (N-2) / 6, ret = 0;
	for (int i = 0; i < N; i++)
		ret += sum[A[i]] / tot;
	return ret;
}

int main() {
	int cas;
	scanf("%d", &cas);

	while(cas--) {
		init();

		printf("%.7lf\n", 1 - solve());
	}
	return 0;
}
