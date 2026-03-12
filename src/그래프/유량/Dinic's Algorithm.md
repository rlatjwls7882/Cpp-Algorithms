## Dinic's Algorithm 🟢 Platinum I
Edmonds-Karp를 개선한 방법으로, 레벨 그래프와 블로킹 플로우를 이용해 최대 유량을 구하는 알고리즘

시간복잡도: $O(V^2E)$ ($V$: 정점 수, $E$: 간선 수)

![](https://github.com/user-attachments/assets/d165439e-7d5c-444f-843f-252a2e923358)

애드몬드-카프 알고리즘에서 사용했던 그래프를 다시 사용하겠다. Dinic 알고리즘에서는 prev 배열 대신 **level 배열**과 **work 배열**을 사용한다.

![](https://github.com/user-attachments/assets/2d630d3d-f31c-47fa-ad39-852f43b5c952)

먼저 S에서 시작하여 유량을 더 보낼 수 있는 간선(c-f>0)을 따라 BFS를 수행한다. BFS를 통해 각 정점까지의 level(거리)를 계산하여 레벨 그래프(level graph)를 만든다.

![](https://github.com/user-attachments/assets/8629db20-9079-4c41-8882-b5aaeafb7eb9)

이렇게 만들어진 레벨 그래프에서 DFS를 이용해 유량을 흘려보낼 수 있는 경로를 찾는다. 이때 다음 정점은 **level[next] == level[cur] + 1**이고 **c - f > 0**인 간선만 따라갈 수 있다. 처음으로 찾은 경로는 **S → 1 → 2 → E**이다. 경로를 탐색하면서 각 정점에서 몇 번째 간선을 사용했는지를 work 배열에 기록한다. (0-index 기준이며 work[i] = 1이면 i번째 정점에서 1번 간선까지 사용했다는 의미이다.) 경로가 완성되면 **E → 2 → 1 → S** 방향으로 되돌아가며 해당 경로의 최소 잔여 용량만큼 유량을 흘려준다. 이 경우 **2**만큼의 유량이 흐르고 역방향 간선에는 **-2**만큼 갱신된다.

![](https://github.com/user-attachments/assets/51fb56b7-672e-4b2d-9d2d-66e8fd7473cf)

아직 더 유량을 보낼 수 있는 경로가 있을 수 있으므로 다시 DFS를 수행한다. 이번에 찾은 경로는 **S → 3 → 4 → E**이다. 동일한 방식으로 경로를 따라 유량을 보내며 이 경우 **1**만큼의 유량이 흐르고 역방향 간선에는 **-1**만큼 갱신된다.

![](https://github.com/user-attachments/assets/26e7cff3-fb13-4069-b9bc-dc49209de101)

다시 DFS를 수행하지만 이번에는 sink인 E까지 도달할 수 있는 경로가 존재하지 않는다. 따라서 현재 레벨 그래프에서 더 이상 보낼 수 있는 유량이 없음을 의미하며 이를 **블로킹 플로우(blocking flow)**라고 한다.

![](https://github.com/user-attachments/assets/9c49a67e-bc6d-474c-b1d8-f55ff86a8d42)

현재 레벨 그래프에서는 더 이상 유량을 보낼 수 없으므로 다시 BFS를 수행하여 새로운 레벨 그래프를 만든다. 그러나 이번 BFS에서는 S에서 E까지 도달할 수 없으므로 알고리즘이 종료된다.

[연습 문제 (백준 13161번)](https://www.acmicpc.net/problem/13161)

``` c++
/** http://boj.kr/fd246063e6b649e88d3a5088f9724c8f 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/** 
 * MAX : 최대 정점 수
 * INF : 대략 10억
 * S : source (시작 지점)
 * E : sink (도착 지점)
 */
const int MAX = 502;
const int INF = 0x3f3f3f3f;
const int S = MAX-2, E = MAX-1;

/** 
 * c[i][j] : i번 정점에서 j번 정점으로의 간선의 최대 용량 (capacity)
 * f[i][j] : i번 정점에서 j번 정점으로의 유량 (flow)
 * level[depth] : source와 각 정점들 사이의 거리 (현재 흐를 수 있는 간선만 사용해서)
 * work[nodeNum] : 더이상 안봐도 되는 간선들 패스하기 위해 사용
 * conn[i][j] : 순방향 간선
 * conn[j][i] : 역방향 간선
 */
int c[MAX][MAX], f[MAX][MAX], level[MAX], work[MAX];
vector<vector<int>> conn(MAX);

/** 
 * bfs를 통해 더 흐를 수 있는 간선만 타고 내려가면서 source와 각 정점들 사이의 거리를 구한다.
 */
bool bfs() {
    queue<int> q; q.push(S);
    memset(level, -1, sizeof level);
    level[S]=0;
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int next:conn[cur]) {
            if(level[next]==-1 && c[cur][next]-f[cur][next]>0) {
                level[next] = level[cur]+1;
                q.push(next);
            }
        }
    }
    return level[E]!=-1;
}

/** 
 * bfs로 구해진 정점들의 거리를 통해, 거리가 1씩 멀어지도록 유량을 흘려보내준다.
 * int &i = work[cur]; 로 work[cur]과 i 연결(더이상 보지 않아도 되는 간선은 패스하여 최적화) 
 */
int dfs(int cur, int curFlow) {
    if(cur==E) return curFlow;
    for(int &i=work[cur];i<conn[cur].size();i++) {
        int next = conn[cur][i];
        if(level[next]==level[cur]+1 && c[cur][next]-f[cur][next]>0) {
            int flow = dfs(next, min(curFlow, c[cur][next]-f[cur][next]));
            if(flow>0) {
                f[cur][next] += flow;
                f[next][cur] -= flow;
                return flow;
            }
        }
    }
    return 0; // 유량을 더이상 흘리지 못하면 0 return
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for(int i=0;i<n;i++) {
        int type; cin >> type;
        if(type==1) {
            conn[S].push_back(i);
            conn[i].push_back(S);
            c[S][i]=INF;
        } else if(type==2) {
            conn[E].push_back(i);
            conn[i].push_back(E);
            c[i][E]=INF;
        }
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cin >> c[i][j];
            if(i!=j) conn[i].push_back(j);
        }
    }

    /** 
     * main 함수의 이 전까지는 애드몬드-카프 알고리즘 쓸 때와 같다.
     * 
     * 디닉 알고리즘은 bfs로 source과 각 정점들의 거리를 확인 후
     * dfs로 flow를 흘려준다.
     * 더이상 못 흘려보내주면 다시 bfs해서 거리 재설정.
     * source에서 아무 정점에도 가지 못하면 디닉 알고리즘 종료
     */
    int totalFlow=0;
    while(bfs()) {
        memset(work, 0, sizeof work);
        while(true) {
            int flow = dfs(S, INF);
            if(flow==0) break;
            totalFlow += flow;
        }
    }
    /** 디닉 알고리즘 끝 */

    bfs();
    vector<int> A, B;
    for(int i=0;i<n;i++) {
        if(level[i]==-1) B.push_back(i+1);
        else A.push_back(i+1);
    }

    cout << totalFlow << '\n';
    for(int e:A) cout << e << ' '; cout << '\n';
    for(int e:B) cout << e << ' '; cout << '\n';
}
```
