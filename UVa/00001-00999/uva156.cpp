#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

#define N 1005
#define M 25

struct word{
	char before[M];
	char change[M];
	int bo;
};

word s[N];
char str[M];

void swap(word &a){
	int l = strlen(a.before);
	for (int i = 0; i <= l; i++){
		if (a.before[i] >= 'A' && a.before[i] <= 'Z')
			a.change[i] = a.before[i] + 32;
		else
			a.change[i] = a.before[i];
	}
	sort(a.change, a.change + l);
}

int judge(int n){
	for (int i = 0; i < n; i++){
		if (strcmp(s[i].change, s[n].change) == 0){
			s[i].bo++;
			return 0;
		}
	}
	s[n].bo = 0;
	return 1;
}

int cmp(const word &a, const word &b){
	return strcmp(a.before, b.before) < 0;
}

int main(){
	int n = 0;

	// Read.
	do{
		memset(str, 0, sizeof(str));
		scanf("%s", s[n].before);
		swap(s[n]);

		if (strcmp(s[n].before, "#") == 0)
			break;

		s[n].bo = 0;
		if(judge(n))
			n++;
	}while (1);

	sort(s, s + n, cmp);
	
	// Printf.
	for (int i = 0; i < n; i++){
		if (s[i].bo)
			continue;
		printf("%s\n", s[i].before);
	}
return 0;}	
