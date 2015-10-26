#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 2 * 1e5 + 5;

/***************** FFT ************************/
const double pi = acos(-1.0);

struct Complex {
    double r,i;
    Complex(double r = 0,double i = 0): r(r), i(i) { }
    Complex operator + (const Complex &u) { return Complex(r+u.r,i+u.i); }
    Complex operator - (const Complex &u) { return Complex(r-u.r,i-u.i); }
    Complex operator * (const Complex &u) { return Complex(r*u.r-i*u.i,r*u.i+i*u.r); }
};
Complex X[maxn], Y[maxn];

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

void fft (ll* a, int n, ll* b, int m, ll* c, int& k) {
	k = 1;
	while (k < 2 * n || k < 2 * m) k <<= 1;

	for (int i = 0; i < n; i++)
		X[i] = Complex(a[i], 0);
	for (int i = n; i < k; i++)
		X[i] = Complex(0, 0);

	for (int i = 0; i < m; i++)
		Y[i] = Complex(b[i], 0);
	for (int i = m; i < k; i++)
		Y[i] = Complex(0, 0);

	dft(X, k, 1);
	dft(Y, k, 1);
	for (int i = 0; i < k; i++)
		X[i] = X[i] * Y[i];
	dft(X, k, -1);
	for (int i = 0; i < k; i++)
		c[i] = (ll)(X[i].r + 0.5);
}

/***********************************************/

ll a[maxn], b[maxn], c[maxn];
char s[maxn];

int main () {
	while (scanf("%s", s) == 1) {
		int n = strlen(s);
		for (int i = 0; i < n; i++)
			a[n-i-1] = s[i]-'0';

		scanf("%s", s);
		int m = strlen(s);
		for (int i = 0; i < m; i++)
			b[m-i-1] = s[i]-'0';

		int k;
		fft(a, n, b, m, c, k);
		ll s = 0;
		for (int i = 0; i < k; i++) {
			c[i] += s;
			s = c[i] / 10;
			c[i] %= 10;
		}
		while (s) {
			c[k++] = s % 10;
			s /= 10;
		}

		while (k && c[k-1] == 0) k--;

		if (k) {
			ll s = 0;
			for (int i = k-1; i >= 0; i--)
				printf("%lld", c[i]);
			printf("\n");
		} else
			printf("0\n");
	}
	return 0;
}
