#include <bits/stdc++.h>

using namespace std;

/* 
	1. a line is represented in the fromat of y = m * x + c.
	2. Insert lines into the struct by the method insert(m, c)
	3. Get maximum value by at some x, by any of the lines by getMaxVal(ll x)
	4. Range of query for the method getMaxVal is limited from (-inf, +inf)
	5. Memory O(n)
	6. Amortized insertion time O(n log n)
	7. query time O(log n * log(maxx) )

	Tested : OK. Codechef - CYCLRACE
*/
#define X first
#define Y second

typedef long long ll;
const ll inf = (ll)1e16;
typedef pair<ll, ll> pll;

struct ConvexHullTrick{

	struct line{
		ll m, c; double leastX; // leastX means this line contributes from `leastX` in the convex hull
		bool operator < (const line& l) const {
			return m < l.m;
		}
		ll valueAt(ll x){
			return m * x + c;
		}
		double intersection(const line& l) const{
			if (l.m == m) return inf;
			return (double)(l.c - c) / (double)(m - l.m);
		}
	};

	set <line> hull;

	bool outside(set<line>::iterator it){
		if(it == hull.begin() || it == hull.end() || it == hull.find(*hull.rbegin())) return 0;
		auto it1 = ++it; --it;
		auto it2 = --it; ++it;
		return it->intersection(*it1) <= it->intersection(*it2);
	}

	void update(set<line>::iterator it){
		if(it == hull.begin()) return ;
		auto p = --it; ++it;
		double val = it -> intersection(*p);
		line tmp = {it->m, it->c, val};
		hull.erase(it);
		hull.insert(tmp);
	}

	void insert(ll m , ll c){ // insert line m*x+c
		line l = {m, c, -inf};
		auto it = hull.lower_bound(l);
		if(it != hull.end() && it->m == m){
			if(it -> c < c) hull.erase(it);
			else return ;
		}
		hull.insert(l), it = hull.find(l);
		if(outside(it)){
			hull.erase(it);
			return;
		}
		while(it != hull.begin() && outside(--it)){
			hull.erase(it);
			it = hull.find(l);
		}
		it = hull.find(l);
		while(it != hull.end() && it != hull.find(*hull.rbegin()) && outside(++it)){
			hull.erase(it);
			it = hull.find(l);
		}
		it = hull.find(l); 
		update(it);
		it = hull.find(l);
		
		if(it != hull.end()){
			++it;
			if(it != hull.end()) update(it);
		}
	}

	void print(){
		for(auto p : hull) cerr << "m = " << p.m << ", c = " << p.c << ", leastX = "<<p.leastX << "\n";
	}

	ll getMaxVal(ll x){
		ll l = 0, r = 1000000000, m; // set suitable value for r
		while(r > l){
			m = (l+r)/2;
			auto it = hull.lower_bound({m,0,0});
			if(it != hull.end() && it -> leastX <= x) l = m+1;
			else r = m;
		}
		auto it = hull.lower_bound({l, 0, 0});
		--it;
		return (it->m) * x + (it->c);
	}
};

struct query{
	int type, tm;
} queries[100100];

vector<pll> changes[100100];// time, speed

int main()
{
	ConvexHullTrick ch;
	int N, Q;
	scanf("%d %d", &N, &Q);
	for(int i = 0; i < Q; ++i){
		int tp, tm, idx, spd;
		scanf("%d %d", &tp, &tm);
		queries[i].type = tp;
		queries[i].tm = tm;
		if(tp == 1) { // change the speed
			scanf("%d %d", &idx, &spd);
			changes[idx].push_back({tm, spd});
		}
	}
	for(int i = 1; i <= N; ++i){
		ll pos = 0, vel = 0, pt = 0;
		for(pll p : changes[i]){
			pos += vel * (p.X - pt);
		    vel = p.Y;
	       	pt = p.X;
	 		ch.insert(vel, pos - vel * pt);		
		}
		// debug
		// ch.print();
	}
	for(int i = 0; i < Q; ++i) if(queries[i].type == 2){
		ll val = ch.getMaxVal(queries[i].tm);
		printf("%lld\n",val);
	}
	return 0;
}
