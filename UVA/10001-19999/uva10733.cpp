#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
ll n;

ll solve (int k) {
	ll ret = 1;
	for (int i  = 0; i < k; i++)
		ret *= n;
	return ret;
}

ll still () {
	return solve(6);
}

ll rot_point () {
	return 2 * 4 * solve(2);
}

ll rot_edge () {
	return 6 * solve(3);
}

ll rot_plane () {
	return 3 * 2 * solve(3) + 3 * solve(4);
}

ll polya () {
	return still() + rot_point() + rot_edge() + rot_plane();;
}

int main () {
	while (scanf("%lld", &n) == 1 && n) {
		printf("%lld\n", polya() / 24);
	}
	return 0;
}
