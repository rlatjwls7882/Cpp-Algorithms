/** https://www.acmicpc.net/problem/13161 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 502;
const int S = MAX-2, E = MAX-1;
const int INF = 0x3f3f3f3f;

int c[MAX][MAX], f[MAX][MAX], level[MAX], work[MAX];
vector<vector<int>> conn(MAX);

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
    return 0;
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

    int totalFlow=0;
    while(bfs()) {
        memset(work, 0, sizeof work);
        while(true) {
            int flow = dfs(S, INF);
            if(flow==0) break;
            totalFlow += flow;
        }
    }

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
