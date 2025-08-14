## Sweeping Algorithm
선을 한쪽 방향으로 이동시키며 정렬된 이벤트를 순서대로 처리해 문제를 해결하는 알고리즘

시간복잡도 : O(NlogN) (N : 이벤트 개수, 정렬 O(NlogN) + 스캔 O(N))

[연습 문제 (백준 2170번)](https://www.acmicpc.net/problem/2170)

``` c++
/** https://www.acmicpc.net/problem/2170 제출 코드 */
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
