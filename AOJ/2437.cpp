#include<bits/stdc++.h>
using namespace std;

int Na,Nt,Ng,Nc;
int M;

string S[51];
vector<string> v[51];
int dp[2][53][53][53];

#define MOD (1000000007)

void add(int &a,int b){
  a = (a+b)%MOD;
}

int main(){
  cin >> Na >> Nt >> Ng >> Nc;
  cin >> M;
  for(int i=0;i<M;i++){
    cin >> S[i];
    S[i].erase(S[i].end()-1);    
    string buf;
    getline( cin, buf );
    stringstream sin(buf);
    string tmp;
    while( sin >> tmp ) v[i].push_back( tmp );
    /*
      cout << S[i] << " : " << endl;
      for(int j=0;j<(int)v[i].size();j++) cout << v[i][j] << " ";
      cout << endl;
    */
  }
  bool f = true;
  map<string,vector<vector<char> > > fie;
  for(int i=M-1;i>-1;i--){
    vector<vector<char> > &vc = fie[S[i]];
    for(int j=0;j<(int)v[i].size();j++){
      if( v[i][j][0] == '[' ){
        vc.push_back( vector<char>() );
        for(int k=1;k<(int)v[i][j].size()-1;k++){
          vc.back().push_back( v[i][j][k] );
        }
      } else
        for(int k=0;k<(int)fie[v[i][j]].size();k++)
          vc.push_back( fie[v[i][j]][k] );        
    }
    if( (int)vc.size() > Na + Nt + Ng + Nc ) { f = false; break;   }
  }

  vector<vector<char> > A = fie[S[0]];
  int N = A.size();
  dp[0][0][0][0] = 1;

  if( N - Na - Nt - Ng != Nc || !f) { cout << 0 << endl; return 0; }
  
  for(int i=0;i<N;i++){
    int now = i&1;
    int nex = 1-now;
    memset(dp[nex],0,sizeof(dp[nex]));
    for(int a = 0; a <= Na; a++){
      for(int t = 0; t <= Nt; t++){
        for(int g = 0; g <= Ng; g++ ){
          int c = i - a - t - g;

          if( !dp[now][a][t][g] ) continue;
          if( c > Nc ) continue;


                    
          for(int j=0;j<(int)A[i].size();j++){
            if( A[i][j] == 'A' ) add(dp[nex][a+1][t][g],dp[now][a][t][g]);
            else if( A[i][j] == 'T' ) add(dp[nex][a][t+1][g],dp[now][a][t][g]);
            else if( A[i][j] == 'G' ) add(dp[nex][a][t][g+1],dp[now][a][t][g]);
            else add(dp[nex][a][t][g],dp[now][a][t][g]);            
          }
        }
      }
    }
  }
  cout << dp[N&1][Na][Nt][Ng] << endl;

  
  
}
