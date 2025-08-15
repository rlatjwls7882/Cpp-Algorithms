## Rotating Calipers (회전하는 캘리퍼스)
볼록 껍질에서 모든 점 쌍 중 가장 먼 두 점 등을 O(N)에 찾는 알고리즘

시간복잡도 : O(NlogN) (그라함 스캔 O(NlogN), 회전하는 캘리퍼스 O(N))

![rotating calipers](https://www-cgrl.cs.mcgill.ca/~godfried/research/calipers.gif)

[연습 문제 (백준 10254번)](https://www.acmicpc.net/problem/10254)

``` c++
/** https://www.acmicpc.net/problem/10254 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct pos {
    ll x, y, p=0, q=0;
    bool operator<(const pos o) const {
        if(p*o.q!=q*o.p) return p*o.q > q*o.p;
        if(y!=o.y) return y < o.y;
        return x < o.x;
    }
};

ll ccw(pos a, pos b, pos c) {
    pos vec1 = {b.x-a.x, b.y-a.y};
    pos vec2 = {c.x-b.x, c.y-b.y};
    return vec1.x*vec2.y - vec1.y*vec2.x;
}

ll ccw(pos a, pos b, pos c, pos d) {
    pos vec1 = {b.x-a.x, b.y-a.y};
    pos vec2 = {d.x-c.x, d.y-c.y};
    return vec1.x*vec2.y - vec1.y*vec2.x;
}

vector<pos> graham_Scan() {
    int n; cin >> n;
    vector<pos> v(n);
    for(int i=0;i<n;i++) cin >> v[i].x >> v[i].y;
    sort(v.begin(), v.end());

    for(int i=1;i<n;i++) {
        v[i].p = v[i].x - v[0].x;
        v[i].q = v[i].y - v[0].y;
    }
    sort(v.begin(), v.end());

    vector<pos> stk;
    for(int i=0;i<n;i++) {
        while(stk.size()>=2 && ccw(stk[stk.size()-2], stk[stk.size()-1], v[i])<=0) stk.pop_back();
        stk.push_back(v[i]);
    }
    return stk;
}

ll dist(pos a, pos b) {
    return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
}

/** 
 * 회전하는 캘리퍼스 알고리즘
 * - 그라함 스캔으로 볼록 껍질을 찾은 후 시작
 * 
 * - 가장 먼 두 점은 i -> i+1 벡터와 j -> j+1 벡터가 반시계방향일 때 j에 1 증가시킴 (그라함 스캔을 반시계방향으로 했기 때문)
 * - - 반시계 방향일 때 계속 움직이면 두 점이 점점 멀어짐
 * 
 * - 그렇지 않고 시계방향이면 i에 1 증가시킴
 * - - 시계 방향일 때 계속 움직이면 두 점이 점점 가까워짐
 * - - 현재의 i에 대해서는 가장 멀리 떨어져 있는 점을 찾았기에 다음 i에 대해서도 탐색하기 위해 i 증가
 * 
 * - i<n 범위를 넘어가면 종료
 * - - 모든 점을 탐색했기 때문에
 * 
 * - j<n 범위를 넘어가면 종료
 * - - j가 한 바퀴 도는 경우, 겹치는 쌍을 탐색하기 때문에
 * - - ex) (1, 5) 쌍과 (5, 1) 쌍
 */
void rotating_Calipers(vector<pos> stk) {
    int n = stk.size();
    pos a, b;
    ll maxDist=0;
    int i=0, j=1;
    while(i<n && j<n) {
        ll curDist = dist(stk[i], stk[j]);
        if(curDist>maxDist) {
            maxDist = curDist;
            a = stk[i];
            b = stk[j];
        }
        if(ccw(stk[i], stk[i+1], stk[j], stk[j+1])>0) j++;
        else i++;
    }
    cout << a.x << ' ' << a.y << ' ' << b.x << ' ' << b.y << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        rotating_Calipers(graham_Scan());
    }
}
```
