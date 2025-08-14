## Kruskal’s Algorithm
간선을 가중치 순으로 정렬해 사이클을 피하며 [최소 스패닝 트리](https://en.wikipedia.org/wiki/Minimum_spanning_tree)를 만드는 알고리즘

시간복잡도 : O(ElogE) (E : 간선 수)

![Kruskal’s Algorithm gif](https://upload.wikimedia.org/wikipedia/commons/b/bb/KruskalDemo.gif)

[연습 문제 (백준 1197번)](https://www.acmicpc.net/problem/1197)

``` c++
/** https://www.acmicpc.net/problem/1197 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 20'000;

int parent[MAX];

int _find(int x) {
    if(parent[x]==x) return x;
    return parent[x] = _find(parent[x]);
}

bool _union(int x, int y) {
    x = _find(x);
    y = _find(y);

    if(x==y) return false;
    if(x<y) parent[y]=x;
    else parent[x]=y;
    return true;
}

struct edge {
    int a, b, c;
    bool operator<(const edge e) const {
        return c < e.c;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int v, e; cin >> v >> e;
    vector<edge> edges;
    while(e--) {
        int a, b, c; cin >> a >> b >> c;
        edges.push_back({a-1, b-1, c});
    }
    for(int i=0;i<v;i++) parent[i]=i;

    /** 
     * 크루스칼 알고리즘
     * 모든 정점을 최소 비용으로 연결하는 알고리즘
     * - 간선을 비용 기준으로 오름차순으로 정렬
     * - 순서대로 두 정점이 다른 집합에 있을 때만 DSU로 합치면서 비용 누적
     * - - v개의 정점은 v-1번의 합치기 연산 가능
     * - - 나머지 간선은 무시
     */
    int total=0;
    sort(edges.begin(), edges.end());
    for(auto e : edges) {
        if(_union(e.a, e.b)) {
            total += e.c;
        }
    }
    cout << total;
}
```
