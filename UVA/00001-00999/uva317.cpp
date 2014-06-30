#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 5
int n, Max, num[N][N];
const int yes[N] = {5, 6, 8};
const int no[N] = {5, 7, 7}; 

int main(){
    scanf("%d", &n);
    for (int t = 1; t <= n; t++){
    // Init.
    memset(num, 0, sizeof(num));
    Max = 0;

    // Read.
    for (int i = 1; i <= 3; i++){
        for (int j = 0; j < 3; j++)
        scanf("%d", &num[i][j]);
        sort(num[i], num[i] + 3);
    }
    
    // Handle.
    for (int k = 0; k <= 3; k++){
        int sum = 0;
        for (int i = 1; i <= 3; i++){
        if (i == k){
            for (int j = 0; j < 3; j++)
            sum += num[i][j] * yes[j];
        }
        else{
            for (int j = 0; j < 3; j++)
            sum += num[i][j] * no[j];
        }
        }
        if (sum > Max)
        Max = sum;
    }

    printf("Test #%d\n%d\n\n", t, Max);
    }
    return 0;}
