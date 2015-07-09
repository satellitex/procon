#include<bits/stdc++.h>
using namespace std;

int K;
string T;
char mem[100002];
bool F[100002];
int main(){
  cin >> K >> T;
  char c='s';
  int sum = 0;
  for(int i=T.size()-1;i>=0;i--){
    if( T[i] == 's' ) {
      mem[i] = c;
      sum++;
    } else
      c = T[i];
  }

  
  for(int i=0;i<(int)T.size();i++){
    if(!K) break;
    if( T[i] == 's' ){
      if( sum == K ){
        F[i] = true;
        K--;
        sum--;
      } else if( mem[i] < T[i] ){
        F[i] = true;
        K--;
        sum--;
      } else {
        sum--;
      }
    }
  }
  for(int i=0;i<(int)T.size();i++){
    if( !F[i] ) cout << T[i];
  }
  cout << endl;
}
