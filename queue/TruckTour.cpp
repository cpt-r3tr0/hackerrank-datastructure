#include <bits/stdc++.h>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N, i, j, k, petro, dis;
    long long total = 0;
    cin >> N;
    vector<int> a(N);
    for (i = 0; i < N; i++) {
        cin >> petro >> dis;
        a[i] = petro - dis;
        total += a[i];
    }
    long long sum;
    bool found;
    for (i = 0; i < N; i++) {
        if (a[i] < 0) {
            continue;
        }
        k = i;
        sum = 0;
        found = true;
        for (j = 0; j < N; j++) {
            sum += a[k%N];
            k++;
            if (sum < 0) {
                found = false;
                break;
            }
        }
        if (found) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}
