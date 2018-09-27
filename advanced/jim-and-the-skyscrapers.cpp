#include <iostream>
#include <algorithm>
using namespace std;

int N;
int H[300100];
pair<int, int> order[300100];

bool cmp(pair<int, int> a, pair<int, int> b){
    if(a.first!=b.first)
        return a.first>b.first;
    return a.second<b.second;
}

int bit[300100];

void add(int x){
    for(; x<=300010; x+=x&-x)
        bit[x]++;
}

int sum(int x){
    int s=0;
    for(; x>0; x-=x&-x)
        s+=bit[x];
    return s;
}

int main(){
        /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    scanf("%d", &N);
    for(int i=1; i<=N; i++)
        scanf("%d", H+i), order[i]=make_pair(H[i], i);
    sort(order+1, order+1+N, cmp);
    int cur=1000001;
    long long cnt=0;
    long long ans=0;
    int csum=0;
    for(int i=1; i<=N; i++){
        if(order[i].first!=cur){
            cur=order[i].first;
            cnt=0;
            csum=sum(order[i].second);
        }
        int nsum=sum(order[i].second);
        if(csum!=nsum)
            csum=nsum, cnt=0;
        add(order[i].second);
        csum++;
        ans+=cnt;
        cnt++;
    }
    printf("%lld\n", ans*2);
    return 0;
}
