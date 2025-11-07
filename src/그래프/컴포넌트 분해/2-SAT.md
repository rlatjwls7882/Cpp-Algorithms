## 2-SAT (2-Satisfiability) 🟢 Platinum IV
2개의 변수로 이루어진 [CNF](https://ko.wikipedia.org/wiki/논리곱_표준형)가 주어졌을 때, 이를 만족시도록 변수에 (True/False)를 대입 가능한지 [Implication Graph](https://en.wikipedia.org/wiki/Implication_graph)를 만들어 SCC를 형성해 확인하는 문제

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

(A∨B) ∧ (B∨C) 라는 조건은 다음 네 개의 조건으로 분해할 수 있다.  
- ¬A -> B : A가 참이 아니라면 B가 참이어야 한다.
- ¬B -> A : B가 참이 아니라면 A가 참이어야 한다.
- ¬B -> C
- ¬C -> B

이 네 가지 조건을 동시에 만족해야 한다.

![](https://github.com/user-attachments/assets/4e8b38df-e834-47c7-86e1-75c87bef1234)

이를 그래프로 나타내면 이와 같이 나타내진다.

![](https://github.com/user-attachments/assets/7957c9df-d94c-4547-b0e9-7cfe836745bf)

만약 (¬1∨2) ∧ (¬2∨3) ∧ (2∨¬3) 을 구해야 한다고 하자. 이를 그래프로 나타내면 이렇게 나타내진다.

![](https://github.com/user-attachments/assets/f8b8ff42-7ae4-47fa-a13a-00a805a21330)

이 그래프를 SCC들을 뽑아내면 이렇게 나타내진다. 같은 SCC에 속한 것들은 서로 도달 가능하므로 true / false 값이 함께 결정된다.
때문에 이 경우에는 전체 식이 참이 되도록 true / false를 할당할 수 있다.  
할당하는 방법은 위상 순서가 높은 쪽이 false면 낮은 쪽은 무엇을 할당하든 상관 없지만, 위상 순서가 높은 쪽이 true라면 낮은 쪽도 무조건 true여야 한다.  
- ¬2와 ¬3이 false라면(2와 3이 true) ¬1은 어떤 것을 할당하든 조건을 만족한다. 반대로 ¬2와 ¬3이 true라면(2와 3이 false) ¬1은 true여야만 전체 조건을 만족한다.  
- 반대로 1이 false라면 2와 3은 어떤 것을 할당하든 조건을 만족한다. 반대로 1이 true라면 2와 3은 true여야만 전체 조건을 만족한다.  

![](https://github.com/user-attachments/assets/e0a06b13-071d-4462-8c46-31f7cff28a15)

하지만 이 경우에는 2에 false를 할당하는 것과 2에 true를 할당하는 조건을 동시에 만족시킬 수 없기 때문에 전체 조건을 만족할 수 없다.

[연습 문제 (백준 11280번)](https://www.acmicpc.net/problem/11280)

``` c++
/** http://boj.kr/b20a77bd213644739a5eb1305a00df79 제출 코드 */
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
