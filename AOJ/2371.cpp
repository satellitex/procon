#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
ll T;
int cnt;
int coun;
map<string,int> smap;
struct edge{
  int to;
  ll c;
};
  
vector<edge> G[100008];
vector<int> V[100008];
int F[100008];
typedef pair<ll,ll> P;

int st,ed;
int stoi(string s){
  if( smap.count(s) == 0  ) return smap[s] = cnt++;
  return smap[s];
}

struct state{
  int id;
  P c;
  state(int id,P c) : id(id),c(c) {}
  state(){}
  bool operator<(const state s) const {
    return c > s.c;
  }
};

P mem[100008];
#define INF (1LL<<60LL)
P dijk(){
  fill(mem,mem+coun,P(INF,INF) );
  priority_queue<state> q;
  for(int i=0;i<(int)V[st].size();i++){
    q.push( state( V[st][i], P(0,0) ) );
    mem[V[st][i]] = P(0,0);
  }
  while( !q.empty() ){
    state p = q.top(); q.pop();
    if( mem[p.id] < p.c ) continue;
    // cout << p.id << " " << p.c.first << " " << p.c.second  << " "<< F[p.id] << endl;
    int sid = F[p.id];
    if( sid == ed ) return p.c;
    for(int i=0;i<(int)V[sid].size();i++){
      int to = V[sid][i];
      if( to == p.id ) continue;
      P nc = p.c;
      nc.first += T;
      nc.second += 1LL;
      //cout << "to " << to << " cost " << nc.first << " "<< nc.second << endl;
      if( mem[to] > nc ) {
        mem[to] = nc;
        q.push( state(to,nc) );
      }
    }
    for(int i=0;i<(int)G[p.id].size();i++){
      edge e = G[p.id][i];
      P nc = p.c;
      nc.first += e.c;
      //      if( e.c == 27 ) cout << "e.to " << e.to << " [ " << F[e.to] << " ] " <<  " cost " << nc.first << " "<< nc.second << " " << mem[e.to].first << endl;
      if( mem[e.to] > nc ){
        mem[e.to] = nc;
        q.push( state(e.to,nc) );
      }
    }
  }
  return P(-1,-1);
}

int main(){
  cin >> N >> T;
  string A,B;
  cin >> A >> B;
  st = stoi(A); ed = stoi(B);
  coun = 0;
  for(int i=0;i<N;i++){
    int a; cin >> a;
    int be = coun;
    for(int j=0;j<a;j++){
      string t; cin >> t;
      int v = stoi(t);
      V[v].push_back(coun);
      F[coun] = v;
      coun++;
    }
    for(int j=0;j<a-1;j++){
      ll c; cin >> c;
      G[be].push_back( (edge){be+1,c} );
      G[be+1].push_back( (edge){be,c} );
      be++;
    }
  }
  P res = dijk();
  if( res == P(-1,-1) ) cout << -1 << endl;
  else cout << res.first << " "<< res.second << endl;
      
}
