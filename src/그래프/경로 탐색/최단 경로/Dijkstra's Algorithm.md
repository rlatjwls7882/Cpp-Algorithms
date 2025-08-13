\## \[Dijkstra's Algorithm (다익스트라 알고리즘)](src/그래프/경로%20탐색/최단%20경로/Dijkstra's%20Algorithm)

가중치가 음수가 없는 그래프에서, 시작 정점으로부터 누적 거리가 가장 짧은 정점부터 차례대로 탐색하여 최단 거리를 구하는 알고리즘



우선순위 큐와 최단 거리 배열을 사용해, 더 짧은 경로를 발견할 때마다 업데이트한다.



시간복잡도 : O(ElogV)



!\[Dijkstra's Algorithm Animation](https://upload.wikimedia.org/wikipedia/commons/5/57/Dijkstra\_Animation.gif)



\[연습 문제 (백준 1753번)](https://www.acmicpc.net/problem/1753)



``` c++

/\*\* https://www.acmicpc.net/problem/1753 제출 코드 \*/

\#include<bits/stdc++.h>

using namespace std;



const int INF = 0x3f3f3f3f;

const int MAX = 20001;



struct element {

&nbsp;   int pos, cost;

&nbsp;   bool operator<(const element e) const {

&nbsp;       return cost > e.cost; // 우선순위 큐라 일반 정렬과 부호 반대

&nbsp;   }

};



int minCost\[MAX];

vector<vector<element>> conn(MAX);



int main() {

&nbsp;   ios::sync\_with\_stdio(0); cin.tie(0);

&nbsp;   int v, e, k; cin >> v >> e >> k;

&nbsp;   while(e--) {

&nbsp;       int u, v, w; cin >> u >> v >> w;

&nbsp;       conn\[u].push\_back({v, w}); // 단방향 간선

&nbsp;   }



&nbsp;   /\*\* 

&nbsp;    \* Dijkstra Algorithm

&nbsp;    \* 우선순위 큐에서 비용이 작은 경로부터 꺼내 탐색함

&nbsp;    \*/

&nbsp;   fill(minCost, minCost+MAX, INF); // 기본값 초기화

&nbsp;   priority\_queue<element> pq; pq.push({k, 0}); // 시작 정점 넣기

&nbsp;   while(!pq.empty()) {

&nbsp;       auto cur = pq.top(); pq.pop();

&nbsp;       if(minCost\[cur.pos]<=cur.cost) continue; // 현재 경로가 비용이 더 크다면 제외

&nbsp;       minCost\[cur.pos] = cur.cost;



&nbsp;       for(auto next:conn\[cur.pos]) {

&nbsp;           int nextCost = cur.cost + next.cost;

&nbsp;           if(nextCost<minCost\[next.pos]) { // 현재 경로로 다음 정점에 도달하는 비용이 더 적다면

&nbsp;               pq.push({next.pos, nextCost});

&nbsp;           }

&nbsp;       }

&nbsp;   }



&nbsp;   for(int i=1;i<=v;i++) {

&nbsp;       if(minCost\[i]==INF) cout << "INF\\n";

&nbsp;       else cout << minCost\[i] << '\\n';

&nbsp;   }

}

```

