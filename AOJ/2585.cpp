#include<bits/stdc++.h>
using namespace std;

struct edge{
  int to,c,t,r;
};
struct state{
  int h,id,c;
  state(int h,int id,int c):h(h),id(id),c(c){}
  state(){}
  bool operator<(const state& st) const {
    return c > st.c;
  }
};

int N,M,H,K;
int S,T,P;
vector<edge> G[111];
#define INF (1<<29)
int flag[(1<<8)];


int mem[26][111];

int solve(int bi){
  fill(mem[0],mem[25],INF);
  priority_queue<state> q;
  q.push( state(0,S,0) );
  mem[0][S] = 0;
  
  while( !q.empty() ){
    state p = q.top(); q.pop();
    if( mem[p.h][p.id] < p.c ) continue;
    if( p.id == T ) return p.c;
    for(int i=0;i<(int)G[p.id].size();i++){
      edge e = G[p.id][i];
      int nc = e.c;
      int nh = p.h + e.t;
      if( nh > H ) continue;
      if( bi & (1<<e.r) ) nc = 0;
      if( mem[nh][e.to] > nc + p.c ) {
	mem[nh][e.to] = nc + p.c;
	q.push( state(nh,e.to,nc + p.c) );
      }
    }
  }
  return -1;
}

int main(){
  while( cin >> N >> M >> H >> K && (N||M||H||K) ){
    for(int i=0;i<N;i++) G[i].clear();
    for(int i=0;i<M;i++){
      int a,b,c,h,r;
      cin >> a >> b >> c >> h >> r;
      --a; --b; --r;
      G[a].push_back( (edge){b,c,h,r} );
      G[b].push_back( (edge){a,c,h,r} );
    }
    
    cin >>  S>> T; --S; --T;
    cin >> P;
    fill(flag,flag+(1<<K),INF);
    flag[0] = 0;
    for(int i=0;i<P;i++){
      int l,f; cin >> l >> f;
      int bit = 0;
      for(int j=0;j<l;j++){
	int k; cin >> k; k--;
	bit |= (1<<k);
      }
      flag[bit] = min( flag[bit], f );
    }
    for(int i=0;i<(1<<K);i++)
      for(int j=0;j<(1<<K);j++)
	flag[i|j] = min( flag[i|j], flag[i]+flag[j] );
    int res = INF;
    for(int i=0;i<(1<<K);i++){
      if( flag[i] >= INF ) continue;
      //   cout << bitset<8>(i)<< " "<< flag[i] << endl;
      int ret = solve(i);
      if( ret != -1 ) res = min( res, flag[i] + ret );
    }
    if( res >= INF) cout << -1 << endl;
    else cout << res << endl;
  }
}
