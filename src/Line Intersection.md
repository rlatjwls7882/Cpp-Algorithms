## Line Intersection
두 선분이 서로 교차하는지 CCW를 통해 판별하는 알고리즘 (진교차 기준)

시간복잡도 : O(1)

[연습 문제 (백준 17386번)](https://www.acmicpc.net/problem/17386)

``` c++
/** https://www.acmicpc.net/problem/17386 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct line {
    ll x1, y1, x2, y2;
};

struct vect {
    ll x, y;
};

/** ccw 알고리즘 */
int ccw(vect a, vect b) {
    ll ret = a.x*b.y-b.x*a.y;
    if(ret>0) return 1;
    if(ret<0) return -1;
    return 0;
}

/** 
 * 두 선분이 교차하려면
 * A의 양 끝점에서 B의 양 끝점을 바라봤을 때 방향이 서로 달라야 하고
 * B의 양 끝점에서 A의 양 끝점을 바라봤을 때 방향이 서로 달라야 함.
 */
bool isInterSect(line a, line b) {
    // a -> b로의 ccw 판별
    vect ab = {a.x2-a.x1, a.y2-a.y1};
    vect bc = {b.x1-a.x2, b.y1-a.y2};
    vect bd = {b.x2-a.x2, b.y2-a.y2};
    int abc = ccw(ab, bc);
    int abd = ccw(ab, bd);

    // b -> a로의 ccw 판별
    vect cd = {b.x2-b.x1, b.y2-b.y1};
    vect da = {a.x1-b.x2, a.y1-b.y2};
    vect db = {a.x2-b.x2, a.y2-b.y2};
    int cda = ccw(cd, da);
    int cdb = ccw(cd, db);

    // 이 문제에선 두 점이 일직선에 위치하는 경우는 나타나지 않음.
    return abc * abd < 0 && cda * cdb < 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    line a, b; cin >> a.x1 >> a.y1 >> a.x2 >> a.y2 >> b.x1 >> b.y1 >> b.x2 >> b.y2;
    cout << isInterSect(a, b);
}
```
