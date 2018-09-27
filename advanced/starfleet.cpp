#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <assert.h>
using namespace std;

typedef long long int64;

template<typename T> struct skip {};
template<typename T> istream& operator>>(istream& is, const skip<T> s){
	T t; is >> t;
	return is;
}

typedef pair< int, int > par;

const int
	MAXN = 1 << 17;

int N, Q, S;
int Y, F;
struct query{
	int lo, hi, id;
};

vector< query > queries;
int ys[MAXN];
int fs[MAXN];
int answer[MAXN];
par seq[MAXN];

int values[MAXN];

bool operator < (const query& a, const query & b){
	int ax = a.lo / S;
	int bx = b.lo / S;
	if (ax != bx) return ax < bx;
	return a.hi < b.hi;
}

struct promoter{
	int cnt[MAXN];
	int pos[MAXN];
	int curMax;

	promoter(int n){
		cnt[0] = n;
		curMax = 0;
	}

	void promote(int x){
		--cnt[ pos[x] ];
		++cnt[ ++pos[x] ];
		curMax = max(curMax, pos[x]);
	}

	void demote(int x){
		--cnt[ pos[x] ];
		++cnt[ --pos[x] ];
		if (cnt[curMax] == 0)
			--curMax;
	}

	int getMax(){
		return curMax;
    }


} prom(MAXN);

int main(){
        /* Enter your code here. Read input from STDIN. Print output to STDOUT */
	cin >> N >> Q >> skip<int>();

    for(int i = 0; i< N; ++i){
		int y, f;
		cin >> skip<int>() >> y >> f;
		ys[i] = y;
		fs[i] = f;
		seq[i] = make_pair(y, f);
	}

	sort(ys, ys + N);
	Y = N;

	sort(fs, fs + N);
	F = unique(fs, fs + N) - fs;

	for (int i = 0; i < N; ++i)
		seq[i].second = lower_bound(fs, fs + F, seq[i].second) - fs;

	sort(seq, seq + N);

	for (int i = 0; i < N; ++i)
		values[i] = seq[i].second;

	for (int i = 0; i < Q; ++i){
		int lo, hi;
		cin >> hi >> lo >> skip<int>();
		lo = lower_bound(ys, ys + Y, lo) - ys;
		hi = upper_bound(ys, ys + Y, hi) - ys - 1;
		if (lo <= hi)
			queries.push_back((query){lo, hi, i});
	}

	S = max(10, (int)sqrt(N));

	sort(queries.begin(),queries.end());

	assert(Q > 0);

	int lo = queries[0].lo;
	int hi = lo - 1;

	for (int i = 0; i < queries.size(); ++i){
		while (lo < queries[i].lo){
			prom.demote(values[lo]);
			lo++;
		}

		while (lo > queries[i].lo){
			--lo;
			prom.promote(values[lo]);
		}

		while (hi > queries[i].hi){
			prom.demote(values[hi]);
			hi--;
		}

		while (hi < queries[i].hi){
			hi++;
			prom.promote(values[hi]);
		}

		answer[ queries[i].id ] = prom.getMax();
	}

	for (int i = 0; i < Q; ++i)
		cout << answer[i] << endl;

	return 0;
}
