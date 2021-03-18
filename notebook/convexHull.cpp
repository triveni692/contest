// Code Tested on condeforces.com/contest/575/problem/E
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;
LL MOD = 1000000007;

struct point{
	int x, y;
	bool operator < (const point& p) const{
		if(p.x == x) return y < p.y;
		return x < p.x;
	}
	bool operator == (const point & p) const{
		return x == p.x && y == p.y;
	}
};

point a0;

bool cmp(const point & a, const point& b){
	LL x = (a.y - a0.y) * 1LL * (b.x - a0.x);
	LL y = (b.y - a0.y) * 1LL * (a.x - a0.x);
	if(x == y) return a.x + a.y < b.x + b.y;
	return x < y;
}

LL area(const point& a, const point& b, const point& c){
	LL ar = a.x * 1LL * b.y - b.x * 1LL * a.y;
	ar += b.x * 1LL * c.y - c.x * 1LL * b.y;
	ar += c.x * 1LL * a.y - a.x * 1LL * c.y;
	return ar;
}

// vector<points> will be changed, dont send empty vector<>
void getConvexHull(vector<point> & pts, vector<point> & hull){
	sort(pts.begin(), pts.end());
	pts.resize(unique(pts.begin(), pts.end()) - pts.begin());
	int n = pts.size();
	a0 = pts.front();
	sort(pts.begin() + 1, pts.end(), cmp);
	hull.push_back(pts[0]);
	pts.push_back(a0);
	for(int i = 1; i <= n; ++i){
		while(hull.size() > 1){
			int h = hull.size();
			if(area(hull[h-2], hull[h-1], pts[i]) <= 0) hull.pop_back();
			else break;
		}
		hull.push_back(pts[i]);
	}
	pts.pop_back();
	hull.pop_back();
	return ;
}

int main()
{
	vector<point> pts;
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i){
		int x, y;
		cin >> x >> y;
		pts.push_back({x, y});
	}
	vector<point> hull;
	getConvexHull(pts, hull); // Note that vector `pts` will be changes completely
	int h = hull.size();
	cout << h << "\n";
	for(point & p: hull){
		cout << p.x << " " << p.y <<"\n";
	}

	return 0;
}

