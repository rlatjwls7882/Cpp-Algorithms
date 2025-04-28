/** https://www.acmicpc.net/problem/17412 제출 코드 */
#include <bits/stdc++.h>
using namespace std;

/**
 * INF : INT_MAX
 * MAX : 최대 정점의 개수
 * S : source
 * E : sink
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
    
    while(P--) {
        int u, v; cin >> u >> v;
        c[u-1][v-1]++;
        conn[u-1].push_back(v-1);
        conn[v-1].push_back(u-1);
    }

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
        if(prv[E]==-1) break;

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
