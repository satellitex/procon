#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N;

int main(){
  cin>> N;
  ll st=0,ed = 2000000000LL;
  bool f = false;
  while( st <= ed ){
    ll h = (st + ed)/2;
    ll num = h * (h+1)/2;
    if( N < num ){
      ed = h - 1;
    } else if ( num < N )
      st = h + 1;
    else {
      f = true;
      cout << h << endl; break;
    }      
  }
  if( !f ) cout << -1 << endl;
}
