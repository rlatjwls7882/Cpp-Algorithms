## Dinic's Algorithm
Edmonds-Karp 알고리즘을 최적화한 알고리즘으로, 레벨 그래프를 구성해 블로킹 플로우를 흘려 불필요한 탐색을 줄여 최대 유량을 구하는 알고리즘

시간복잡도 : O(V²E)

![](https://github.com/user-attachments/assets/d165439e-7d5c-444f-843f-252a2e923358)

애드몬드-카프 알고리즘에서 썻던 그래프를 다시 사용하겠다. 디닉에서는 prev 배열 대신에 level 배열과 work 배열을 사용한다.

![](https://github.com/user-attachments/assets/2d630d3d-f31c-47fa-ad39-852f43b5c952)

먼저 S에서 유량을 흘려보낼 수 있는(c-f>0) 정점으로 bfs를 한번 돌려 각 정점들의 level(거리)을 찾는다.

![](https://github.com/user-attachments/assets/8629db20-9079-4c41-8882-b5aaeafb7eb9)

이렇게 만들어진 경로를 통해 dfs로 유량을 흘릴 수 있는 모든 경로에 유량을 보낸다. (조건 : level[next] == level[cur]+1, c-f>0)  
첫번 째로 찾은 경로는 S -> 1 -> 2 -> E 이고 이때 경로를 찾으면서 몇 번째 간선을 타고 갔는지 work 배열에 기록한다. (0-Index로 구현, work[i]의 값이 1이면 이번에 1번 간선을 타고 갔고, 1보다 작은 번호의 간선들로는 유량을 흘려도 E에 도착 못한다는 뜻)  
E -> 2 -> 1 -> S 로 돌아오며 유량을 2씩 흘려준다. (역간선으로는 -2씩 흘려준다.)

![](https://github.com/user-attachments/assets/51fb56b7-672e-4b2d-9d2d-66e8fd7473cf)

아직 더 유량을 흘려보낼 수 있는지 모르기 때문에 다시 dfs를 시작한다.  
이번에 찾은 경로는 S -> 3 -> 4 -> E 이고 이때 경로를 찾으면서 몇 번째 간선을 타고 갔는지 work 배열에 기록한다.  
E -> 4 -> 3 -> S 로 돌아오며 유량을 1씩 흘려준다. (역간선으로는 -1씩 흘려준다.)

![](https://github.com/user-attachments/assets/26e7cff3-fb13-4069-b9bc-dc49209de101)

아직 더 유량을 흘려보낼 수 있는지 모르기 때문에 다시 dfs를 시작한다.  
이번에는 E에 도착하지 못해, 찾은 경로가 없다.  

![](https://github.com/user-attachments/assets/9c49a67e-bc6d-474c-b1d8-f55ff86a8d42)

이전에 bfs로 찾은 level들로는 더이상 유량을 보낼 수 없기에 다른 level 경로들을 찾는다.  
S에서 bfs로 E에 도착하지 못하기 때문에 dfs 탐색을 더 이상 하지 않고 종료한다. (work배열은 dfs 탐색 바로 전에 초기화되기 때문에 쓰레기 값)

[연습 문제 (백준 13161번)](https://www.acmicpc.net/problem/13161)

``` c++
/** https://www.acmicpc.net/problem/13161 제출 코드 */
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
