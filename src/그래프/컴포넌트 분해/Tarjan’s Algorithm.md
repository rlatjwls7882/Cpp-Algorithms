## Tarjan’s Algorithm (SCC)

그래프에서 나타나는 [SCC (Strongly Connected Component)](https://ko.wikipedia.org/wiki/강한_연결_요소)을 한번의 dfs로 뽑아내는 알고리즘
SCC : 임의의 두 정점 사이에 사이클이 존재해 서로 왔다 갔다 할 수 있는 정점들의 그룹

시간복잡도 : O(V + E) (V : 정점 수, E : 간선 수)

![](https://github.com/user-attachments/assets/736940b8-7a30-4be8-89c1-8586b49ed4ce)

이런 그래프가 주어진다고 하자. 여기서 자신이 속한 그룹 번호를 나타내는 parent와, 이미 그룹화했는지 확인하는 visited 두개의 배열을 사용한다.

![](https://github.com/user-attachments/assets/e322aed2-f672-49dc-815f-1e39537e1219)

먼저 1번 정점부터 방문한다. 1번 정점을 스택에 넣고, remember(해당 정점이 방문 가능한 가장 작은 그룹 번호)과 1번 정점의 parent에 1(parent[cur] = ++idx, 그룹번호 1번)을 저장한다.  
1번 정점과 연결된 2번 정점을 방문한 적 없기에(parent[next]==0) 먼저 방문한다.

![](https://github.com/user-attachments/assets/2ca7a60c-a619-47eb-b504-d31818963458)

2번 정점에 방문한다. 2번 정점을 스택에 넣고, remember과 2번 정점의 parent에 2을 저장한다.  
2번 정점과 연결된 3번 정점을 방문한 적 없기에 먼저 방문한다.

![](https://github.com/user-attachments/assets/1ccdc827-2878-4b92-8096-df30c56804d6)

3번 정점에 방문한다. 3번 정점을 스택에 넣고, remember과 3번 정점의 parent에 3을 저장한다.  
3번 정점과 연결된 4번 정점을 방문한 적 없기에 먼저 방문한다.

![](https://github.com/user-attachments/assets/e80cb2b1-56e4-4ebd-9803-f6d7fe74bef1)

4번 정점에 방문한다. 4번 정점을 스택에 넣고, remember과 4번 정점의 parent에 4를 저장한다.  
4번 정점과 연결된 3번 정점을 방문한 적 있지만(parent[3]!=0), 3번 정점의 그룹이 확정되지 않았기에(visited[next]==false) remember에 원래의 값과 4번 정점의 현재 그룹(parent[4]) 중 작은 값을 저장한다.  
4번 정점과 연결된 8번 정점을 방문한 적 없기에 먼저 방문한다.

![](https://github.com/user-attachments/assets/26b53322-acba-4509-b8f8-2b12d9def098)

8번 정점에 방문한다. 8번 정점을 스택에 넣고, remember과 4번 정점의 parent에 5를 저장한다.  
8번 정점과 연결된 8번 정점을 방문한 적 있지만, 8번 정점의 그룹이 확정되지 않았기에 remember에 원래의 값과 8번 정점의 현재 그룹 중 작은 값을 저장한다.  

![](https://github.com/user-attachments/assets/e8479f11-5100-45c9-b1e2-a7907d08842d)

8번 정점에서 더이상 방문할 수 있는 정점이 없다.  
remember값이 처음 저장한 값과 동일하다면(그룹의 대표 정점) 스택에서 cur가 나올때까지 빼서 사이클 목록에 저장하고, visited 값을 true로, parent 값을 remember로 업데이트한다.  
그 결과, 8번 정점만 꺼내져서 업데이트 되었다.  
만들어진 그룹(사이클)은 파란색으로 표시하였다.

![](https://github.com/user-attachments/assets/aac174e6-4d88-4c65-af4f-99465b18861b)

4번 정점으로 되돌아가서, 4번 정점에서 더이상 방문할 수 있는 정점이 없다.  
remember값이 처음 저장한 값과 동일하기에 스택에서 cur가 나올때까지 빼서 사이클 목록에 저장하고, visited 값을 true로, parent 값을 remember로 업데이트한다.  
그 결과, 3번, 4번 정점이 꺼내져서 업데이트 되었다.

![](https://github.com/user-attachments/assets/779a50b3-7202-47f7-bd46-2af82898ab2e)

3번 정점으로 되돌아가서, 3번 정점과 연결된 7번 정점을 방문한 적 없기에 방문한다. 7번 정점을 스택에 넣고, remember과 7번 정점의 parent에 6을 저장한다.  

![](https://github.com/user-attachments/assets/3b866c15-d718-4483-bdc5-758b47b57947)

6번 정점에 방문한다. 6번 정점을 스택에 넣고, remember과 6번 정점의 parent에 7을 저장한다.
6번 정점과 연결된 7번 정점을 방문한 적 있지만, 7번 정점의 그룹이 확정되지 않았기에 remember에 원래의 값과 7번 정점의 현재 그룹 중 작은 값을 저장한다.  
remember값이 처음 저장한 값과 동일하지 않기에 되돌아간다.

![](https://github.com/user-attachments/assets/3cc85dbc-47cc-4aae-84a3-638ab71389d7)

7번 정점으로 되돌아간다. 연결된 8번 정점은 이미 그룹이 만들어져서 패스한다.  
7번 정점에서 더이상 방문할 수 있는 정점이 없다.  
remember값이 처음 저장한 값과 동일하기에 스택에서 cur가 나올때까지 빼서 사이클 목록에 저장하고, visited 값을 true로, parent 값을 remember로 업데이트한다.  
그 결과, 6번, 7번 정점이 꺼내져서 업데이트 되었다.

![](https://github.com/user-attachments/assets/1d7a749c-95b7-4492-a89d-a7cae0db4cf2)

몇 번의 과정 후에 2번 정점까지 되돌아가서 5번 정점을 방문한다. 2번 정점을 스택에 넣고, remember과 2번 정점의 parent에 8를 저장한다.  
5번 정점과 연결된 1번 정점을 방문한 적 있지만, 1번 정점의 그룹이 확정되지 않았기에 remember에 원래의 값과 1번 정점의 현재 그룹 중 작은 값을 저장한다.  

![](https://github.com/user-attachments/assets/e7b127c0-ac55-4de6-aedf-2ad033226978)

몇 번의 과정 후에 1번 정점까지 되돌아간다. 1번 정점에서 더이상 방문할 수 있는 정점이 없다.  
remember값이 처음 저장한 값과 동일하기에 스택에서 cur가 나올때까지 빼서 사이클 목록에 저장하고, visited 값을 true로, parent 값을 remember로 업데이트한다.  
그 결과, 1번, 2번, 5번 정점이 꺼내져서 업데이트 되었다.

그리고 스택이 비어있고 방문 하지 않은 정점이 없어 종료한다. (방문 안한 정점이 있다면 그 정점을 root로 추가 탐색 시작)

[연습 문제 (백준 2150번)](https://www.acmicpc.net/problem/2150)

``` c++
/** https://www.acmicpc.net/problem/2150 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/** 
 * MAX : 최대 정점 개수
 * visited[i] : i번 정점이 현재 임의의 SCC에 포함되었는지 여부
 * idx : 각 정점에 할당하는 SCC번호 (dfs 탐색 순서로 SCC번호를 할당해서 정점번호와는 다르게 할당됨, 같은 값을 가진 정점들은 같은 SCC에 속함)
 * parent[i] : i번 정점과 같은 SCC에 속하며 갈 수 있는 제일 작은 SCC 번호
 * conn[i][j] : i에서 j로의 간선
 * SCCs[i][j] : i번째 SCC의 j번째 정점 (각각의 SCC는 위상정렬되어 나타나기에 i가 클수록 더 우선순위가 높음)
 * stk : SCC를 뽑아내기 위해 사용하는 스택
 */
const int MAX = 10001;

bool visited[MAX];
int idx, parent[MAX];
vector<vector<int>> conn(MAX), SCCs;
stack<int> stk;

int dfs(int cur) {
    /** 
     * 스택에 현재 정점 번호를 넣고, parent[cur]에 SCC 번호를 기록함
     * rem : 현재의 정점에서 도달할 수 있는 가장 작은 SCC 번호
     * parent[cur] :
     * SCC에 포함 안되었을 때 -> 현재의 정점에 할당된 SCC번호
     * SCC에 포함 되었을 때 -> 같은 SCC에 속한 가장 작은 SCC번호
     */
    stk.push(cur);
    int rem = parent[cur] = ++idx;
    
    /** 
     * 현재 정점에서 이동할 수 있는 정점에 대해:
     * 한번도 방문한 적이 없는 정점은 그 정점에 대해 dfs 탐색을 하고 그 정점에서 도달 가능한 가장 작은 SCC 번호를 받아오고,
     * 방문한 적은 있지만 현재 어떠한 SCC에도 소속되지 않은 정점에 대해서는 그 정점의 SCC 번호를 받아온다.
     * prof. 방문한 적이 있지만 어떠한 SCC에도 소속되지 않았다는 것은 해당 정점에서 도달 가능한 다른 정점과는 같은 SCC에 속할 수 없음을 뜻함
     * 
     * 현재 정점보다 받아온 SCC번호가 큰 경우 : 순방향 간선을 타고 간 것
     * 현재 정점보다 받아온 SCC번호가 작은 경우 : 역방향 간선을 타고 간 것 -> 사이클이 존재할 가능성이 있음
     */
    for(int next:conn[cur]) {
        if(!parent[next]) rem = min(rem, dfs(next));
        else if(!visited[next]) rem = min(rem, parent[next]);
    }

    /** 
     * 현재 도달 가능한 가장 작은 SCC번호가 자기 자신인 경우 -> 사이클 발견
     * prof. rem == parent[cur] == top인 경우(자신으로부터 도달한 다른 정점에서 다시 돌아오지 못한 경우, 사이클 존재 X) 크기가 1인 SCC 발견
     * prof. rem == parent[cur] != top인 경우(자신으로부터 도달한 다른 정점에서 다시 돌아온 경우, 사이클 존재 O) 크기가 1보다 큰 SCC 발견
     * 
     * 스택에서 자기 자신을 발견할 때까지 뽑아 같은 SCC에 집어넣기
     * 
     * 집어넣으면서:
     * visited[top] = true;을 해줘서 SCC에 포함되었다 마킹
     * parent[top] = rem;을 해줘서 도달 가능한 가장 작은 SCC번호로 설정
     */
    if(rem==parent[cur]) {
        SCCs.push_back(vector<int>());
        while(true) {
            int top = stk.top(); stk.pop();
            SCCs.back().push_back(top);
            visited[top] = true;
            parent[top] = rem;
            if(top==cur) break;
        }
    }
    return rem;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int v, e; cin >> v >> e;

    // 간선 연결
    while(e--) {
        int a, b; cin >> a >> b;
        conn[a].push_back(b);
    }

    /** Tarjan's Algorithm 시작 */
    for(int i=1;i<=v;i++) {
        if(!visited[i]) dfs(i);
    }
    /** Tarjan's Algorithm 끝 */

    for(int i=0;i<SCCs.size();i++) {
        sort(SCCs[i].begin(), SCCs[i].end());
    }
    sort(SCCs.begin(), SCCs.end());

    cout << SCCs.size() << '\n';
    for(auto SCC:SCCs) {
        for(int val:SCC) {
            cout << val << ' ';
        }
        cout << "-1\n";
    }
}
```
