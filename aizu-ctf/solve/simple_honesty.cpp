#include<bits/stdc++.h>
using namespace std;

#define MOD (1000000007)

int N,M,K,Q;
int dp[111][111][111];

void add(int &a,int b){
  if( b < 0 )  b += MOD;
  a = (a+b)%MOD;
}


int main(){
  cin >> N >> M >> K >> Q;
  for(int i=0;i<N;i++) dp[i][0][i] = 1;
  for(int a=0;a<N;a++){
    for(int day=0;day<M;day++){
      for(int b=0;b<N;b++){
	if( dp[a][day][b] == 0 ) continue;
	for(int k=0;k<N;k++){
	  if( ((k/K)&1) ) continue;
	  add(dp[a][day+1][(b+k)%N],dp[a][day][b]);
	}
      }
    }
  }
  for(int i=0;i<Q;i++){
    int a,b,c; cin >> a >> b >> c;
    cout << dp[a][b][c] << endl;
  }

}
