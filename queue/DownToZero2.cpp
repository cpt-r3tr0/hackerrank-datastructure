#include <bits/stdc++.h>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int test;
    cin >> test;
    while (test--){
        int n ;
        cin >> n ;
        int steps = 0;
        if (n==0){
            cout << 0 << endl;
            continue;
        }
        if (n==1){
            cout << 1 << endl;
            continue;
        }
        vector<int> dist(n+1,0);
        queue<int> q;
        q.push(n) ;
        dist[n] = 1 ;
        while (1){
            int element = q.front();
            q.pop();
            if(element == 2){
                cout << dist[2] + 1 << endl;
                break ;
            }
            if (dist[element-1] == 0 ){
                dist [element-1] = dist[element]+1;
                q.push(element-1);
            }
            for (int i=2; i*i<=element; i++){
                if (element%i == 0){
                    int maxfrac = element/i;
                    if (dist[maxfrac] == 0) dist [maxfrac] = dist[element] + 1, q.push(maxfrac);
                }
            }
        }
    }
    return 0;
}
