#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e6 + 5;
const int maxm = 1e5 + 5 * 7;

int N, M, od[maxn], nw[maxn], P[maxn<<1];
vector<int> L[maxm], R[maxm];

void init () {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &od[i], &nw[i]);
        P[i<<1] = od[i];
        P[(i<<1)|1] = nw[i];
    }

    sort(P, P + 2 * N);
    M = unique(P, P + 2 * N) - P;
    for (int i = 0; i < M; i++) {
        L[i].clear(); R[i].clear();
    }
	while(M > maxm);

    for (int i = 0; i < N; i++) {
        od[i] = lower_bound(P, P + M, od[i]) - P;
        nw[i] = lower_bound(P, P + M, nw[i]) - P;
        L[od[i]].push_back(nw[i]);
        R[nw[i]].push_back(od[i]);
    }

    for (int i = 0; i < M; i++) {
        sort(L[i].begin(), L[i].end());
        od[i] = unique(L[i].begin(), L[i].end()) - L[i].begin();
        sort(R[i].begin(), R[i].end());
        nw[i] = unique(R[i].begin(), R[i].end()) - R[i].begin();
    }
}

int main () {
    int cas;
    scanf("%d", &cas);
    for (int kcas = 1; kcas <= cas; kcas++) {
        init();
        int a = 0, b = 0, c = 0;

        for (int i = 0; i < M; i++) {
            if (od[i] == 0) continue;

            bool flag = true;
            for (int j = 0; j < od[i] && flag; j++)
                flag = (nw[L[i][j]] == 1 && R[L[i][j]][0] == i);

            if (flag) {
                if (od[i] == 1) c++;
                else a++;
                for (int j = 0; j < od[i]; j++)
                    nw[L[i][j]] = 0;
                od[i] = 0;
            }
        }

        for (int i = 0; i < M; i++) {
            if (nw[i] == 0) continue;

            bool flag = true;
            for (int j = 0; j < nw[i] && flag; j++)
                flag = (od[R[i][j]] == 1 && L[R[i][j]][0] == i);

            if (flag) {
				if (nw[i] == 1) c++;
				else b++;
                for (int j = 0; j < nw[i]; j++)
                    od[R[i][j]] = 0;
                nw[i] = 0;
            }
        }

        printf("Case #%d: %d %d %d\n", kcas, a, b, c);
    }
    return 0;
}
