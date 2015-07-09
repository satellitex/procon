#include<bits/stdc++.h>
using namespace std;
int N;
int st[10001];
int dp[(1<<12)];
int main(){
  cin >> N;
  for(int i=0;i<N;i++){
    string S;
    cin >> S;
    st[i] = 0;
    for(int j=0;j<(int)S.size();j++)
      if( S[j] == 'o' ) st[i] |= (1<<j);
  }
  dp[0] = 0;
  int res = 0;
  for(int i=0;i<(1<<12);i++){
    for(int j=0;j<N;j++){
      if( (i | st[j]) == i ) continue;
      dp[i|st[j]] = max( dp[i|st[j]], dp[i] + 1 );
    }
    res = max( res, dp[i] );
  }

  cout << res << endl;
}
