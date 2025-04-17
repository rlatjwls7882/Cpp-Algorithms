#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX = 2502;
const int S = MAX-2, E = MAX-1;
/**
 * c : capacity
 * f : flow
 */
int c[MAX][MAX], f[MAX][MAX], prv[MAX];
vector<vector<int>> conn(MAX);

int main() {
    /**
     * 순방향 간선
     * conn[a].push_back(b);
     * c[a][b] = inputCapacity;
     * 
     * 역방향 간선
     * conn[b].push_back(a);
     */
    int totalFlow=0;
    while(true) {
        memset(prv, -1, sizeof prv);
        queue<int> q; q.push(S);
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(int next:conn[cur]) {
                if(c[cur][next]-f[cur][next]>0 && prv[next]==-1) {
                    prv[next] = cur;
                    if(next==E) break;
                    q.push(next);
                }
            }
        }
        if(prv[E]==-1) break;

        int flow = INF;
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
