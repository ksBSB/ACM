#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define MAX 2005
#define N 205
#define M 80

struct country{
	char city[M];
	char women[N][M];
	int cnt;
	country(){
		memset(city, 0, sizeof(city));
		memset(women, 0, sizeof(women));
		cnt = 0;
	}
};

int cmp(const country &a, const country &b){
	return strcmp(a.city, b.city) < 0;
}

country man[MAX];
int main(){
	int n, leap = 0, bo;
	char str[N], name[M];

	// Read.
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		bo = 0;
		scanf("%s", man[leap].city);
		gets(man[leap].women[man[leap].cnt++]);

		for (int j = 0; j < leap; j++){
			if (strcmp(man[leap].city, man[j].city) == 0){
				bo = 1;
				strcpy(man[j].women[man[j].cnt++], man[leap].women[man[leap].cnt - 1]);
				break;
			}
		}
		if (bo)
			man[leap].cnt = 0;
		else
			leap++;
	}

	sort(man, man + leap, cmp);	

	for (int i = 0; i < leap; i++)
		printf("%s %d\n", man[i].city, man[i].cnt);
	return 0;
}
