## Kruskal’s Algorithm 🟡 Gold IV
간선을 가중치 순으로 정렬한 뒤 사이클이 생기지 않는 간선만 선택하여 최소 스패닝 트리를 만드는 알고리즘

시간복잡도: $O(E\log E)$ ($E$: 간선 수)

![](https://github.com/user-attachments/assets/87c836f6-fbe1-48dc-9987-2a62a7bce253)

다음과 같은 그래프가 있다고 하자. 초기 상태에서는 모든 정점이 서로 다른 집합에 속하므로 집합의 개수는 총 5개이다.

먼저 모든 간선을 가중치 기준으로 **오름차순 정렬**한다.

![](https://github.com/user-attachments/assets/07b3d708-69de-4033-8815-5c543fdb1e47)

가중치가 가장 작은 간선은 **1번 정점과 5번 정점을 비용 2로 연결하는 간선**이다. 두 정점은 서로 다른 집합에 속하므로 이 간선을 선택하고 두 집합을 합친다. (DSU의 **Union 연산**)

![](https://github.com/user-attachments/assets/9821c7d7-b374-426b-93a7-ac0c8c4a18d9)

다음 간선은 **2번 정점과 3번 정점을 비용 5로 연결하는 간선**이다. 두 정점이 서로 다른 집합에 있으므로 이 간선도 선택하고 집합을 합친다.

![](https://github.com/user-attachments/assets/b49409c7-a222-40c8-a879-83b357ab1212)

다음 간선은 **4번 정점과 5번 정점을 비용 5로 연결하는 간선**이다. 이 두 정점 역시 서로 다른 집합에 속하므로 간선을 선택하고 집합을 합친다.

![](https://github.com/user-attachments/assets/347c7cd2-3c86-4e09-bda7-bb098d15b738)

다음 간선은 **1번 정점과 2번 정점을 비용 6으로 연결하는 간선**이다. 두 정점이 서로 다른 집합에 있으므로 이 간선도 선택하고 집합을 합친다.

![](https://github.com/user-attachments/assets/e5351ee3-6e1a-446e-9a97-4d664a2c5041)

다음 간선은 **3번 정점과 5번 정점을 비용 6으로 연결하는 간선**이다. 그러나 두 정점은 이미 같은 집합에 속해 있으므로 이 간선을 선택하면 **사이클이 발생한다.** 따라서 이 간선은 선택하지 않는다.

이때 두 정점이 같은 집합에 속해 있는지 확인하기 위해 **Find 연산**을 수행한다.

이후 남아 있는 간선들도 모두 같은 집합에 속한 정점들을 연결하는 간선이므로 선택되지 않는다. 이렇게 선택된 간선들은 **최소 스패닝 트리(Minimum Spanning Tree)**를 이루게 된다.

[연습 문제 (백준 1197번)](https://www.acmicpc.net/problem/1197)

``` c++
/** http://boj.kr/71ab3ebe37394291bb957f50cd5b3228 제출 코드 */
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
    cin.tie(0)->sync_with_stdio(0);
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
