#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef long long LL;

LL L[100005], R[100005];
int A[100005];

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N;
    cin>>N;
    for(int i=0; i<N;i++)
        cin>>A[i];
    stack<int> mys;
    mys.push(0);
    for(int i=1; i<N;i++){
        while(!mys.empty() and A[mys.top()]<=A[i]) mys.pop();
        if(!mys.empty())
            L[i] = 1 + mys.top();
        mys.push(i);
    }
    while(!mys.empty())mys.pop();
    mys.push(N-1);
    for(int i = N-2; i>=0; i--)  {
        while(!mys.empty() and A[mys.top()]<=A[i]) mys.pop();
        if(!mys.empty())
            R[i] = 1 + mys.top();
        mys.push(i);
    }
    LL ans  = 0;
    for(int i=0; i<N;i++)
        ans = max(ans,L[i]*R[i]);
    cout<<ans<<endl;

    return 0;
}
