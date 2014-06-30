#include<stdio.h>
#include<string.h>

int main()
{
	int h,m;

	while (scanf("%d:%d", &h, &m), h || m)
	{
		double hour = 30 * ( h % 12 ) + 0.5 * m;
		double min = 6 * m;
		double t = hour - min;
		if ( t < 0)
			t = -t;
		if ( t > 180)
			t = 360 - t;
		printf("%.3f\n", t);
	}
	return 0;
}
