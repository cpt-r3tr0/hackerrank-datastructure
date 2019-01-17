#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    long N;
    cin>>N;
    int x,y,k=0,i,max;
    int a[100000];
    for(i=0;i<N;i++){
        cin>>x;
        if(x==1){
            cin>>y;
            a[k]=y;
            k++;
            if(y>max)
                max=y;
            }
        if(x==2){
            if(a[--k]==max){
                max=0;
                for(int z=0;z<k;z++){
                    if(a[z]>max)
                        max=a[z];
                }
                a[k]=0;
            }
        }
        if(x==3)
               cout<<max<<endl;
    }
    return 0;
}
