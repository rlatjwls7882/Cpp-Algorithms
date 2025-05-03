## 2-SAT (2-Satisfiability Problem)
2개의 변수로 이루어진 [CNF](https://ko.wikipedia.org/wiki/%EB%85%BC%EB%A6%AC%EA%B3%B1_%ED%91%9C%EC%A4%80%ED%98%95)가 주어졌을 때, 이를 만족시도록 변수에 (True/False)를 대입 가능한지 [Implication Graph](https://en.wikipedia.org/wiki/Implication_graph)를 만들어 SCC를 형성해 확인하는 문제

2-SAT 문제에서 (A∨B) ∧ (B∨C)인 경우 A 또는 B가 참이어야 하고, B 또는 C가 참이어야 한다.

이를 말로 풀어서 쓰면 다음과 같다.

A가 참이 아닌 경우 B가 참이어야하고, B가 참이 아닌 경우 A가 참이어야 한다. **그리고** B가 참이 아닌 경우 C가 참이어야하고, C가 참이 아닌 경우 B가 참이어야 한다.

이 네 개의 조건을 동시에 만족해야 한다.

이를 그래프로 나타내면 notA -> B, notB -> A, notB -> C, notC -> B 의 4개의 노드와 4개의 간선으로 나타내진다.

이렇게 모든 간선에 대해 SCC를 뽑아내고, 각각의 SCC가 동시에 만족해야 하는 집합들이니 notA와 A가 같은 SCC 안에 있는 경우가 2-SAT 문제에서 조건을 만족시키도록 할당이 불가능한 경우이다.

[연습 문제 (백준 11280번)](https://www.acmicpc.net/problem/11280)

``` c++
/** https://www.acmicpc.net/problem/11280 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 20000; // MAX : 최대 정점 수 (입력된 n 값의 2배)

/** Tarjan's Algorithm 시작 */
int idx, parent[MAX];
bool visited[MAX];
vector<vector<int>> conn(MAX), SCCs;
stack<int> stk;

int dfs(int cur) {
    stk.push(cur);
    int rem = parent[cur] = ++idx;

    for(int next:conn[cur]) {
        if(!parent[next]) rem = min(rem, dfs(next));
        else if(!visited[next]) rem = min(rem, parent[next]);
    }

    if(rem == parent[cur]) {
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
/** Tarjan's Algorithm 끝 */

/** -1과 1은 각각 0과 1번 정점으로 할당 */
int oppo(int x) {
    return x%2==0 ? x+1 : x-1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    /** 
     * 모든 정점들을 False 정점과 True 정점 두개로 분할.
     * False 정점의 경우 짝수번째로 할당.
     * True 정점의 경우 홀수번째로 할당.
     * 
     * 각각의 조건에 대해:
     * notX -> Y (X가 참이 아니라면 Y가 참이어야 한다.)
     * notY -> X (Y가 참이 아니라면 X가 참이어야 한다.)
     * 두 간선 추가.
     */
    while(m--) {
        int x, y; cin >> x >> y;
        x = x<0 ? -x*2-2 : x*2-1;
        y = y<0 ? -y*2-2 : y*2-1;
        conn[oppo(x)].push_back(y);
        conn[oppo(y)].push_back(x);
    }
    
    /** 
     * Tarjan's Algorithm으로 SCC 뽑아내기
     */
    for(int i=0;i<2*n;i++) {
        if(!visited[i]) dfs(i);
    }
    
    /** 
     * i와 i+1번째 정점(i는 짝수)에 대해 같은 SCC에 속하면 2-SAT 불가능
     */
    for(int i=0;i<2*n;i+=2) {
        if(parent[i]==parent[i+1]) {
            cout << 0;
            return 0;
        }
    }
    cout << 1;
}
```
