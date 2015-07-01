#include<bits/stdc++.h>
using namespace std;


struct P3{
  double x,y,z;
};
struct data{
  P3 p,v;
  double r,vr;
};

data D[222];

const double EPS = 1E-9;

double twi(double a){ return a*a; }

double check(P3 a,P3 va,double ra,double vra,P3 b, P3 vb,double rb,double vrb, double t){
  //  cout << sqrt( twi(a.x + va.x * t - b.x - vb.x * t ) +
  //            twi(a.y + va.y * t - b.y - vb.y * t ) +
  //             twi(a.z + va.z * t - b.z - vb.z * t ) ) - (ra - vra * t) - (rb - vrb * t) << endl;
  return sqrt( twi(a.x + va.x * t - b.x - vb.x * t ) +
               twi(a.y + va.y * t - b.y - vb.y * t ) +
               twi(a.z + va.z * t - b.z - vb.z * t ) ) - (ra - vra * t) - (rb - vrb * t);
}

struct event{
  double t;
  int p1,p2;
  event(){ p2 = -1; }
  bool operator<(const event e) const {
    return t < e.t;
  }
  event(double t,int p1){
    this->t = t; this->p1 = p1;
    p2 = -1;
  }
  event(double t,int p1,int p2) : t(t),p1(p1),p2(p2) {}
};

int main(){
  int n;
  while( cin >> n && n ){
    double F[222];
    fill(F,F+n,-1.0);
    vector<event> del;
    del.clear();
    for(int i=0;i<n;i++){
      double px,py,pz,vx,vy,vz,r,vr;
      cin >> px >> py >> pz >> vx >> vy >> vz >> r >> vr;
      D[i]=(data){(P3){px,py,pz},(P3){vx,vy,vz},r,vr};
      del.push_back( event( r/vr , i ) );
    }
    
    for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
        
        double st = 0, ed = min( del[i].t, del[j].t );
        while( ed - st  > EPS ){
          //cout << st << " - " << ed << endl;
          double t1 = (ed-st)/3.0 + st;
          double t2 = (ed-st)/3.0*2.0 + st;
          double h1 = check(D[i].p,D[i].v,D[i].r,D[i].vr,D[j].p,D[j].v,D[j].r,D[j].vr,t1);
          double h2 = check(D[i].p,D[i].v,D[i].r,D[i].vr,D[j].p,D[j].v,D[j].r,D[j].vr,t2);
          //          cout << "(t1,t2) " << t1 << " " << t2 << " h1 = " << h1 << " h2 = " << h2 << endl;
          if( h1 < h2 ){
            ed = t2;
          } else {
            st = t1;
          }
        }
        if( check(D[i].p,D[i].v,D[i].r,D[i].vr,D[j].p,D[j].v,D[j].r,D[j].vr,ed) > EPS ) continue;
        st = 0.0;
        while( ed - st > EPS ){
          double t = (st+ed)/2.0;
          double h = check(D[i].p,D[i].v,D[i].r,D[i].vr,D[j].p,D[j].v,D[j].r,D[j].vr,t);
          //          cout << st << " - " <<ed << " t = " << t << " h = " << h << endl;
          if( h < EPS ) 
            ed = t;
          else
            st = t;
        }
        
        del.push_back( event(ed,i,j) );      
      }
    }

    sort(del.begin(),del.end());
    for(int i=0;i<del.size();i++){
      //cout << del[i].t << " "<< del[i].p1 << " "<< del[i].p2 << endl;
      if( del[i].p2 == -1 ){
        if( F[del[i].p1] < -EPS ) F[del[i].p1] = del[i].t;
      } else {
        if( F[del[i].p1] < -EPS && F[del[i].p2] < -EPS ) {
          F[del[i].p1] = del[i].t;
          F[del[i].p2] = del[i].t;
        }
      }
    }
    for(int i=0;i<n;i++){
      printf("%.10lf\n",F[i]);
    }
      
  }  
}
