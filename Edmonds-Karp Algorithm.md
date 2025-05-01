# 작성중
## Edmonds-Karp Algorithm
그래프에서 시작 지점에서 유량을 흘려서, 도착지점까지 유량이 얼마나 도착하는지 찾는 알고리즘

시간복잡도 O(VE²)

``` c++
/** https://www.acmicpc.net/problem/17412 제출 코드 */
#include <bits/stdc++.h>
using namespace std;

/**
 * INF : INT_MAX
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
