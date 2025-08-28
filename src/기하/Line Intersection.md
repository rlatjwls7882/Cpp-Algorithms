## Line Intersection
두 선분이 서로 교차하는지 CCW를 통해 판별하는 알고리즘

시간복잡도 : O(1)

![](https://github.com/user-attachments/assets/b5c9a42d-d7a4-4e83-9311-8a8e6ee994dd)

이렇게 두 개의 직선이 있다고 하자. P1 P2를 직선 A의 양 끝 점으로, P3 P4를 직선 B의 양 끝 점으로 두자.

![](https://github.com/user-attachments/assets/e22665a3-5862-4ca8-97a9-624abf0aee25)

이 때, 두 직선이 겹치는 첫 번째 조건은 직선 A에 대해 P3, P4가 서로 CCW 로 다른 방향에 위치해야 한다.  
위 사진에서는 P1 -> P2 -> P4 가 반시계 방향이고, P1 -> P2 -> P3가 시계방향으로 서로 반대이다.

![](https://github.com/user-attachments/assets/8ba7e268-d338-49df-a297-9125d43a1712)

두 번째 조건은 직선 B에 대해 P1, P2가 서로 CCW 로 다른 방향에 위치해야 한다.  
위 사진에서는 P3 -> P4 -> P1 가 반시계 방향이고, P3 -> P4 -> P2가 시계방향으로 서로 반대이다.

![](https://github.com/user-attachments/assets/e0982725-1d28-4015-b598-b1618b105b90)

하지만 만약 이렇게 두 직선이 일직선으로 되는 경우는 예외 처리해주어야 한다.  
두 직선이 일직선이면, 이전 두 조건에서 판별한 4가지 값이 모두 0이 나올 것이다. (일직선)  
그리고 이 때는, P3 또는 P4가 P1과 P2 사이에 있는 경우, P1 또는 P2가 P3와 P4 사이에 있는 경우에 두 직선이 교차한다.

[연습 문제 (백준 17387번)](https://www.acmicpc.net/problem/17387)

``` c++
/** http://boj.kr/b7c8e66120fa4c15abd64f5511e852d4 제출 코드 */
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
