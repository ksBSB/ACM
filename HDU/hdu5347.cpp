#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

double F[100];

int main () {
	F[1] = 1312;
	F[2] = 2372;
	F[3] = 520;
	F[4] = 899;
	F[5] = 800;
	F[6] = 1086;
	F[7] = 1402;
	F[8] = 1313;
	F[9] = 1681;
	F[10] = 2080;
	F[11] = 495;
	F[12] = 737;
	F[13] = 577;
	F[14] = 786;
	F[15] = 1011;
	F[16] = 999;
	F[17] = 1251;
	F[18] = 1520;
	F[35] = 1139;
	F[36] = 1350;
	F[53] = 1008;
	F[54] = 1170;
	F[85] = 890;
	F[86] = 1037;
	int u, v;
	while (scanf("%d%d", &u, &v) == 2) {
		printf("%s BIGGER\n",F[u] > F[v] ? "FIRST" : "SECOND");
	}
}
