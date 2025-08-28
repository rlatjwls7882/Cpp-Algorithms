## Bellman-Ford Algorithm
가중치가 음수인 그래프에서도, 모든 간선을 최대 V-1번 완화해 최단 거리를 구하고 음수 사이클 여부를 판별하는 알고리즘

시간복잡도 : O(VE)

![](https://github.com/user-attachments/assets/ec2faed3-229f-4245-adcc-87edc20913fd)

이렇게 연결된 그래프가 있고 1번 정점에서 탐색을 시작한다고 가정하자.

![](https://github.com/user-attachments/assets/932be387-a036-4e10-a117-55a87ba01bb1)

1번 정점에서 연결된 다른 모든 정점에 대해 최소비용 업데이트를 한다.

![](https://github.com/user-attachments/assets/cca6aff3-4f14-4d2d-93a3-186a6a376797)

2번 정점에서 연결된 다른 모든 정점에 대해 최소비용 업데이트를 한다.

![](https://github.com/user-attachments/assets/9f06c533-496f-4332-8e91-9998f4d73b4d)

3번 정점에서 연결된 다른 모든 정점에 대해 최소비용 업데이트를 한다.

![](https://github.com/user-attachments/assets/57a7f37b-dd3e-4a59-962b-089d194166af)

4번 정점에서 연결된 다른 모든 정점에 대해 최소비용 업데이트를 한다.

![](https://github.com/user-attachments/assets/84589da1-f873-44e9-9517-d3727c68a334)

5번 정점에서 연결된 다른 모든 정점에 대해 최소비용 업데이트를 한다.

첫번째 반복이 끝났다. 이번 반복에서 최단거리 업데이트가 이루어졌으니 다음 반복을 시작한다. (최단거리 업데이트가 한번이라도 발생하지 않으면 종료)

![](https://github.com/user-attachments/assets/66b74bbf-ffb3-4047-abff-4c4a0bc71d79)

두번째 반복의 결과는 다음과 같다. 이번 반복에서 최단거리 업데이트가 이루어졌으니 다음 반복을 시작한다.

![](https://github.com/user-attachments/assets/dffba307-d85c-4ea0-a05c-c73a8cb87267)

세번째 반복의 결과는 다음과 같다. 이번 반복에서 최단거리 업데이트가 이루어졌으니 다음 반복을 시작한다.

...

이렇게 쭉 반복하다 n(정점 수)번째 반복에서도 반복이 이루어지면 이 그래프에는 음수 사이클이 존재한다고 판단하고 종료한다.

그 이유는 한번의 반복에서 아주 운이 없어서 업데이트가 적게 이루어진다 하더라도 최소 1개의 정점은 업데이트 된다. (0개면 종료)

처음 거리가 0인 기준점을 제외하면 업데이트 시킬 정점이 n-1개이니, n번째 반복에는 정상적인 경우라면 업데이트가 이루어질 수 없다.

[연습 문제 (백준 11657번)](https://www.acmicpc.net/problem/11657)

``` c++
/** http://boj.kr/99e189479d7c4da1a50839057be86dc9 제출 코드 */
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
 * - 음수 사이클이 존재하는 경우 return false
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
