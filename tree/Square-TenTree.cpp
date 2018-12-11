#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 1000 * 1000 + 5;
char L[N], R[N], M[N];
int n;

vector < pair<int,string> > split_prefix(char *t) {
    int len = 1;
    int lev = 0;
    int rg = n - 1;

    vector < pair<int,string> > res;
    while (rg >= 0) {
        int lf = max(0, rg - len + 1);
        int fnz = -1;
        for (int i = lf; i <= rg; ++i)
            if (t[i] != '0') {
                fnz = i;
                break;
            }
        if (fnz != -1)
            res.push_back(make_pair(lev, string(t + fnz, rg - fnz + 1)));
        len += len;
        if (lev == 0) len = 1;
        lev++;
        rg = lf - 1;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    scanf("%s%s", L, R);
    n = strlen(R);
    int m = strlen(L);
    for (int i = 0; i < n; ++i) {
        L[n - i - 1] = (m - i - 1 < 0 ? '0' : L[m - i - 1]);
        M[i] = '0';
    }
    for (int i = n - 1; i >= 0; --i) {
        if (L[i] != '0') {
            L[i]--;
            break;
        }
        L[i] = '9';
    }

    int lcp = 0;
    while (lcp < n && L[lcp] == R[lcp])
        ++lcp;

    vector < pair<int, string> > res, tmp;
    int rg = n - 1;
    int len = 1;
    int lev = 0;
    while (rg >= 0) {
        int lf = max(0, rg - len + 1);

        if (lf <= lcp) break;

        int fnz = -1;
        for (int i = lf; i <= rg; ++i) {
            M[i] = R[i];
            R[i] = '0';
        }

        rg = lf - 1;
        len += len;
        if (lev == 0) len = 1;
        lev++;
    }

    int rem = 0;
    for (int i = n - 1; i >= 0; --i) {
        R[i] += rem - L[i];
        rem = 0;
        if (R[i] < 0) {
            rem = -1;
            R[i] += 10;
        }
        R[i] += '0';
    }

    res = split_prefix(R);
    reverse(res.begin(), res.end());//The last thing left is to
    tmp = split_prefix(M);
    for (int i = 0; i < tmp.size(); ++i)
        res.push_back(tmp[i]);

    printf("%d\n", res.size());
    for (int i = 0; i < res.size(); ++i)
        printf("%d %s\n", res[i].first, res[i].second.c_str());
    return 0;
}
