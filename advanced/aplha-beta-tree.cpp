#include <iostream>
#include <algorithm>
using namespace std;

long long mod = 1000000009;

struct data {
    long long ways;
    long long sum[2];

    data operator+(const data & r) const {
        data res;
        res.ways = (ways + r.ways) % mod;
        res.sum[0] = (sum[0] + r.sum[0]) % mod;
        res.sum[1] = (sum[1] + r.sum[1]) % mod;
        return res;
    }
};

data merge(const data & l, const data & r) {
    data res;
    res.sum[0] = (l.sum[0] * r.ways + r.sum[0] * l.ways) % mod;
    res.sum[1] = (l.sum[1] * r.ways + r.sum[1] * l.ways) % mod;
    res.ways = (l.ways * r.ways) % mod;
    return res;
}

data dp[200][200];

long long a[200];

data & solve(int l, int r) {
    if (dp[l][r].ways) {
        return dp[l][r];
    }

    data & res = dp[l][r];

    if (l == r) {
        res.ways = 1;
        return res;
    }

    for (int i = l; i < r; ++i) {
        data tmp = merge(solve(l, i), solve(i + 1, r));
        swap(tmp.sum[0], tmp.sum[1]);
        tmp.sum[0] = (tmp.sum[0] + tmp.ways * a[i]);
        res = res + tmp;
    }
    return res;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;

    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j)
                dp[i][j].ways = dp[i][j].sum[0] = dp[i][j].sum[1] = 0;
        }
        long long alpha, beta;
        scanf("%lld%lld", &alpha, &beta);

        for (int i = 0; i < n; ++i)
            scanf("%lld", a + i);
        sort(a, a + n);

        data & ans = solve(0, n);
        long long v = ans.sum[0] * alpha - ans.sum[1] * beta;
        v %= mod;
        if (v < 0)
            v += mod;
        printf("%lld\n", v);
    }


    return 0;
}
