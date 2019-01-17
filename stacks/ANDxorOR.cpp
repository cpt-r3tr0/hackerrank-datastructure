#include <bits/stdc++.h>
using namespace std;

int height[1000005];
int leftmin[1000005];
int rightmin[1000005];
int N;

int evaluate(int Ax, int Bx){
    return (((Ax & Bx)^(Ax | Bx))|(Ax ^ Bx));
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int temp,area=0;
    stack<int> stack1;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>height[i];
    }
    //stack1.push(0);
    temp = 0;
    for(int i=0;i<N;i++){
        while(!stack1.empty()){
            temp = stack1.top();
            if(height[temp]>height[i]){
                stack1.pop();
                rightmin[temp] = i;
            }
            else break;
        }
        stack1.push(i);
    }
    while(!stack1.empty()){
        temp = stack1.top();
        stack1.pop();
        rightmin[temp] = N;
    }
    temp = N-1;
    for(int i=N-1;i>=0;i--){
        while(!stack1.empty()){
            temp = stack1.top();
            if(height[temp]>height[i]){
                stack1.pop();
                leftmin[temp] = i;
            }
            else break;
        }
        stack1.push(i);
    }
    while(!stack1.empty()){
        temp = stack1.top();
        stack1.pop();
        leftmin[temp] = -1;
    }
    for(int i=0;i<N;i++){
        temp = evaluate(height[i],height[rightmin[i]]);
        if(height[rightmin[i]]>0 && temp>area)area=temp;
    }
    for(int i=0;i<N;i++){
        temp = evaluate(height[i],height[leftmin[i]]);
        if(height[leftmin[i]]>0 && temp>area )area=temp;
    }
    cout<<area;
    return 0;
}
