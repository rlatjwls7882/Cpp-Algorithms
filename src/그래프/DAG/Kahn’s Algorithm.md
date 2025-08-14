## Kahn’s Algorithm (Topological Sort, 위상 정렬)
방향성이 있고 사이클이 없는 그래프[(DAG)](https://ko.wikipedia.org/wiki/유향_비순환_그래프)에서, 모든 정점을 선행 관계를 만족하도록 나열하는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

![Kahn's Algorithm GIF](https://iq.opengenus.org/content/images/2020/03/algo.gif)

[연습 문제 (백준 2252번)](https://www.acmicpc.net/problem/2252)

``` c++
/** https://www.acmicpc.net/problem/2252 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/** 
 * MAX : 최대 정점 수
 * inDegree[i] : 정점 i으로 들어오는 간선의 개수
 * conn[i] : 정점 i에서 다른 정점으로 향하는 간선들
 */
const int MAX = 32'001;

int inDegree[MAX];
vector<vector<int>> conn(MAX);

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    while(m--) {
        int a, b; cin >> a >> b;
        inDegree[b]++; // 정점 b로 들어오는 간선의 개수 +1
        conn[a].push_back(b); // 정점 a에서 정점 b로의 간선 연결
    }

    /** 
     * Kahn’s Algorithm (Topological Sort)
     * 정점 i에 들어오는 간선이 없는 경우 큐에 추가
     * - i에 들어오는 간선이 없다는 뜻은 i보다 선행되야만 하는 정점이 없다는 뜻
     */
    queue<int> q;
    for(int i=1;i<=n;i++) {
        if(!inDegree[i]) {
            q.push(i);
        }
    }

    /** 
     * 정점 cur에서 도착 가능한 바로 다음 정점의 inDegree 값을 1씩 감소
     * 다음 정점의 inDegree 값이 0이 되면 큐에 추가
     * - inDegree[next]==0 -> next보다 선행되야 하는 정점이 없다.
     * 이 문제에서는 사이클이 없지만 만약 사이클이 있다면 큐에 들어가는 총 정점 수가 n보다 작음
     */
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        cout << cur << ' ';
        for(int next:conn[cur]) {
            if(--inDegree[next]==0) q.push(next);
        }
    }
}
```
