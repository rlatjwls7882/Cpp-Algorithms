## CCW (Counter ClockWise) Algorithm
세 점이 이루는 방향이 시계 방향인지, 반시계 방향인지 판별하는 알고리즘

시간복잡도 : O(1)

[연습 문제(백준 11758번)](https://www.acmicpc.net/problem/11758)

``` c++
/** https://www.acmicpc.net/problem/11758 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

struct vect {
    int x, y;
};

/** 
 * CCW 알고리즘
 * 벡터 a 이후 벡터 b로 움직일 때 시계 방향으로 움직이는지, 반시계 방향으로 움직이는지 구하는 알고리즘
 * 
 * 벡터 a와 벡터 b를 외적하여 나온 값이 양수이면 반시계 방향으로
 * 나온 값이 음수이면 시계 방향으로
 * 나온 값이 0이면 일직선으로 이동한 경우이다.
 */
int cross(vect a, vect b) {
    int ret = a.x*b.y-b.x*a.y;
    if(ret>0) return 1;
    if(ret<0) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int x1, y1, x2, y2, x3, y3; cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    cout << cross({x2-x1, y2-y1}, {x3-x2, y3-y2});
}
```
