#include<bits/stdc++.h>
using namespace std;

#define INF (1000000009)
#define MAX (1<<19)

//ノード
struct node {
  node *l,*r,*p;
  int key;
  int sum;
  int rb;
  node(int c){
    key = c;
    l=r=p=NULL;
    sum = 1;
    rb = 1;
  }
};

//平行二分探索木
struct RBTree{
  node* root;
  RBTree(){ root = NULL; }
  bool isR(node* n){ return !n && n->rb == 1; }
  bool isL(node* n){ return !n && n->rb == 0; }

  node* rotateL(node *v){
    node* R = v->r;
    node* x1 = R->l;
    node* vp = v->p;
    assert( R );
    //子の貼替え
    v->r = x1;
    R->l = v;
    //親の貼替え
    x1->p = v;
    v->p = R;
    R->p = vp;
    //部分木の要素数
    v->sum = v->l->sum + v->r->sum + 1;
    R->sum = R->l->sum + R->r->sum + 1;   
    return R;
  }

  node* rotateR(node *v){
    node* L = v->l;
    node* x2 = L->r;
    node* vp = v->p;
    assert( L );
    //子の貼替え
    v->l = x2;
    L->r = v;
    //親の貼替え
    x2->p = v;
    v->p = L;
    L->p = vp;
    //部分木の要素数
    v->sum = v->l->sum + v->r->sum + 1;
    L->sum = L->l->sum + L->r->sum + 1;   
    return L;
  }

  node* rotateLR(node *v){
    v->l = rotateL(v->l);
    return rotateR(v);
  }
  node* rotateRL(node *v){
    v->r = rotateR(v->r);
    return rotateL(v);
  }


  //挿入
  void insert( int num ){
    root = insert( root, new node(num) );
    root->rb = 1;
  }

  node* insert(node* v, node* n){
    //    if( v ) cout << "insert " << v->key << endl;
    //else cout << "end" << endl;
    if( v == NULL )  return n;
    else if( n->key >= v->key ){
      v->r = insert( v->r, n );
      v->r->p = v;
      return balance(v);
    } else {
      v->l = insert( v->l, n );
      v->l->p = v;
      return balance(v);
    }
  }

  node* balance(node *v){
    if( v->rb ) return v;
    else if( isR(v->l) && isR(v->l->l) ) {
      v = rotateR(v);
      v->l->rb = 0;
    } else if( isR(v->l) && isR(v->l->r) ){
      v = rotateLR(v);
      v->l->rb = 0;
    } else if( isR(v->r) && isR(v->r->l) ){
      v = rotateRL(v);
      v->r->rb = 0;
    } else if( isR(v->r) && isR(v->r->r) ){
      v = rotateL(v);
      v->r->rb = 0;
    }
    return v;
  }

  //o <= key となる最大の o
  int search(int key){
    node *v = root;
    int rs = -INF;
    while( v != NULL ){
      if( v->key <= key ){
        rs = max( v->key, rs );
        v = v->r;
      } else {
        v = v->l;
      }
    }
    return rs;
  }

  // o <= key となる o の数
  int getnums(int key){
    node *v = root;
    node *rs = NULL;
    while( v != NULL ){
      if( v->key <= key ) {
        rs = v;
        v = v->r;
      }
      else v = v->l;      
    }
    v = rs;
    int res = 0;
    while( v != NULL ){
      if( v->l ) res += v->l->sum;
      res++;
      v = v->p;
    }
    return res;    
  }
};

//セグメントツリー
struct seg{
  RBTree A[MAX];
  RBTree B[MAX];
  int n;
  void init(int N){
    n = 1;
    while( n < N ) n*=2;    
  }

  //線分がクロスしていないかのチェック
  bool check( int x, int k ){
    //    cout << A[k].search(x) << " " << x << " - B " << B[k].search(x) << " "<< x << endl;
    if( A[k].search(x) == x || B[k].search(x) == x ) return false;
    int st = A[k].getnums(x);
    int ed = B[k].getnums(x);
    //out << st << " " << ed << endl;
    if( st == ed ) return true;
    return false;
  }
  
