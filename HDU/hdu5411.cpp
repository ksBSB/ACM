#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 55;
const int mod = 2015;

struct Mat {
    int r, c, arr[maxn][maxn];
    Mat (int r = 0, int c = 0): r(r), c(c) { memset(arr, 0, sizeof(arr)); }

    Mat operator * (const Mat& u) {
        Mat ret(r, u.c);
        for (int k = 0; k < c; k++) {
            for (int i = 0; i < r; i++) {
                if (arr[i][k] == 0) continue;
                for (int j = 0; j < u.c; j++)
                    ret.arr[i][j] = (ret.arr[i][j] + arr[i][k] * u.arr[k][j]) % mod;
            }
        }
        return ret;
    }

	/*
    Mat operator + (const Mat& u) {
        Mat ret(r, c);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                ret.arr[i][j] = (arr[i][j] + u.arr[i][j]) % mod;
        return ret;
    }
	*/
};

int N, M;

Mat pow_mat (Mat x, int n) {

    Mat ret(N + 1, 1);
    for (int i = 0; i <= N; i++)
        ret.arr[i][0] = 1;

    while (n) {
        if (n&1)
            ret = x * ret;
        x = x * x;
        n >>= 1;
    }
    return ret;
}

void put (Mat u) {
    for (int i = 0; i < u.r; i++) {
        printf("%d", u.arr[i][0]);
        for (int j = 1; j < u.c; j++)
            printf(" %d", u.arr[i][j]);
        printf("\n");
    }
}

int main () {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d", &N, &M);
        int n, x;
        Mat T(N + 1, N + 1);
        for (int i = 0; i < N; i++) {
            scanf("%d", &n);
            for (int j = 0; j < n; j++) {
                scanf("%d", &x);
                T.arr[x-1][i] = 1;
            }
			T.arr[N][i] = 1;
        }
		T.arr[N][N] = 1;

        Mat ans = pow_mat(T, M-1);
		//put(ans);
        int ret = 0;
		for (int i = 0; i <= N; i++) {
			ret = (ret + ans.arr[i][0]) % mod;
		}
		printf("%d\n", ret);
	}
	return 0;
}
