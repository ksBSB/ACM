#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
using namespace std;
const int N = 100;
int main() {
    char str[N], aid[N], ans[N];
    map<string, string> vec;
    while (gets(str) && str[0] != '\0') {
    sscanf(str, "%s%s", ans, aid);
    vec[aid] = ans;
    }
    while(gets(aid)) {
    if (vec.find(aid) == vec.end())
        cout << "eh" << endl;
    else
        cout << vec[aid] << endl;
    }
    return 0;    
}
