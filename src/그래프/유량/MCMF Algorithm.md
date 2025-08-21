## MCMF (Min Cost Max Flow) Algorithm
Edmonds-Karp 알고리즘에 SPFA(Shortest Path Faster Algorithm)를 합쳐 최대의 유량을 흘리면서, 그 중에서 최소 비용을 찾는 알고리즘

시간복잡도 : O(FVE) (F : 최대 유량)

![](https://github.com/user-attachments/assets/2b044011-572e-4512-af79-d1b4dcb90c38)

해당 그래프가 주어지고, 역추적을 위한 prev 배열과 최소 비용을 위한 curCost 배열을 이용한다.  

![](https://github.com/user-attachments/assets/192977de-97a2-4600-923d-21da567b6c5e)

반복에서 Edmonds-Karp에서 BFS를 사용했던 것과 달리, SPFA를 사용해 탐색한다. (조건: c-f>0, curCost[cur] + 간선의 비용 < curCost[next])  
이 때, S -> 3 -> 2 -> E 경로가 발견되고, 비용과 유량을 업데이트한다.

![](https://github.com/user-attachments/assets/d11ac2eb-eb0f-4a54-97d6-2970a876be0c)

다음 반복에서는 S -> 1 -> 2 -> E 경로가 발견되었고, 비용과 유량을 업데이트한다.

![](https://github.com/user-attachments/assets/c485c37a-7477-4649-ac01-5609288406f4)

다음 반복에서는 S -> 3 -> 4 -> E 경로가 발견되었고, 비용과 유량을 업데이트한다.  

![](https://github.com/user-attachments/assets/89d6e08b-2e89-46a9-bdc5-7211ef47a27a)

다음 반복에서는 S에서 E로 가는 경로가 발견되지 않았고, 반복을 종료한다.

[연습 문제 (백준 11408번)](https://www.acmicpc.net/problem/11408)

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
