## PBS(Parallel Binary Search, 병렬 이분 탐색) 🟢 Platinum I
이분 탐색 쿼리가 여러 번 주어질 때, 각 쿼리를 개별 이분탐색하지 않고 같은 mid끼리 묶어 한 번의 검증으로 여러 쿼리를 처리하는 오프라인 기법.

시간복잡도 : O((N+Q)logC) (C : 최대 이분탐색 범위)

[연습문제 (백준1396번)](https://www.acmicpc.net/problem/1396)

위 문제는 각 정점 위에 공을 올려놓고, 간선에는 이동을 위한 최소 온도가 적혀있다.  
이 때, x 정점에서 y 정점으로 이동하기 위한 최소 온도를 찾는 문제이다.

![](https://github.com/user-attachments/assets/1c4d1d30-9cff-444d-93b8-469fac46e261)

x=1, y=5 쿼리와 x=2, y=3 쿼리가 주어진다고 하자.  
각 쿼리마다 이분 탐색을 해주어야 하고, 처음에는 가능한 범위가 동일하다.

![](https://github.com/user-attachments/assets/fb63e609-0e95-40ed-8e20-72d254bf402e)

첫 번째 반복에서 각각 mid=5, mid=5로 설정되고, 온도가 5 이하인 모든 간선들을 DSU로 합친다.  
확인해보니 1 - 5 이동이 가능해 첫 번째 쿼리의 right를 mid로 업데이트하고, 2 - 3 이동이 가능해 두 번째 쿼리의 right를 mid로 업데이트한다. 

![](https://github.com/user-attachments/assets/45e86da9-eee5-4e28-9b8d-8d368c5aa594)

두 번째 반복에서 각각 mid=2, mid=2로 설정되고, 온도가 2 이하인 모든 간선들을 DSU로 합친다.  
확인해보니 1 - 5 이동이 불가능해 첫 번째 쿼리의 left를 mid+1로 업데이트하고, 2 - 3 이동이 가능해 두 번째 쿼리의 right를 mid로 업데이트한다.

![](https://github.com/user-attachments/assets/00b76527-2719-4545-bb8b-b66e068172b7)

세 번째 반복에서 각각 mid=4, mid=1로 설정되고, 먼저 온도가 1 이하인 모든 간선들을 DSU로 합친다.  
이번에는 첫번째 쿼리는 살펴볼 준비가 되지 않았고(온도가 4 이하인 모든 간선들을 합쳐야 하지만 현재 1 이하까지만 합침), 2 - 3 이동이 불가능해 두 번째 쿼리의 left를 mid+1로 업데이트한다.

![](https://github.com/user-attachments/assets/d7a9fdc1-9064-4150-a7e8-69cd2ef4f21f)

온도가 4 이하인 모든 간선들을 DSU로 합친다.  
1 - 5 이동이 가능해 첫 번째 쿼리의 right를 mid로 업데이트한다.

![](https://github.com/user-attachments/assets/02a71bdc-73fd-4269-917d-bffe1121e513)

네 번째 반복에서 각각 mid=3, mid=2로 설정되고, 먼저 온도가 2 이하인 모든 간선들을 DSU로 합친다.  
첫번째 쿼리는 살펴볼 준비가 되지 않았고, 2 - 3 이동이 가능해 두 번째 쿼리의 right를 mid로 업데이트한다. (그대로 유지)

![](https://github.com/user-attachments/assets/9d29e0d2-db65-47ba-bb76-d051410b98a6)

온도가 3 이하인 모든 간선들을 DSU로 합친다.  
1 - 5 이동이 불가능해 첫 번째 쿼리의 left를 mid+1로 업데이트한다.

이제 모든 쿼리에 대해 left와 right가 동일해졌으니 병렬 이분 탐색을 종료한다.

``` c++
/** http://boj.kr/232895714fb74cb49c8bb564c5dcdd37 제출 코드 */
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
