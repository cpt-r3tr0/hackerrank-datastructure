#include <iostream>
#include <vector>
#include <algorithm>

using namespace std ;

struct segment
{
    bool isleft ;
    int point ;
    bool isfielder ;
} ;
vector <segment> v (400010) ;
vector <segment> :: iterator it ;

bool cmpr ( segment & a , segment & b ){
    if ( a.point != b.point )
        return a.point < b.point ;
    if ( a.isleft != b.isleft )
        return a.isleft ;
    return ! ( a.isfielder ) ;
}

int main (){
    int n , m ;
    cin >> n >> m ;
    int counter = 0 ;
    for ( int i = 0 ; i < n ; i ++ ){
        int a , b;
        cin >> a >> b ;
        segment temp ;
        temp.isleft = true ;
        temp.point = a ;
        temp.isfielder = false ;
        v [ counter ++ ] = temp ;
        temp.isleft = false ;
        temp.point = b ;
        v [ counter ++ ] = temp ;
    }
    for ( int i = 0 ; i < m ; i ++ ){
        int a , b;
        cin >> a >> b ;
        segment temp ;
        temp.isleft = true ;
        temp.point = a ;
        temp.isfielder = true ;
        v [ counter ++ ] = temp ;
        temp.isleft = false ;
        temp.point = b ;
        v [ counter ++ ] = temp ;
    }
    it = v.begin () ;
    advance ( it , counter ) ;
    sort ( v.begin () , it , cmpr );
    int bat = 0 , field = 0 ;
    long long int ans = 0 ;
    for ( int i = 0 ; i < counter ; i ++ ){
        if ( v[i].isleft == true ){
            if ( v[i].isfielder ){
                ans += bat ;
                field ++ ;
            }
            else{
                ans += field ;
                bat ++ ;
            }
        }
        else
            (v[i].isfielder) ? field--:bat-- ;

    }
    cout << ans ;
    return 0 ;
}
