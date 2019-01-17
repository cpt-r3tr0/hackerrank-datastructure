#include <bits/stdc++.h>

using namespace std;
int *a;
int n;

void maxSlidingWindow(int A[], int n, int w, int B[]){
    deque<int> Q;
    for (int i = 0; i < w; i++){
        while (!Q.empty() && A[i] >= A[Q.back()])
            Q.pop_back();
        Q.push_back(i);
    }
    for (int i = w; i < n; i++) {
        B[i-w] = A[Q.front()];
        while (!Q.empty() && A[i] >= A[Q.back()])
            Q.pop_back();
        while (!Q.empty() && Q.front() <= i-w)
            Q.pop_front();
        Q.push_back(i);
    }
    B[n-w] = A[Q.front()];
}

int query(int d){
    int B[n-d+1];
    maxSlidingWindow(a,n,d,B) ;
    int ans = INT_MAX;
    for(int i=0;i<n-d+1;i++){
        if(ans > B[i] )
            ans = B[i];
    }
    return ans;
}


int main() {
    cin>>n;
    int q;
    cin>>q;
    a = new int[n];
    for(int i=0;i<n;i++)
        cin>>a[i];

    int d;
    for(int i=0;i<q;i++){
        cin>>d;
        cout<<query(d)<<endl;
    }
    return 0;
}
