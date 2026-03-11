## BFS (Breadth First Search, 너비 우선 탐색) ⚪ Silver II
그래프에서 시작 정점으로부터 가까운 정점부터 차례대로 탐색하는 알고리즘

시간복잡도: $O(V+E)$ ($V$: 정점 수, $E$: 간선 수)

![](https://github.com/user-attachments/assets/db80081e-9bb2-4fad-9669-bddeb24483cf)

위와 같이 연결된 그래프가 있다고 하자. 탐색은 **1번 정점에서 시작**하며, 동시에 여러 정점으로 이동할 수 있는 경우 **정점 번호가 작은 순서**로 방문한다고 가정한다.

![](https://github.com/user-attachments/assets/ef0d9085-aa81-49e1-9e40-50d262bf01bc)

처음에는 **1번 정점**에서 탐색을 시작한다. 1번 정점과 연결된 정점은 **2번, 3번, 5번**이다.

![](https://github.com/user-attachments/assets/3495d9e2-cf4a-4193-85ca-7a6678630b49)

아직 방문하지 않은 정점인 **2번, 3번, 5번 정점을 큐에 순서대로 넣는다.**

![](https://github.com/user-attachments/assets/bf9d07b9-4487-4cca-bb59-d98a6e61920b)

큐의 맨 앞에 있는 **2번 정점**을 꺼내 방문한다. 2번 정점과 연결된 정점은 **1번, 4번**이다.

![](https://github.com/user-attachments/assets/9a6c6e59-133a-4cb6-bc02-9c8c9ab67274)

이미 방문한 1번 정점을 제외하고, **4번 정점을 큐에 넣는다.**

![](https://github.com/user-attachments/assets/ed3e841c-c479-4711-8d64-42776d4cd45b)

다음으로 큐의 맨 앞에 있는 **3번 정점**을 방문한다. 3번 정점과 연결된 정점은 **1번, 4번**이지만, 모두 이미 방문했거나 큐에 들어 있으므로 추가되는 정점은 없다.

![](https://github.com/user-attachments/assets/828b9bc1-126d-4d38-9edf-04c4ae69cc6f)

다음으로 큐의 맨 앞에 있는 **5번 정점**을 방문한다. 5번 정점과 연결된 정점은 **1번 정점**뿐이며 이미 방문했으므로 큐에 추가되는 정점은 없다.

![](https://github.com/user-attachments/assets/99eef719-02b4-4274-9317-9f272fb1f250)

마지막으로 큐의 맨 앞에 있는 **4번 정점**을 방문한다. 4번 정점과 연결된 정점은 **2번, 3번**이지만 이미 방문했으므로 큐에 추가되는 정점은 없다.

이후 **큐가 비게 되므로 탐색이 종료된다.**

[연습 문제 (백준 24444번)](https://www.acmicpc.net/problem/24444)

``` c++
/** http://boj.kr/5a29153331384b3cb8dc9d68127f6b34 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

int cnt, visited[200'001];
vector<vector<int>> conn(200'001);

int main() {
    cin.tie(0)->sync_with_stdio(0);
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
