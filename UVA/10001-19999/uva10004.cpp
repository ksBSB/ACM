#include<stdio.h>
#define N 205

struct rode{
	int value;
	int dis;
}num[N];
int n, t, bo;
int get_fa(int x, int &sum){
	sum += num[x].dis;
	return x != num[x].value?get_fa(num[x].value, sum):x;
}

int main(){
	while (scanf("%d", &n), n){
		// Init.
		for (int i = 0; i < n; i++){
			num[i].value = i;
			num[i].dis = 0;
		}
		bo = 0;

		// Read.
		scanf("%d", &t);
		for (int i = 0; i < t; i++){
			int a, b, pi = 0, qi = 0;
			scanf("%d%d", &a, &b);
			int p = get_fa(a, pi), q = get_fa(b, qi);

			if(p == q){
				if (pi % 2 == qi % 2)
					bo = 1;
			}
			else{
				num[p].value = q;
				if (pi % 2 != qi % 2)
					num[p].dis = 0;
				else
					num[p].dis = 1;
			}
		}
		if (bo)
			printf("NOT BICOLORABLE.\n");
		else
			printf("BICOLORABLE.\n");
	}
	return 0;}
