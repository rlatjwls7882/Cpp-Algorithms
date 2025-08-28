## Backtracking
모든 경우를 탐색하되, 해답이 될 수 없는 경로는 중간에 가지치기하여 탐색을 중단하는 완전 탐색 알고리즘

시간복잡도 : 최악 O(Kⁿ) (K : 선택지 개수, n : 깊이)

![](https://github.com/user-attachments/assets/753916ab-5999-4c9d-9c03-1d6e5db03b6b)

[연습 문제 (백준 15649번)](https://www.acmicpc.net/problem/15649)

위 문제는 nPm을 전부 출력하는 문제로, 깊이마다 선택지를 하나씩 채워 넣고, 사용된 숫자는 제외하는 방식으로 구현된다.

![](https://github.com/user-attachments/assets/15c12411-6cf2-45ab-98c7-ec599bd16e6b)

n=4, m=3인 경우를 예로 살펴보겠다.

초기에는 위와 같이 할당되어 있다.

![](https://github.com/user-attachments/assets/46c53ca8-f25d-41ab-bdf7-b10d0e921297)

출력의 깊이 0 (첫 번째 칸)에서 1~4까지 반복문을 돌며 사용하지 않은 것을 사용한다.

그 결과 첫 번째 칸에는 1이 할당되었다.

![](https://github.com/user-attachments/assets/93da5a15-d9d3-4396-93d9-90cee6411df0)

깊이 1에서는 2가 할당되어 다음과 같아진다.

![](https://github.com/user-attachments/assets/08069977-a5ad-4d72-97ed-939239eb67e1)

깊이 2에서는 3이 할당되어 다음과 같아진다.

![](https://github.com/user-attachments/assets/6950fd5d-b975-4490-aaa9-2b984067e5c1)

깊이 3에서는 범위를 벗어나 지금까지 기록한 '1 2 3'을 출력된다.

![](https://github.com/user-attachments/assets/65dffecc-8b6b-4f18-8738-a3010b010b62)

다시 깊이 2로 돌아가보니 이번에는 4가 할당된다.

![](https://github.com/user-attachments/assets/a95f8b20-3e16-43ef-87da-a6790c8f0df3)

깊이 3에서는 이번에는 기록한 '1 2 4'를 출력된다.

![](https://github.com/user-attachments/assets/dbff43a2-fdc5-4eec-9044-50aef6730a65)

그 다음에는 깊이 1까지 돌아가 깊이 1에 3이 할당된다.

![](https://github.com/user-attachments/assets/c1309fa2-9951-4c4b-abf2-e96b49503d5f)

깊이 2에서는 2가 할당된다.

![](https://github.com/user-attachments/assets/02d56a61-06dd-4e3d-8790-022f0b89d7e3)

깊이 3에서는 기록한 '1 3 2'가 출력된다.

이러한 과정을 통해

$1 2 3$  
$1 2 4$  
$1 3 2$  
$1 3 4$  
$2 1 3$  
$2 1 4$  
$...$  
이 출력된다.

``` c++
/** http://boj.kr/1a898dba13d74c9fb524af5ca7770877 제출 코드 */
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
