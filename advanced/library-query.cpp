#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <assert.h>
using namespace std;

const int MAXN = 10002;
int a[MAXN], n;
int seglen, segcnt;
vector<int> segs[MAXN];

inline int get_seg_id(int id) {
    return id / seglen;
}

int solve(int x, int y, int k) {
    int lo = 1, hi = 1000;
    int ans = 0;
    int start_seg = get_seg_id(x);
    int end_seg = get_seg_id(y);
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int cnt = 0;
        if (start_seg == end_seg) {
            for (int i = x ; i <= y ; ++i)
                if (a[i] < mid) ++cnt;
        } else {
            for (int i = x ; i < n && i < (start_seg + 1) * seglen ; ++i)
                if (a[i] < mid) ++cnt;
            for (int i = end_seg * seglen ; i <= y ; ++i)
                if (a[i] < mid) ++cnt;
            for (int i = start_seg + 1 ; i < end_seg ; ++i)
                cnt += lower_bound(segs[i].begin(), segs[i].end(), mid) - segs[i].begin();
        }
        if (cnt < k) {
            if (mid > ans) ans = mid;
            lo = mid + 1;
        } else hi = mid - 1;
    }
    return ans;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int T, nq;
    scanf("%d", &T);
    while (T--) {
        scanf("%d",&n);
        seglen = max(1, (int)sqrt(n));
        segcnt = (n + seglen - 1) / seglen;
        for (int i = 0 ; i < segcnt ; ++i)
            segs[i].clear();
        for (int i = 0 ; i < n ; ++i) {
            scanf("%d",&a[i]);
            int seg_id = get_seg_id(i);
            segs[seg_id].push_back(a[i]);
        }
        for (int i = 0 ; i < segcnt ; ++i)
            sort(segs[i].begin(), segs[i].end());
        scanf("%d",&nq);
        while (nq--) {
            int type, x, y, k;
            scanf("%d", &type);
            if (type == 1) {
                scanf("%d%d", &x, &k);
                --x;
                int sid = get_seg_id(x);
                int flg;
                if (a[x] > k) flg = 0;
                else flg = 1;
                vector<int>::iterator itr = lower_bound(segs[sid].begin(), segs[sid].end(), a[x]);
                assert(*itr == a[x]);
                int idx = itr - segs[sid].begin();
                *itr = k;
                if (flg == 0) {
                    for (int i = idx ; i >= 1 && segs[sid][i] < segs[sid][i-1] ; --i) {
                        swap(segs[sid][i], segs[sid][i-1]);
                    }
                } else {
                    for (int i = idx ; i + 1 < segs[sid].size() && segs[sid][i] > segs[sid][i+1] ; ++i) {
                        swap(segs[sid][i], segs[sid][i+1]);
                    }
                }
                a[x] = k;
            } else {
                scanf("%d%d%d", &x, &y, &k);
                printf("%d\n", solve(x-1, y-1, k));
            }
        }
    }
    return 0;
}
