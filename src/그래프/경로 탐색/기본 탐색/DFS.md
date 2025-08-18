## DFS (Depth First Search, 깊이 우선 탐색)
그래프에서 한 정점에서 한 경로를 끝까지 따라간 뒤 막히면 이전 분기점으로 되돌아가 다른 분기를 탐색하는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

![](https://github.com/user-attachments/assets/db80081e-9bb2-4fad-9669-bddeb24483cf)

이렇게 연결된 그래프가 있고, 1번 정점에서 탐색을 시작하며, 동시에 여러 개의 정점에 도달할 수 있다면 정점 번호 오름차순으로 이동한다고 가정하자.

![](https://github.com/user-attachments/assets/8e516255-81ff-4613-92cf-19bd4cf4906e)

맨 처음에는 1번 정점에 이동할 것이다. 이 정점에서 이동할 수 있는 정점은 2번, 3번, 5번 정점이다.

![](https://github.com/user-attachments/assets/f76ca427-fc54-4973-a45d-336b4c019c12)

2번, 3번, 5번 정점 중 번호가 작은 2번으로 이동한다. 2번 정점에서 이동할 수 있는 정점은 1번, 4번 정점이다.

![](https://github.com/user-attachments/assets/468737e5-96e1-4620-8949-1e23a13fc493)

방문한 정점인 1번을 제외하고 가장 작은 4번에 이동한다. 4번 정점에서 이동할 수 있는 정점은 2번, 3번 정점이다.

![](https://github.com/user-attachments/assets/53262d6d-2bcf-42a3-8ebc-ee005e6cace7)

방문한 정점인 2번을 제외하고 가장 작은 3번에 이동한다. 3번 정점에서 이동할 수 있는 정점은 1번, 4번 정점이다.

![](https://github.com/user-attachments/assets/627977c5-1096-4d25-b199-336ade9e290b)

더 이상 3번 정점에서 이동할 수 있는 정점에 없어서 이전에 방문한 4번 정점으로 되돌아온다.

![](https://github.com/user-attachments/assets/dd166840-59d0-4261-80d2-1fb30962a137)

더 이상 4번 정점에서 이동할 수 있는 정점에 없어서 이전에 방문한 2번 정점으로 되돌아온다.

![](https://github.com/user-attachments/assets/6b7aabf4-f160-4a01-a25c-a4916c98c0b4)

더 이상 2번 정점에서 이동할 수 있는 정점에 없어서 이전에 방문한 1번 정점으로 되돌아온다.

![](https://github.com/user-attachments/assets/ffce1c6d-b433-40ed-a914-73c7e4dc6aaf)

3번 정점은 이미 방문한 상태여서 이동하지 않고, 5번 정점으로 이동한다. 5번 정점에서 이동 가능한 정점은 1번 정점이다.

![](https://github.com/user-attachments/assets/63cf3983-9f68-42f8-88e1-faa82526da9e)

5번 정점이서 이동할 수 있는 정점이 없어, 1번 정점으로 돌아오고, 1번 정점에서도 이동할 수 있는 정점이 없어 종료한다.

[연습 문제 (백준 24479번)](https://www.acmicpc.net/problem/24479)

``` c++
/** https://www.acmicpc.net/problem/24479 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 200'001;

int cnt, visited[MAX];
vector<vector<int>> conn(MAX);

/** 
 * DFS
 * 방문할 수 있는 노드가 보이면 이동.
 * 방문할 수 있는 노드가 보이지 않으면 다시 뒤로 되돌아감.
 * 미로 찾기에서 왼손의 법칙을 쓰는 것과 같음.
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
    ios::sync_with_stdio(0); cin.tie(0);
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
