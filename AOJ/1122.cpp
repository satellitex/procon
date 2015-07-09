#include<bits/stdc++.h>
using namespace std;

template < class BidirectionalIterator >
bool next_combination ( BidirectionalIterator first1 ,
  BidirectionalIterator last1 ,
  BidirectionalIterator first2 ,
  BidirectionalIterator last2 )
{
  if (( first1 == last1 ) || ( first2 == last2 )) {
    return false ;
  }
  BidirectionalIterator m1 = last1 ;
  BidirectionalIterator m2 = last2 ; --m2;
  while (--m1 != first1 && !(* m1 < *m2 )){
  }
  bool result = (m1 == first1 ) && !(* first1 < *m2 );
  if (! result ) {
    // ①
    while ( first2 != m2 && !(* m1 < * first2 )) {
      ++ first2 ;
    }
    first1 = m1;
    std :: iter_swap (first1 , first2 );
    ++ first1 ;
    ++ first2 ;
  }
  if (( first1 != last1 ) && ( first2 != last2 )) {
    // ②
    m1 = last1 ; m2 = first2 ;
    while (( m1 != first1 ) && (m2 != last2 )) {
      std :: iter_swap (--m1 , m2 );
      ++ m2;
    }
    // ③
    std :: reverse (first1 , m1 );
    std :: reverse (first1 , last1 );
    std :: reverse (m2 , last2 );
    std :: reverse (first2 , last2 );
  }
  return ! result ;
}
 
template < class BidirectionalIterator >
bool next_combination ( BidirectionalIterator first ,
  BidirectionalIterator middle ,
  BidirectionalIterator last )
{
  return next_combination (first , middle , middle , last );
}

vector<int> data;
int L,H;



int main(){
  for(int i=0;i<=9;i++) data.push_back( i );
  while( cin >> L >> H && (H||L) ){
    vector<vector<int> > T;
    vector<int> Hit,Blow;    
    for(int i=0;i<H;i++){
      string s; int h,b; cin >> s >> h >> b;
      T.push_back( vector<int>() ); Hit.push_back( h ); Blow.push_back( b );
      for(int j=0;j<L;j++) T[i].push_back( s[j]-'0' );
    }
    vector<int> ans;
    bool flag = true;
    sort(data.begin(),data.end());
    do {
      do {
        int pos[10];
        memset(pos,-1,sizeof(pos));
        for(int i=0;i<L;i++) pos[data[i]] = i;
        bool f = true;
        for(int i=0;i<H;i++){
          int c1,c2; c1 = c2 = 0;
          for(int j=0;j<L;j++){
            int p = pos[T[i][j]];
            if( p == -1 ) continue;
            else if( p == j ) c1++;
            else c2++;
            if( c1 > Hit[i] || c2 > Blow[i] ) break;
          }
          if( c1 != Hit[i] || c2 != Blow[i] ) f = false;
          if(!f)break;
        }
        if( f ) {
          if( ans.empty() ) 
            for(int i=0;i<L;i++) ans.push_back( data[i] );
          else
            flag = false;
        }
      } while( next_permutation( data.begin(), data.begin() + L ) );
      if( !flag ) break;
    } while( next_combination( data.begin(), data.begin() + L, data.end() ) );

    if( flag && !ans.empty() ){
      for(int i=0;i<L;i++ ) cout << ans[i];
      cout << endl;
    } else
      cout << "NO" << endl;
  }

}
