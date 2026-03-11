## Bellman-Ford Algorithm 🟡 Gold IV
가중치가 음수인 그래프에서도 최단 거리를 구하고 음수 사이클의 존재 여부를 판별하는 알고리즘

시간복잡도: $O(VE)$ ($V$: 정점 수, $E$: 간선 수)

![](https://github.com/user-attachments/assets/ec2faed3-229f-4245-adcc-87edc20913fd)

위와 같이 연결된 그래프가 있고 **1번 정점에서 탐색을 시작**한다고 가정하자.

![](https://github.com/user-attachments/assets/932be387-a036-4e10-a117-55a87ba01bb1)

먼저 1번 정점에서 시작하여 연결된 모든 간선을 확인하며 다른 정점들의 최소 비용을 갱신한다.

![](https://github.com/user-attachments/assets/cca6aff3-4f14-4d2d-93a3-186a6a376797)

다음으로 2번 정점에서도 연결된 모든 간선을 확인하며 최소 비용을 갱신한다.

![](https://github.com/user-attachments/assets/9f06c533-496f-4332-8e91-9998f4d73b4d)

같은 방식으로 3번 정점에서도 연결된 모든 간선을 확인하며 최소 비용을 갱신한다.

![](https://github.com/user-attachments/assets/57a7f37b-dd3e-4a59-962b-089d194166af)

이어서 4번 정점에서도 연결된 모든 간선을 확인하며 최소 비용을 갱신한다.

![](https://github.com/user-attachments/assets/84589da1-f873-44e9-9517-d3727c68a334)

마지막으로 5번 정점에서도 연결된 모든 간선을 확인하며 최소 비용을 갱신한다.

이로써 **첫 번째 반복**이 끝난다. 이번 반복에서 최단 거리 갱신이 발생했으므로 다음 반복을 계속 진행한다. (한 번의 반복에서 갱신이 전혀 발생하지 않으면 알고리즘을 종료한다.)

![](https://github.com/user-attachments/assets/66b74bbf-ffb3-4047-abff-4c4a0bc71d79)

두 번째 반복의 결과는 다음과 같다. 이 반복에서도 최단 거리 갱신이 발생했으므로 다음 반복을 진행한다.

![](https://github.com/user-attachments/assets/dffba307-d85c-4ea0-a05c-c73a8cb87267)

세 번째 반복의 결과는 다음과 같다. 이처럼 모든 간선을 반복적으로 확인하며 최소 비용을 계속 갱신한다.

$$
\vdots
$$

이 과정을 반복하다가 **$n$번째 반복에서도 최단 거리 갱신이 발생한다면**, 그래프에는 **음수 사이클이 존재한다고 판단한다.**

그 이유는 한 번의 반복에서 최소 한 개의 정점의 거리는 반드시 갱신되기 때문이다. (갱신이 전혀 발생하지 않으면 알고리즘이 종료된다.)

시작 정점을 제외하면 거리가 갱신될 수 있는 정점은 최대 $n-1$개이므로 정상적인 경우라면 **$n$번째 반복에서는 더 이상 갱신이 발생할 수 없다.**

따라서 $n$번째 반복에서도 갱신이 발생한다면 이는 **음수 사이클로 인해 거리가 계속 감소하고 있기 때문**이다.

[연습 문제 (백준 11657번)](https://www.acmicpc.net/problem/11657)

``` c++
/** http://boj.kr/42f4592a0ec44609b3ede32dfe7aa19f 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX = 501;

struct element {
    int pos, cost;
};

int n, m;
long long minCost[MAX];
vector<vector<element>> conn(MAX);

/** 
 * Bellman-Ford Algorithm
 * - 음수 사이클이 존재하는 경우 return false
 */
bool bellman_ford() {
    fill(minCost, minCost+MAX, INF);
    minCost[1]=0;
    for(int i=0;i<n;i++) {
        bool change=false;
        for(int cur=1;cur<=n;cur++) { // 모든 정점에 대해 모든 간선을 살펴보기
            if(minCost[cur]==INF) continue; // 도달 못한 정점은 패스
            for(auto next:conn[cur]) {
                long long nextCost = minCost[cur] + next.cost;
                if(nextCost<minCost[next.pos]) {
                    minCost[next.pos] = nextCost;
                    change=true;
                }
            }
        }
        if(!change) return true;
    }
    return false; // n-1번의 업데이트를 진행하고도 변화가 있으면 사이클 존재
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    while(m--) {
        int a, b, c; cin >> a >> b >> c;
        conn[a].push_back({b, c});
    }

    if(!bellman_ford()) { // 사이클이 존재하는 경우
        cout << -1;
        return 0;
    }

    for(int i=2;i<=n;i++) {
        if(minCost[i]==INF) cout << "-1\n";
        else cout << minCost[i] << '\n';
    }
}
```
