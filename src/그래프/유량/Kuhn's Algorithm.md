## Kuhn's Algorithm (Maximum Bipartite Matching, 이분 매칭)

그래프를 [이분 그래프](https://ko.wikipedia.org/wiki/%EC%9D%B4%EB%B6%84_%EA%B7%B8%EB%9E%98%ED%94%84)로 나타내었을 때 최대 매칭 수(왼쪽과 오른쪽의 쌍의 수)를 찾는 알고리즘

시간복잡도 : O(VE) (V : 양쪽 그룹 중 더 큰 정점의 크기)

![image](https://github.com/user-attachments/assets/56ba1be0-a03c-4bb8-8816-b7da371723da)

이분 그래프란 정점들을 그림처럼 왼쪽 정점 그룹과 오른쪽 정점 그룹으로 나누었을 때, 서로 다른 그룹들 사이에만 간선이 있는 그래프이다.

[연습 문제 (백준 11375번)](https://www.acmicpc.net/problem/11375)

직원들을 각각 왼쪽 정점으로, 일들을 각각 오른쪽 정점으로 설정해두고 직원-일 간의 최대 쌍의 수를 구해주면 된다.

``` c++
/** https://www.acmicpc.net/problem/11375 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 1001; // 최대 정점 개수 (문제마다 다름)
int A[MAX], B[MAX]; // A : 왼쪽 정점이 선택한 오른쪽 정점 번호, B : 오른쪽 정점이 선택한 왼쪽 정점 번호, 맨 처음에 -1로 한번 초기화
bool visited[MAX]; // 이미 이번 확인에서 방문한 정점인지 확인하기 위한 배열, 매 방문마다 false로 초기화
vector<vector<int>> conn(MAX); // 왼쪽 정점 -> 오른쪽 정점으로의 간선 목록

/**
 * cur번째 왼쪽 정점이 아직 선택이 안된 오른쪽 정점과 새로 매칭이 되는지 확인.
 * 
 * 만약 왼쪽 정점과 오른쪽 정점이 다음과 같이 간선이 있다면,
 * 1 -> 1
 * 1 -> 2
 * 2 -> 2
 * 
 * main의 for문에서 dfs(1) 호출
 * 1 -> 1 살펴봄 : 첫 매칭 발생. (A[1]==1, B[1]==1)
 * 
 * main의 for문에서 dfs(2) 호출
 * 2 -> 1 을 살펴보는데 B[1]에 이미 1이란 값이 들어있음. : 왼쪽 1번 정점을 다른 오른쪽 정점과 매칭할 수 있는지 확인
 * 1 -> 1 살펴봄 : 오른쪽 1번 정점은 방금 방문해서 더 살펴볼 필요가 없음(visited[1]==true)
 * 1 -> 2 살펴봄 : 매칭 변경 가능 (1 -> 2로 변경, A[1]==2, B[2]==1)
 * 2 -> 1 다시 살펴봄 : 매칭 가능 (A[2]==1, B[1]==2)
 */
bool dfs(int cur) {
    visited[cur]=true;
    for(int next:conn[cur]) {
        if(B[next]==-1 || !visited[B[next]] && dfs(B[next])) {
            A[cur] = next;
            B[next] = cur;
            return true;
        }
    }
    return false;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, M; cin >> N >> M;

    /** 
     * i번째 왼쪽 정점(직원 정점)이 j번째 오른쪽 정점(일 정점)과 간선이 있음.
     */
    for(int i=1;i<=N;i++) {
        int cnt; cin >> cnt;
        while(cnt--) {
            int j; cin >> j;
            conn[i].push_back(j);
        }
    }

    /** 
     * 왼쪽 정점과 오른쪽 정점이 서로 어디에 연결되었는지 확인하기 위한 배열
     * A[i] : i번 왼쪽 정점이 A[i]번 오른쪽 정점과 연결됨.
     * B[i] : i번 오른쪽 정점이 B[i]번 왼쪽 정점과 연결됨.
     * 처음에는 연결이 안되어있어서 -1로 초기화 (꼭 -1일 필요는 없고 절대 등장하지 않은 편한 숫자로 초기화하면 됨)
     */
    memset(A, -1, sizeof A);
    memset(B, -1, sizeof B);

    /** 
     * cnt : 최대 매칭 수
     * i번 왼쪽 정점이 아직 선택되지 않았다면(A[i]==-1) 매칭할 수 있는지 확인
     * dfs(i)==true면, 새로 매칭 가능
     */
    int cnt=0;
    for(int i=1;i<=N;i++) {
        if(A[i]==-1) {
            memset(visited, false, sizeof visited);
            if(dfs(i)) cnt++;
        }
    }
    cout << cnt;
}
```
