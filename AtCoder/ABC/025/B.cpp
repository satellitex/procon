#include<bits/stdc++.h>
using namespace std;
int N,A,B;

int main()
{
  int res = 0;
  cin >> N >> A >> B;
  for(int i=0;i<N;i++){
    string s;
    int d;
    cin>> s >> d;
    d = min( d, B );
    d = max( d, A );
    if( s == "East" ) res += d;
    else res -= d;
  }
  if( res > 0 ) cout << "East " << res << endl;
  else if( res < 0 )cout << "West " << -res << endl;
  else cout << 0 << endl;
}
