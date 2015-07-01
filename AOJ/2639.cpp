/*--------------------------------------------------------
ポルンガのゲーム実況
  https://www.youtube.com/user/oXpolungaXo

＞＞チャンネル登録お願いします！！＜＜
  --------------------------------------------------------*/


#include<bits/stdc++.h>
using namespace std;
int memo[61][2];
int main(){
  int A,B,C;
  cin >> A >> B >> C;
  int time = 0,ok=1;
  int res = 0;
  bool f = false;
  while( !memo[time][ok] ){
    memo[time][ok] = 1;   
    for(int i=1;i<=60;i++){
      time++;
      //      cout << time << " " << ok << endl;
      if( ok == 1 ) {
        if( C == i ) {
          res += i;
          f = true; break;
        }            
        if( time == A ) {
          time = 0; ok = 0;
        }
      } else if( time == B ){
        time = 0; ok = 1;
      }                  
    }
    if( f ) break;
    res += 60;
  }
  if( f ) cout << res << endl;
  else cout << -1 << endl;
}
