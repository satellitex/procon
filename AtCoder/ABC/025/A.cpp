#include<bits/stdc++.h>
using namespace std;
string S;
int N;
vector<string> v;
int main(){
  cin >> S;
  cin >> N;
  for(int i=0;i<S.size();i++){
    for(int j=0;j<S.size();j++){
      string t=""; t += S[i]; t+= S[j];
      v.push_back( t );
    }
  }
  sort(v.begin(),v.end());
  //  for(int i=0;i<(int)v.size();i++) cout << v[i] << endl;
  cout << v[N-1] << endl;
}
