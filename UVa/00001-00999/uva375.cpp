#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;

int main(){
	double b, h;
	int t;
	const double pi = 4 * atan(1.0);
	cin >> t;

	while (t--){
		cin >> b >> h;
		double sum = 0;

		while (1){

			double leap = atan(h /(b / 2));
			double r = tan(leap / 2) * b / 2;
			if (r < 0.000001)
				break;

			sum += 2 * pi * r;
			b = b * (h - 2 * r) / h;
			h = h - 2 * r;
		}
		printf("%13.6lf\n", sum);
		if (t) 
			cout << endl;
	}
	return 0;}
