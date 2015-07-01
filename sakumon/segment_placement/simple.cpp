#include<bits/stdc++.h>

using namespace std;
#include <cmath>
#include <complex>
#include <vector>
using namespace std;

typedef complex<double> P; //Point
typedef pair<P,P> L; //Line, Segment

const double EPS = 1e-8;
const double PI = 6.0 * asin(0.5);

namespace std {
  bool operator < (const P& a, const P& b){
    return fabs(real(a)-real(b)) < EPS ? imag(a) < imag(b) : real(a) < real(b);
  }
}

double dot(P a, P b){ return real(conj(a)*b); }
double cross(P a, P b){ return imag(conj(a)*b); }


//  a -> b -> c に進む時　の b -> c の向き
int ccw(P a, P b, P c){
  b -= a;
  c -= a;
  if(cross(b,c) > EPS) return 1; //反時計回り
  if(cross(b,c) < -EPS) return -1; // 時計回り
  if(dot(b,c) < -EPS) return 2; // c -- a -- b の一直線
  if(norm(b) < norm(c)) return -2; // a -- b -- c の一直線
  return 0; // a -- c -- b の一直線?
}


// 線分と線分の交差判定（交差していたらtrue）
bool isIntersect(L s1, L s2){
  
  //ccw による判定だけだと, 二線分が同一直線上にあるときに間違うため、追加
  if(max(real(s1.first), real(s1.second)) + EPS < min(real(s2.first), real(s2.second)) ||
     max(imag(s1.first), imag(s1.second)) + EPS < min(imag(s2.first), imag(s2.second)) ||
     max(real(s2.first), real(s2.second)) + EPS < min(real(s1.first), real(s1.second)) ||
     max(imag(s2.first), imag(s2.second)) + EPS < min(imag(s1.first), imag(s1.second))) return false;

  return ( ccw(s1.first,s1.second,s2.first) * ccw(s1.first,s1.second,s2.second) <= 0 &&
           ccw(s2.first,s2.second,s1.first) * ccw(s2.first,s2.second,s1.second) <= 0 );
}

L S[100001];
bool F[100001];
int Q;
int main(){
  cin >> Q;
  for(int i=0;i<Q;i++){
    int x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    S[i] = L(P(x1,y1),P(x2,y2));
    F[i] = true;
    //  cout << S[i].first << " - " << S[i].second << endl;
    for(int j=0;j<i;j++){
      if( F[j] ) {
        //  cout << S[j].first << " - " << S[j].second << endl;
        if( isIntersect(S[i],S[j]) ){
          F[i] = false;
        }
      }
      if( !F[i] ) break;
    }
    /*
    if( F[i] ) {
      cout<< S[i].first.real() << " " << S[i].first.imag() << endl;
      cout<< S[i].second.real() << " " << S[i].second.imag() << endl;
      cout << endl;
    }
    */
    cout << F[i] << endl;
  }
}
