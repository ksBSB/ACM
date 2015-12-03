#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1e4 + 5;
const double inf = 1e20;
const double pi = 4 * atan(1.0);
const double eps = 1e-8;

int N;
double L, R, X[maxn], Y[maxn], A[maxn];

double getDistance(double x, double y) { return sqrt(x * x + y * y); }

void init () {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%lf%lf", &X[i], &Y[i]);

    double s = 0;
    L = 0, R = inf;
    for (int i = 0; i < N; i++) {
        int v = (i + 1) % N;
        s = getDistance(X[i]-X[v], Y[i]-Y[v]) - s;
        if (i&1) L = max(L, -s);
        else R = min(R, s);
    }

    /*
    s = 0;
    for (int i = 1; i <= N; i++) {
        int u = N - i;
        int v = (N - i + 1) % N;
        s = getDistance(X[u]-X[v], Y[u]-Y[v]) - s;
        if (i&1) R = min(R, s);
        else L = max(L, -s);
    }
    */
}

double get(double m) {
    double ret = m * m;
    A[0] = m;
    for (int i = 1; i < N; i++) {
        double s = getDistance(X[i] - X[i-1], Y[i] - Y[i-1]);
        m = s - m;
        ret += m * m;
        A[i] = m;
    }
    return ret;
}

double solve () {
    while (R - L > eps) {
        double l = (2 * L + R) / 3;
        double r = (L + 2 * R) / 3;
        if (get(l) >= get(r)) L = l;
        else R = r;
    }
    return L;
}

int main () {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        init();
        double ans = 0;
        for (int i = 0; i < N; i++) {
            int v = (i + 1) % N;
            ans = getDistance(X[i] - X[v], Y[i] - Y[v]) - ans;
        }

        if ((L > R) || (N % 2 == 0 && fabs(ans) > eps)) printf("IMPOSSIBLE\n");
        else {

            if (N&1) ans /= 2;
            else ans = solve();
            printf("%.2lf\n", get(ans) * pi);
            for (int i = 0; i < N; i++) printf("%.2lf\n", A[i]);
        }
    }
    return 0;
}