  bool query(int a,int b,int x,int k,int l,int r){   
    if( a >= r || l >= b ) return true;
    else if( a <= l && r <= b ) return check(x,k);
    else {
      bool L = query( a, b, x, 2 * k + 1, l, ( l + r ) / 2 );
      bool R = query( a, b, x, 2 * k + 2, ( l + r ) / 2, r );
      return min( L, R );
    }
  }

  bool query(int a,int b,int x){
    return query(a,b,x,0,0,n);
  }

  void add(int id,int st,int ed){
    id += n-1;
    A[id].insert( st );
    B[id].insert( ed );
    while( id > 0 ){
      id = (id-1)/2;
      A[id].insert( st );
      B[id].insert( ed );
    }
  }  
};

//縦と横に対しセグメントツリーを持つ
seg TATE,YOKO;

//各縦の行、横の行に対し、始点・終点ごとに平行二分探索木を持つ
RBTree TS[200001],TE[200001];
RBTree YS[200001],YE[200001];

int Q;

//線分が同一線上にないかのチェック
bool checkH( RBTree *a, RBTree *b, int st, int ed ){
  if( a->search(st) == st ||
      a->search(ed) == ed ||
      b->search(st) == st ||
      b->search(ed) == ed ) return false;
  int num1 = a->getnums( st );
  int num2 = a->getnums( ed );
  int num3 = b->getnums( st );
  int num4 = b->getnums( ed );
  if( num1 == num2 && num2 == num3 && num3 == num4 ) return true;
  return false;
}

int X1[100001],X2[100001];
int Y1[100001],Y2[100001];

//座標圧縮
int compress(int *x1,int *x2){
  vector<int> xs;
  for(int i=0;i<Q;i++){
    xs.push_back(x1[i]);
    xs.push_back(x2[i]);
  }
  sort(xs.begin(),xs.end());
  xs.erase(unique(xs.begin(),xs.end()),xs.end());
  for(int i=0;i<Q;i++){
    x1[i] = upper_bound( xs.begin(), xs.end(), x1[i] ) - xs.begin();
    x2[i] = upper_bound( xs.begin(), xs.end(), x2[i] ) - xs.begin();
  }
  return xs.size();
}

int main(){
  cin >> Q;
  for(int i=0;i<Q;i++){
    cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];
    if( X1[i] > X2[i] ) swap(X1[i],X2[i]);
    if( Y1[i] > Y2[i] ) swap(Y1[i],Y2[i]);
  }

  int W = compress(X1,X2);
  int H = compress(Y1,Y2);

  TATE.init(W);
  YOKO.init(H);

  
  for(int i=0;i<Q;i++){
    if( X1[i] == X2[i] ) { // tatesen
      bool f1 = TATE.query(Y1[i],Y2[i]+1,X1[i]);
      bool f2 = checkH( &TS[X1[i]], &TE[X1[i]], Y1[i],Y2[i] );
      //cout << "tate " << f1 << " " << f2 << endl;
      if( f1 && f2 ) {
        cout << 1 << endl;
        YOKO.add( X1[i], Y1[i], Y2[i] );
        TS[X1[i]].insert( Y1[i] );
        TE[X1[i]].insert( Y2[i] );
      } else
        cout << 0 << endl;
    } else { // yokosen
      bool f1 = YOKO.query(X1[i],X2[i]+1,Y1[i]);
      bool f2 = checkH( &YS[Y1[i]], &YE[Y1[i]], X1[i],X2[i] );
      //cout << "yoko " << f1 << " " << f2 << endl;
      if( f1 && f2 ) {
        cout << 1 << endl;
        TATE.add( Y1[i], X1[i], X2[i] );
        YS[Y1[i]].insert( X1[i] );
        YE[Y1[i]].insert( X2[i] );
      } else
        cout << 0 << endl;
    }
  }
  
  
}
