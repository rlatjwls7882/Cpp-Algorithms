## DFS (Depth First Search, 깊이 우선 탐색)
그래프에서 한 노드에서 한 경로를 끝까지 따라간 뒤 막히면 이전 분기점으로 되돌아가 다른 분기를 탐색하는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

스택(재귀 호출 스택 또는 자료구조 스택)을 사용해 구현하며, 인접 정점 순서가 탐색 순서를 결정된다.

![DFS animation](https://upload.wikimedia.org/wikipedia/commons/7/7f/Depth-First-Search.gif)

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
