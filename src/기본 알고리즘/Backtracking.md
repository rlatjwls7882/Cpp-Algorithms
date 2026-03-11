## Backtracking (백트래킹) ⚪ Silver III
모든 경우를 탐색하면서 해답이 될 수 없는 경로는 가지치기하여 탐색을 줄이는 완전 탐색 기법

시간복잡도: 최악 $O(K^n)$ ($K$: 선택지 개수, $n$: 깊이)

$_nP_m$의 모든 경우를 오름차순으로 출력하는 문제를 생각해보자.

이 문제는 백트래킹을 이용해 해결할 수 있다. 각 깊이에서 하나의 숫자를 선택하여 결과 배열을 채우고 이미 사용한 숫자는 다시 선택하지 않도록 제외한다.

![](https://github.com/user-attachments/assets/15c12411-6cf2-45ab-98c7-ec599bd16e6b)

예를 들어 $n=4$, $m=3$인 경우를 살펴보자. 초기 상태에서는 아직 어떤 숫자도 선택되지 않았다.

![](https://github.com/user-attachments/assets/46c53ca8-f25d-41ab-bdf7-b10d0e921297)

깊이 $0$에서는 첫 번째 칸에 들어갈 숫자를 결정한다. $1$부터 $4$까지 차례대로 확인하면서 아직 사용하지 않은 숫자를 선택한다. 먼저 $1$이 선택된다.

![](https://github.com/user-attachments/assets/93da5a15-d9d3-4396-93d9-90cee6411df0)

이후 깊이 $1$에서는 두 번째 칸에 들어갈 숫자를 결정한다. 이미 $1$은 사용되었으므로 남아 있는 숫자 중 가장 작은 $2$가 선택된다.

![](https://github.com/user-attachments/assets/08069977-a5ad-4d72-97ed-939239eb67e1)

다음으로 깊이 $2$에서는 세 번째 칸에 들어갈 숫자를 결정한다. 사용하지 않은 숫자 중 가장 작은 $3$이 선택된다.

![](https://github.com/user-attachments/assets/6950fd5d-b975-4490-aaa9-2b984067e5c1)

이제 깊이가 $m=3$에 도달했으므로 현재까지 선택한 값인 **1 2 3**을 출력한다.

![](https://github.com/user-attachments/assets/65dffecc-8b6b-4f18-8738-a3010b010b62)

출력을 마친 뒤에는 백트래킹을 통해 이전 상태로 되돌아간다. 깊이 $2$에서 다음으로 선택할 수 있는 숫자는 $4$이므로 세 번째 칸의 값을 $4$로 바꾼다.

![](https://github.com/user-attachments/assets/a95f8b20-3e16-43ef-87da-a6790c8f0df3)

다시 깊이 $3$에 도달했으므로 이번에는 **1 2 4**를 출력한다.

![](https://github.com/user-attachments/assets/dbff43a2-fdc5-4eec-9044-50aef6730a65)

이후 다시 이전 상태로 돌아가 깊이 $1$에서 다음 가능한 숫자를 선택한다. 두 번째 칸에는 $3$이 들어간다.

![](https://github.com/user-attachments/assets/c1309fa2-9951-4c4b-abf2-e96b49503d5f)

그 다음 깊이 $2$에서는 아직 사용하지 않은 숫자 중 $2$가 선택된다.

![](https://github.com/user-attachments/assets/02d56a61-06dd-4e3d-8790-022f0b89d7e3)

따라서 이번에는 **1 3 2**가 출력된다.

이와 같은 과정을 반복하면 가능한 모든 순열이 차례대로 출력된다.

$1 2 3$  
$1 2 4$  
$1 3 2$  
$1 3 4$  
$2 1 3$  
$2 1 4$  
$\cdots$

이처럼 백트래킹은 현재 깊이에서 가능한 값을 하나 선택한 뒤 하나의 경우를 완성하면 이전 단계로 되돌아가 다음 선택지를 탐색하는 방식으로 동작한다.

![](https://github.com/user-attachments/assets/753916ab-5999-4c9d-9c03-1d6e5db03b6b)

[연습 문제 (백준 15649번)](https://www.acmicpc.net/problem/15649)

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
void backtracking(int depth=0) {
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
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    backtracking();
}
```
