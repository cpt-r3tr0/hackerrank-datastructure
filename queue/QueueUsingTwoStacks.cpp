#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    cin >> n;
    vector<int> v;

    for (int i=0; i < n; i++)
    {
        int q, num;
        cin >> q;
        switch(q) {
            case 1:
             cin >> num;
             v.push_back(num);
             break;
            case 2:
              v.erase(v.begin());
              break;
            case 3:
              num = v.front();
              cout << num << endl;
              break;

        }

    }
    return 0;
}
