## Edmonds-Karp Algorithm 🟢 Platinum IV
그래프에서 시작 지점(source)에서 유량을 흘려서, 도착 지점(sink)까지 유량이 얼마나 도착하는지 찾는 알고리즘

시간복잡도: $O(VE^2)$ ($V$: 정점 수, $E$: 간선 수)

![](https://github.com/user-attachments/assets/f3d8703f-6bda-401f-889a-458d27e8b002)

다음과 같은 그래프가 주어졌다고 하자. 간선의 f/c에서 f는 현재 흐르는 유량(flow), c는 간선의 총 용량(capacity)을 의미한다. prev 배열은 BFS 탐색 과정에서 각 정점이 어떤 정점을 통해 방문되었는지를 저장하는 배열이다. 먼저 S에서 탐색을 시작하고 유량을 더 보낼 수 있는 간선(c-f>0)을 따라 BFS를 수행한다. 이때 S에서 갈 수 있는 정점인 1번, 3번 정점을 큐에 넣는다. 이후 BFS를 계속 진행하여 sink인 E까지 도달 가능한 경로를 찾는다.

![](https://github.com/user-attachments/assets/6730b216-1533-4936-88f2-7a3d92b22269)

BFS를 통해 만들어진 prev 배열을 이용하여 E에서 S까지 거슬러 올라가며 증가 경로(augmenting path)를 찾는다. 이 경우 경로는 **S → 1 → 2 → E**이며 이 경로에서 흘릴 수 있는 최대 유량은 각 간선의 남은 용량 중 최소값인 **2**이다. 따라서 이 경로의 순방향 간선에는 **+2**만큼 유량을 추가하고 역방향 간선에는 **-2**만큼 유량을 갱신한다.

![](https://github.com/user-attachments/assets/0b9eef43-ce78-49f2-bba2-75608660e4de)

prev 배열을 초기화한 뒤 다시 S부터 BFS를 수행하여 새로운 증가 경로를 찾는다. 이번에는 **S → 3 → 4 → E** 경로가 발견되고 이 경로에서 보낼 수 있는 최대 유량은 **1**이다. 따라서 해당 경로의 순방향 간선에는 **+1**, 역방향 간선에는 **-1**만큼 유량을 갱신한다.

![](https://github.com/user-attachments/assets/7f98653f-5833-4d15-baa0-7f0dab8d2a6f)

다음 반복에서는 S에서 E까지 더 이상 유량을 보낼 수 있는 경로가 존재하지 않는다. 따라서 알고리즘이 종료되며 최종적으로 얻은 최대 유량은 **3**이다.

---

지금까지의 설명에서는 순방향 간선만을 이용해 증가 경로를 찾았다. 하지만 실제 알고리즘에서는 역방향 간선(residual edge)을 이용해 더 나은 경로를 찾을 수도 있다.

![](https://github.com/user-attachments/assets/428951c0-c683-48e5-8b68-6c6e9169fe4b)

예를 들어 처음에 **S → 3 → 2 → E** 경로로 유량 1이 흐르고 이후 **S → 1 → 2 → E** 경로로 유량 1이 흐른 상태라고 하자.

![](https://github.com/user-attachments/assets/bd0dd2ad-6a25-4e06-b8e5-0e4818c1e924)

이 상태에서 순방향 간선만 보면 더 이상 S에서 E로 보낼 수 있는 경로가 없는 것처럼 보인다. 그러나 잔여 그래프(residual graph)에서는 역방향 간선을 사용할 수 있다. 간선 **3 → 2**의 역방향 간선인 **2 → 3**을 고려하면 새로운 경로를 만들 수 있다.

![](https://github.com/user-attachments/assets/6846050d-72e8-422d-b6b2-94be7229b862)

이 역방향 간선을 포함하면 **S → 1 → 2 → 3 → 4 → E** 경로로 유량을 다시 보낼 수 있다. 모든 유량이 흐른 뒤의 최종 결과만 보면 이는 **S → 3 → 4 → E** 경로로 1의 유량, **S → 1 → 2 → E** 경로로 2의 유량이 흐른 것과 동일한 상태가 된다.

[연습 문제 (백준 17412번)](https://www.acmicpc.net/problem/17412)

``` c++
/** http://boj.kr/abf5d13ef49941ca81ce5ad00ea918a9 제출 코드 */
#include <bits/stdc++.h>
using namespace std;

/**
 * MAX : 해당 문제의 최대 정점의 개수
 * S : source (시작점)
 * E : sink (도착점)
 */
const int INF = 0x3f3f3f3f;
const int MAX = 400;
const int S = 0;
const int E = 1;

/**
 * c[u][v] : u에서 v로의 최대 용량 (capacity)
 * f[u][v] : u에서 v로 흐르는 유량 (flow)
 * prv[i] : i에 도달하기 위해 방문한 이전 정점
 * conn[u][v] : 순방향 간선
 * conn[v][u] : 역방향 간선
 */
int c[MAX][MAX], f[MAX][MAX], prv[MAX];
vector<vector<int>> conn(MAX);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, P; cin >> N >> P;

    /** 
     * 정점에 간선 추가
     * 최적의 경로를 찾아 flow를 더 흘리기 위해 역방향 간선도 추가해줘야함.
     */
    while(P--) {
        int u, v; cin >> u >> v;
        c[u-1][v-1]++;
        conn[u-1].push_back(v-1);
        conn[v-1].push_back(u-1);
    }

    /** 
     * S -> E 로의 bfs 탐색
     * prv[next] = cur : 역추적을 위해 next -> cur 경로 기록
     */
    int totalFlow=0;
    while(true) {
        memset(prv, -1, sizeof prv);
        queue<int> q; q.push(S);

        while(!q.empty() && prv[E]==-1) {
            int cur = q.front(); q.pop();
            for(int next:conn[cur]) {
                if(c[cur][next]-f[cur][next]>0 && prv[next]==-1) {
                    prv[next] = cur;
                    if(next==E) break;
                    q.push(next);
                }
            }
        }
        if(prv[E]==-1) break; // 더이상 sink에 도달 못하면 종료

        /** 
         * sink부터 역추적하면서 최대로 흘릴 수 있는 flow를 찾고, 유량 흘리기
         * f[prv[i]][i] : 순방향 간선이어서 flow만큼 채워짐
         * f[i][prv[i]] : 역방향 간선이어서 flow만큼 빠짐 (더 나은 간선이 있는지 찾기 위해 쓰임)
         */
        int flow=INF;
        for(int i=E;i!=S;i=prv[i]) {
            flow = min(flow, c[prv[i]][i]-f[prv[i]][i]);
        }
        for(int i=E;i!=S;i=prv[i]) {
            f[prv[i]][i] += flow;
            f[i][prv[i]] -= flow;
        }
        totalFlow += flow;
    }
    cout << totalFlow;
}
```
