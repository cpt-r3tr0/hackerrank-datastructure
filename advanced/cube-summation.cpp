#include <iostream>

using namespace std;
const int N = 102;
long long bit[N][N][N];

long long que(int x, int y, int z)
{
    long long ret = 0;
    for(int i = x; i >= 0; i = (i&(i+1))-1)
        for(int j = y; j >= 0; j = (j&(j+1))-1)
        for(int k = z; k >= 0; k = (k&(k+1))-1)
        ret += bit[i][j][k];
        return ret;
}

int main(){
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t; cin >> t;
    while(t--){
        int n, m; cin >> n >> m;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
            for(int k = 0; k < N; ++k)
            bit[i][j][k] = 0;
            while(m--){
            string a; cin >> a;
            if(a == "UPDATE"){
                int x, y, z; cin >> x >> y >> z;
                long long val; cin >> val;
                long long cur;
                {
                    long long x1 = x, y1 = y, z1 = z;
                    long long x2 = x, y2 = y, z2 = z;
                    cur = que(x2, y2, z2);
                    cur -= (x1 == 0) ? 0 : que(x1-1, y2, z2);
                    cur -= (y1 == 0) ? 0 : que(x2, y1-1, z2);
                    cur -= (z1 == 0) ? 0 : que(x2, y2, z1-1);
                    cur += (x1 == 0 or y1 == 0) ? 0 : que(x1-1, y1-1, z2);
                    cur += (x1 == 0 or z1 == 0) ? 0 : que(x1-1, y2, z1-1);
                    cur += (y1 == 0 or z1 == 0) ? 0 : que(x2, y1-1, z1-1);
                    cur -= (x1 == 0 or y1 == 0 or z1 == 0) ? 0 : que(x1-1, y1-1, z1-1);
                }

                val = val - cur;
                for(int i = x; i < N; i |= (i+1))
                    for(int j = y; j < N; j |= (j+1))
                    for(int k = z; k < N; k |= (k+1))
                    bit[i][j][k] += val;
                    }
            else
            {
                int x1, y1, z1; cin >> x1 >> y1 >> z1;
                int x2, y2, z2; cin >> x2 >> y2 >> z2;

                long long ret = que(x2, y2, z2);
                ret -= (x1 == 0) ? 0 : que(x1-1, y2, z2);
                ret -= (y1 == 0) ? 0 : que(x2, y1-1, z2);
                ret -= (z1 == 0) ? 0 : que(x2, y2, z1-1);
                ret += (x1 == 0 or y1 == 0) ? 0 : que(x1-1, y1-1, z2);
                ret += (x1 == 0 or z1 == 0) ? 0 : que(x1-1, y2, z1-1);
                ret += (y1 == 0 or z1 == 0) ? 0 : que(x2, y1-1, z1-1);
                ret -= (x1 == 0 or y1 == 0 or z1 == 0) ? 0 : que(x1-1, y1-1, z1-1);

                cout << ret << '\n';
            }
        }
    }
    return 0;
}
