/** https://www.acmicpc.net/problem/13510 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX = 100000;

struct edge {
    int u, v, c;
};

int subTreeCnt[MAX];
int _size, arr[MAX*3];
vector<edge> edges(MAX);
int edgeNum[MAX];
vector<vector<int>> conn(MAX), child(MAX);
int nodeCnt, nodeNum[MAX], groupCnt, groupNum[MAX], head[MAX], parent[MAX], depth[MAX];

void dfs1(int cur) {
    subTreeCnt[cur]=1;
    for(int next:conn[cur]) {
        if(!subTreeCnt[next]) {
            dfs1(next);
            subTreeCnt[cur] += subTreeCnt[next];
            child[cur].push_back(next);
            if(subTreeCnt[child[cur].front()] > subTreeCnt[child[cur].back()]) swap(child[cur].front(), child[cur].back());
        }
    }
}

void dfs2(int cur, int curDepth) {
    int u = nodeNum[cur] = nodeCnt++;
    depth[u] = curDepth;

    groupNum[u] = groupCnt;
    if(head[groupCnt]==-1) head[groupCnt]=u;

    if(child[cur].empty()) {
        groupCnt++;
        return;
    }
    for(int next:child[cur]) {
        dfs2(next, curDepth+1);
        parent[nodeNum[next]] = u;
    }
}

void construct(int n) {
    _size=1;
    while(_size<n) _size<<=1;
    _size<<=1;

    for(int i=0;i<n-1;i++) {
        int u = nodeNum[edges[i].u];
        int v = nodeNum[edges[i].v];
        if(depth[u]>depth[v]) edgeNum[i] = u;
        else edgeNum[i] = v;
        arr[edgeNum[i]+_size/2] = edges[i].c;
    }
    for(int i=_size/2-1;i>0;i--) arr[i] = max(arr[i*2], arr[i*2+1]);
}

void update(int i, int c) {
    i = edgeNum[i]+_size/2;
    arr[i] = c;
    while(i>1) {
        i>>=1;
        arr[i] = max(arr[i*2], arr[i*2+1]);
    }
}

int search(int L, int R, int nodeNum=1, int nodeL=0, int nodeR=_size/2-1) {
    if(R<nodeL || nodeR<L) return 0;
    if(L<=nodeL && nodeR<=R) return arr[nodeNum];
    int mid = (nodeL+nodeR)/2;
    return max(search(L, R, nodeNum*2, nodeL, mid), search(L, R, nodeNum*2+1, mid+1, nodeR));
}

int query(int u, int v) {
    int res=0;
    u = nodeNum[u];
    v = nodeNum[v];
    while(groupNum[u]!=groupNum[v]) {
        int uHead = head[groupNum[u]], vHead = head[groupNum[v]];
        if(depth[uHead]>depth[vHead]) {
            res = max(res, search(uHead, u));
            u = parent[uHead];
        } else {
            res = max(res, search(vHead, v));
            v = parent[vHead];
        }
    }
    return max(res, search(min(u, v)+1, max(u, v)));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for(int i=0;i<n-1;i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].c;
        edges[i].u--;
        edges[i].v--;
        conn[edges[i].u].push_back(edges[i].v);
        conn[edges[i].v].push_back(edges[i].u);
    }

    dfs1(0);
    memset(head, -1, sizeof head);
    dfs2(0, 0);

    construct(n);

    int m; cin >> m;
    while(m--) {
        int a, b, c; cin >> a >> b >> c;
        if(a==1) {
            update(b-1, c);
        } else {
            cout << query(b-1, c-1) << '\n';
        }
    }
}
