#include<bits/stdc++.h>
using namespace std;

struct ConvexHull {
    using ll = long long;
    struct point {
        ll x, y, p=0, q=0;
        bool operator<(const point o) const {
            if(p*o.q!=o.p*q) return p*o.q>o.p*q;
            if(y!=o.y) return y<o.y;
            return x<o.x;
        }
    };
    vector<point> hull;

    inline ll ccw(point a, point b, point c) {
        point v1 = {b.x-a.x, b.y-a.y};
        point v2 = {c.x-a.x, c.y-a.y};
        return v1.x*v2.y-v2.x*v1.y;
    }

    inline ll ccw(point a, point b, point c, point d) {
        point v1 = {b.x-a.x, b.y-a.y};
        point v2 = {d.x-c.x, d.y-c.y};
        return v1.x*v2.y-v2.x*v1.y;
    }

    inline ll dist(point a, point b) {
        return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
    }

    inline ConvexHull(vector<point> v) {
        sort(v.begin(), v.end());

        for(int i=1;i<v.size();i++) {
            v[i].p = v[i].x-v[0].x;
            v[i].q = v[i].y-v[0].y;
        }
        sort(v.begin(), v.end());

        hull.clear();
        for(point cur:v) {
            while(hull.size()>=2 && ccw(hull[hull.size()-2], hull[hull.size()-1], cur)<=0) hull.pop_back();
            hull.push_back(cur);
        }
    }

    inline ll rotating_calipers() {
        ll ret=0, i=0, j=1;
        while(i<hull.size() && j<hull.size()) {
            ret = max(ret, dist(hull[i], hull[j]));
            if(ccw(hull[i], hull[(i+1)%hull.size()], hull[j], hull[(j+1)%hull.size()])>0) j++;
            else i++;
        }
        return ret;
    }
};