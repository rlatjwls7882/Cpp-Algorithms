## Edmonds-Karp Algorithm
그래프에서 시작 지점(source)에서 유량을 흘려서, 도착 지점(sink)까지 유량이 얼마나 도착하는지 찾는 알고리즘

시간복잡도 O(VE²)

[연습 문제(백준 17412번)](https://www.acmicpc.net/problem/17412)

``` c++
/** https://www.acmicpc.net/problem/17412 제출 코드 */
#include <bits/stdc++.h>
using namespace std;

/**
 * INF : 대략 10억
 * MAX : 해당 문제의 최대 정점의 개수
 * S : source (시작점)
 * E : sink (도착점)
 */
const int INF = 0x3f3f3f3f;
const int MAX = 400;
const int S = 0;
const int E = 1;

/**
 * c[u][v] : u에서 v로의 최대 용량(capacity)
 * f[u][v] : u에서 v로 흐르는 유량(flow)
 * prv[i] : i에 도달하기 위해 방문한 이전 정점
 * conn[u][v] : 순방향 간선
 * conn[v][u] : 역방향 간선
 */
int c[MAX][MAX], f[MAX][MAX], prv[MAX];
vector<vector<int>> conn(MAX);

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, P; cin >> N >> P;

    /** 
     * 정점에 간선 추가
     * 최적의 경로를 찾아 flow를 더 흘리기 위해 역방향 간선도 추가해줘야함.
     */
    while(P--) {
        int u, v; cin >> u >> v;
        c[u-1][v-1]++;
        conn[u-1].push_back(v-1);
        conn[v-1].push_back(u-1);
    }

    /** 
     * S -> E 로의 bfs 탐색
     * prv[next] = cur : 역추적을 위해 next -> cur 경로 기록
     */
    int totalFlow=0;
    while(true) {
        memset(prv, -1, sizeof prv);
        queue<int> q; q.push(S);

        while(!q.empty() && prv[E]==-1) {
            int cur = q.front(); q.pop();
            for(int next:conn[cur]) {
                if(c[cur][next]-f[cur][next]>0 && prv[next]==-1) {
                    prv[next] = cur;
                    if(next==1) break;
                    q.push(next);
                }
            }
        }
        /** 더이상 sink에 도달 못하면 종료 */
        if(prv[E]==-1) break;

        /** 
         * sink부터 역추적하면서 최대로 흘릴 수 있는 flow를 찾고, 흘리기
         * f[prv[i]][i] : 순방향 간선이어서 flow만큼 채워짐
         * f[i][prv[i]] : 역방향 간선이어서 flow만큼 빠짐 (더 나은 간선이 있는지 찾기 위해 쓰임)
         * 
         * c[1][2] = 
         * S -> 1 -> 2 -> E 
         */
        int flow=INF;
        for(int i=E;i!=S;i=prv[i]) {
            flow = min(flow, c[prv[i]][i]-f[prv[i]][i]);
        }
        for(int i=E;i!=S;i=prv[i]) {
            f[prv[i]][i] += flow;
            f[i][prv[i]] -= flow;
        }
        totalFlow += flow;
    }
    cout << totalFlow;
}
```


역방향 간선으로 더 나은 간선을 찾는 것은 다음과 같은 경우이다.

S -> 3 -> 2 -> E 방향으로 1만큼의 유량이 흐른 후 S -> 1 -> 2 -> E 방향으로 1만큼의 유량이 흐르면 다음 그림과 같아진다. (분자를 유량으로, 분모를 용량으로 나타냈다.)
![img1](https://github.com/user-attachments/assets/36c6674c-0ae9-4e28-883e-b7070ed7e769)

이 상황에서 순방향 간선만 보면 더이상 흐를 수 있는 방향이 보이지 않지만, 역방향 간선을 보면 다르다.

3 -> 2의 역간선인 2 -> 3을 나타내면 다음과 같다.

![img2](https://github.com/user-attachments/assets/3ba50c34-f511-481d-92df-216494029f4d)

이 역간선까지 포함시키면, S -> 1 -> 2 -> 3 -> 4 -> E 방향으로 1만큼의 유량이 흐를 수 있다.

모든 유량이 흐른 후 최종 상태는 다음과 같다.

![img3](https://github.com/user-attachments/assets/5526dbe2-ad15-4fa2-809b-e61690ea93e6)

이 상태만 놓고 보면 S -> 3 -> 4 -> E 방향으로 1만큼의 유량이, S -> 1 -> 2 -> E 방향으로 2만큼의 유량이 흐른 것과 똑같다.
