#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

struct Point {
	int x, y;
	Point(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}
	bool operator < (const Point& a) const {
		return x < a.x || (x == a.x && y < a.y);
	}
};

multiset<Point> vec;
multiset<Point>::iterator iter;

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		printf("Case #%d:\n", kcas);

		int n, x, y;
		vec.clear();
		scanf("%d", &n);

		while (n--) {
			scanf("%d%d", &x, &y);
			Point p(x, y);
			iter = vec.lower_bound(p);

			if (iter == vec.begin() || (--iter)->y > y) {
				vec.insert(p);
				iter = vec.upper_bound(p);
				while (iter != vec.end() && iter->y >= y)
					vec.erase(iter++);
			}
			printf("%lu\n", vec.size());
		}

		if (kcas < cas)
			printf("\n");
	}
	return 0;
}
