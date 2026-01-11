#include<bits/stdc++.h>
using namespace std;

struct Dinic { // O(V²E), 모든 간선의 용량이 1이면 O(min(V^(2/3), E^(1/2))E)
    typedef long long ll;
    const int INF = 0x3f3f3f3f;
    const ll LINF = 0x3f3f3f3f3f3f3f3f;
    struct Edge {
        int to, rev;
        ll c;
    };
    int S=0, E;
    vector<int> level, work;
    vector<vector<Edge>> conn;

    inline Dinic(int SZ, int s, int e) {
        S=s;
        E=e;
        work = vector<int>(SZ);
        level = vector<int>(SZ);
        conn = vector<vector<Edge>>(SZ);
    }

    inline void edge(int u, int v, ll c) {
        conn[u].push_back({v, (int)conn[v].size(), c});
        conn[v].push_back({u, (int)conn[u].size()-1, 0});
    }

    inline bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q; q.push(S);
        level[S]=0;
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(Edge &next:conn[cur]) {
                if(level[next.to]==-1 && next.c) {
                    level[next.to]=level[cur]+1;
                    q.push(next.to);
                }
            }
        }
        return level[E]!=-1;
    }

    ll dfs(int cur, ll curFlow) {
        if(cur==E) return curFlow;
        for(int &i=work[cur];i<conn[cur].size();i++) {
            Edge &next=conn[cur][i];
            if(level[next.to]==level[cur]+1 && next.c) {
                ll flow = dfs(next.to, min(curFlow, next.c));
                if(flow) {
                    next.c-=flow;
                    conn[next.to][next.rev].c+=flow;
                    return flow;
                }
            }
        }
        return 0;
    }

    inline ll res() {
        ll total=0, flow;
        while(bfs()) {
            fill(work.begin(), work.end(), 0);
            while(flow=dfs(S, LINF)) total+=flow;
        }
        return total;
    }
};