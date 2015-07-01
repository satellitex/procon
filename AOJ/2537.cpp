#include<bits/stdc++.h>
using namespace std;



typedef complex<double> P; //Point
typedef pair<P,P> L; //Line, Segment

const double EPS = 1e-10;
const double PI = 6.0 * asin(0.5);

namespace std {
  bool operator < (const P& a, const P& b){
    return fabs(real(a)-real(b)) < EPS ? imag(a) < imag(b) : real(a) < real(b);
  }
}

double dot(P a, P b){ return real(conj(a)*b); }

double cross(P a, P b){ return imag(conj(a)*b); }

// 射影
P proj(P p, L l){
    return l.first + dot(p - l.first, l.second - l.first) / norm(l.second - l.first) * (l.second - l.first);
}

// 反射（線対称な点）
P reflect(P p, L l){
  return p + (proj(p,l) - p) * 2.0;
}

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


// 直線と線分の交差判定
bool isIntersectLS(L l, L s){
  return cross(l.second-l.first, s.first-l.first) * cross(l.second-l.first, s.second-l.first) < EPS;
}

// ２直線間の交点
P crossPoint(L l, L m){
  double A = cross(l.second - l.first, m.second - m.first);
  double B = cross(l.second - l.first, l.second - m.first);
  if(fabs(A) < EPS && fabs(B) < EPS) return m.first;
  else if(fabs(A) >= EPS) return m.first + B / A * (m.second - m.first);
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

// 線分と点の交差判定
bool isIntersectSP(L s, P p){ 
  return abs(s.first-p) + abs(s.second-p) - abs(s.second-s.first) < EPS; 
}

//円
struct Circle{
  P c; //中心点
  double r; //半径
  Circle(P c=P(0,0), double r=0):c(c),r(r){}
};


vector<L> kabe;

//円と線分の交点
vector<P> getIntersectCS(Circle c, L s){
  vector<P> res;
  P h = proj(c.c, s);
  double d = abs(c.c - h);
  if(d > c.r + EPS);
  else if(d > c.r - EPS){
    if(isIntersectSP(s,h)) res.push_back(h);
  }
  else {
    P v = s.second - s.first;
    v = (sqrt(c.r*c.r - d*d) / abs(v)) * v;
    if(isIntersectSP(s, h+v)) res.push_back(h+v);
    if(isIntersectSP(s, h-v)) res.push_back(h-v);
  }
  return res;
}


void ref(Circle c,P v){
  for(int i=0;i<4;i++){
    if( isIntersectLS(L(c.c,c.c+v),kabe[i]) ){
      vector<P> pos = crossPoint(L(c.c,c.c+v),kabe[i]);
      
    }
  }
}

bool ischeck( Circle c1, Circle c2 ){
  if( abs( c1.c - c2.c ) < c1.r + c2.r + EPS ) return true;
  return false;
}

int main(){
};
