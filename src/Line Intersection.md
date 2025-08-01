## Line Intersection
두 선분이 서로 교차하는지 CCW를 통해 판별하는 알고리즘

시간복잡도 : O(1)

[연습 문제 (백준 17387번)](https://www.acmicpc.net/problem/17387)

``` c++
/** https://www.acmicpc.net/problem/17387 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

struct line {
    long long x1, y1, x2, y2;
};

/** ccw 알고리즘 */
int ccw(line a) {
    long long ret = a.x1*a.y2 - a.x2*a.y1;
    if(ret>0) return 1;
    if(ret<0) return -1;
    return 0;
}

/** 
 * 두 선분이 교차하려면
 * A의 양 끝점에서 B의 양 끝점을 바라봤을 때 방향이 서로 달라야 하고
 * B의 양 끝점에서 A의 양 끝점을 바라봤을 때 방향이 서로 달라야 함.
 * 
 * 또는 두 선분이 일렬로 위치해 있고, 겹치는 경우
 */
bool isIntersect(line a, line b) {
    int aToB1 = ccw({a.x2-a.x1, a.y2-a.y1, b.x1-a.x2, b.y1-a.y2});
    int aToB2 = ccw({a.x2-a.x1, a.y2-a.y1, b.x2-a.x2, b.y2-a.y2});
    int bToA1 = ccw({b.x2-b.x1, b.y2-b.y1, a.x1-b.x2, a.y1-b.y2});
    int bToA2 = ccw({b.x2-b.x1, b.y2-b.y1, a.x2-b.x2, a.y2-b.y2});

    if(aToB1 * aToB2==0 && bToA1 * bToA2==0) { // 두 선분이 일렬로 위치한 경우
        return (min(a.x1, a.x2)<=b.x1 && b.x1<=max(a.x1, a.x2) || min(a.x1, a.x2)<=b.x2 && b.x2<=max(a.x1, a.x2) || min(b.x1, b.x2)<=a.x1 && a.x1<=max(b.x1, b.x2) || min(b.x1, b.x2)<=a.x2 && a.x2<=max(b.x1, b.x2))
        && (min(a.y1, a.y2)<=b.y1 && b.y1<=max(a.y1, a.y2) || min(a.y1, a.y2)<=b.y2 && b.y2<=max(a.y1, a.y2) || min(b.y1, b.y2)<=a.y1 && a.y1<=max(b.y1, b.y2) || min(b.y1, b.y2)<=a.y2 && a.y2<=max(b.y1, b.y2));
    }
    return aToB1 * aToB2 <= 0 && bToA1 * bToA2 <= 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    line a, b;
    cin >> a.x1 >> a.y1 >> a.x2 >> a.y2 >> b.x1 >> b.y1 >> b.x2 >> b.y2;
    cout << isIntersect(a, b);
}
```
