## BFS (Breadth First Search)
그래프에서 시작 정점에서 가까운 정점부터 차례대로 탐색하는 알고리즘

큐를 사용해 구현하고, 무가중치 그래프에서 최단 거리를 구할 때 자주 사용된다.

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

![bfs animation1](https://upload.wikimedia.org/wikipedia/commons/4/46/Animated_BFS.gif)

![bfs animation2](https://upload.wikimedia.org/wikipedia/commons/f/f5/BFS-Algorithm_Search_Way.gif)

[연습 문제 (백준 24444번)](https://www.acmicpc.net/problem/24444)

``` c++
/** https://www.acmicpc.net/problem/24444 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 200'001;

int cnt, visited[MAX];
vector<vector<int>> conn(MAX);

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, r; cin >> n >> m >> r;
    while(m--) {
        int u, v; cin >> u >> v;
        conn[u].push_back(v); // u번 노드에서 v번 노드로 이동 가능
        conn[v].push_back(u); // v번 노드에서 u번 노드로 이동 가능
    }
    for(int i=1;i<=n;i++) sort(conn[i].begin(), conn[i].end()); // 문제의 조건: 방문할 수 있는 노드가 여러 개일 때, 오름차순으로 방문

    /** 
     * BFS
     * 가까운 위치의 정점부터 탐색하는 알고리즘
     * 방문할 수 있는 노드가 보이면 큐에 넣는다.
     */
    queue<int> q; q.push(r);
    visited[r] = ++cnt;
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int next: conn[cur]) {
            if(!visited[next]) { // 방문하지 않은 정점이면 방문
                visited[next] = ++cnt;
                q.push(next);
            }
        }
    }
    for(int i=1;i<=n;i++) cout << visited[i] << '\n';
}
```
