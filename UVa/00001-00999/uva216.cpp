#include<iostream>
#include<string.h>
#include<math.h>
#include<stdio.h>
#include<algorithm>
using namespace std;

#define M 10

struct point{
	int x;
	int y;
};

double count(point a, point b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main()
{
	int n;
	int sign_no[M];  // 记录序号。
	double sign_dis[M]; //记录路程。
	int no[M];
	double dis[M];
	int t = 1;

	while ( cin >> n, n)
	{
		// Init.
		memset (sign_no, 0, sizeof(sign_no));
		memset (sign_dis, 0, sizeof(sign_dis));
		for (int i = 0; i < n; i++)
			no[i] = i;
		point p[M];
		double max_dis = 0;

		// Read.
		for (int i = 0; i < n; i++)
			cin >> p[i].x >> p[i].y;

		// Count.
		do{
			double sum = 0;

			for (int i = 0; i < n - 1; i++)
			{
				dis[i] = count(p[ no[i] ], p[ no[i + 1] ]) + 16;
				sum += dis[i];
			}

			if(max_dis == 0 || max_dis > sum)
			{
				for (int i = 0; i < n; i++)
					sign_no[i] = no[i];
				for (int i = 0; i < n - 1; i++)
					sign_dis[i] = dis[i];

				max_dis = sum;
			}
		}while(next_permutation(no, no + n));

		// Print.
		cout << "**********************************************************" << endl;
		cout << "Network #" << t++ << endl;
		for (int i = 0; i < n - 1; i++)
		{	cout << "Cable requirement to connect (" << p[sign_no[i]].x << "," << p[sign_no[i]].y << ") to (" << p[sign_no[i + 1]].x << "," << p[sign_no[i + 1]].y << ") is ";
			printf("%.2f feet.\n", sign_dis[i]);
		}
		printf("Number of feet of cable required is %.2f.\n", max_dis);
	}
	return 0;
}
