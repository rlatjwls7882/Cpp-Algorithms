## Dijkstra's Algorithm
가중치가 음수가 없는 그래프에서, 시작 정점으로부터 누적 거리가 가장 짧은 정점부터 차례대로 탐색하여 최단 거리를 구하는 알고리즘

시간복잡도 : O(ElogV)

![](https://github.com/user-attachments/assets/4dc78915-77eb-40fd-b10f-302e896da370)

이렇게 연결된 그래프가 있고 1번 정점에서 탐색을 시작한다고 가정하자.

![](https://github.com/user-attachments/assets/7adf008b-e4d8-4e39-b011-a484d5ade1fa)

1번 정점을 탐색할 때 접근 가능한 정점은 2번, 3번, 5번 정점이다.

1번 정점에서 만들 수 있는 (정점, 비용) 쌍은 (2, 4), (5, 1), (3, 3)이고 이를 우선순위 큐에 넣는다.

![](https://github.com/user-attachments/assets/14d50282-3026-4e60-97b5-d5c41bae7fb5)

우선순위 큐에서 비용이 가장 적은 쌍인 (5, 1)를 꺼내 비용을 기록한다.

5번 정점에서 만들 수 있는 쌍은 (1, 2), (2, 4), (3, 6), (4, 4)이고, 이 중 비용이 더 적은 (2, 4), (3, 6), (4, 4)만 우선순위 큐에 넣는다.

![](https://github.com/user-attachments/assets/7e770bd8-16d1-43da-ab47-48202156d87f)

우선순위 큐에서 비용이 가장 적은 쌍인 (3, 3)를 꺼내 비용을 기록한다.

3번 정점에서 만들 수 있는 쌍은 (1, 6), (4, 4), (5, 8)이고, 이 중 비용이 더 적은 (4, 4)만 우선순위 큐에 넣는다.

![](https://github.com/user-attachments/assets/956ca1d2-b1da-4e1d-8183-9f2edc5402d3)

우선순위 큐에서 비용이 가장 적은 쌍인 (2, 4)를 꺼내 비용을 기록한다.

3번 정점에서 만들 수 있는 쌍은 (1, 8), (4, 6), (5, 7)이고, 이 중 비용이 더 적은 (4, 6)만 우선순위 큐에 넣는다.

![](https://github.com/user-attachments/assets/fa6d179f-6399-419c-8a6c-5bd70f7a4cad)

우선순위 큐에서 비용이 가장 적은 쌍인 (2, 4)를 꺼내고 비용이 커서 패스, (4, 4)를 꺼내 비용을 기록한다.

4번 정점에서 만들 수 있는 쌍은 (2, 6), (3, 5), (5, 7)이고, 이 중 비용이 더 적은 쌍이 없어 우선순위 큐에 넣지 않는다.

이후 기록된 비용보다 더 적은 비용 쌍이 없어 이대로 종료된다.

[연습 문제 (백준 1753번)](https://www.acmicpc.net/problem/1753)

``` c++
/** https://www.acmicpc.net/problem/1753 제출 코드 */
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
    ios::sync_with_stdio(0); cin.tie(0);
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
