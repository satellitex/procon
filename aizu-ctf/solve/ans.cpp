#include<bits/stdc++.h>
using namespace std;

#define MOD (1000000007)
typedef long long ll;

int N,M,K,Q;
int dp[10001][10001];

void add(int &a,int b){
  if( b < 0 )  b += MOD;
  a = (a+b)%MOD;
}

int main(){
  scanf("%d%d%d%d",&N,&M,&K,&Q);

  for(int i=0;i<N;i++) dp[1][i]=(i/K+1)%2;
  for(int i=1;i<M;i++){
    int ar[20]={};
    int sum = 0;
    for(int j=N-K+1;j<N;j++) add(sum,dp[i][j]);
    for(int j=0;j<N;j++){
      add(sum,dp[i][j]);
      add(ar[j%(2*K)],sum);
      add(sum,-dp[i][(j+N-K+1)%N]);
    }
    for(int j=0;j<N;j++)
      add(dp[i+1][j],ar[j%(2*K)]);
  }

  ll res = 0;
  for(int i=0;i<Q;i++){
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);

    /*--------------- debug output ----------------------
    if( a==c && b==0 ) puts("1");
    else printf("%d\n",dp[b][(c+N-a)%N]);
    -----------------------------------------------------*/

    /*-------------- FLAG calc --------------------------*/
    //    if( a==c && b==0 ) res+=1LL;
    //else res+=(ll)dp[b][(c+N-a)%N]*(ll)dp[b][(c+N-a)%N];
    
    res += (a==c&&b==0)?1LL:((ll)dp[b][(c+N-a)%N]*(ll)dp[b][(c+N-a)%N]);
    res %= MOD;
    /*---------------------------------------------------*/
  }

  printf("AIZU_{%d}\n",res);

}
