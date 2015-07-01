/*--------------------------------------------------------
ポルンガのゲーム実況
  https://www.youtube.com/user/oXpolungaXo

＞＞チャンネル登録お願いします！！＜＜
  --------------------------------------------------------*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct edge{
  ll to,d;
};
struct state{
  ll id,d,c;
  bool operator<(const state& s) const{
    return d>s.d;
  }
};

ll N,M,C,s,g;
ll W[22][101][101];
vector<edge> G[22][101];

#define INF (1<<29)


void dijk(ll id){
  priority_queue<state> q;
  ll mem[21][111];
  for(ll i=0;i<21;i++)
    for(ll j=0;j<101;j++)
      mem[i][j] = INF;
  
  for(ll i=0;i<C;i++){
    q.push( (state){id,0,i} );
    mem[i][id] = 0;
  }

  while( !q.empty() ){
    state p = q.top(); q.pop();
    if( mem[p.c][p.id] < p.d ) continue;
    for(ll i=0;i<(ll)G[p.c][p.id].size();i++){
        edge e = G[p.c][p.id][i];
        //cout << p.id << " -> " << e.to << " = " << " "<< p.d << " "<< e.d << endl;
        if( mem[p.c][e.to] > p.d + e.d ){
          mem[p.c][e.to] = p.d + e.d;
          q.push( (state){ e.to, p.d+e.d, p.c} );
        }
    }
  }

  for(ll i=0;i<N;i++)
    for(ll j=0;j<C;j++)
      //cout << j << " " << id << " -> " << i << " = " << mem[j][i] << endl;
      W[j][id][i] = mem[j][i];
    
   
}

ll cost[22][21111];

ll solve(ll id){
  priority_queue<state> q;
  ll mem[21][111];
  
  for(ll i=0;i<21;i++)
    for(ll j=0;j<101;j++)
      mem[i][j] = INF;
  
  for(ll i=0;i<C;i++) {
    q.push( (state){id,0,i} );
    mem[i][id] = 0;
  }
  while( !q.empty() ){
    state p = q.top(); q.pop();
    //cout << p.c << " "<< p.id << " "<< p.d << endl;
    if( mem[p.c][p.id] < p.d ) continue;
    if( p.id == g ) return p.d;
    for(ll i=0;i<C;i++){
      if( mem[i][p.id] > p.d ){
        mem[i][p.id] = p.d;
        q.push( (state){p.id,p.d,i} );
      }
    }
    for(ll i=0;i<N;i++){
      if( i == p.id ) continue;
      //cout << p.id << " -> " << i << " = " << p.c << " "<< W[p.c][p.id][i] << endl;     
      if( W[p.c][p.id][i] >= INF ) continue;
      //assert(W[p.c][p.id][i] < 10100);
      ll nc = cost[p.c][W[p.c][p.id][i]] + p.d;
      //cout << "nc = " << nc << endl;
      if( mem[p.c][i] > nc ){
        mem[p.c][i] = nc;
        q.push( (state){i,nc,p.c} );
      }
    }    
  }
  return -1;                       
}

ll p[22];
ll q[55];
ll r[55];
int main(){
  while(  cin >> N >> M >> C >> s >> g && (N||M||C||s||g) ){
    --s;--g;
    for(ll i=0;i<101;i++)
      for(ll j=0;j<21;j++)
        G[j][i].clear();
    
    for(ll i=0;i<M;i++){
      ll x,y,d,c;
      cin >> x >> y >> d >> c;
      --x; --y; --c;
      G[c][x].push_back( (edge){y,d} );
      G[c][y].push_back( (edge){x,d} );
    }
    for(ll i=0;i<C;i++) cin >> p[i];

    
    for(ll i=0;i<C;i++){
      for(ll j=0;j<p[i]-1;j++)
        cin >> q[j];
      q[p[i]-1] = INF;
      for(ll j=0;j<p[i];j++)
        cin >> r[j];
      ll co = 0;
      //      cout << "c : " << i << endl;
      for(ll j=0, k = 0;j<=21100;j++){
        cost[i][j] = co;
        if( j == q[k] ) k++;
        co += r[k];
        /*
        if( j < 10 ){
           cout << "di : " << j << endl;
          cout << q[k] << " " << r[k] << " "<< cost[i][j] << endl;
          }
        */
      }
    }
    
    for(ll i=0;i<N;i++){
      dijk(i); 
    }
    cout << solve(s) << endl;
  }
  
}
