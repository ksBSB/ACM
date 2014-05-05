#include <cstdio>
#include <cstring>

int main () {
	int n, m, Max, Min, t;
	bool fMax = false, fMin = false, flag = false;

	scanf("%d%d%d%d", &n, &m, &Min, &Max);
	for (int i = 0; i < m; i++) {
		scanf("%d", &t);
		if (t == Max)
			fMax = true;
		if (t == Min)
			fMin = true;

		if (t > Max || t < Min)
			flag = true;
	}

	if (fMax == false && fMin == false) {
		if (n - m < 2)
			flag = true;
	} else if (fMax == false || fMin == false) {
		if (n - m < 1)
			flag = true;
	}

	printf("%s\n", flag ? "Incorrect" : "Correct");
	return 0;
}
