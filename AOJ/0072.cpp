#include<bits/stdc++.h>
using namespace std;
struct edge{
  int a,b,c;
  bool operator<(const edge &e) const {
    return c < e.c;
  }
};

struct uni{
  int d[111];
  void init(){
    memset(d,-1,sizeof(d));
  }
  int find(int a){ return d[a]<0?a:(d[a]=find(d[a])); }
  void marge(int a,int b){
    a = find(a); b = find(b);
    if( a == b ) return;
    if( d[a] > d[b] ) swap(a,b);
    d[a]+=d[b]; d[b] = a;
  }  
  bool same(int a,int b){
    return find(a) == find(b);
  }
};

int N,M;
int main(){
  while( ~scanf("%d",&N) && N ){
    scanf("%d",&M);
    vector<edge> E;    
    for(int i=0;i<M;i++){
      int a,b,c;
      scanf("%d,%d,%d",&a,&b,&c);
      c/=100; c--;
      E.push_back( (edge){a,b,c} );
    }
    sort(E.begin(),E.end());
    uni U; U.init();
    int res = 0;
    for(int i=0;i<M;i++){
      edge &e=E[i];
      if( U.same(e.a,e.b) ) continue;
      U.marge(e.a,e.b);
      res+=e.c;
    }
    cout << res << endl;
  }
}
