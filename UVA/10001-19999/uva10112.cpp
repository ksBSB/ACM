#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;

#define N 105
struct coor{
	char name;
	int x;
	int y;
};

coor s[N];
int bo[N];
int n;

double area(int a, int b, int c){
	double t = 0.5 * ( (s[c].y - s[a].y) * (s[b].x - s[a].x) - (s[b].y - s[a].y) * (s[c].x - s[a].x));
	if (t > 0)
		return t;
	else 
		return -t;
}

int judge(int a, int b, int c, double sum){
	double t = 0;
	for (int i = 0; i < n; i++){
		if (bo[i])	continue;
		t = area(a, b, i) + area(a, c, i) + area(b, c, i);
		if (t == sum)
			return 0;
	}
	return 1;
}

int main(){

	while (cin >> n, n){

		// Init.
		memset(s, 0, sizeof(s));
		memset(bo, 0, sizeof(bo));

		for (int i = 0; i < n; i++)
			cin >> s[i].name >> s[i].x >> s[i].y;

		// Count.
		int a = 0, b = 0, c = 0;
		double sum = 0;
		for (int i = 0; i < n; i++){

			if(bo[i]) continue;

			bo[i] = 1;

			for (int j = 0; j < n; j++){

				if (bo[j]) continue;

				bo[j] = 1;

				for (int k = 0; k < n; k++){

					if (bo[k]) continue;

					bo[k] = 1;

					double t = area(i, j, k);

					if (sum < t && judge(i, j, k, t)){
						sum = t;
						a = i;
						b = j;
						c = k;
					}
					bo[k] = 0;
				}
				bo[j] = 0;
			}
			bo[i] = 0;
		}

		// Print.
		cout << s[a].name << s[b].name << s[c].name << endl;
	}
	return 0;}
