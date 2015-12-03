#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;

/* 
 * S(i) 表示第i件物品到第N件物品的价值和
 * win(i, x, y) 表示当前可以买的物品为i，先手剩x元，后手剩y元时，先手是否必胜
 * x + y = A + B - S(1) + S(i);
 * 所以win(i, x, y) 可以化简为win(i, x)
 * 并且win(i, x) ==> win(i, x+1)
 *
 * 记m(i)为min{x: win(i, x)}，则有!win(i, x) <==> x < min(i)
 * D = A + B - S(1) + S(i)
 *
 * m(i) = min{x:x >= S(i) - S(j) && j > i && !win(j, D-x)}
 *		= min{x:x >= S(i) - S(j) && j > i && D - x <= m(j) - 1}
 *		= min{x: max(S(i)-S(j), A + B - S(1) + S(i) - m(j) + 1) && j > i}
 *		= S(i) + min{ max(-S(j), A + B - S(1) - m(j) + 1) | j > i}
 *
 *	最后只要判断A是否大于m(1)即可
 */

int N, A, B;
ll S[maxn];

int main () {
	while (scanf("%d%d%d", &N, &A, &B) == 3) {
		for (int i = 0; i < N; i++) scanf("%lld", &S[i]);
		ll pre = S[N] = 0, now;
		for (int i = N-1; i >= 0; i--) S[i] += S[i+1];
		for (int i = N-1; i >= 0; i--) {
			now = pre + S[i];
			pre = min(pre, max(-S[i], (ll)A + B - S[0] + 1 - now));
		}
		printf("%s\n", A >= now ? "ALICE" : "BOB");
	}
	return 0;
}
