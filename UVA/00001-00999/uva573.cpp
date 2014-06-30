#include<stdio.h>

int main(){
	double high, up, down, f;
	while (scanf("%lf%lf%lf%lf", &high, &up, &down, &f), high && up && down && f){
		f = up * f / 100.0;
		double dis = 0;
		for (int i = 1; ; i++){
			if (up > 0)
				dis += up;

			if (dis > high){
				printf("success on day %d\n", i);
				break;
			}	

			dis -= down;
			up -= f;
			if (dis < 0){
				printf("failure on day %d\n", i);
				break;
			}
		}
	}
	return 0;}
