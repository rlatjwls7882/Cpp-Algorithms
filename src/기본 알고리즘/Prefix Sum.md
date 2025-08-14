## Prefix Sum (누적 합)
배열의 각 인덱스까지의 합을 미리 계산해 두어, 임의 구간의 합을 O(1)에 구하는 알고리즘

시간복잡도 : 전처리 O(N), 쿼리 O(1) (N : 데이터 개수)

![prefix sum image](https://github.com/user-attachments/assets/ce588973-d10a-4442-888f-66d91ddc2bca)

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
