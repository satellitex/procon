#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

map<ll,int> prime_factorize(ll a){
  map<ll,int> res;
  for(ll p=2; p*p<=a; p++){
    if(a % p == 0) {
      int cnt = 0;
      do{
        a /= p;
        cnt++;
      }while(a % p == 0);
      res[p] = cnt;
    }
  }
  if(a > 1) res[a] = 1;
  return res;
}

int main(){
}
