## Kuhn's Algorithm (Maximum Bipartite Matching, 이분 매칭) 🟢 Platinum IV

그래프를 [이분 그래프](https://ko.wikipedia.org/wiki/이분_그래프)로 나타내었을 때 최대 매칭 수(왼쪽과 오른쪽의 쌍의 수)를 찾는 알고리즘

시간복잡도 : O(VE) (V : 왼쪽 그룹의 정점 수)

![](https://github.com/user-attachments/assets/22f0f71c-b5b1-4f0c-90e0-565170d61714)

이렇게 생긴 이분 그래프와 초기 상태가 다음과 같은 배열 2개가 있다고 가정하자. 이 그래프에서 왼쪽 정점 - 오른쪽 정점의 어떤 점도 중복되지 않은 최대 쌍의 수를 구할 것이다.

이분 그래프란 정점들을 그림처럼 왼쪽 정점 그룹과 오른쪽 정점 그룹으로 나누었을 때, 서로 다른 그룹들 사이에만 간선이 있는 그래프이다.

![](https://github.com/user-attachments/assets/64fa9a91-c479-43fd-91a8-01d0147d19a3)

먼저 A1를 연결 가능한 첫번째 매칭 상대인 B1과 연결한다. 중복이 없으니 넘어간다.

![](https://github.com/user-attachments/assets/e797957b-fcdc-4bbd-9e08-cdf69a2571e8)

A2를 연결 가능한 첫번째 매칭 상대인 B3와 연결한다. 중복이 없으니 넘어간다.

![](https://github.com/user-attachments/assets/3656594b-fc8d-44a3-bdf9-05d81dab8e7b)

A3를 연결 가능한 첫번째 매칭 상대인 B1과 연결한다. 중복이 발생했다.

![](https://github.com/user-attachments/assets/f061def3-b7c5-46ba-ad35-2ad6faeaa7d7)

B1과 원래 연결되어있던 A1을 연결 가능한 다음 정점으로 연결하게 한다. 결국 A1은 B2와 연결되었다.

![](https://github.com/user-attachments/assets/9deda089-4d71-4ba0-b037-a5bf49204326)

A4를 연결 가능한 첫번째 매칭 상대인 B3과 연결한다. 중복이 발생했다.

하지만 원래 B3과 연결되어있던 A2는 다른 정점과 연결할 수 없고 이대로 종료된다. (B4는 매칭 실패)

[연습 문제 (백준 11375번)](https://www.acmicpc.net/problem/11375)

직원들을 각각 왼쪽 정점으로, 일들을 각각 오른쪽 정점으로 설정해두고 직원-일 간의 최대 쌍의 수를 구해주면 된다.

``` c++
/** http://boj.kr/2dc9d016c40d40508c1992d763a1b512 제출 코드 */
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
    memset(B, -1, sizeof B);

    /** 
     * cnt : 최대 매칭 수
     * i번 왼쪽 정점이 매칭할 수 있는지 확인
     * dfs(i)==true면, 새로 매칭 가능
     */
    int cnt=0;
    for(int i=1;i<=N;i++) {
        memset(visited, false, sizeof visited);
        if(dfs(i)) cnt++;
    }
    cout << cnt;
}
```
