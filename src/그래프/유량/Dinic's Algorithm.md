## Dinic's Algorithm
Edmonds-Karp 알고리즘을 최적화한 알고리즘

시간복잡도 : O(V²E)

[연습 문제 (백준 13161번)](https://www.acmicpc.net/problem/13161)

``` c++
/** https://www.acmicpc.net/problem/13161 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/** 
 * MAX : 최대 정점 수
 * INF : 대략 10억
 * S : source (시작 지점)
 * E : sink (도착 지점)
 */
const int MAX = 502;
const int INF = 0x3f3f3f3f;
const int S = MAX-2, E = MAX-1;

/** 
 * c[i][j] : i번 정점에서 j번 정점으로의 간선의 최대 용량 (capacity)
 * f[i][j] : i번 정점에서 j번 정점으로의 유량 (flow)
 * level[depth] : source와 각 정점들 사이의 거리 (현재 흐를 수 있는 간선만 사용해서)
 * work[depth] : 더이상 안봐도 되는 간선들 패스하기 위해 사용
 * conn[i][j] : 순방향 간선
 * conn[j][i] : 역방향 간선
 */
int c[MAX][MAX], f[MAX][MAX], level[MAX], work[MAX];
vector<vector<int>> conn(MAX);

/** 
 * bfs를 통해 더 흐를 수 있는 간선만 타고 내려가면서 source와 각 정점들 사이의 거리를 구한다.
 */
bool bfs() {
    queue<int> q; q.push(S);
    memset(level, -1, sizeof level);
    level[S]=0;
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int next:conn[cur]) {
            if(level[next]==-1 && c[cur][next]-f[cur][next]>0) {
                level[next] = level[cur]+1;
                q.push(next);
            }
        }
    }
    return level[E]!=-1;
}

/** 
 * bfs로 구해진 정점들의 거리를 통해, 거리가 1씩 멀어지도록 유량을 흘려보내준다.
 * int &i = work[cur]; 로 work[cur]과 i 연결(더이상 보지 않아도 되는 간선은 패스하여 최적화) 
 */
int dfs(int cur, int curFlow) {
    if(cur==E) return curFlow;
    for(int &i=work[cur];i<conn[cur].size();i++) {
        int next = conn[cur][i];
        if(level[next]==level[cur]+1 && c[cur][next]-f[cur][next]>0) {
            int flow = dfs(next, min(curFlow, c[cur][next]-f[cur][next]));
            if(flow>0) {
                f[cur][next] += flow;
                f[next][cur] -= flow;
                return flow;
            }
        }
    }
    return 0; // 유량을 더이상 흘리지 못하면 0 return
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for(int i=0;i<n;i++) {
        int type; cin >> type;
        if(type==1) {
            conn[S].push_back(i);
            conn[i].push_back(S);
            c[S][i]=INF;
        } else if(type==2) {
            conn[E].push_back(i);
            conn[i].push_back(E);
            c[i][E]=INF;
        }
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cin >> c[i][j];
            if(i!=j) conn[i].push_back(j);
        }
    }

    /** 
     * main 함수의 이 전까지는 애드몬드-카프 알고리즘 쓸 때와 같다.
     * 
     * 디닉 알고리즘은 bfs로 source과 각 정점들의 거리를 확인 후
     * dfs로 flow를 흘려준다.
     * 더이상 못 흘려보내주면 다시 bfs해서 거리 재설정.
     * source에서 아무 정점에도 가지 못하면 디닉 알고리즘 종료
     */
    int totalFlow=0;
    while(bfs()) {
        memset(work, 0, sizeof work);
        while(true) {
            int flow = dfs(S, INF);
            if(flow==0) break;
            totalFlow += flow;
        }
    }
    /** 디닉 알고리즘 끝 */

    bfs();
    vector<int> A, B;
    for(int i=0;i<n;i++) {
        if(level[i]==-1) B.push_back(i+1);
        else A.push_back(i+1);
    }

    cout << totalFlow << '\n';
    for(int e:A) cout << e << ' '; cout << '\n';
    for(int e:B) cout << e << ' '; cout << '\n';
}
```
