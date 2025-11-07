## BFS (Breadth First Search, 너비 우선 탐색) ⚪ Silver II
그래프에서 시작 정점에서 가까운 정점부터 차례대로 탐색하는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

![](https://github.com/user-attachments/assets/db80081e-9bb2-4fad-9669-bddeb24483cf)

이렇게 연결된 그래프가 있고, 1번 정점에서 탐색을 시작하며, 동시에 여러 개의 정점에 도달할 수 있다면 정점 번호 오름차순으로 이동한다고 가정하자.

![](https://github.com/user-attachments/assets/ef0d9085-aa81-49e1-9e40-50d262bf01bc)

맨 처음에는 1번 정점에 이동할 것이다. 이 정점에서 이동할 수 있는 정점은 2번, 3번, 5번 정점이다.

![](https://github.com/user-attachments/assets/3495d9e2-cf4a-4193-85ca-7a6678630b49)

아직 방문하지 않은 2번, 3번, 5번 정점을 큐에 넣는다.

![](https://github.com/user-attachments/assets/bf9d07b9-4487-4cca-bb59-d98a6e61920b)

큐에서 맨 앞에 있는 2번 정점으로 이동한다. 이 정점에서 이동할 수 있는 정점은 1번, 4번 정점이다.

![](https://github.com/user-attachments/assets/9a6c6e59-133a-4cb6-bc02-9c8c9ab67274)

아직 방문하지 않은 4번 정점을 큐에 넣는다.

![](https://github.com/user-attachments/assets/ed3e841c-c479-4711-8d64-42776d4cd45b)

큐에서 맨 앞에 있는 3번 정점으로 이동한다. 이 정점에서 이동할 수 있는 정점은 1번, 4번 정점이다.

큐에 넣을 수 있는 정점은 없다.

![](https://github.com/user-attachments/assets/828b9bc1-126d-4d38-9edf-04c4ae69cc6f)

큐에서 맨 앞에 있는 5번 정점으로 이동한다. 이 정점에서 이동할 수 있는 정점은 1번 정점이다.

큐에 넣을 수 있는 정점은 없다.

![](https://github.com/user-attachments/assets/99eef719-02b4-4274-9317-9f272fb1f250)

큐에서 맨 앞에 있는 4번 정점으로 이동한다. 이 정점에서 이동할 수 있는 정점은 2번, 3번 정점이다.

큐에 넣을 수 있는 정점은 없다. 큐가 비어 종료한다.

[연습 문제 (백준 24444번)](https://www.acmicpc.net/problem/24444)

``` c++
/** http://boj.kr/5a29153331384b3cb8dc9d68127f6b34 제출 코드 */
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
