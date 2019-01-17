#include <bits/stdc++.h>

using namespace std;


int P[100005];
queue<int> q;
int day[100005];
int pre[100005];
int nex[100005];
bool done[100005];

int main(){
 /* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int N;
	scanf("%d", &N);
    for(int i = 0; i < N ; ++i)
		scanf("%d", P+i);
	P[N]=-1;
    for(int i = N-1; i>=1; --i){
		pre[i]=i-1;
		nex[i]=i+1;
		if(P[i] > P[i-1]){
			day[i]=1;
			q.push(i);
		}
	}
	int ans=0;
	while(!q.empty()){
		int cur=q.front();
		q.pop();
		if(done[cur])
			continue;
		done[cur]=1;
		ans=day[cur];
		pre[nex[cur]]=pre[cur];
		nex[pre[cur]]=nex[cur];
		if(P[nex[cur]] > P[pre[cur]]){
			day[nex[cur]]=day[cur]+1;
			q.push(nex[cur]);
		}
	}
	printf("%d\n", ans);
}
