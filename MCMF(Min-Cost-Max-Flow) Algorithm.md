## MCMF(Min-Cost-Max-Flow) Algorithm
최대의 유량을 흘리면서, 그 중에서 최소 비용을 찾는 알고리즘

시간복잡도 : O(VE)

벨만 포드 기반의 SPFA(Shortest-Path-Faster-Algorithm)을 이용하여 구현한다.

``` c++
/** https://www.acmicpc.net/problem/11408 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/**
 * MAX : 최대 정점 개수
 * INF : 대략 10억
 * S : source (시작 지점)
 * E : sink (도착 지점)
 */
const int MAX = 802;
const int INF = 0x3f3f3f3f;
const int S=MAX-2, E=MAX-1;

/**
 * c[u][v] : u에서 v로의 최대 용량(capacity)
 * f[u][v] : u에서 v로 흐르는 유량(flow)
 * cost[u][v] : u에서 v로 가는데 드는 비용
 * cost[v][u] : v에서 u로 가는데 드는 비용 (역방향, =-cost[u][v])
 * prv[i] : i에 도달하기 위해 방문한 이전 정점
 * curCost[i] : i에 도달하기 위해 드는 최소 비용
 * inQueue[i] : i가 큐에 들어있는지 (이미 들어있으면 넣지 않음으로써 메모리와 시간 최적화)
 * conn[u][v] : 순방향 간선
 * conn[v][u] : 역방향 간선
 */
int c[MAX][MAX], f[MAX][MAX], cost[MAX][MAX], prv[MAX], curCost[MAX];
bool inQueue[MAX];
vector<vector<int>> conn(MAX);

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for(int i=0;i<n;i++) {
        conn[i].push_back(S);
        conn[S].push_back(i);
        c[S][i]=1;
    }
    for(int i=n;i<n+m;i++) {
        conn[i].push_back(E);
        conn[E].push_back(i);
        c[i][E]=1;
    }

    /** 
     * 애드몬드-카프 알고리즘에서 순방향에는 cost[i][j]에는 +비용, cost[j][i]에는 -비용 집어넣는 것 추가
     */
    for(int i=0;i<n;i++) {
        int cnt; cin >> cnt;
        while(cnt--) {
            int v; cin >> v; cin >> cost[i][n+v-1];
            c[i][n+v-1]=1;
            cost[n+v-1][i] = -cost[i][n+v-1];
            conn[i].push_back(n+v-1);
            conn[n+v-1].push_back(i);
        }
    }

    /** 
     * 애드몬드-카프 알고리즘과의 차이점
     * inQueue 배열을 통해 정점이 현재 큐에 들어있는지 체크해줘야 함.
     * curCost를 기록해서 source에서 cur번 정점까지의 최소 비용을 계산함.
     * 
     * 애드몬드-카프 알고리즘은 이미 방문한 정점은 더이상 방문하지 않았지만, MCMF 알고리즘은 curCost[next]가 작아지면 갱신
     * 그렇기에 갱신이 많아져서 큐에 넣는 횟수가 증가함 -> inQueue로 이미 들어있는 정점은 큐에 넣지 않음으로써 최적화 해줘야함.
     */
    int totalCost=0, flow=0;
    while(true) {
        memset(prv, -1, sizeof prv);
        fill(curCost, curCost+MAX, INF);
        queue<int> q; q.push(S);
        curCost[S]=0;
        inQueue[S]=true;
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            inQueue[cur]=false;
            for(int next:conn[cur]) {
                if(c[cur][next]-f[cur][next]>0 && curCost[next]>curCost[cur]+cost[cur][next]) {
                    curCost[next] = curCost[cur] + cost[cur][next];
                    prv[next]=cur;
                    if(!inQueue[next]) {
                        inQueue[next]=true;
                        q.push(next);
                    }
                }
            }
        }
        if(prv[E]==-1) break;

        for(int i=E;i!=S;i=prv[i]) {
            f[prv[i]][i]++;
            f[i][prv[i]]--;
        }
        totalCost += curCost[E];
        flow++;
    }
    cout << flow << '\n' << totalCost;
}
```
