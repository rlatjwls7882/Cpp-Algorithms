## Bellman-Ford Algorithm
가중치가 음수인 그래프에서도, 모든 간선을 최대 V-1번 완화해 최단 거리를 구하고 음수 사이클 여부를 판별하는 알고리즘

시간복잡도 : O(VE)

![image](https://i.imgur.com/hcWT22F.png)

[연습 문제 (백준 11657번)](https://www.acmicpc.net/problem/11657)

``` c++
/** https://www.acmicpc.net/problem/11657 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/** 
 * INF : 대략 10억
 * MAX : 최대 정점 수
 */
const int INF = 0x3f3f3f3f;
const int MAX = 501;

struct element {
    int pos, cost;
};

int n, m;
long long minCost[MAX];
vector<vector<element>> conn(MAX);

/** 
 * Bellman-Ford Algorithm
 * - 음수인 간선이 있는 경우 다익스트라 대신 사용
 * - 음수 사이클 판별 가능
 */
bool bellman_ford() {
    fill(minCost, minCost+MAX, INF);
    minCost[1]=0;
    for(int i=0;i<n;i++) {
        bool change=false;
        for(int cur=1;cur<=n;cur++) { // 모든 정점에 대해 모든 간선을 살펴보기
            if(minCost[cur]==INF) continue; // 도달 못한 정점은 패스
            for(auto next:conn[cur]) {
                long long nextCost = minCost[cur] + next.cost;
                if(nextCost<minCost[next.pos]) {
                    minCost[next.pos] = nextCost;
                    change=true;
                }
            }
        }
        if(!change) return true;
    }
    return false; // n-1번의 업데이트를 진행하고도 변화가 있으면 사이클 존재
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    while(m--) {
        int a, b, c; cin >> a >> b >> c;
        conn[a].push_back({b, c});
    }

    if(!bellman_ford()) { // 사이클이 존재하는 경우
        cout << -1;
        return 0;
    }

    for(int i=2;i<=n;i++) {
        if(minCost[i]==INF) cout << "-1\n";
        else cout << minCost[i] << '\n';
    }
}
```
