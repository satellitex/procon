/*===========解法=============
  トポロジカル順序をつける。
  dp[一回目にいる頂点][二回目にいる頂点] = 最小コスト
  遷移する頂点は必ずトポロジカル順序で始点に近い方
  同じ場合遷移先の頂点の組み合わせをすべて試す。
  ここでも遷移先が同じだった場合は、２回目のコストを使う。
 */
#include<bits/stdc++.h>
using namespace std;

const int INF = (1<<29);


int N,M;//N:頂点数　M:辺の数 互いにMAX 1000
int A,B;//A:始点 B:終点

struct edge{
  int to,c1,c2;
};

//グラフ常にDAG
//多重辺を含まない
vector<edge> G[1111];

int pr[1111];//トポロジカル順序

int dp[1111][1111];

//トポロジカル順序付け
void topological_sort(int id,int &cnt){
  for(int i=0;i<(int)G[id].size();i++){
    int to = G[id][i].to;
    topological_sort(to,cnt);
  }
  pr[id] = cnt++;
}

int solve(int id1,int id2){
  if( dp[id1][id2] != -1 ) return dp[id1][id2];
  int ret = INF;
  if( id1 == B && id2 == B ) return dp[id1][id2] = 0;
  if( pr[id1] > pr[id2] ){ //id1のほうがDAG上で手前
    for(int i=0;i<(int)G[id1].size();i++)
      ret = min( ret, solve(G[id1][i].to,id2) +  G[id1][i].c1);    
  } else if( pr[id1] < pr[id2] ){ //id2のほうがDAG上で手前
    for(int i=0;i<(int)G[id2].size();i++)
      ret = min( ret, solve(id1,G[id2][i].to) +  G[id2][i].c1);    
  } else { //同一頂点
    for(int i=0;i<(int)G[id1].size();i++){
      for(int j=0;j<(int)G[id2].size();j++){
        edge e1 = G[id1][i], e2 = G[id2][i];
        if( e1.to == e2.to ) //行き先が等しい時、二回目の通るコストを使う
          ret = min( ret, solve(e1.to,e1.to) + e1.c1 + e1.c2 );
        else
          ret = min( ret, solve(e1.to,e2.to) + e1.c1 + e2.c1 );
      }
    }
  }
  return dp[id1][id2] = ret;
}

int main(){
  cin >> N >> M;
  cin >> A >> B;
  --A; --B;
  for(int i=0;i<M;i++){
    int s,t,c1,c2;// s -> t
    cin >> s >> t >> c1 >> c2;
    --s; --t;
    G[s].push_back( (edge){ t, c1, c2 } );
  }

  int cnt = 0;
  topological_sort(A,cnt);
  
  memset(dp,-1,sizeof(dp));

  cout << solve(A,A) << endl;
}
