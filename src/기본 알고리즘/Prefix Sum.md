## Prefix Sum (누적 합) ⚪ Silver III
배열의 누적 합을 미리 계산하여 임의 구간의 합을 $O(1)$에 구하는 알고리즘

시간복잡도 : 전처리 $O(N)$, 쿼리 $O(1)$ ($N$: 데이터 개수)

![](https://github.com/user-attachments/assets/39b43d6b-7b87-47c0-8b0d-5064c5e1a7e6)

배열 $A$가 다음과 같다고 하자.

![](https://github.com/user-attachments/assets/34f47c73-25fd-4ac0-aea5-8ba7115a7f59)

이때 배열 $A$의 누적 합 배열 $preSum$을 다음과 같이 정의한다.

$$
preSum_i = A_0 + A_1 + \dots + A_i
$$

즉, $preSum_i$는 배열의 첫 번째 원소부터 $i$번째 원소까지의 합을 의미한다.

이때 $A_i + A_{i+1} + \dots + A_j$는 다음과 같이 계산할 수 있다.

$$
(A_0 + A_1 + \dots + A_j) - (A_0 + A_1 + \dots + A_{i-1})
$$

이는 누적 합 배열을 이용하면 $preSum_j - preSum_{i-1}$로 표현할 수 있다.

[연습 문제 (백준 11659번)](https://www.acmicpc.net/problem/11659)

``` c++
/** http://boj.kr/8a8bf787cca8473fa1b0c13219b94918 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

int preSum[100'001]; // preSum[i] : 1번 수부터 i번 수까지의 누적 합

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i=1;i<=n;i++) {
        cin >> preSum[i]; // i번째 수 입력
        preSum[i] += preSum[i-1]; // i번째 수에 0 ~ i-1 수의 합 더하기 -> 0 ~ i 수의 합 완성
    }

    while(m--) {
        int i, j; cin >> i >> j;
        cout << preSum[j] - preSum[i-1] << '\n'; // i ~ j 수의 합 = (0 ~ j 수의 합) - (0 ~ i-1 수의 합)
    }
}
```
