#include<stdio.h>
#include<string.h>
#define N 1005
int num[30];
int get_fa(int x){
	return num[x] != x?get_fa(num[x]):x;}

int abt(int k){
	return k > 0?k:-k;}

int main(){
	int n, t, bo;
	int f[30], e[30];
	char word[N];
	scanf("%d" ,&t);
	while (t--){
		// Init.
		memset(f, 0, sizeof(f));
		memset(e, 0, sizeof(e));
		bo = 0;
		for (int i = 0; i < 26; i++)
			num[i] = i;

		// Read.
		scanf("%d%*c", &n);
		for (int i = 0; i < n; i++){
			gets(word);
			int a = word[0] - 'a';
			int b = word[strlen(word) - 1] - 'a';
			f[a]++;
			e[b]++;
			num[get_fa(a)] = get_fa(b);
		}

		// Find.
		int god;
		for (int i = 0; i < 26; i++)
			if ((f[i] || e[i]) && i == get_fa(i)){
				god = i;
				break;
			}

		for (int i = 0; i < 26; i++){
			bo += abt(f[i] - e[i]);
			if ((e[i] || f[i]) && god != get_fa(i))
				bo +=10;
		}
		if (bo > 2)
			printf("The door cannot be opened.\n");
		else
			printf("Ordering is possible.\n");
	}
	return 0;}
