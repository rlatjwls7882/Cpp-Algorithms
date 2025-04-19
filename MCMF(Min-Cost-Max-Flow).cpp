/** https://www.acmicpc.net/problem/11408 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/**
 * MAX : 최대 정점 개수
 * INF : INT_MAX
 * S : source
 * E : sink
 */
const int MAX = 802;
const int INF = 0x3f3f3f3f;
const int S=MAX-2, E=MAX-1;

/**
 * c[u][v] : u에서 v로의 최대 용량(capacity)
 * f[u][v] : u에서 v로 흐르는 유량(flow)
 * cost[u][v] : u에서 v로 가는데 드는 비
 * prv[i] : i에 도달하기 위해 방문한 이전 정점용
 * curCost[i] : i에 도달하기 위해 드는 최소 비용
 * inQueue[i] : i가 큐에 들어있는지 (메모리, 시간 최적화)
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
