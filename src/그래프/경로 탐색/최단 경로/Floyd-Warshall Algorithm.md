## Floyd-Warshall Algorithm
모든 정점 쌍 사이의 최단 거리를 DP로 구하는 알고리즘

시간복잡도 : O(V³), 공간복잡도 : O(V²)

[연습 문제 (백준 11404번)](https://www.acmicpc.net/problem/11404)

``` c++
/** https://www.acmicpc.net/problem/11404 제출 코드 */
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
