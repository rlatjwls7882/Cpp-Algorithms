## TSP (Traveling Salesman Problem, 외판원 순회 문제)
비트마스킹 + DP로 모든 도시를 한 번씩 순회하고 다시 시작 도시로 돌아오는 최소 비용을 계산하는 알고리즘

시간복잡도 : O(N² x $2^N$) (N : 도시의 수, $2^N$ : 가능한 방문 조합의 수)

![](https://github.com/user-attachments/assets/64f58ba6-69b0-438a-8506-3c7a1472e300)

이렇게 연결된 그래프에서 TSP를 풀어보도록 하자.

![](https://github.com/user-attachments/assets/1d3ab93e-0e5d-4da4-abed-1960dd2fcd69)

일반적인 DP와 과정은 비슷하지만 방문했다고 기록하는 공간이 비트필드라는 차이가 있다.  
0번 도시에서 탐색을 시작하자고 하자.  
현재 위치에 임시 비용 (INF)를 저장한다.  
방문하지 않은 제일 번호가 작은 도시인(비트필드가 0인 도시들) 1번 도시로 이동한다.

![](https://github.com/user-attachments/assets/3312e43f-1e75-4f17-9322-abf0475a29d6)

1번 도시에 도착한다.  
현재 위치에 임시 비용을 저장한다.  
방문하지 않은 제일 번호가 작은 도시인 2번 도시로 이동한다.

![](https://github.com/user-attachments/assets/a1217a39-2f36-4bf6-958b-1fdb3a10969f)

2번 도시에 도착한다.  
모든 도시에 방문했고 (visit == (1<<N)-1) 2번 도시에서 0번 도시로의 길이 있기 때문에 그 길의 비용인 6을 저장한다 (없으면 INF 저장).

![](https://github.com/user-attachments/assets/6feb6082-0e23-40db-a006-1be63559f2fd)

더 이상 방문할 수 있는 도시가 없어서 1번 도시로 돌아온다.  
방금 갔다왔던 1 -> 2 경로가 기존 경로보다 비용이 적기에 경로를 업데이트한다.

![](https://github.com/user-attachments/assets/44ff15c3-2def-45c0-86cb-e3bff6bb78f2)

더 이상 방문할 수 있는 도시가 없어서 0번 도시로 돌아온다.  
방금 갔다왔던 0 -> 1 경로가 기존 경로보다 비용이 적기에 경로를 업데이트한다.  
이번에는 0 -> 2번 경로를 탐색한다.

![](https://github.com/user-attachments/assets/21eef713-2313-4494-98c7-041cfca59c26)

2번 도시에 도착한다.  
현재 위치에 임시 비용을 저장한다.  
방문하지 않은 제일 번호가 작은 도시인 1번 도시로 이동한다.

![](https://github.com/user-attachments/assets/9db25bcf-088b-4254-b863-5d082f603a4b)

1번 도시에 도착한다.  
모든 도시에 방문했고 1번 도시에서 0번 도시로의 길이 있기 때문에 그 길의 비용인 5를 저장한다.

![](https://github.com/user-attachments/assets/d4ac69d9-270c-4b40-99b2-6720ff562af4)

더 이상 방문할 수 있는 도시가 없어서 2번 도시로 돌아온다.  
방금 갔다왔던 2 -> 1 경로가 기존 경로보다 비용이 적기에 경로를 업데이트한다.

![](https://github.com/user-attachments/assets/85ea214b-b747-475a-9bad-8894b60e44a6)

더 이상 방문할 수 있는 도시가 없어서 0번 도시로 돌아온다.  
방금 갔다왔던 0 -> 2 경로가 기존 경로보다 비용이 크기에 경로를 업데이트하지 않는다.  
모든 경로를 방문했기에 종료한다. (TSP의 최소 비용은 dp[0][1])

[연습 문제 (백준 2098번)](https://www.acmicpc.net/problem/2098)

``` c++
/** https://www.acmicpc.net/source/share/d95a2d2c96f644929d3c3c380fde08a5 제출 코드 */
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
