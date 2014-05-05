#include<string.h>
#include<algorithm>
#include<math.h>
#include<stdio.h>
using namespace std;

#define N 105


struct dis{
  double lenth;
  int a;
  int b;
};

struct coor{
  double x;
  double y;
};

int cmp(const dis &a, const dis &b)
{
  return a.lenth < b.lenth;
}

int num[N];

int get_fa(int x)
{
  return num[x] != x? get_fa(num[x]):x;
}

double count_dis(coor a, coor b)
{
  return sqrt( pow( a.x - b.x, 2) + pow (a.y - b.y, 2));
}

int main()
{
  int k;

  scanf("%d", &k);

  while (k--)
  {
    int n;
    scanf("%d", &n);
    coor t[N];

    // Init.
    for (int i = 0; i < n; i++)
      num[i] = i;
    int cnt = 0;
    double sum = 0;
    dis l[N * N];

    // Read.
    for (int i = 0; i < n; i++)
      scanf("%lf%lf", &t[i].x, &t[i].y);

    // Count.
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
      {
        l[cnt].lenth= count_dis(t[i], t[j]);
        l[cnt].a = i;
        l[cnt].b = j;
        cnt++;
      }


    sort(l, l + cnt, cmp);

    for (int i = 0; i < cnt; i++)
    {
      if (get_fa(l[i].a) == get_fa(l[i].b))
        continue;
      sum += l[i].lenth;
      num[get_fa(l[i].a)] = get_fa(l[i].b);
    }
 
    printf("%.2f\n", sum);

    if(k)
      printf("\n");

  }
  return 0;}
