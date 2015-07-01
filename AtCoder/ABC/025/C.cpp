#include<bits/stdc++.h>
using namespace std;


int B[3][3];
int C[3][3];


typedef pair<int,int> P;
map<vector<vector<int> >,P> dp;


void view(vector<vector<int> > v){
  cout << "view" << endl;
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++) cout << v[j][i];
    cout << endl;
  }
}

int result(const vector<vector<int> > v, int x,int y,int p){
  int ret = 0;  
  if( x > 0 )
    if( v[x-1][y] == p + 1 ) ret += C[x-1][y];
  if( x + 1 < 3 )
    if( v[x+1][y] == p + 1 ) ret += C[x][y];
  
  if( y > 0 )
    if( v[x][y-1] == p + 1 ) ret += B[x][y-1];
  if( y + 1 < 3 )
    if( v[x][y+1] == p + 1 ) ret += B[x][y];

  return ret;
}

P solve(vector<vector<int> > st){
  if( dp.count(st) == 1 ) return dp[st];
  P ret = P(0,0);
  int cnt = 0;
  for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
      if( st[j][i] !=  0 ) cnt++;
  if( cnt == 9 ){
    //view(st);
    return dp[st] = P(0,0);
  }
  
  for(int x=0;x<3;x++){
    for(int y=0;y<3;y++){
      if( st[x][y] == 0 ) {
        int p = cnt & 1;
        int nr = result( st, x, y , p );
        st[x][y] = p+1;
        P to = solve(st);
        to.first += nr;
        to.second *= -1;

        //view(st);
        //cout << to.first << " " << to.second << endl;

        ret = max( ret, to );
        st[x][y] = 0;
      }
    }
  }
  ret.first *= -1;
  swap(ret.first,ret.second);
  return dp[st] = ret;
}

int main(){
  for(int i=0;i<2;i++)
    for(int j=0;j<3;j++)
      cin >> B[j][i];

  for(int i=0;i<3;i++)
    for(int j=0;j<2;j++)
      cin >> C[j][i];

  vector<vector<int> > st;
  st = vector<vector<int> >(3);
  for(int i=0;i<3;i++) st[i] = vector<int>(3);
  P res = solve(st);
  cout << res.first << endl;
  cout << -res.second << endl;
}
