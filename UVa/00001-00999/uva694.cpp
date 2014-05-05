#include <stdio.h>
int main() {
    long long cur, max, cnt, cas = 1, rec;
    while (scanf("%lld%lld", &cur, &max)) {
	if (cur < 0 || max < 0)	break;
	cnt = 1;
	rec = cur;
	while (cur != 1) {
	    if (cur % 2)
		cur = 3 * cur + 1;
	    else
		cur = cur / 2;
	    if (cur > max)	break;
	    cnt++;
	}
	printf("Case %lld: A = %lld, limit = %lld, number of terms = %lld\n", cas++, rec, max, cnt);
    }
    return 0;
}
