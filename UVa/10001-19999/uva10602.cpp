#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
bool cmp(const string &a, const string &b)  { return a < b;}
const int N = 105;
string tmp[N];

int main() {
    int cas, n, cnt, end;
    cin >> cas;
    while (cas--) {
  cin >> n;

  for (int i = 0; i < n; i++)
      cin >> tmp[i];

  sort(tmp, tmp + n);
  cnt = tmp[0].size();

  for(int i = 1 ; i < n ; i++){ 
      if(tmp[i][0] != tmp[i - 1][0]){  
    cnt += tmp[i].size();  
    continue;  
      }  
      int j;
      for(j = 0; j < tmp[i - 1].size(); j++){  
    if(tmp[i - 1][j] != tmp[i][j]) {
        break;  
    }
      }  
      cnt += tmp[i].size() - j;  
  } 
  cout << cnt << endl;
  for (int i = 0; i < n; i++)
      cout << tmp[i] << endl;
    }
    return 0;
}
