#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX = 2502;
const int S = MAX-2, E = MAX-1;
int c[MAX][MAX], f[MAX][MAX], cost[MAX][MAX], curCost[MAX], prv[MAX];
bool inQueue[MAX];
vector<vector<int>> conn(MAX);

int main() {
    
    int totalCost=0;
    while(true) {
        memset(prv, -1, sizeof prv);
        memset(inQueue, 0, sizeof inQueue);
        fill(curCost, curCost+MAX, INF);
        curCost[S]=0;
        queue<int> q; q.push(S);
        inQueue[S]=true;
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            inQueue[cur]=false;
            for(int next:conn[cur]) {
                if(c[cur][next]-f[cur][next]>0 && curCost[next]>curCost[cur]+cost[cur][next]) {
                    curCost[next] = curCost[cur] + cost[cur][next];
                    prv[next] = cur;
                    if(!inQueue[next]) {
                        q.push(next);
                        inQueue[next]=true;
                    }
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
            totalCost += cost[prv[i]][i]*flow;
        }
    }
    cout << totalCost;
}
