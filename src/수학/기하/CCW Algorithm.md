## CCW (CounterclockWise) Algorithm 🟡 Gold V
세 점이 이루는 방향이 시계 방향인지, 반시계 방향인지 판별하는 알고리즘

시간복잡도 : O(1)

![](https://github.com/user-attachments/assets/0a99a5c9-0305-4084-8837-7553e1c7c8a7)

이렇게 A->B->C가 반시계 방향(CCW)일 때, A->B 벡터와 A->C 벡터를 외적 하면 (|AB||AC|sinθ) sinθ가 양수여서 전체 값도 양수가 나온다.

![](https://github.com/user-attachments/assets/216c190b-18c3-4970-9d41-efd914f48026)

반대로 A->B->C가 시계 방향(CW)일 때, A->B 벡터와 A->C 벡터를 외적 하면 sinθ가 음수여서 전체 값도 음수가 나온다.

![](https://github.com/user-attachments/assets/0511f0f1-f73d-4eed-a4ac-1952869dc239)

세 점이 한 직선 위에 있으면 sinθ가 0이어서 전체 값도 0이 나온다

[연습 문제(백준 11758번)](https://www.acmicpc.net/problem/11758)

``` c++
/** http://boj.kr/8afb1c7579c3432381d3ce0827b8fde9 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
};

/** 
 * CCW 알고리즘
 * 1번 벡터 이후 2번 벡터로 움직일 때 시계 방향으로 움직이는지, 반시계 방향으로 움직이는지 구하는 알고리즘
 * 
 * 1번 벡터와 2번 벡터를 외적하여 나온 값이 양수이면 반시계 방향으로
 * 나온 값이 음수이면 시계 방향으로
 * 나온 값이 0이면 일직선으로 이동한 경우이다.
 */
int ccw(point a, point b, point c) {
    point vect1 = {b.x-a.x, b.y-a.y};
    point vect2 = {c.x-a.x, c.y-a.y};

    int ret = vect1.x*vect2.y-vect1.y*vect2.x;
    if(ret>0) return 1;
    if(ret<0) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    point p1, p2, p3; cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
    cout << ccw(p1, p2, p3);
}
```
