#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
int N,Q;
ll p[100001];
ll x[100001];
ll tmp[100001];
int K[100001];
ll R[43][100003];
ll T[43][100003];

#define MOD (1000000007)


ll lcm(ll a,ll b){
  return a / __gcd(a,b) * b;
}

struct seg{
  ll d[(1<<18)];
  int n;
  void init(int _n){
    n = 1; while( n < _n ) n*=2;
    for(int i=0;i<2*n;i++) d[i] = 1LL;
  }
  void set(int id,ll k){
    id+=n-1;
    d[id] = k;
    while( id > 0 ){
      id = (id-1)/2;
      d[id] = lcm(d[2*id+1],d[2*id+2]);
    }
  }
  ll query(int a,int b,int k,int l,int r){    
    if( b <= l || r <= a ) return 1LL;
    else if( a <= l && r <= b ) return d[k];
    else {
      ll vl = query( a, b, 2*k + 1, l, (l+r)/2 );
      ll vr = query( a, b, 2*k + 2, (l+r)/2, r );
      //       cout << a << " " << b << " "<< k << " " << l << " " << r<< " " << vl << " "<< vr << " " << lcm(vl,vr) << endl;
      return lcm(vl,vr);
    }
  }
  ll query(int a,int b){
    return query(a,b,0,0,n);
  }
};

seg S;


void view(){
  for(int k=0;k<=5;k++){
    for(int i=0;i<=N;i++)
      cout << R[k][i] << " ";
    cout << endl;
  }

  for(int k=0;k<=5;k++){
    for(int i=0;i<=N;i++)
      cout << T[k][i] << " ";
    cout << endl;
  }

}

int main(){
  cin >> N >> Q;
  S.init(N);
  for(int i=0;i<N;i++) {
    cin >> p[i]; p[i]--;
    x[i] = i;
  }
  memset(K,-1,sizeof(K));
  for(int k=1;k<=41;k++){
    for(int i=0;i<N;i++) tmp[i] = p[x[i]];
    for(int i=0;i<N;i++) x[i] = tmp[i];
    for(int i=0;i<N;i++) if( x[i] == i && K[i] < 0 ) K[i] = k;
    for(int i=0;i<N;i++) R[k][i+1] = (R[k][i] + x[i]+1LL)%MOD;
  }

  for(int k=0;k<=41;k++)
    for(int i=0;i<=N;i++)
      R[k+1][i] = (R[k][i] + R[k+1][i])%MOD;

  for(int k=1;k<=40;k++){
    for(int i=0;i<=N;i++){
      ll sum = 0;
      if( K[i] == k )
        sum = R[k][i+1]-R[k][i]+MOD; sum%=MOD;      
      T[k][i+1] = (T[k][i] + sum)%MOD;
    }
  }
  
  //  view();
  
  for(int i=0;i<N;i++) S.set(i,K[i]);  

  for(int i=0;i<Q;i++){
    int l,r;
    cin >> l >> r; --l; --r;
    if( l > r ) swap(l,r);
    ///    cout << "[ " << l << " , " << r+1 << " ) " << endl;
    ll num = S.query(l,r+1);

    ll res = 0;
    for(int k=1;k<=40;k++){
      ll ks = num/(ll)k;
      ks %= MOD;
      if( num % (ll)k ) continue;
      //cout << num << " " << ks << endl;
      //cout << T[k][r+1] - T[k][l] << endl;
      res += (ks * (T[k][r+1] - T[k][l] + MOD)%MOD ) %MOD;
      res %= MOD;
      //      ll rs = num%(ll)k;
      //res += rsum + (R[rs][r+1]-R[rs][l]+MOD)%MOD;
      //res %= MOD;
    }
    cout << res << endl;
  }
}
