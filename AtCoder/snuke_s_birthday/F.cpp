#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;

int L,N,K;
int X[100003];
int C[100003];
int cnt;
bool check(double val){
  int k = K;
  cnt = 0;
  for(int i=0;i<N;i++){
    double ky = (double)(X[i+1]-X[i]);
    int st = 0, ed = K;
    int ret=K;
    while( st <= ed ){
      int h = (st + ed)/2;
      double r = ky / (double)(h+1) / 2.0;
      if( r < val - EPS ){
        ret = min(ret,h);
        ed = h - 1;
      } else 
        st = h + 1;
    }
    C[i] = ret;
    k -= ret;
    cnt += ret;
    if( k < 0 ) return false;
  }
  return true;
}

bool eq(double a,double b){
  return abs(a-b)<1E-7;
}

int main(){
  cin >> L >> N >> K;
  for(int i=0;i<N;i++) cin >> X[i];
  X[N] = L;
  double st = 0.0, ed = (double)L;
  while( abs(ed-st) > EPS ){
    double h = (st + ed)/2.0;
    if( check(h) ) ed = h;
    else st = h;
  }
  assert( check( ed ) );
  bool f = false;
  priority_queue<double> q;
  for(int i=0;i<N;i++){
    double ky = (X[i+1]-X[i]);
    double rs = ky / (double)(C[i]+1) / 2.0;
    //    cout << ed << " " << rs << " "<< f << " "<< C[i] << endl;
    if( eq(ed,rs) ){
      //cout << "in" << endl;
      if(!f){
        if( C[i] ) q.push( rs );
        q.push( rs );
        f = true;
        continue;
      }
      else if( K-cnt > 0 ){
        cnt++; C[i]++;
      }
    }
    rs = ky / (double)(C[i]+1) / 2.0;
    q.push( rs );
  }
  //  cout << q.top() << endl;
  double res = q.top(); q.pop();
  res += q.top();
  printf("%.10lf\n",res);
}
