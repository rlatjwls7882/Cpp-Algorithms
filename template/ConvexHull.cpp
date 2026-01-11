#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct ConvexHull {
    struct point {
        ll x, y, p=0, q=0;
        bool operator<(const point &o) const {
            if(p*o.q!=o.p*q) return p*o.q>o.p*q;
            if(p*p+q*q!=o.p*o.p+o.q*o.q) return p*p+q*q<o.p*o.p+o.q*o.q;
            if(y!=o.y) return y<o.y;
            return x<o.x;
        }
        bool operator==(const point &o) const {
            return x==o.x && y==o.y;
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

    inline ll triArea(point a, point b, point c) { // area*2
        return a.x*b.y+b.x*c.y+c.x*a.y-a.x*c.y-b.x*a.y-c.x*b.y;
    }

    inline ll area() { // area*2
        ll ret=0;
        for(int i=1;i<hull.size()-1;i++) ret += triArea(hull[0], hull[i], hull[i+1]);
        return ret;
    }

    inline void angleSort(vector<point> &v) {
        for(int i=0;i<v.size();i++) v[i].p=v[i].q=0;
        sort(v.begin(), v.end());

        for(int i=1;i<v.size();i++) {
            v[i].p = v[i].x-v[0].x;
            v[i].q = v[i].y-v[0].y;
        }
        sort(v.begin(), v.end());

        int revIdx=v.size()-1;
        while(revIdx>1 && ccw(v[0], v[revIdx-1], v[revIdx])==0) revIdx--;
        reverse(v.begin()+revIdx, v.end());
    }

    inline ConvexHull(vector<point> &v) {
        for(int i=0;i<v.size();i++) v[i].p=v[i].q=0;
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

    inline bool inHull(point &p) {
        if(ccw(hull[0], hull[1], p)<0) return false;
        if(ccw(hull[0], hull[hull.size()-1], p)>0) return false;

        int l=1, r=hull.size()-2;
        while(l<r) {
            int m = l+r+1>>1;
            if(ccw(hull[0], hull[m], p)>0) l=m;
            else r=m-1;
        }
        return ccw(hull[l], hull[l+1], p)>=0;
    }

    inline ll rotatingCalipers() {
        ll ret=0, i=0, j=1;
        while(i<hull.size() && j<hull.size()) {
            ret = max(ret, dist(hull[i], hull[j]));
            if(ccw(hull[i], hull[(i+1)%hull.size()], hull[j], hull[(j+1)%hull.size()])>0) j++;
            else i++;
        }
        return ret;
    }
};