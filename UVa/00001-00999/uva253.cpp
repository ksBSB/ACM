#include<stdio.h>
#include<map>
using namespace std;

#define N 15
#define M 5

int main(){
	char sen[N];
	while (scanf("%s", sen) != EOF){
		map<char , int> s[5], t[5];
		int cnt = 0;

		for (int i = 0; i < 3; i++){
			s[i][sen[i]]++;
			s[i][sen[M - i]]++;
			t[i][sen[i + 6]]++;
			t[i][sen[11 - i]]++;
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (s[i]['r'] == t[j]['r'] && s[i]['g'] == t[j]['g'] && s[i]['b'] == t[j]['b']){
					t[j]['r'] = t[j]['g'] = t[j]['b'] = 0;
					cnt++;
					break;
				}
		if (cnt == 3)
			printf("TRUE\n");
		else 
			printf("FALSE\n");
	}
	return 0;}
