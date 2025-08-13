## TSP (Traveling Salesman Problem, 외판원 순회 문제)
비트마스킹 + DP로 모든 도시를 한 번씩 순회하고 다시 시작 도시로 돌아오는 최소 비용을 계산하는 알고리즘

시간복잡도 : O(N x 2<sup>N</sup>)

N : 도시의 수

2<sup>N</sup> : 가능한 방문 조합의 수

[연습 문제 (백준 2098번)](https://www.acmicpc.net/problem/2098)

``` c++
/** https://www.acmicpc.net/problem/2098 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/** 
 * INF : 대략 10억
 * w[i][j] : i번에서 j번으로 가기 위한 비용
 * w[i][j]와 w[j][i]는 서로 다를 수 있음.
 * dp[i][k] : i를 마지막으로 방문했을 때, 방문한 도시들의 집합이 k인 경우의 최소 비용. k는 n비트로 나타냄 (비트마스킹)
 */
const int INF = 0x3f3f3f3f;
int n, w[16][16], dp[16][1<<16];

/** 
 * visit: 현재까지 방문한 도시들의 비트 마스크 (visit이 이진수로 10011이면 0, 1, 4번 도시를 방문함)
 * dp[cur][visit] : 현재 도시가 cur이고, 방문한 도시 집합이 visit일 때 최소 비용
 * 
 * 모든 종류를 다 선택한 경우 (visit == 2^n-1) 마지막 도시에서 첫번째 도시로 가는 경로가 존재하면 그 비용을 return.
 * 이미 방문한 조합인 경우 (dp[cur][visit]!=-1) : 이미 계산된 최소 비용 return.
 * 그렇지 않은 경우는 현재 도시 ~ 마지막 도시까지의 최소 비용을 계산하여 저장.
 */
int dfs(int cur, int visit) {
    if(visit == (1<<n)-1) return (w[cur][0]==0 ? INF : w[cur][0]);
    if(dp[cur][visit]!=-1) return dp[cur][visit];
    dp[cur][visit] = INF;
    for(int next=0;next<n;next++) {
        if(!(visit & (1<<next)) && w[cur][next]) {
            dp[cur][visit] = min(dp[cur][visit], dfs(next, visit | (1<<next)) + w[cur][next]);
        }
    }
    return dp[cur][visit];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cin >> w[i][j];
        }
    }
    memset(dp, -1, sizeof dp);
    cout << dfs(0, 1);
}
```
