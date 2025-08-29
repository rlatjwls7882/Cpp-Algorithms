## Graham's Scan (Convex Hull)
기준점을 잡아 점들을 각도로 정렬한 후, 스택을 이용해 볼록 껍질의 방향성을 유지하지 않는 점을 제거하며 볼록 껍질을 찾는 알고리즘

시간복잡도 : O(NlogN)

![](https://github.com/user-attachments/assets/b2981dcf-e7e9-4f5a-89ab-a1f0e90ee898)

이렇게 5개의 점이 있다고 하자.

![](https://github.com/user-attachments/assets/6fda21b7-0eee-4986-92fe-d4348567791e)

처음에는 우선 기준점을 잡아야 한다. (보통 y가 가장 작고, y값이 같다면 x가 가장 작은 점)

![](https://github.com/user-attachments/assets/8dea310c-7b84-4f8a-9844-738aa51d51ec)

기준점 p1을 기준으로 반시계방향으로 각도 정렬을 하여, 방문할 점 순서를 정한다.

![](https://github.com/user-attachments/assets/142d34ce-2e6a-41fd-b0bc-e6b38c91f3c4)

첫번째 점과 두번째 점은 스택에 넣어놓는다.

![](https://github.com/user-attachments/assets/29b47def-84a8-4fd2-af1f-e150f9a3d826)

P3를 볼록 껍질에 넣을지 판단한다.  
P1 -> P2 -> P3가 반시계 방향으로 회전하는지 확인한다. (처음에 시계 방향으로 각도 정렬했으면 시계방향으로 회전하는지 확인)  
반시계 방향으로 회전해 그대로 스택에 넣는다.

![](https://github.com/user-attachments/assets/f04e1f42-efa8-4709-8791-ac768133be97)

P4를 볼록 껍질에 넣을지 판단한다.  
P2 -> P3 -> P4가 반시계 방향으로 회전하는지 확인한다.  
반시계 방향으로 회전해 그대로 스택에 넣는다.

![](https://github.com/user-attachments/assets/1ba5366c-8efd-4d18-bfd7-7a5648791000)

P5를 볼록 껍질에 넣을지 판단한다.  
P3 -> P4 -> P5가 반시계 방향으로 회전하는지 확인한다.  
시계 방향으로 회전해 이전에 스택에 넣었던 P4를 꺼낸다.

![](https://github.com/user-attachments/assets/32b573e3-5211-4c32-90f8-9a212cffe474)

P2 -> P3 -> P5가 반시계 방향으로 회전하는지 확인한다.  
반시계 방향으로 회전해 그대로 스택에 넣는다.

![](https://github.com/user-attachments/assets/273fdb37-a601-448c-a825-fb8088fdbea8)

더 이상 확인할 점이 없어서 P5를 P1과 연결한다.


[연습 문제(백준 1708번)](https://www.acmicpc.net/problem/1708)

``` c++
/** http://boj.kr/c12b0c398f4e4d8b8b98d469f194e9be 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
    ll x, y;
    ll p=0, q=0; // 기준점으로부터의 상대 위치
    bool operator<(const point b) const {
        if(p*b.q!=q*b.p) return p*b.q > q*b.p;
        if(y!=b.y) return y < b.y;
        return x < b.x;
    }
};

ll ccw(point a, point b, point c) {
    point vec1 = {b.x-a.x, b.y-a.y};
    point vec2 = {c.x-a.x, c.y-a.y};
    return vec1.x*vec2.y - vec1.y*vec2.x;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    /** 
     * 모든 점들 입력
     * 그 후 y가 가장 작고, x가 가장 작은 점을 찾기 위해 정렬
     */
    vector<point> v(n);
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
    vector<point> stk;
    for(int i=0;i<n;i++) {
        while(stk.size()>=2 && ccw(stk[stk.size()-2], stk[stk.size()-1], v[i])<=0) stk.pop_back();
        stk.push_back(v[i]);
    }
    cout << stk.size();
}
```
