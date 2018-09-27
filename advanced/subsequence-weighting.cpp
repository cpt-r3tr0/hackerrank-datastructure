#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>
using namespace std;

typedef long long ll;



ll Tree[800000];
void updateTree(int b, int e, int p, ll  val, int idx=1) {
	if(p < b || p > e) return ;
	if(p == b && p == e){
		Tree[idx] = max(Tree[idx],val);
		return ;
	}
	int mid = (b+e)/2;
	int lt = (idx<<1);
	int rt = ((idx<<1)+1);
	updateTree(b, mid, p, val, lt);
	updateTree(mid+1, e, p, val, rt);
	Tree[idx] = max(Tree[lt], Tree[rt]);
	return ;
}
ll query(int b,int e,int start,int end,int node){
	if(e<start || b>end)return 0;
	if(b<=start && e>=end)return Tree[node];
	int mid=(start+end)>>1;
	return max(query(b,e,start,mid,node*2),query(b,e,mid+1,end,node*2+1));
}
ll input[200000];
ll w[200000];
map<ll,int>m;
set<ll>s;
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int test;
    cin >> test;
    while(test--){
		m.clear();
        s.clear();
		s.empty();

        memset(Tree,0,sizeof Tree);

        int n;
        cin>> n;

        for(int i=0;i<n;i++)
            scanf("%lld",&input[i]), s.insert(input[i]);

        for(int i=0;i<n;i++)
			scanf("%lld",&w[i]);
		int in=1;
		set<ll>::iterator it;
		for(it=s.begin();it!=s.end();it++){
			m[*it]=in;
			in++;
		}in--;
		ll ans=0;
		for(int i=0;i<n;i++){
			int mapped=m[input[i]];
			if(mapped==1){
				updateTree(1,in,mapped,w[i],1);
				ans=max(ans,w[i]);
			}
			else{
				ll get=query(1,mapped-1,1,in,1);
				ans=max(ans,get+w[i]);
				updateTree(1,in,mapped,w[i]+get,1);
			}
		}
		cout<<ans<<endl;
	}
    return  0;
}
