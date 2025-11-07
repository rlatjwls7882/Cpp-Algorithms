## Sweeping Algorithm 🟡 Gold V
선을 한쪽 방향으로 이동시키며 정렬된 이벤트를 순서대로 처리해 문제를 해결하는 알고리즘

시간복잡도 : O(NlogN) (N : 이벤트 개수, 정렬 O(NlogN) + 스캔 O(N))

![](https://github.com/user-attachments/assets/87ae8c0e-77b0-44d0-a332-15d8e3218220)

이렇게 선이 4개가 있고, 모든 선이 차지하는 길이를 구한다고 해보자.

![](https://github.com/user-attachments/assets/32a0b077-03b8-48a7-a346-bc0d419501d5)

먼저 선들을 왼쪽 점을 기준으로 오차순으로 정렬한다.  
처음에는 left와 right를 -INF로 두고 반복을 시작한다.

![](https://github.com/user-attachments/assets/4be886fd-3332-49ed-97ab-4f9987ece7ec)

이전에 기록한 선이 현재 보고 있는 선과 이어지지 않아서(right<cur.left) 이전 선의 길이를 더하고(sum += right-left) 새로운 선을 시작한다.  
합치는 첫번째 선이기 때문에 left랑 right 모두 기록한다.

![](https://github.com/user-attachments/assets/3a7c6b87-277a-47d4-a1b2-2951c7c44aeb)

이전에 기록한 선과 겹치기 때문에 right를 업데이트 한다.

![](https://github.com/user-attachments/assets/49c7149a-3234-426d-86df-555957f2a2f1)

이전에 기록한 선과 겹치기 때문에 right를 업데이트 한다. (하지만 cur.right가 더 작아 결과적으론 그대로이다.)

![](https://github.com/user-attachments/assets/7fe9ea46-1416-4cdb-8f2a-177161ef4b6f)

이전에 기록한 선이 현재 보고 있는 선과 이어지지 않아서 이전 선의 길이를 더하고 새로운 선을 시작한다.  
합치는 첫번째 선이기 때문에 left랑 right 모두 기록한다.  
더 이상 볼 선이 없어서 반복을 종료한다.  
반복 종료 후에, 마지막으로 기록한 선의 길이를 더한다. (sum += right-left)

[연습 문제 (백준 2170번)](https://www.acmicpc.net/problem/2170)

``` c++
/** http://boj.kr/087c352e69304ef09e3d4886b8f54d1a 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

struct line {
    int left, right;
    bool operator<(const line l) const {
        return left < l.left;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;

    vector<line> lines(n);
    for(int i=0;i<n;i++) cin >> lines[i].left >> lines[i].right;
    sort(lines.begin(), lines.end()); // 선을 왼쪽 점 기준으로 오름차순으로 정렬

    int sum=0, left=-INF, right=-INF;
    for(line l : lines) {
        if(l.left<=right) { // 만약 이번 선이 지금까지의 선과 겹친다면
            right = max(right, l.right); // 선 합치기 (이전 선의 오른쪽 부분이 현재의 오른쪽보다 더 클 수 있기 때문에 max 함수 사용)
        } else { // 겹치지 않는다면
            sum += right-left; // 이전 선들의 길이 누적
            left = l.left; // 이번 선의 왼쪽 좌표 기록
            right = l.right; // 이번 선의 오른쪽 좌표 기록
        }
    }
    sum += right-left; // 마지막 선의 길이 처리

    cout << sum;
}
```
