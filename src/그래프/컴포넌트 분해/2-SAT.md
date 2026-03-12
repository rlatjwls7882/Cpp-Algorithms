## 2-SAT (2-Satisfiability) 🟢 Platinum IV
2-[CNF](https://ko.wikipedia.org/wiki/논리곱_표준형) 식이 주어졌을 때 [Implication Graph](https://en.wikipedia.org/wiki/Implication_graph)를 만들고 SCC를 이용해 식이 만족 가능한지 판단하는 알고리즘

시간복잡도: $O(V + E)$ ($V$: 정점 수, $E$: 간선 수)

(A ∨ B) ∧ (B ∨ C) 와 같은 조건이 주어졌다고 하자. 2-SAT에서는 각 절 (A ∨ B)를 다음 두 개의 조건으로 변환한다.

- ¬A → B
- ¬B → A

즉 A가 거짓이면 B는 참이어야 하고, B가 거짓이면 A는 참이어야 한다. 따라서 (A ∨ B) ∧ (B ∨ C)는 다음 네 개의 조건으로 표현할 수 있다.

- ¬A → B
- ¬B → A
- ¬B → C
- ¬C → B

이 조건들을 그래프로 나타낸 것이 **Implication Graph**이다.

![](https://github.com/user-attachments/assets/4e8b38df-e834-47c7-86e1-75c87bef1234)

이와 같이 각 리터럴을 정점으로 두고 조건을 간선으로 표현할 수 있다.

![](https://github.com/user-attachments/assets/7957c9df-d94c-4547-b0e9-7cfe836745bf)

예를 들어 (¬1 ∨ 2) ∧ (¬2 ∨ 3) ∧ (2 ∨ ¬3) 이라는 식이 있다고 하자. 이를 implication graph로 표현하면 위와 같은 그래프가 된다.

![](https://github.com/user-attachments/assets/f8b8ff42-7ae4-47fa-a13a-00a805a21330)

이 그래프에서 SCC를 구하면 위와 같이 그룹이 나뉜다. 같은 SCC에 속한 정점들은 서로 도달 가능하므로 반드시 같은 논리 값을 가져야 한다. 따라서 어떤 변수 x와 ¬x가 같은 SCC에 속해 있다면 식을 만족하는 값 할당은 존재하지 않는다.

이 예제에서는 모든 변수와 그 부정이 서로 다른 SCC에 속해 있으므로 식을 만족하는 값 할당이 존재한다. 값을 할당할 때는 SCC를 위상 순서의 역순으로 처리하며 아직 값이 정해지지 않은 변수에 대해 해당 값을 true로 두고 그 부정은 false로 설정한다.

- ¬2와 ¬3이 false라면 (2와 3이 true) ¬1은 어떤 값을 할당하더라도 조건을 만족한다.
- 반대로 ¬2와 ¬3이 true라면 (2와 3이 false) ¬1은 반드시 true여야 한다.
- 1이 false라면 2와 3은 어떤 값을 할당하더라도 조건을 만족한다.
- 반대로 1이 true라면 2와 3도 반드시 true여야 한다.

![](https://github.com/user-attachments/assets/e0a06b13-071d-4462-8c46-31f7cff28a15)

하지만 이 경우에는 2와 ¬2가 같은 SCC에 속하게 된다. 이는 2가 참이어야 한다는 조건과 거짓이어야 한다는 조건이 동시에 존재함을 의미하므로 전체 식을 만족하는 값 할당은 존재하지 않는다.

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
