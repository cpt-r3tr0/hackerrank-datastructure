#include <bits/stdc++.h>
using namespace std;

int m, n;

const int mycount = 10000;
vector<int> prime_results;
vector<int> sieve(int n){
    set<int> primes;
    vector<int> vec;

    primes.insert(2);

    for(int i=3; i<=n ; i+=2)
        primes.insert(i);

    int p=*primes.begin();
    vec.push_back(p);
    primes.erase(p);

    int maxRoot = sqrt(*(primes.rbegin()));

    while(primes.size() > 0){
        if(p > maxRoot){
            while(primes.size() > 0){
                p=*primes.begin();
                vec.push_back(p);
                primes.erase(p);
            }
            break;
        }

        int i = p*p;
        int temp = (*(primes.rbegin()));

        while(i<=temp){
            primes.erase(i);
            i += p;
            i += p;
        }

        p=*primes.begin();
        vec.push_back(p);
        primes.erase(p);
    }

    return vec;
}
int a[100005];
vector<int> thearray[mycount];
void print1(int i){
    for (int j = 0; j < thearray[i].size(); j++)
                printf("%d\n", thearray[i][j]);
}

void print2(int i){
    for (int j = thearray[i].size() - 1; j >= 0;j--)
                printf("%d\n", thearray[i][j]);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int i,
        j,
        k,
        q,
        l;

    prime_results = sieve(mycount);
    scanf("%d %d", &n, &q);

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (i = 0; i < n; i++) {
        for (j = 0; j < q; j++) {
            k = prime_results[j];
            if (a[i] % k == 0) {
                thearray[j].push_back(a[i]);
                break;
            }
        }

        if (j == q)
            thearray[j].push_back(a[i]);
    }

    for (i = 0; i < q; i++)
        ((i & 1)==0) ? print1(i): print2(i) ;

    (q & 1) ? print1(i): print2(i) ;

    return 0;
}
