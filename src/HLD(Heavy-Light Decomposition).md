## HLD(Heavy-Light Decomposition)
트리에서 세그먼트 트리로 구간 쿼리를 최적화하는 알고리즘

시간복잡도 : O(Qlog²N) (Q : 쿼리의 수)

[연습 문제 (백준 13510번)](https://www.acmicpc.net/problem/13510)

``` c++
/** https://www.acmicpc.net/problem/13510 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/** 
 * MAX : 문제에서 등장하는 최대 정점의 수
 */
typedef long long ll;
const int MAX = 100000;

/** 
 * edge : 해당 문제에서 간선에 가중치가 존재하고, i번째 간선의 가중치를 변경하는 쿼리가 등장하기에 추가.
 * edges[i] : i번째 간선
 * edgeNum[i] : i번 간선 업데이트가 세그먼트 트리에서 영향을 주는 인덱스, 이 문제에서 i번째 간선의 cost를 더 깊은 노드에 담았다. 
 */
struct edge {
    int u, v, c;
};
vector<edge> edges(MAX);
int edgeNum[MAX];

/** 
 * 세그먼트 트리에서 사용함.
 * _size : 세그먼트 트리에서 사용할 크기
 * arr[MAX*4] : 세그먼트 트리 (MAX*4로 설정하는 이유는 최악의 경우 MAX*4개의 정점이 필요함.)
 */
int _size, arr[MAX*4];

/** 
 * dfs1에서 사용함.
 * subTreeCnt[i] : i번 노드보다 아래에 있는 노드의 개수 (무거운 간선을 찾기 위해 쓰임)
 * conn[i][j] : i에서 conn[i][j]로의 간선이 존재함.
 * child[i][j] : i의 자식이 conn[i][j]임.
 */
int subTreeCnt[MAX];
vector<vector<int>> conn(MAX), child(MAX);

/** 
 * dfs2에서 사용함.
 * nodeCnt : 각 노드들에 할당되는 정점 번호.
 * nodeNum[i] : i번 정점에 할당되는 정점 번호(nodeCnt).
 * 
 * groupCnt : 각 노드들에 할당되는 그룹 번호.
 * groupNum[u] : u번(nodeNum[i]) 정점에 할당되는 그룹 번호(groupCnt).
 * 
 * head[g] : g번(groupNum[u]) 그룹의 최상단 정점 번호(nodeCnt)
 * parent[u] : u번(nodeNum[i]) 정점의 부모 정점 번호(nodeCnt)
 * depth[u] : u번(nodeNum[i]) 정점의 트리에서의 깊이
 */
int nodeCnt, nodeNum[MAX], groupCnt, groupNum[MAX], head[MAX], parent[MAX], depth[MAX];

/** 
 * dfs1:
 * 트리를 루트부터 탐색하면서 각 노드들의 자식 노드들 찾기 (child[cur]에 추가)
 * 가장 무거운(자식이 가장 많은) 자식 노드를 첫번째 자식 노드로 설정 (연산 최적화)
 * 트리를 잘 정돈하면(모든 노드들에 대해 가장 무거운 자식 노드를 첫번째 자식으로 놓으면) 한번의 쿼리를 수행하는데 O(log²N)까지 최적화된다. (증명은 하지 않겠다)
 */
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

/** 
 * dfs2 :
 * 잘 정돈된 트리에서 각 정점들에 노드 번호 매기기
 * 현재 노드에 그룹 번호 매기기
 * 그룹에서 head[g]가 아직 없다면 현재 노드를 head[g]로 설정
 * 현재 노드의 자식들에 대해서도 같은 작업 진행
 */
void dfs2(int cur, int curDepth) {
    int u = nodeNum[cur] = nodeCnt++; // 현재 노드에 번호 매기기
    depth[u] = curDepth; // 노드에 현재의 깊이 담기

    groupNum[u] = groupCnt; // 현재 노드에 그룹 번호 매기기
    if(head[groupCnt]==-1) head[groupCnt]=u; // 만약 그룹 내에 head[g]가 설정되지 않았다면 현재 노드가 최상단 노드

    if(child[cur].empty()) {
        groupCnt++;
        return;
    }
    for(int next:child[cur]) { 
        dfs2(next, curDepth+1);
        parent[nodeNum[next]] = u;
    }
}

/** Segment Tree 시작 */
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
/** Segment Tree 끝 */

/** 
 * 두 노드 사이의 간선 중 최대 비용 return
 * 
 * 두 그룹중 그룹 번호가 큰 노드에 대하여: (u가 더 작다고 가정)
 * head[groupNum[u]]와 u 사이에 세그먼트 트리로 구간 탐색.
 * u를 parent[head[groupNum[u]]]로 설정. (더 아래에 있는 노드를 점점 위로 올림, 노드들을 한번에 뛰어넘음으로써 연산 최적화)
 * 
 * 위 과정을 반복하면 두 정점이 같은 그룹에 속하게 됨.
 * 마지막으로 같은 그룹일 때 두 점 사이에서 구간 연산을 하고 return
 */
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
    return max(res, search(min(u, v)+1, max(u, v))); // 이 문제에선 간선 비용을 한 정점에서 위로 올라가는 간선의 비용으로 설정해놓아서 min(u, v)+1 ~ max(u, v) 탐색
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

    /** 
     * 모든 노드의 연결을 입력받고
     * dfs1을 하여 트리를 정돈하고
     * dfs2로 트리의 정점들을 그룹화 (트리에서 세그먼트 트리를 사용하여 구간 탐색을 최적화하기 위해)
     */
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
```
