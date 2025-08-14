## Backtracking
모든 경우를 탐색하되, 해답이 될 수 없는 경로는 중간에 가지치기하여 탐색을 중단하는 완전 탐색 알고리즘

시간복잡도 : 최악 O(Kⁿ) (K : 선택지 개수, n : 깊이)

![backtracking image](https://github.com/user-attachments/assets/753916ab-5999-4c9d-9c03-1d6e5db03b6b)

[연습 문제 (백준 15649번)](https://www.acmicpc.net/problem/15649)

``` c++
/** https://www.acmicpc.net/problem/15649 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/** 
 * n : 선택지의 개수
 * m : 최대 깊이
 * arr[i] : 깊이 i일때의 저장된 값
 * visited[i] : i번째 선택지가 사용되었는지 여부
 */
int n, m, arr[8];
bool visited[8];

/** 
 * Backtracking
 * - 최대 깊이에 도달한 경우
 * - - 문제에서 요구하는 것을 수행하고 return으로 빠져나오기
 * - 최대 깊이에 도달하지 않은 경우
 * - - n개의 선택지 중 사용 안된 것을 사용하고 다음 깊이로 이동
 */
void back(int depth=0) {
    if(depth==m) {
        // 문제 요구사항 : 출력
        for(int i=0;i<m;i++) cout << arr[i] << ' ';
        cout << '\n';
        return;
    }

    for(int i=0;i<n;i++) {
        if(!visited[i]) { // i번째 선택지를 사용 안한 경우
            visited[i]=true; // 사용 마킹
            arr[depth]=i+1;
            back(depth+1); // 다음 깊이로 이동
            visited[i]=false; // 사용 마킹 해제
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    back();
}
```
