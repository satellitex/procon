#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


ll H,h0,m0,s0;
int main(){
  while( cin >> H >> h0 >> m0 >> s0 && (H||h0||m0||s0) ){
    ll d = 119*H - 1, n = s0 * d;
    //    cout << d << endl;
    while(1){
      ll h = 3600 * h0 * d + 60 * m0 * d + n;
      ll m = 60 * H * d * m0 + n * H;
      ll s = 60*H*n;
      ll one = 3600 * H * d;
      if( h == m && m == s ) {}
      else {
        ll x1 = (h+m)/2;
        ll x2 = (h+m+one)/2;
        if( x2 >= one ) x2 -= one;
        //if( n == 0 )        cout <<h << " "<< m << " "<< s << " " << x1 << " "<< x2 << endl;
        
        if( x1 == s || x2 == s ){
          ll gcd = __gcd(n,d);
          cout << h0 << " " << m0 << " " << n/gcd << " "<< d/gcd <<endl;
          break;
        }
      }
      n++;
      //      cout << n << " " << d*60 << endl;
      if( n == d*60 ){ n = 0; m0++; }
      if( m0 == 60 ){ m0=0; h0++; }
      if( h0 == H ) { h0 = 0; }
    }
  } 
}
