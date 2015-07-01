#include<bits/stdc++.h>
using namespace std;

int H,W,N;
char A[111][111];
char buf[1024];
int dx[]={0,1,0,-1};
int dy[]={-1,0,1,0};
char dc[]="NESW";
int x,y,d;
int gx,gy;

bool ischeckC(){
  int nx = x + dx[d], ny = y + dy[d];
  if( A[nx][ny] == '#' ) return true;
  return false;
}

bool ischeck(char c){
  if( 'T' == c ) return true;
  if( 'C' == c ) return ischeckC();
  int cd=-1;
  for(int i=0;i<4;i++){
    if( dc[i] == c ) cd = i;
  }
  if( d == cd ) return true;
  return false;
}

int cnt = 0;
int res = 0;
void move(char c){
  //  cout << x << " "<< y << " " << d << " " << c  << endl;
  int nx=x,ny=y;
  if( c == '^' ) {
    nx = x + dx[d]; ny = y + dy[d];
  } else if( c == 'v' ){
    nx = x + dx[(d+2)%4]; ny = y + dy[(d+2)%4];
  } else if( c == '>' )
    d=(d+1)%4;
  else
    d=(d+3)%4;
        
  if( A[nx][ny] != '#' ){
    x = nx; y = ny;
  }
  res++;
  //cout << x << " "<< y << " " << d << " " << c <<"  res : "  <<res << endl;
  if( A[x][y] == 'g' ) throw(0);
}
void consume(char c){
  if( buf[cnt] == c ){
    cnt++;
  } else {
    cout << "cnt : " << cnt << " c : " << c << " really : " << buf[cnt] << endl;
    throw(0);
  }
}

void program(bool );
bool sentence(bool );
bool calc(bool );
bool ifs(bool );
bool whiles(bool );
string term();

void program(bool fl){
  while( sentence(fl) );
}

bool sentence(bool fl){
  for(;;){
    bool ret = calc(fl);
    if( ret ) continue;
    ret = ifs(fl);
    if( ret ) continue;
    ret = whiles(fl);
    if( ret ) continue;
    break;
  }
}

bool ifs(bool fl){
  if( buf[cnt] == '[' ){
    cnt++;
    string t = term();
    bool f = false;
    if( t[0] == '~' ){
      f = ischeck(t[1]);
      f = !f;      
    } else {
      f = ischeck(t[0]);
    }
    sentence(f && fl);          
    consume(']');
    return true;
  }
  return false;
}
typedef pair<int,int> P;
typedef pair<P,int> PP;
bool whiles(bool fl){
  if( buf[cnt] == '{' ){
    set<PP> flg;
    cnt++;
    int mt = cnt;
    while( 1 ){
      if(flg.find(PP(P(x,y),d))!=flg.end()){
        res = -1; throw(0);
      }
      flg.insert(PP(P(x,y),d));
      cnt = mt;
      string t = term();
      bool f;
      if( t[0] == '~' ){
        f = ischeck(t[1]);
        f = !f;      
      } else {
        f = ischeck(t[0]);
      }
      //cout << cnt << " " << buf[cnt] << endl;
            //            cout << x <<" " <<y << " "<< d << " "  << f << " " << fl << " " << "  " << t << endl;
      //cout << flg[x][y][d] << endl;
      //if( !f ) cout << f << endl;
      sentence(f && fl);
      //if( f&&fl ) cout << f << " "<< fl<< endl;
      if( !f || !fl ) break;
    }
    consume('}');
    return true;
  }
  return false;
}

string term(){
  string ret;
  if( buf[cnt] == '~' )
    ret += buf[cnt++];
  ret += buf[cnt++];
  return ret;
}

bool calc(bool fl){
  //  cout << buf[cnt] << " " << fl << " " << cnt  << endl;
  if( buf[cnt] == '^' || buf[cnt] == 'v' || buf[cnt] == '<' || buf[cnt] == '>' ) {
    if(fl) move(buf[cnt]);
    cnt++;
    return true;
  } 
  return false;
}


int main(){
  cin >> H >> W;
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      cin >> A[j][i];
      if( A[j][i] == 's' ) {
        x = j; y = i; d = 0;
      }
      if( A[j][i] == 'g' ){
        gx = j; gy = i;
      }
    }
  }
  cin >> buf;
  N = strlen(buf);
  bool f =false;
  cnt = 0;
  try{
    sentence(true);    
  } catch(...) {
    //cout << "catch" << endl;
      cout << res << endl;
      f = true;
  }
  if( !f ) cout << -1 << endl;
}
