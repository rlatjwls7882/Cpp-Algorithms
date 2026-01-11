#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("fma")
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

struct Dinic { // O(V²E), 모든 간선의 용량이 1이면 O(min(V^(2/3), E^(1/2))E)
    struct Edge {
        int to, rev;
        ll c;
    };
    int S, E;
    vector<int> level, work;
    vector<vector<Edge>> conn;

    Dinic(int SZ, int s, int e) {
        S=s; E=e;
        work = vector<int>(SZ);
        level = vector<int>(SZ);
        conn = vector<vector<Edge>>(SZ);
    }

    void edge(int u, int v, ll c) {
        conn[u].push_back({v, (int)conn[v].size(), c});
        conn[v].push_back({u, (int)conn[u].size()-1, 0});
    }

    bool bfs() {
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

    ll res() {
        ll total=0, flow;
        while(bfs()) {
            fill(work.begin(), work.end(), 0);
            while(flow=dfs(S, LINF)) total+=flow;
        }
        return total;
    }
};

struct MCMF { // O(FVE) F는 최대유량
    int S, E;
    vector<unsigned char> inQ;
    vector<int> prv;
    vector<ll> curCost;
    vector<vector<int>> conn;
    vector<vector<ll>> c, cost;

    MCMF(int SZ, int s, int e) {
        S=s; E=e;
        inQ = vector<unsigned char>(SZ);
        prv = vector<int>(SZ);
        curCost = vector<ll>(SZ);
        conn = vector<vector<int>>(SZ);
        c = vector<vector<ll>>(SZ, vector<ll>(SZ));
        cost = vector<vector<ll>>(SZ, vector<ll>(SZ));
    }

    void edge(int u, int v, ll cap, ll co) {
        c[u][v]=cap;
        cost[u][v]=co;
        cost[v][u]=-co;
        conn[u].push_back(v);
        conn[v].push_back(u);
    }

    pair<ll, ll> res() {
        ll totalFlow=0, totalCost=0;
        while(true) {
            queue<int> q; q.push(S);
            fill(prv.begin(), prv.end(), -1);
            fill(curCost.begin()+1, curCost.end(), LINF);
            while(!q.empty()) {
                int cur = q.front(); q.pop();
                inQ[cur]=false;
                for(int next:conn[cur]) {
                    if(c[cur][next] && curCost[next]>curCost[cur]+cost[cur][next]) {
                        curCost[next]=curCost[cur]+cost[cur][next];
                        prv[next]=cur;
                        if(!inQ[next]) {
                            q.push(next);
                            inQ[next]=true;
                        }
                    }
                }
            }
            if(prv[E]==-1) break;

            ll flow=LINF;
            for(int i=E;i!=S;i=prv[i]) {
                flow = min(flow, c[prv[i]][i]);
            }
            for(int i=E;i!=S;i=prv[i]) {
                c[prv[i]][i]-=flow;
                c[i][prv[i]]+=flow;
            }
            totalFlow+=flow;
            totalCost+=curCost[E]*flow;
        }
        return {totalFlow, totalCost};
    }
};