/*--------------------------------------------------------
ポルンガのゲーム実況
  https://www.youtube.com/user/oXpolungaXo

＞＞チャンネル登録お願いします！！＜＜
  --------------------------------------------------------*/

#include<bits/stdc++.h>
using namespace std;

struct edge{
  int to,d;
};
struct state{
  int id,d,c;
  bool operator<(const state& s) const{
    return d>s.d;
  }
};

int N,M,C,s,g;
int W[22][101][101];
vector<edge> G[22][101];

#define INF (1<<29)


void dijk(int id){
  priority_queue<state> q;
  int mem[21][111];
  for(int i=0;i<C;i++)
    for(int j=0;j<N;j++)
      mem[i][j] = INF;
  for(int i=0;i<C;i++){
    q.push( (state){id,0,i} );
    mem[i][id] = 0;
  }

  while( !q.empty() ){
    state p = q.top(); q.pop();
    if( mem[p.c][p.id] < p.d ) continue;
    for(int i=0;i<(int)G[p.c][p.id].size();i++){
        edge e = G[p.c][p.id][i];
        //cout << p.id << " -> " << e.to << " = " << " "<< p.d << " "<< e.d << endl;
        if( mem[p.c][e.to] > p.d + e.d ){
          mem[p.c][e.to] = p.d + e.d;
          q.push( (state){e.to,p.d+e.d,p.c} );
        }
    }
  }

  for(int i=0;i<N;i++){
    for(int j=0;j<C;j++){
      //cout << j << " " << id << " -> " << i << " = " << mem[j][i] << endl;
      W[j][id][i] = mem[j][i];
    }
  }  
}

int cost[22][11111];

int solve(int id){
  priority_queue<state> q;
  int mem[21][111];
  
  for(int i=0;i<C;i++)
    for(int j=0;j<N;j++)
      mem[i][j] = INF;
  
  for(int i=0;i<C;i++) {
    q.push( (state){id,0,i} );
    mem[i][id] = 0;
  }
  while( !q.empty() ){
    state p = q.top(); q.pop();
    //cout << p.c << " "<< p.id << " "<< p.d << endl;
    if( mem[p.c][p.id] < p.d ) continue;
    if( p.id == g ) return p.d;
    for(int i=0;i<C;i++){
      if( mem[i][p.id] > p.d ){
        mem[i][p.id] = p.d;
        q.push( (state){p.id,p.d,i} );
      }
    }
    for(int i=0;i<N;i++){
      if( i == p.id ) continue;
      //cout << p.id << " -> " << i << " = " << p.c << " "<< W[p.c][p.id][i] << endl;     
      if( W[p.c][p.id][i] >= INF ) continue;
      int nc = cost[p.c][W[p.c][p.id][i]] + p.d;
      //cout << "nc = " << nc << endl;
      if( mem[p.c][i] > nc ){
        mem[p.c][i] = nc;
        q.push( (state){i,nc,p.c} );
      }
    }    
  }
  return -1;                       
}

int p[22];
int q[55];
int r[55];
int main(){
  while(  cin >> N >> M >> C >> s >> g && (N||M||C||s||g) ){
    --s;--g;
    for(int i=0;i<N;i++)
      for(int j=0;j<C;j++)
        G[j][i].clear();
    
    for(int i=0;i<M;i++){
      int x,y,d,c;
      cin >> x >> y >> d >> c;
      --x; --y; --c;
      G[c][x].push_back( (edge){y,d} );
      G[c][y].push_back( (edge){x,d} );
    }
    for(int i=0;i<C;i++) cin >> p[i];

    
    for(int i=0;i<C;i++){
      for(int j=0;j<p[i]-1;j++)
        cin >> q[j];
      q[p[i]-1] = INF;
      for(int j=0;j<p[i];j++)
        cin >> r[j];
      int co = 0;
      //      cout << "c : " << i << endl;
      for(int j=0, k = 0;j<=10100;j++){
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
    
    for(int i=0;i<N;i++){
      dijk(i); 
    }
    cout << solve(s) << endl;
  }
  
}
