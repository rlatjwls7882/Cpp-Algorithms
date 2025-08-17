## Parallel Binary Search (병렬 이분 탐색)
이분 탐색 쿼리가 여러 번 주어질 때, 모든 쿼리를 동시에 mid 기준으로 묶어서 병렬 처리함으로써 중복 계산을 줄이는 알고리즘

시간복잡도 : O((N+Q)logC) (C : 최대 이분탐색 범위)

[연습문제 (백준1396번)](https://www.acmicpc.net/problem/1396)

``` c++
/** https://www.acmicpc.net/problem/1396 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 100'000;

int parent[MAX], cnt[MAX], res[MAX][2];

int _find(int x) {
    if(x==parent[x]) return x;
    return parent[x] = _find(parent[x]);
}

void _union(int x, int y) {
    x = _find(x);
    y = _find(y);
    if(x==y) return;
    if(x<y) {
        parent[y] = x;
        cnt[x] += cnt[y];
    } else {
        parent[x] = y;
        cnt[y] += cnt[x];
    }
}

struct edge {
    int a, b, c;
    bool operator<(const edge q) const {
        return c < q.c;
    }
};

struct query {
    int x, y;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;

    /** 
     * 간선 입력.
     * MST를 진행하기 위해 cost를 기준으로 정렬
     */
    vector<edge> edges;
    for(int i=0;i<m;i++) {
        int a, b, c; cin >> a >> b >> c;
        edges.push_back({a-1, b-1, c});
    }
    sort(edges.begin(), edges.end());

    /** 쿼리 입력 */
    int q; cin >> q;
    vector<query> queries(q);
    for(int i=0;i<q;i++) {
        cin >> queries[i].x >> queries[i].y;
        queries[i].x--;
        queries[i].y--;
    }

    /** 
     * PBS 알고리즘
     * 각 쿼리는 답이 될 수 있는 간선의 최소 cost를 이분 탐색으로 찾는다.
     * 쿼리별로 이분 탐색을 독립적으로 하면 QM 시간이 걸려 시간초과 발생.
     * 모든 쿼리를 동시에 mid 인덱스 기준으로 묶어 처리해 QlogM까지 시간을 줄인다는 것이 PBS 알고리즘의 핵심
     */
    vector<int> left(q, 0), right(q, m);
    while(true) {
        bool chk=false;
        vector<vector<int>> mids(m);
        for(int i=0;i<q;i++) {
            if(left[i]<right[i]) {
                chk=true;
                mids[(left[i]+right[i])/2].push_back(i);
            }
        }
        if(!chk) break;

        // 각 반복마다 MST를 처음부터 다시 찾음
        for(int i=0;i<n;i++) {
            parent[i]=i;
            cnt[i]=1;
        }

        for(int i=0;i<m;i++) {
            _union(edges[i].a, edges[i].b);
            for(int idx : mids[i]) {
                if(_find(queries[idx].x) == _find(queries[idx].y)) {
                    right[idx] = i;
                    res[idx][0] = edges[i].c; // 최소 cost
                    res[idx][1] = cnt[_find(queries[idx].x)]; // 움직일 수 있는 정점의 개수
                } else {
                    left[idx] = i+1;
                }
            }
        }
    }
    for(int i=0;i<q;i++) {
        if(left[i]==m) cout << "-1\n";
        else cout << res[i][0] << ' ' << res[i][1] << '\n';
    }
}
```
