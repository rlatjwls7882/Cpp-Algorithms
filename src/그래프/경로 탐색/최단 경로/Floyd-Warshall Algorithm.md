## Floyd-Warshall Algorithm
모든 정점 쌍 사이의 최단 거리를 DP로 구하는 알고리즘

시간복잡도 : O(V³), 공간복잡도 : O(V²)

![](https://github.com/user-attachments/assets/2ec3a22f-d56c-417a-9375-98aa31300ea1)

위와 같은 그래프를 사용해보겠다.

![](https://github.com/user-attachments/assets/7cb8c016-4641-4c6d-81cb-49667ba54bad)

그래프의 간선을 입력해 인접 행렬을 만드면 다음과 같다. i번 행, j번 열의 원소는 i번 정점에서 j번 정점에 도달하기 위한 최소 거리이다.

![](https://github.com/user-attachments/assets/12799956-fcf1-4925-8285-732dba799f47)

이후 mid(경유지)를 1로 하는 모든 start와 end 쌍에 대해 최단 거리를 구한다.

2 -> 1 -> 3, 3 -> 1 -> 2, 3 -> 1 -> 5, 5 -> 1 -> 3 경로에 대해 최단 거리가 단축된다.

![](https://github.com/user-attachments/assets/43c6cfb2-5628-4013-99d7-53d51fd7d5bb)

mid를 2로 하는 모든 start와 end 쌍에 대해 최단 거리를 구한다.

1 -> 2 -> 4, 4 -> 2 -> 1 경로에 대해 최단 거리가 단축된다.

![](https://github.com/user-attachments/assets/d69a14a6-893b-4a66-823f-bee996dac040)

mid를 3으로 하는 모든 start와 end 쌍에 대해 최단 거리를 구한다.

1 -> 3 -> 4, 4 -> 3 -> 1 경로에 대해 최단 거리가 단축된다.

![](https://github.com/user-attachments/assets/a5524a8e-d8a8-4d70-ae0b-e540c5e03f54)

mid를 4로 하는 모든 start와 end 쌍에 대해 최단 거리를 구한다.

2 -> 4 -> 3, 3 -> 4 -> 2 경로에 대해 최단 거리가 단축된다.

![](https://github.com/user-attachments/assets/12b60334-6832-4537-818e-5da7d010ee2a)

mid를 5로 하는 모든 start와 end 쌍에 대해 최단 거리를 구한다.

mid=5에 대해서는 단축될 최단 거리가 없다.

[연습 문제 (백준 11404번)](https://www.acmicpc.net/problem/11404)

``` c++
/** http://boj.kr/16aa77515ca84d378b5b10dabfa5ba2a 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/** 
 * INF : 대략 10억
 * MAX : 최대 정점 수
 * minCost[i][j] : i에서 j로 이동할 때의 최소 비용
 */
const int INF = 0x3f3f3f3f;
const int MAX = 101;

int minCost[MAX][MAX];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;

    fill(&minCost[0][0], &minCost[MAX-1][MAX], INF);
    for(int i=1;i<=n;i++) minCost[i][i]=0;
    while(m--) {
        int a, b, c; cin >> a >> b >> c;
        minCost[a][b] = min(minCost[a][b], c);
    }

    /** 
     * Floyd-Warshall Algorithm
     * 모든 정점 쌍 최단거리 계산
     * - mid : 경유지
     * - start : 출발지
     * - end : 도착지
     * 
     * mid를 하나씩 늘려가며 start → end 경로와 start → mid → end 경로 중 더 짧은 경로를 선택
     */
    for(int mid=1;mid<=n;mid++) {
        for(int start=1;start<=n;start++) {
            for(int end=1;end<=n;end++) {
                minCost[start][end] = min(minCost[start][end], minCost[start][mid]+minCost[mid][end]);
            }
        }
    }

    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(minCost[i][j]==INF) cout << "0 ";
            else cout << minCost[i][j] << ' ';
        }
        cout << '\n';
    }
}
```
