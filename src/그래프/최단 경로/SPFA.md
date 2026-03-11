## SPFA (Shortest Path Faster Algorithm) 🟡 Gold IV
Bellman-Ford를 기반으로 큐를 사용해 갱신이 필요한 정점만 처리하여 최단 거리를 구하는 알고리즘

시간복잡도: 경험적 평균 $O(V+E)$, 최악 $O(VE)$ ($V$ : 정점 수, $E$ : 간선 수)

![](https://github.com/user-attachments/assets/8ed14afb-9a4d-45d8-ade7-4be426d14077)

벨만-포드와 같은 그래프를 사용하고 **1번 정점에서 탐색을 시작**한다고 가정하자.

![](https://github.com/user-attachments/assets/8bbe5845-680b-4a02-a86e-844e3cfb4c80)

탐색을 시작하기 전에 **시작 정점인 1번 정점을 큐에 넣는다.**

![](https://github.com/user-attachments/assets/0ce3cc31-51e6-4a9e-a793-45f03e470efe)

큐의 맨 앞 원소인 **1번 정점**을 꺼낸다. 1번 정점에서 접근 가능한 정점은 **2번, 3번, 5번**이다. 각 정점에 대해 간선을 완화하여 거리를 갱신한다. 2번 정점의 거리는 **4**, 3번 정점의 거리는 **3**, 5번 정점의 거리는 **1**로 갱신된다. 따라서 **2번, 3번, 5번 정점이 큐에 들어간다.**

![](https://github.com/user-attachments/assets/6f640c65-5006-41dd-b555-c8bebc3832f1)

다음으로 큐의 맨 앞 원소인 **2번 정점**을 꺼낸다. 2번 정점에서 접근 가능한 정점은 **1번, 4번, 5번**이다. 이 중 거리가 단축되는 **4번 정점**의 거리를 **6**으로 갱신한다. 따라서 **4번 정점이 큐에 들어간다.**

![](https://github.com/user-attachments/assets/2eab59aa-d7f9-482b-a81c-80d042c32c59)

다음으로 큐의 맨 앞 원소인 **3번 정점**을 꺼낸다. 3번 정점에서 접근 가능한 정점은 **1번, 4번, 5번**이다. 이 중 **4번 정점**의 거리가 **4**로 단축되지만 이미 큐에 들어 있으므로 **새로 큐에 들어가는 정점은 없다.**

![](https://github.com/user-attachments/assets/3f7c7ab7-b774-49bd-91e1-714119e7e463)

다음으로 큐의 맨 앞 원소인 **5번 정점**을 꺼낸다. 5번 정점에서 접근 가능한 정점은 **1번, 2번, 3번, 4번**이다. 이 중 **4번 정점**의 거리가 **-2**로 단축되지만 이미 큐에 들어 있으므로 **새로 큐에 들어가는 정점은 없다.**

![](https://github.com/user-attachments/assets/d1474c75-263e-4be1-97e0-67ad5d6f4177)

다음으로 큐의 맨 앞 원소인 **4번 정점**을 꺼낸다. 4번 정점에서 접근 가능한 정점은 **2번, 3번, 5번**이다. 이 중 **2번 정점**의 거리는 **0**, **3번 정점**의 거리는 **-1**, **5번 정점**의 거리는 **-5**로 단축된다. 따라서 **2번, 3번, 5번 정점이 큐에 들어간다.**

이 과정을 반복하다가 **큐가 비게 되면 더 이상 갱신될 정점이 없다는 의미이므로 알고리즘이 정상적으로 종료된다.** 또한 벨만-포드와 같은 원리로 하나의 정점이 **$n$번 이상 갱신되면(`cnt == n`)** 해당 그래프에는 **음수 사이클이 존재한다고 판단하고 종료한다.**

[연습 문제 (백준 11657번)](https://www.acmicpc.net/problem/11657)

``` c++
/** http://boj.kr/99e189479d7c4da1a50839057be86dc9 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

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
    cin.tie(0)->sync_with_stdio(0);
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
