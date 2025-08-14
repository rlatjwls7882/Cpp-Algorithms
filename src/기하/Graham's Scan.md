## Graham's Scan (Convex Hull)
기준점을 잡아 점들을 각도로 정렬한 후, 스택을 이용해 볼록 껍질의 방향성을 유지하지 않는 점을 제거하며 볼록 껍질을 찾는 알고리즘

시간복잡도 : O(NlogN)

![Graham's scan Animation](https://upload.wikimedia.org/wikipedia/commons/7/71/GrahamScanDemo.gif)

[연습 문제(백준 1708번)](https://www.acmicpc.net/problem/1708)

``` c++
/** https://www.acmicpc.net/problem/1708 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct pos {
    ll x, y;
    ll p=0, q=0; // 기준점으로부터의 상대 위치
    bool operator<(const pos b) const {
        if(p*b.q!=q*b.p) return p*b.q > q*b.p;
        if(y!=b.y) return y < b.y;
        return x < b.x;
    }
};

ll ccw(pos a, pos b, pos c) {
    pos vec1 = {b.x-a.x, b.y-a.y};
    pos vec2 = {c.x-a.x, c.y-a.y};
    return vec1.x*vec2.y - vec1.y*vec2.x;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    /** 
     * 모든 점들 입력
     * 그 후 y가 가장 작고, x가 가장 작은 점을 찾기 위해 정렬
     */
    vector<pos> v(n);
    for(int i=0;i<n;i++) cin >> v[i].x >> v[i].y;
    sort(v.begin(), v.end());

    /** 
     * y가 가장 작고 x가 가장 작은 점을 기준점으로 삼고, 각 점들의 상대 위치를 마킹
     * 기준점을 기준으로 시계 반대 방향으로 정렬
     */
    for(int i=0;i<n;i++) {
        v[i].p = v[i].x-v[0].x;
        v[i].q = v[i].y-v[0].y;
    }
    sort(v.begin(), v.end());

    /** 
     * Graham's scan
     * 점들이 한 방향으로만 돌도록 선택
     * 이 풀이에서는 점들을 시계 반대 방향으로 정렬했으니, 각 점들이 순서대로 시계 반대방향(ccw>0)이 되도록 선택
     */
    vector<pos> stk;
    for(int i=0;i<n;i++) {
        while(stk.size()>=2 && ccw(stk[stk.size()-2], stk[stk.size()-1], v[i])<=0) stk.pop_back();
        stk.push_back(v[i]);
    }
    cout << stk.size();
}
```
