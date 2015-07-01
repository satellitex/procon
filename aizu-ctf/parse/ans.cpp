#include<bits/stdc++.h>
using namespace std;

struct state{
  int num;
  string s;
  bool f;
  state(string a){
    s = a; f = true;
    num = 0;
  }
  state(int a){
    num = a; f = false;
  }
  state(){}
};

int pl(int a,int b){ return a + b; }
string pl(string a,string b){ return a+b; }
state pl(state a,state b){
  if( a.f ) return state( pl(a.s,b.s) );
  return state( pl(a.num,b.num) ); 
}

int mi(int a,int b){ return a - b; }
string mi(string a,string b){
  string A = "";
  int m = b.size();
  if( a.size() < b.size() ) return a;
  for(int i=0;i<(int)a.size()-m+1;i++){
    if( a.substr(i,m) == b ) i+=m-1;
    else A += a[i];      
  }
  return A;
}
state mi(state a,state b){
  if( a.f ) return state( mi(a.s,b.s) );
  return state( mi(a.num,b.num) );
}

int kake(int a,int b){ return a*b; }
string kake(string a,int b){
  string A="";
  for(int i=0;i<b;i++) A += a;
  return A;
}
state kake(state a,state b){
  if( a.f ) return state( kake(a.s,b.num) );
  return state( kake(a.num,b.num) );
}

int waru(int a,int b){ return a/b; }
string waru(string a,int b){
  string A = "";
  for(int i=0;i<(int)a.size();i+=b){
    A += a[i];
  }
  return A;
}
state waru(state a,state b){
  if( a.f ) return state(waru(a.s,b.num));
  return state(waru(a.num,b.num));
}

char S[1012];
int cnt;
state expression();
state term();
state fact();

void consume(char c){
  if( S[cnt] == c ){
    cnt++;
  } else {
    cout << "c :" << c << " S[cnt] = " << S[cnt] << " but got : " << cnt << endl;
    while( S[cnt] !='\0' ){
      cout << S[cnt++] << endl;
    }
    throw 0;
  }
}


state number(){
  int ret = 0;
  if( !isdigit( S[cnt] ) ) return state(-1);
  while( isdigit( S[cnt] ) ){
    ret *= 10;
    ret += S[cnt++]-'0';
  }
  return state(ret);
}

state getstr(){
  string ret;
  if( S[cnt] != '\"' ) return state(-1);
  cnt++;
  while( S[cnt] != '\"' )
    ret += S[cnt++];
  consume('\"');
  return ret;
}

state expression(){
  state ret = term();
  for( ;; ){
    if( S[cnt] == '+' ) {
      cnt++;
      ret = pl( ret, term() );
    } else if( S[cnt] == '-' ){
      cnt++;
      //      cout << '-' << ret.s << endl;
      ret = mi( ret, term() );
    } else
      break;
  }
  return ret;  
}

state term(){
  state ret = fact();
  for( ;; ){
    if( S[cnt] == '*' ) {
      cnt++;
      ret = kake(ret,fact());
    } else if( S[cnt] == '/' ){
      cnt++;
      ret = waru(ret,fact());
    } else
      break;
  }
  return ret;
}

state fact(){
  state ret = number();
  if( ret.num != -1 ) return ret;
  ret = getstr();
  if( ret.num != -1 ) return ret;
  consume('(');
  ret = expression();
  consume(')');
  return ret;
}

int main(){
  cin >> S;
  cnt = 0;
  try {
    state ans = expression();
    cout << ans.s << endl;
  } catch( ... ){
    cout << "err" << endl;
  }
}
