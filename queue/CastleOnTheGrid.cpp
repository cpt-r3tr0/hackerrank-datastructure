#include <bits/stdc++.h>
using namespace std;

vector<long long int> g[1000007];
long long int dis[10001];
bool visited[10001] ;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
	long long int n ;
	cin >> n ;
	string temp ;
	vector<string> v;
    queue<long long int> q;
	for(long long int i=0;i<n;i++){
		cin >> temp ;
		v.push_back(temp) ;
	}
	long long int a,b,c,d,start,end,next,front;
	cin >> a >> b >> c >> d ;
	for(long long int i=0;i<n;i++){
		for(long long int j=0;j<n;j++){
			if(v[i][j]=='.'){
				start = i*n+j;
				for(long long int k=i-1;k>=0;k--){
					if(v[k][j]=='.') end = n*k+j, g[start].push_back(end);
                    else break ;
				}
				for(long long int k=i+1;k<n;k++){
                    if(v[k][j]=='.') end = k*n + j, g[start].push_back(end);
                    else break;
                }
                for(long long int k=j-1;k>=0;k--){
                    if(v[i][k] == '.') end = i*n + k, g[start].push_back(end);
                    else break;
                }
                for(long long int k=j+1;k<n;k++){
                    if(v[i][k]=='.') end = i*n + k, g[start].push_back(end);
                    else break;
                }
			}
		}
	}
	start = a*n+b;
    q.push(start);
    visited[start] = 1;
    while(q.empty()==0){
        front = q.front();
        q.pop();
        for(long long int i=0;i<g[front].size();i++){
            next = g[front][i];
            if(visited[next]==0){
                visited[next] = 1;
                dis[next] = dis[front]+1;
                q.push(next);
            }
        }
    }
    cout<<dis[c*n+d] ;
	return 0 ;
}
