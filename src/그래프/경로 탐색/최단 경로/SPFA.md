## SPFA (Shortest Path Faster Algorithm)
큐를 사용해 Bellman-Ford의 간선 완화를 [휴리스틱](https://en.wikipedia.org/wiki/Heuristic_(computer_science))으로 가속하여 최단 거리를 구하는 알고리즘

시간복잡도 : 경험적 평균 O(V+E), 최악 O(VE) (V : 정점 수, E : 간선 수)

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
const int MAX = 20001;

struct element {
    int pos, cost;
};

/** 
 * minCost[i] : 시작 정점에서 i번 정점까지의 최단 거리
 * inQueue[i] : i번 정점이 큐에 들어있는지 확인하는 배열
 * cnt[i] : 음수 사이클을 찾기 위해 i번 정점으로의 최단거리가 몇 번 업데이트 됐는지 기록하는 배열
 */
long long minCost[MAX];
int inQueue[MAX], cnt[MAX];
vector<vector<element>> conn(MAX);

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    while(m--) {
        int a, b, c; cin >> a >> b >> c;
        conn[a].push_back({b, c}); // 단방향 간선
    }

    /** 
     * SPFA (Shortest Path Faster Algorithm)
     * - 우선순위 큐 대신 inQueue 배열과 큐를 사용
     */
    fill(minCost, minCost+MAX, INF); // 기본값 초기화
    queue<int> q; q.push(1); minCost[1]=0; // 시작 정점 넣기
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        inQueue[cur]=false;
        if(++cnt[cur]==n) { // 정점이 n번 업데이트 되는 경우 음수 사이클 존재 (Bellman-Ford와 동일)
            cout << -1;
            return 0;
        }
        for(auto next:conn[cur]) {
            long long nextCost = minCost[cur] + next.cost;
            if(nextCost<minCost[next.pos]) { // 현재 경로로 다음 정점에 도달하는 비용이 더 적다면
                minCost[next.pos] = nextCost; // 최단거리 업데이트
                if(!inQueue[next.pos]) { // 큐에 들어있지 않은 경우만 큐에 넣기
                    q.push(next.pos);
                    inQueue[next.pos]=true;
                }
            }
        }
    }

    for(int i=2;i<=n;i++) {
        if(minCost[i]==INF) cout << "-1\n";
        else cout << minCost[i] << '\n';
    }
}
```
