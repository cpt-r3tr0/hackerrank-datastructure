#include <bits/stdc++.h>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N;
    cin >> N;

    vector<int> a(N);
    for (int i = 0; i < N; ++i)
        cin >> a.at(i);
    int max = 0;
    int top;
    int top_area;

    int i = 0;
    stack<int> s;
    while (i < N) {
        if (s.empty() || a.at(s.top()) <= a.at(i)) {
            s.push(i);
            i++;
        } else {
            top = s.top();
            s.pop();
            top_area = (s.empty()) ? a.at(top) * i : a.at(top) * (i - s.top() - 1) ;

            if (max < top_area) max = top_area;
        }
    }

    while(!s.empty()) {
        top = s.top();
        s.pop();

        top_area = (s.empty()) ? a.at(top) * i : a.at(top) * (i - s.top() - 1) ;

        if (max < top_area)
            max = top_area;
    }

    cout << max << endl;

    return 0;
}
