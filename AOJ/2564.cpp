#include<bits/stdc++.h>
using namespace std;

struct edge{
  int to,from,no,flag;
};
int N,M;
vector<int> same[3111];
vector<int> Gs[511],Gn[511];
edge E[3111];
struct uni{
  int d[3111];
  void init(){ memset(d,-1,sizeof(d)); }
  int find(int a){ return d[a]<0?a:(d[a] = find(d[a])); }
  void marge(int a,int b){
    a = find(a), b = find(b);
    if( a == b ) return;
    if( d[a] > d[b] ) swap(a,b);
    d[a] += d[b]; d[b] = a;   
  }
};
uni U;

void view(){
  cout << "view" << endl;
  for(int i=0;i<M;i++){
    cout << E[i].flag << endl;
  }
}

bool check(){
  //  view();
  for(int i=0;i<M;i++) if( !E[i].flag ) return false;
  return true;
}

bool update(){
  //  view();
  bool ret = false;
  for(int i=0;i<M;i++){
    if( E[i].flag ) {
      int p = U.find(i);
      if( same[p].empty() ) continue;
      
      for(int i=0;i<(int)same[p].size();i++)
	E[same[p][i]].flag = 1;
      ret = true;
      same[p].clear();
    }
  }
  for(int i=0;i<N;i++){
    vector<int> e;
    for(int j=0;j<(int)Gs[i].size();j++)
      if( !E[Gs[i][j]].flag ) e.push_back( Gs[i][j] );
    for(int j=0;j<(int)Gn[i].size();j++)
      if( !E[Gn[i][j]].flag ) e.push_back( Gn[i][j] );
    if(e.size()==1) {
      E[e[0]].flag = 1;      
      ret = true;
    }
 
  }
  return ret;
}

int main(){
  
  cin >> N >> M;
  for(int i=0;i<M;i++){
    int s,t; cin >> s>> t;
    E[i] = (edge){s,t,i,0};
    Gs[s].push_back(i);
    Gn[t].push_back(i);
  }

  U.init();
  for(int i=0;i<N;i++)
    if( Gs[i].size() == 1 && Gn[i].size() ==1 )
      U.marge(Gs[i][0],Gn[i][0]);
  for(int i=0;i<M;i++)
    same[U.find(E[i].no)].push_back( E[i].no );
  
 

  int cnt = 0;
  do{
    if( M == 0 ) continue;
    cnt++;
    for(int i=0;i<M;i++){
      if( E[i].flag ) continue;
      E[i].flag = 1;
      break;
    }
    while( update() );
    
  } while( !check() );
  cout << cnt << endl;
}
