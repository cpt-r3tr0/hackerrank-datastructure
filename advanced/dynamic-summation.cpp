#include <bits/stdc++.h>

using namespace std;

typedef long long int LLI;
typedef vector<int> VI;
typedef pair<int, bool> PIB;

const int N_MODS = 5;
const int MOD[N_MODS] = {143601703, 235439621, 393965597, 523222925, 1010408256};

LLI modPow(LLI b, LLI e, int m) {
    LLI r = 1; b %= m;
    while (e) {
        if (e & 1) r = (r * b) % m;
        b = (b * b) % m;
        e >>= 1;
    }
    return r;
}

int gcd(int a, int b) {
    while (b){
        a %= b;
        swap(a, b);
    }
    return a;
}

int extGCD(int a, int b, int &x, int &y) {
    int nx, ny;
    x = ny = 1;
    y = nx = 0;

    while (b) {
        int q = a/b;
        a -= q*b; swap(a, b);
        x -= q*nx; swap(x, nx);
        y -= q*ny; swap(y, ny);
    }

    return a;
}

void combine(int &r1, int &m1, int r2, int m2) {
    int x, y; extGCD(m1, m2, x, y);

    r1 = r1*y*m2 + r2*x*m1;
    m1 *= m2;

    r1 %= m1;
    if (r1 < 0) r1 += m1;
}

struct segtreeSumMod {
    int n;
    VI mem[N_MODS], prop[N_MODS];

    segtreeSumMod(int n_) : n(n_) {
        for (int i = 0; i < N_MODS; ++i) {
            mem[i] = VI(2*n-3);
            prop[i] = VI(2*n-3);
        }
    }

    mutable int s, e;
    mutable int inc[N_MODS];

    void incRange(int s, int e, LLI a, LLI b, bool invert) {
        for (int i = 0; i < N_MODS; ++i) {
            LLI val = modPow(a, b, MOD[i]) + modPow(a+1, b, MOD[i]) + modPow(b+1, a, MOD[i]);
            inc[i] = (int) (val % MOD[i]);
        }

        if (invert) {
            this->s = 0; this->e = s; incRangeRec(0, n-2);
            this->s = e; this->e = n-1; incRangeRec(0, n-2);
        }
        else {
            this->s = s; this->e = e; incRangeRec(0, n-2);
        }
    }

    void incRangeRec(int lo, int hi) {
        int m = (lo + hi) / 2;
        if (lo == hi) m += n-2;

        LLI len = intLen(lo, hi);
        if (len) {
            if ((s <= lo) && (hi+1 <= e))
                incProps(m);
            else if (lo < hi) {
                incMems(m, len);
                incRangeRec(lo, m); incRangeRec(m+1, hi);
            }
        }
    }

    void incProps(int z) {
        for (int i = 0; i < N_MODS; ++i)
            prop[i][z] = (prop[i][z] + inc[i]) % MOD[i];
    }

    void incMems(int z, LLI mult) {
        for (int i = 0; i < N_MODS; ++i)
            mem[i][z] = (mem[i][z] + inc[i] * mult) % MOD[i];
    }

    VI sumRange(int s, int e, bool invert) const {
        for (int i = 0; i < N_MODS; ++i)
            inc[i] = 0;

        if (invert) {
            this->s = 0; this->e = s; sumRangeRec(0, n-2);
            this->s = e; this->e = n-1; sumRangeRec(0, n-2);
        }
        else {
            this->s = s; this->e = e; sumRangeRec(0, n-2);
        }

        return VI(inc, inc+N_MODS);
    }

    void sumRangeRec(int lo, int hi) const {
        int m = (lo + hi) / 2;
        if (lo == hi) m += n-2;

        LLI len = intLen(lo, hi);
        if (len) {
            if ((s <= lo) && (hi+1 <= e))
                addMems(m);
            else if (lo < hi) {
                sumRangeRec(lo, m); sumRangeRec(m+1, hi);
            }

            addProps(m, len);
        }
    }

    void addMems(int z) const {
        for (int i = 0; i < N_MODS; ++i)
            inc[i] = (inc[i] + mem[i][z]) % MOD[i];
    }

    void addProps(int z, LLI mult) const {
        for (int i = 0; i < N_MODS; ++i)
            inc[i] = (inc[i] + prop[i][z] * mult) % MOD[i];
    }

    LLI intLen(int lo, int hi) const {
        int p = max(s, lo), q = min(e-1, hi);
        return (p <= q) ? (q - p + 1) : 0;
    }
};

struct modTrees {
    int n;

    VI pos, end;
    vector<VI> children;
    segtreeSumMod stats;

    modTrees(int n_, const vector<VI> &g) : n(n_), pos(n_), end(n_), children(n_), stats(n_+1) { dfs(g); }

    int dfs(const vector<VI> &g, int v = 0, int cur = 0) {
        pos[v] = cur++;
        end[v] = pos[v] + 1;

        for (auto i : g[v])
            if (!end[i]) {
            cur = dfs(g, i, cur);
            end[v] = end[i];
            children[v].push_back(i);
        }

        return cur;
    }

    bool isAOutsideB(int a, int b) const {
        return (pos[a] < pos[b]) || (end[b] <= pos[a]);
    }

    int childPath(int start, int target) const {
        int lo = 0, hi = (int) children[start].size();
        while (hi-lo > 1) {
            int m = (lo + hi) / 2;
            int cm = children[start][m];
            if (pos[cm] > pos[target])
                hi = m;
            else
                lo = m;
        }
        return children[start][lo];
    }

    PIB subtreeRange(int r, int t) const {
        if (r == t)
            return PIB(0, false);
        if (isAOutsideB(r, t))
            return PIB(t, false);
        return PIB(childPath(t, r), true);
    }

    void update(int r, int t, LLI a, LLI b) {
        PIB z = subtreeRange(r, t);
        stats.incRange(pos[z.first], end[z.first], a, b, z.second);
    }

    int report(int r, int t, int m) const {
        PIB z = subtreeRange(r, t);

        VI res = stats.sumRange(pos[z.first], end[z.first], z.second);

        int ans = 0, mm = 1;
        for (int i = 0; i < N_MODS; ++i) {
            int g = gcd(MOD[i], m);
            if (g > 1)
                combine(ans, mm, res[i] % g, g);
        }

        return ans;
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n; cin >> n;

    vector<VI> g(n);
    for (int i = 0; i < n-1; ++i) {
        int x, y;
        cin >> x >> y;
        g[x-1].push_back(y-1);
        g[y-1].push_back(x-1);
    }

    modTrees solver(n, g);

    int q;
    cin >> q;
    while (q--) {
        char op;
        cin >> op;
        if (op == 'U') {
            int r, t; LLI a, b;
            cin >> r >> t >> a >> b;
            solver.update(r-1, t-1, a, b);
        }
        else {
            int r, t, m;
            cin >> r >> t >> m;
            cout << solver.report(r-1, t-1, m) << '\n';
        }
    }
}
