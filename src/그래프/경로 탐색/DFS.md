## DFS (Depth First Search, 깊이 우선 탐색) ⚪ Silver II
그래프에서 한 경로를 가능한 깊게 탐색하다가 막히면 이전 분기점으로 돌아가 다른 경로를 탐색하는 알고리즘

시간복잡도: $O(V+E)$ ($V$: 정점 수, $E$: 간선 수)

![](https://github.com/user-attachments/assets/db80081e-9bb2-4fad-9669-bddeb24483cf)

위와 같이 연결된 그래프가 있다고 하자. 탐색은 **1번 정점에서 시작**하며 동시에 여러 정점으로 이동할 수 있는 경우 **정점 번호가 작은 순서**로 이동한다고 가정한다.

![](https://github.com/user-attachments/assets/8e516255-81ff-4613-92cf-19bd4cf4906e)

처음에는 시작 정점인 **1번 정점**에 위치한다. 1번 정점과 연결된 정점은 **2번, 3번, 5번**이다.

![](https://github.com/user-attachments/assets/f76ca427-fc54-4973-a45d-336b4c019c12)

이 중 가장 번호가 작은 **2번 정점으로 이동**한다. 2번 정점과 연결된 정점은 **1번, 4번**이다.

![](https://github.com/user-attachments/assets/468737e5-96e1-4620-8949-1e23a13fc493)

이미 방문한 **1번 정점은 제외**하고 **4번 정점으로 이동**한다. 4번 정점과 연결된 정점은 **2번, 3번**이다.

![](https://github.com/user-attachments/assets/53262d6d-2bcf-42a3-8ebc-ee005e6cace7)

이미 방문한 **2번 정점을 제외**하고 **3번 정점으로 이동**한다. 3번 정점과 연결된 정점은 **1번, 4번**이다.

![](https://github.com/user-attachments/assets/627977c5-1096-4d25-b199-336ade9e290b)

3번 정점에서 **방문하지 않은 정점이 없으므로** 이전에 방문했던 **4번 정점으로 되돌아간다.**

![](https://github.com/user-attachments/assets/dd166840-59d0-4261-80d2-1fb30962a137)

4번 정점에서도 더 이상 방문할 정점이 없으므로 이전에 방문했던 **2번 정점으로 되돌아간다.**

![](https://github.com/user-attachments/assets/6b7aabf4-f160-4a01-a25c-a4916c98c0b4)

2번 정점에서도 더 이상 방문할 정점이 없어 **1번 정점으로 되돌아간다.**

![](https://github.com/user-attachments/assets/ffce1c6d-b433-40ed-a914-73c7e4dc6aaf)

1번 정점으로 돌아왔을 때 **3번 정점은 이미 방문된 상태**이므로 이동하지 않고 다음으로 번호가 작은 **5번 정점으로 이동**한다.

![](https://github.com/user-attachments/assets/63cf3983-9f68-42f8-88e1-faa82526da9e)

5번 정점에서 방문하지 않은 정점이 없으므로 **1번 정점으로 되돌아온다.** 이후 1번 정점에서도 더 이상 방문할 정점이 없으므로 **탐색이 종료된다.**

이와 같이 DFS는 한 경로를 가능한 한 깊게 탐색하다가 더 이상 방문할 수 있는 정점이 없으면 이전 정점으로 되돌아가 다른 경로를 탐색하는 방식으로 동작한다.

[연습 문제 (백준 24479번)](https://www.acmicpc.net/problem/24479)

``` c++
/** http://boj.kr/ca29bf44e6ec44d7ab2d37e0264c9879 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

int cnt, visited[200'001];
vector<vector<int>> conn(200'001);

/** 
 * DFS
 * 방문할 수 있는 노드가 보이면 이동.
 * 방문할 수 있는 노드가 보이지 않으면 다시 뒤로 되돌아감.
 * 미로 찾기에서 왼손의 법칙을 쓰는 것과 유사함.
 */
void dfs(int cur) {
    visited[cur] = ++cnt; // 방문 순서 마킹
    for(int next:conn[cur]) {
        if(!visited[next]) { // 방문하지 않은 정점이면 방문
            dfs(next);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, r; cin >> n >> m >> r;
    while(m--) {
        int u, v; cin >> u >> v;
        conn[u].push_back(v); // u번 노드에서 v번 노드로 이동 가능
        conn[v].push_back(u); // v번 노드에서 u번 노드로 이동 가능
    }
    for(int i=1;i<=n;i++) sort(conn[i].begin(), conn[i].end()); // 문제의 조건: 방문할 수 있는 노드가 여러 개일 때, 오름차순으로 방문

    dfs(r); // DFS 시작
    for(int i=1;i<=n;i++) cout << visited[i] << '\n';
}
```
