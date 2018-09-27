#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>
#include <vector>

using namespace std;

typedef long long  LL;
LL dist[201000], n;
int cnt[201000];

void add_dist(int pos, int v){
	pos++;

	while(pos <= n)
		dist[pos] += v,
		pos += pos & -pos;
}

LL  sum_upto_dist(int pos){
	LL  ans = 0;
	pos++;

	while(pos > 0)
		ans += dist[pos],
		pos -= pos & -pos;

	return ans;
}

void add_city(int pos){
	pos++;

	while(pos <= n)
		cnt[pos]++,
		pos += pos & -pos;
}

int count_upto(int pos){
	pos++;
	int ans = 0;

	while(pos > 0)
		ans += cnt[pos],
		pos -= pos & -pos;
	return ans;
}

#define MOD 1000000007
int main(){
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t, ds_index[201000];
	cin >> t;
	while(t--){
		memset(dist, 0, sizeof(dist));
		memset(cnt, 0, sizeof(cnt));

		int c;
		cin >> c;

		n = c + 10;

		vector<int> distance, people;
		for(int i = 0; i < c; i++){
			int x;
			cin >> x;
			distance.push_back(x);
		}

		for(int i = 0; i < c; i++){
			int x;
			cin >> x;
			people.push_back(x);
		}

		vector< pair< int, int > > vc;

		vector< pair< int, int > > vp;

		vector< pair< int, int > > vd;

		for(int i = 0; i < c; i++){
			vp.push_back(make_pair(people[i], i));
			vd.push_back(make_pair(distance[i], i));
			vc.push_back(make_pair(people[i], distance[i]));
		}


		sort(vp.begin(),vp.end());
		sort(vd.begin(), vd.end());

		for(int i = 0; i < c; i++)
			ds_index[vd[i].second] = i;

		LL  ans = 0;
		for(int i = 0; i < c; i++){
            int pos = ds_index[vp[i].second];
			LL  sum_added_before = sum_upto_dist(pos);
			int cities_before = count_upto(pos);
			LL  sum_added_after = sum_upto_dist(n-1) - sum_added_before;
			int cities_after = count_upto(n-1) - cities_before;
			LL  tot_dist = 0;

			if(cities_before)
				tot_dist = (((LL )vc[vp[i].second].second)*(cities_before) - sum_added_before) % MOD;

			if(cities_after)
				tot_dist += (sum_added_after - ((LL )vc[vp[i].second].second)*(cities_after)) % MOD;

			LL  tot_cable = ((tot_dist % MOD) * (vp[i].first % MOD)) % MOD;
			ans += tot_cable;
			ans %= MOD;
			add_dist(pos, vc[vp[i].second].second);
			add_city(pos);
		}

		cout << ans % MOD << endl;

	}
}
