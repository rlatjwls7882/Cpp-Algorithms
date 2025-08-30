## Rotating Calipers (회전하는 캘리퍼스)
볼록 껍질에서 모든 점 쌍 중 가장 먼 두 점 등을 O(N)에 찾는 알고리즘

시간복잡도 : O(N) (그라함 스캔 제외)

![](https://github.com/user-attachments/assets/03bf9b93-10f5-4e34-883d-676f7c67cfd3)

이미 그라함 스캔을 마쳐 볼록 껍질을 찾은 상태라고 하자.  
i=0, j=1인 상태에서 반복을 시작한다.  
현재 위치한 두 점 i=0, j=1 사이의 거리를 계산하여 최댓값에 업데이트한다.  
0 -> 1 벡터와 1 -> 2벡터가 반시계 방향으로 회전하기 때문에 (ccw>0) j를 증가시킨다. (잘 살펴보면 반시계 방향으로 회전하는 경우 다음 점으로 갈수록 멀어진다.)

![](https://github.com/user-attachments/assets/fbf5b71c-b593-4ab5-997f-a4f0777d92f7)

현재 위치한 두 점 i=0, j=2 사이의 거리를 계산하여 최댓값에 업데이트한다.  
0 -> 1 벡터와 2 -> 3벡터가 반시계 방향으로 회전하기 때문에 j를 증가시킨다.

![](https://github.com/user-attachments/assets/58be6c68-6132-4945-9b52-1525b63975fc)

현재 위치한 두 점 i=0, j=3 사이의 거리를 계산하여 최댓값에 업데이트한다.  
0 -> 1 벡터와 3 -> 4벡터가 반시계 방향으로 회전하기 때문에 j를 증가시킨다.

![](https://github.com/user-attachments/assets/a3bdaecd-060e-4945-b860-0a751929e400)

현재 위치한 두 점 i=0, j=4 사이의 거리를 계산하여 최댓값에 업데이트한다.  
0 -> 1 벡터와 4 -> 5벡터가 반시계 방향으로 회전하지 않기 때문에 i를 증가시킨다. (잘 살펴보면 반시계 방향으로 회전하지 않는 경우 다음 점으로 갈수록 가까워진다.)

![](https://github.com/user-attachments/assets/55131dd8-0c7a-4c36-83a2-e27c035429db)

현재 위치한 두 점 i=1, j=4 사이의 거리를 계산하여 최댓값에 업데이트한다.  
1 -> 2 벡터와 4 -> 5벡터가 반시계 방향으로 회전하지 않기 때문에 i를 증가시킨다.

![](https://github.com/user-attachments/assets/acd1b7f8-5c8b-4d11-9fb7-030f64e985e4)

현재 위치한 두 점 i=2, j=4 사이의 거리를 계산하여 최댓값에 업데이트한다.  
2 -> 3 벡터와 4 -> 5벡터가 반시계 방향으로 회전하지 않기 때문에 i를 증가시킨다.

![](https://github.com/user-attachments/assets/64afcb95-0fe7-4210-9c0e-f1550f4667a4)

현재 위치한 두 점 i=3, j=4 사이의 거리를 계산하여 최댓값에 업데이트한다.  
3 -> 4 벡터와 4 -> 5벡터가 반시계 방향으로 회전하기 때문에 j를 증가시킨다.

![](https://github.com/user-attachments/assets/1a54e5b0-938b-474f-bc4c-613c0cec05cf)

현재 위치한 두 점 i=3, j=5 사이의 거리를 계산하여 최댓값에 업데이트한다.  
3 -> 4 벡터와 5 -> 0벡터가 반시계 방향으로 회전하기 때문에 j를 증가시킨다.  
j가 6이 되어 반복을 종료한다.

[연습 문제 (백준 9240번)](https://www.acmicpc.net/problem/9240)

``` c++
/** http://boj.kr/c103693446fc4558a9c6dbbe46642365 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

struct point {
    int x, y, p=0, q=0;
    bool operator<(const point o) const {
        if(p*o.q!=q*o.p) return p*o.q > q*o.p;
        if(y!=o.y) return y < o.y;
        return x < o.x;
    }
};

int ccw(point a, point b, point c) {
    point vec1 = {b.x-a.x, b.y-a.y};
    point vec2 = {c.x-a.x, c.y-a.y};
    return vec1.x*vec2.y - vec1.y*vec2.x;
}

int ccw(point a, point b, point c, point d) {
    point vec1 = {b.x-a.x, b.y-a.y};
    point vec2 = {d.x-c.x, d.y-c.y};
    return vec1.x*vec2.y - vec1.y*vec2.x;
}

vector<point> graham_scan() {
    int c; cin >> c;
    vector<point> v(c);
    for(int i=0;i<c;i++) cin >> v[i].x >> v[i].y;
    sort(v.begin(), v.end());

    for(int i=1;i<c;i++) {
        v[i].p = v[i].x-v[0].x;
        v[i].q = v[i].y-v[0].y;
    }
    sort(v.begin(), v.end());

    vector<point> stk;
    for(int i=0;i<c;i++) {
        while(stk.size()>=2 && ccw(stk[stk.size()-2], stk[stk.size()-1], v[i])<=0) stk.pop_back();
        stk.push_back(v[i]);
    }
    return stk;
}

int dist(point a, point b) {
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

/** 
 * 회전하는 캘리퍼스 알고리즘
 * - 그라함 스캔으로 볼록 껍질을 찾은 후 시작
 * 
 * - 가장 먼 두 점은 i -> i+1 벡터와 j -> j+1 벡터가 반시계방향일 때 j에 1 증가시킴
 * - - 그라함 스캔을 반시계방향으로 했기 때문에 반시계 방향일 때 계속 움직이면 두 점이 점점 멀어짐
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
void rotating_calipers(vector<point> hull) {
    int n = hull.size();
    int maxDist=0, i=0, j=1;
    while(i<n && j<n) {
        maxDist = max(maxDist, dist(hull[i], hull[j]));
        if(ccw(hull[i], hull[(i+1)%n], hull[j], hull[(j+1)%n])>0) j++;
        else i++;
    }
    cout << setprecision(6) << fixed << sqrt(maxDist);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    rotating_calipers(graham_scan());
}
```
