## Dijkstra's Algorithm 🟡 Gold IV
가중치가 음수가 없는 그래프에서 시작 정점으로부터의 최단 거리를 구하는 알고리즘

시간복잡도: $O(ElogV)$ ($V$: 정점 수, $E$: 간선 수)

![](https://github.com/user-attachments/assets/4dc78915-77eb-40fd-b10f-302e896da370)

위와 같이 연결된 그래프가 있고 **1번 정점에서 탐색을 시작**한다고 가정하자.

![](https://github.com/user-attachments/assets/7adf008b-e4d8-4e39-b011-a484d5ade1fa)

먼저 **1번 정점**을 방문한다. 1번 정점과 연결된 정점은 **2번, 3번, 5번**이다. 이때 만들 수 있는 (정점, 비용) 쌍은 (2, 4), (5, 1), (3, 3)이며 이를 **우선순위 큐에 넣는다.**

![](https://github.com/user-attachments/assets/14d50282-3026-4e60-97b5-d5c41bae7fb5)

우선순위 큐에서 비용이 가장 작은 쌍인 (5, 1)을 꺼내고 **5번 정점의 최단 거리를 1로 기록한다.** 5번 정점에서 만들 수 있는 쌍은 (1, 2), (2, 4), (3, 6), (4, 4)이다. 이미 기록된 최단 거리보다 **더 작은 경우만** 우선순위 큐에 넣으므로 (2, 4), (3, 6), (4, 4)를 큐에 추가한다.

![](https://github.com/user-attachments/assets/7e770bd8-16d1-43da-ab47-48202156d87f)

우선순위 큐에서 비용이 가장 작은 쌍인 (3, 3)을 꺼내고 **3번 정점의 최단 거리를 3으로 기록한다.** 3번 정점에서 만들 수 있는 쌍은 (1, 6), (4, 4), (5, 8)이다. 이 중 기존 최단 거리보다 작은 경우만 큐에 넣으므로 (4, 4)만 추가된다.

![](https://github.com/user-attachments/assets/956ca1d2-b1da-4e1d-8183-9f2edc5402d3)

우선순위 큐에서 (2, 4)를 꺼내고 **2번 정점의 최단 거리를 4로 기록한다.** 2번 정점에서 만들 수 있는 쌍은 (1, 8), (4, 6), (5, 7)이다. 이 중 기존 최단 거리보다 작은 경우는 (4, 6)뿐이므로 이를 우선순위 큐에 넣는다.

![](https://github.com/user-attachments/assets/fa6d179f-6399-419c-8a6c-5bd70f7a4cad)

다음으로 우선순위 큐에서 (2, 4)가 나오지만 이미 더 짧은 거리로 처리된 상태이므로 **무시한다.** 그 다음 (4, 4)를 꺼내고 **4번 정점의 최단 거리를 4로 기록한다.** 4번 정점에서 만들 수 있는 쌍은 (2, 6), (3, 5), (5, 7)이며 기존 최단 거리보다 작은 경우가 없으므로 우선순위 큐에 추가하지 않는다.

이후 더 이상 최단 거리를 갱신할 수 있는 정점이 없으므로 **탐색이 종료된다.**

[연습 문제 (백준 1753번)](https://www.acmicpc.net/problem/1753)

``` c++
/** http://boj.kr/e655a4c35f9b4f9b8862d49ff4009992 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX = 20001;

struct element {
    int pos, cost;
    bool operator<(const element e) const {
        return cost > e.cost; // 우선순위 큐라 일반 정렬과 부호 반대
    }
};

int minCost[MAX]; // 최단 거리를 저장하는 배열
vector<vector<element>> conn(MAX);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int v, e, k; cin >> v >> e >> k;
    while(e--) {
        int u, v, w; cin >> u >> v >> w;
        conn[u].push_back({v, w}); // 단방향 간선
    }

    /** 
     * Dijkstra Algorithm
     * 우선순위 큐에서 비용이 작은 경로부터 꺼내 탐색함
     */
    fill(minCost, minCost+MAX, INF); // 기본값 초기화
    priority_queue<element> pq; pq.push({k, 0}); // 시작 정점 넣기
    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        if(minCost[cur.pos]<=cur.cost) continue; // 현재 경로가 비용이 더 크다면 제외
        minCost[cur.pos] = cur.cost;

        for(auto next:conn[cur.pos]) {
            int nextCost = cur.cost + next.cost;
            if(nextCost<minCost[next.pos]) { // 현재 경로로 다음 정점에 도달하는 비용이 더 적다면
                pq.push({next.pos, nextCost});
            }
        }
    }

    for(int i=1;i<=v;i++) {
        if(minCost[i]==INF) cout << "INF\n";
        else cout << minCost[i] << '\n';
    }
}
```
