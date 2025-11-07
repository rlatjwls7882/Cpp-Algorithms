## Point in Convex Polygon (볼록 다각형 내부의 점 판정) 🟢 Platinum III
볼록 다각형에 대해, 기준점을 잡고 이분 탐색을 이용해 점이 내부에 있는지 O(logN)에 판정하는 알고리즘

시간복잡도 : O(logN) (N : 볼록 껍질의 점의 수)

![](https://github.com/user-attachments/assets/4dc402a8-f23c-4b39-8382-c2e8c3f41fdf)

빨간색 점이 첫 번째 점(0)이고 파란색 점이 판별할 점(p)이라고 하자.

![](https://github.com/user-attachments/assets/b456ff22-00be-45d7-9d74-71371d2a8f69)

점 p가 볼록 껍질 내부에 있으려면 0 -> 1 -> p 벡터가 반시계 방향이어야 하고, 0 -> 5 -> p 벡터가 시계 방향이어야 한다.

![](https://github.com/user-attachments/assets/a33dbe38-7101-45f8-9544-c63677510918)

이분 탐색에서의 첫번째 반복에서는 0 -> 3 -> p 벡터가 반시계 방향이다. (left = mid)

점 p가 0 -> 3 왼쪽에 있으니 자동으로 0 -> 1, 0 -> 2일 때도 점 p가 왼쪽에 존재한다는 것을 알 수 있다.

![](https://github.com/user-attachments/assets/af04d3cd-b3e7-4e3a-bdc1-c7b0837347a0)

이분 탐색에서의 두 번째 반복에서는 0 -> 4 -> p 벡터가 시계 방향이다. (right = mid)

점 p가 0 -> 4 오른쪽에 있으니 자동으로 0 -> 5일 때도 점 p가 오른쪽에 존재한다는 것을 알 수 있다.

![](https://github.com/user-attachments/assets/da152538-4000-4179-8479-82793031a5e4)

마지막으로 left -> right -> p 가 반시계 방향이라면 점 p는 볼록 껍질 안에 존재한다.

[연습 문제 (백준 20670번)](https://www.acmicpc.net/problem/20670)

``` c++
/** http://boj.kr/53b52acf09254afc8ee95823889d15d8 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
    ll x, y;
};

ll ccw(point a, point b, point c) {
    point vec1 = {b.x-a.x, b.y-a.y};
    point vec2 = {c.x-a.x, c.y-a.y};
    return vec1.x*vec2.y - vec1.y*vec2.x;
}

bool isInside(vector<point> &hull, point p) {
    if(ccw(hull[0], hull[1], p)<0) return false; // 0 -> 1 -> p 가 반시계 방향이어야 한다.
    if(ccw(hull[0], hull[hull.size()-1], p)>0) return false; // 0 -> n-1 -> p 가 시계 방향이어야 한다.

    int left=1, right=hull.size()-1;
    while(left+1<right) {
        int mid = (left+right)/2;
        if(ccw(hull[0], hull[mid], p)>0) left=mid; // 반시계 방향이라면 left 증가
        else right=mid; // 시계 방향이라면 right 증가
    }
    return ccw(hull[left], hull[right], p)>0; // left -> right -> p 가 반시계 방향이어야 한다.
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    vector<point> A(n), B(m);
    for(int i=0;i<n;i++) cin >> A[i].x >> A[i].y;
    for(int i=0;i<m;i++) cin >> B[i].x >> B[i].y;

    int cnt=0;
    while(k--) {
        point p; cin >> p.x >> p.y;
        if(!isInside(A, p) || isInside(B, p)) cnt++;
    }
    if(!cnt) cout << "YES";
    else cout << cnt;
}
```
