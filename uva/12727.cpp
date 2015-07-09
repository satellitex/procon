#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct state{
  int l,r,c;
  state(){}
  state(int l,int r,int c):l(l),r(r),c(c){}
  bool operator<(const state& s) const{
    return l == s.l ? r < s.r : l < s.l;
  }
};
int T,N,M,K;
  
bool dp[33][33][301];
bool ok[301];

ll get(int x){
  ll res = 0;
  for(int i=min(x,300);i>-1;i--){
    if( ok[i] ){
      res += (ll)(x-i+1)*(ll)i;
      x = i-1;
    }
  }
  return res;
}

int main(){
  cin >> T;
  for(int ttt=1;ttt<=T;ttt++){
    cin >> N >> M >> K;
    state S[33];

    int sum = 0;
    S[0].l = S[0].r = S[0].c = 0;
    for(int i=1;i<=M;i++){
      cin >> S[i].l >> S[i].r >> S[i].c;
      sum += S[i].c;
    }
    assert( sum <= 300 );

    sort(S,S+M+1);

    memset(dp,0,sizeof(dp));
    memset(ok,0,sizeof(ok));

    dp[0][0][0] = true;
    vector<int> nex[33][33];

    for(int k=0;k<=M;k++)  
      for(int i=k;i<=M;i++)
        for(int j=i+1;j<=M;j++)
          if( ( (S[k].r+1 < S[j].l && S[j].l < S[i].r + 1) || S[j].l == S[i].r+1 ) && S[i].r < S[j].r  ) 
            nex[k][i].push_back(j);

            
    for(int i=0;i<=M;i++){
      for(int j=0;j<=M;j++){
        for(int k=0;k<=300;k++){
          if( !dp[i][j][k] ) continue;
          //          cout << i  << " "<< j << " " << k << " " << dp[i][j][k] << endl;
          for(int l=0;l<(int)nex[j][i].size();l++)
            dp[nex[j][i][l]][i][k+S[nex[j][i][l]].c] = true;        
        if( S[i].r == N ) ok[k] = true;
        }
      }
    }

    ll res = 0;
    for(int i=0;i<K;i++){
      int x,y; cin >> x >> y;
      res += get(y)-get(x-1);
    }
    cout << "Case #" << ttt  << ": ";
    cout << res << endl;
  }
}
