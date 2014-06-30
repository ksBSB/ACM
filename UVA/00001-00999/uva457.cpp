#include <stdio.h>
#include <string.h>
const int N = 42;
const char sign[] = " .xW";
int DNA[10], tmp[N], rec[N];

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
	// Init
	memset(DNA, 0, sizeof(DNA));
	memset(tmp, 0, sizeof(tmp));
	memset(rec, 0, sizeof(rec));
	tmp[20] = rec[20] = 1;

	for (int i = 0; i < 10; i++)
	    scanf("%d", &DNA[i]);

	for (int data = 1; data <= 50; data++) {
	    for (int i = 1; i <= 40; i++)
		printf("%c", sign[tmp[i]]);
	    printf("\n");

	    for (int i = 1; i <= 40; i++) 
		rec[i] = DNA[tmp[i - 1] + tmp[i] + tmp[i + 1]];
	    memcpy(tmp, rec, sizeof(rec));
	}
	if (cas)
	    printf("\n");
    }
    return 0;
}
