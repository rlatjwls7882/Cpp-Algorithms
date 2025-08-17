## Prefix Sum (누적 합)
배열의 각 인덱스까지의 합을 미리 계산해 두어, 임의 구간의 합을 O(1)에 구하는 알고리즘

시간복잡도 : 전처리 O(N), 쿼리 O(1) (N : 데이터 개수)

![](https://github.com/user-attachments/assets/39b43d6b-7b87-47c0-8b0d-5064c5e1a7e6)

입력된 배열 A가 다음과 같다고 하자.

![](https://github.com/user-attachments/assets/34f47c73-25fd-4ac0-aea5-8ba7115a7f59)

그러면 배열 A의 누적 합 preSum은 다음과 같다고 할 수 있다. 여기서 preSum[i]는 A[0] ~ A[i] 까지의 합이다.

이제 A[i] ~ A[j] 까지의 합은 A[0] ~ A[j]의 합 - (A[0] ~ A[i-1]의 합)으로 나타낼 수 있고, 이는 preSum[j] - preSum[i-1]과 같다.

[연습 문제 (백준 11659번)](https://www.acmicpc.net/problem/11659)

``` c++
/** https://www.acmicpc.net/problem/11659 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

// MAX : 수의 최대 개수
const int MAX = 100'001;

// preSum[i] : 1번 수부터 i번 수까지의 누적 합
int preSum[MAX];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for(int i=1;i<=n;i++) {
        cin >> preSum[i]; // i번째 수 입력
        preSum[i] += preSum[i-1]; // i번째 수에 0 ~ i-1 수의 합 더하기 -> 0 ~ i 수의 합 완성
    }

    while(m--) {
        int i, j; cin >> i >> j;
        cout << preSum[j] - preSum[i-1] << '\n'; // i ~ j 수의 합 = 0 ~ j 수의 합 - 0 ~ i-1 수의 합
    }
}
```
