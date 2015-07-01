#include<bits/stdc++.h>
using namespace std;
int M,N;

const double EPS = 1E-10;

double A[18][18];
double R[18][18][18];
double dp[(1<<16)][18];

double solve(int st,int id){
  if( dp[st][id] > -EPS ) return dp[st][id];
  double ret = 0.0;
  if( id == N ) return dp[st][id] = 1.0;
  for(int i=0;i<M;i++){
    if( st & (1<<i) ) continue;
    double at=0.0;
    for(int j=id;j<=N;j++){
      at += solve(st|(1<<i),j)*R[i][id][j];
    }
    ret = max( ret, at );
  }
  return dp[st][id] = ret;
}

int main(){
  fill(dp[0],dp[(1<<16)],-1.0);
  
  cin >> M >> N;
  for(int i=0;i<M;i++)
    for(int j=0;j<N;j++) cin >> A[i][j];
  for(int i=0;i<M;i++){
    for(int j=0;j<N;j++){
      R[i][j][j] = (1.0-A[i][j]);
      double r = A[i][j];
      for(int k=j+1;k<N;k++){
        R[i][j][k] = r * (1.0-A[i][k]);
        r *= A[i][k];
      }
      R[i][j][N] = r;
    }
  }
  printf("%.10lf\n",solve(0,0));  
}
