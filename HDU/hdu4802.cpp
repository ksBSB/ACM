#include <cstdio>
#include <cstring>

double cal (char ch) {
	switch (ch) {
		case 'A':
			return 4;
		case 'B':
			return 3;
		case 'C':
			return 2;
		case 'D':
			return 1.3;
		case 'F':
			return 0;
	}
	return 0;
}

int main () {
	int n;
	while (scanf("%d", &n) == 1) {
		int cnt = 0;
		double sum = 0;

		int a;
		char str[10];
		for (int i = 0; i < n; i++) {
			scanf("%d%s", &a, str);
			if (str[0] == 'P' || str[0] == 'N')
				continue;

			cnt += a;
			double tmp = cal(str[0]);

			if (str[1] == '+')
				tmp += 0.3;
			else if (str[1] == '-')
				tmp -= 0.3;
			sum += tmp * a;
		}

		if (cnt)
			sum /= cnt;
		printf("%.2lf\n", sum);
	}
	return 0;
}
