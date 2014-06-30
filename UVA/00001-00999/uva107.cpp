#include<stdio.h>
#include<math.h>
using namespace std;

int main(){
	int H, M;
	while (scanf("%d%d", &H, &M), H && M){
		double N = 1;
		while (fabs(log(N) / log(N + 1) - log(M) / log(H) )> 1e-10)
			N++;
		double k = int(log(H) / log(N + 1) + 0.5);
		if ((int)N == 1)
			printf("%d ", (int)k);
		else
			printf("%d ", int(0.5 + (1 - pow(N, k)) / (1 - N)));
		printf("%d\n", int(0.5 + (1 - pow(N / (N + 1), k + 1)) * (N + 1) * H));
	}
	return 0;}
