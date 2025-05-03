## Tarjan’s Algorithm

그래프에서 나타나는 [SCC (Strongly Connected Component)](https://ko.wikipedia.org/wiki/%EA%B0%95%ED%95%9C_%EC%97%B0%EA%B2%B0_%EC%9A%94%EC%86%8C)을 한번의 dfs로 뽑아내는 알고리즘
SCC : 임의의 두 정점 사이에 사이클이 존재해 서로 왔다 갔다 할 수 있는 정점들의 그룹

시간복잡도 : O(V + E) (V : 정점 수, E : 간선 수)

[연습 문제 (백준 2150번)](https://www.acmicpc.net/problem/2150)

``` c++
/** https://www.acmicpc.net/problem/2150 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/** 
 * MAX : 최대 정점 개수
 * visited[i] : i번 정점이 현재 임의의 SCC에 포함되었는지 여부
 * idx : 각 정점에 할당하는 SCC번호 (dfs 탐색 순서로 SCC번호를 할당해서 정점번호와는 다르게 할당됨, 같은 값을 가진 정점들은 같은 SCC에 속함)
 * parent[i] : i번 정점과 같은 SCC에 속하며 갈 수 있는 제일 작은 SCC 번호
 * conn[i][j] : i에서 j로의 간선
 * SCCs[i][j] : i번째 SCC의 j번째 정점 (각각의 SCC는 위상정렬되어 나타나기에 i가 클수록 더 우선순위가 높음)
 * stk : SCC를 뽑아내기 위해 사용하는 스택
 */
const int MAX = 10001;

bool visited[MAX];
int idx, parent[MAX];
vector<vector<int>> conn(MAX), SCCs;
stack<int> stk;

int dfs(int cur) {
    /** 
     * 스택에 현재 정점 번호를 넣고, parent[cur]에 SCC 번호를 기록함
     * rem : 현재의 정점에서 도달할 수 있는 가장 작은 SCC 번호
     * parent[cur] :
     * SCC에 포함 안되었을 때 -> 현재의 정점에 할당된 SCC번호
     * SCC에 포함 되었을 때 -> 같은 SCC에 속한 가장 작은 SCC번호
     */
    stk.push(cur);
    int rem = parent[cur] = ++idx;
    
    /** 
     * 현재 정점에서 이동할 수 있는 정점에 대해:
     * 한번도 방문한 적이 없는 정점은 그 정점에 대해 dfs 탐색을 하고 그 정점에서 도달 가능한 가장 작은 SCC 번호를 받아오고,
     * 방문한 적은 있지만 현재 어떠한 SCC에도 소속되지 않은 정점에 대해서는 그 정점의 SCC 번호를 받아온다.
     * prof. 방문한 적이 있지만 어떠한 SCC에도 소속되지 않았다는 것은 해당 정점에서 도달 가능한 다른 정점과는 같은 SCC에 속할 수 없음을 뜻함
     * 
     * 현재 정점보다 받아온 SCC번호가 큰 경우 : 순방향 간선을 타고 간 것
     * 현재 정점보다 받아온 SCC번호가 작은 경우 : 역방향 간선을 타고 간 것 -> 사이클이 존재할 가능성이 있음
     */
    for(int next:conn[cur]) {
        if(!parent[next]) rem = min(rem, dfs(next));
        else if(!visited[next]) rem = min(rem, parent[next]);
    }

    /** 
     * 현재 도달 가능한 가장 작은 SCC번호가 자기 자신인 경우 -> 사이클 발견
     * prof. rem == parent[cur] == top인 경우(자신으로부터 도달한 다른 정점에서 다시 돌아오지 못한 경우, 사이클 존재 X) 크기가 1인 SCC 발견
     * prof. rem == parent[cur] != top인 경우(자신으로부터 도달한 다른 정점에서 다시 돌아온 경우, 사이클 존재 O) 크기가 1보다 큰 SCC 발견
     * 
     * 스택에서 자기 자신을 발견할 때까지 뽑아 같은 SCC에 집어넣기
     * 
     * 집어넣으면서:
     * visited[top] = true;을 해줘서 SCC에 포함되었다 마킹
     * parent[top] = rem;을 해줘서 도달 가능한 가장 작은 SCC번호로 설정
     */
    if(rem==parent[cur]) {
        SCCs.push_back(vector<int>());
        while(true) {
            int top = stk.top(); stk.pop();
            SCCs.back().push_back(top);
            visited[top] = true;
            parent[top] = rem;
            if(top==cur) break;
        }
    }
    return rem;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int v, e; cin >> v >> e;

    // 간선 연결
    while(e--) {
        int a, b; cin >> a >> b;
        conn[a].push_back(b);
    }

    /** Tarjan's Algorithm 시작 */
    for(int i=1;i<=v;i++) {
        if(!visited[i]) dfs(i);
    }
    /** Tarjan's Algorithm 끝 */

    for(int i=0;i<SCCs.size();i++) {
        sort(SCCs[i].begin(), SCCs[i].end());
    }
    sort(SCCs.begin(), SCCs.end());

    cout << SCCs.size() << '\n';
    for(auto SCC:SCCs) {
        for(int val:SCC) {
            cout << val << ' ';
        }
        cout << "-1\n";
    }
}
```
