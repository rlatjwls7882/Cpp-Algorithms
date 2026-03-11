## Binary Search (이분 탐색) ⚪ Silver IV
정렬된 데이터에서 탐색 범위를 절반씩 줄여가며 원하는 값을 찾는 알고리즘

시간복잡도: $O(M\log N)$ ($N$: 데이터 개수, $M$: 탐색 횟수)

![](https://github.com/user-attachments/assets/1f4ee66c-4b08-4ab5-ba4d-f8dff4e8c1e8)

정렬된 길이 $7$의 배열 $A$에서 값 $21$을 찾는다고 가정하자.

초기에 $21$이 존재할 수 있는 인덱스 범위는 $0 \leq i \leq 6$이다.

![](https://github.com/user-attachments/assets/2613290c-f15a-4205-9e92-2dc45827b02a)

현재 탐색 범위의 가운데 값을 확인한다. $mid = \lfloor \frac{left+right}{2} \rfloor = 3$

이때 $A_{mid} < 21$이므로 $left \leq i \leq mid$인 모든 $A_i$가 $21$보다 작다는 것을 알 수 있다.

따라서 탐색 범위를 $left = mid+1$로 갱신한다.

![](https://github.com/user-attachments/assets/4b4658a1-bb3b-4d80-b80e-cb065d8d6d18)

다시 탐색 범위의 가운데 값을 확인한다. $mid = \lfloor \frac{left+right}{2} \rfloor = 5$

이번에도 $A_{mid} < 21$이므로 $left \leq i \leq mid$인 모든 $A_i$가 $21$보다 작다는 것을 알 수 있다.

따라서 탐색 범위를 $left = mid+1$로 갱신한다.

![](https://github.com/user-attachments/assets/50309bc0-aedc-450f-94b0-a24148d95c4a)

다시 탐색 범위의 가운데 값을 확인한다. $mid = \lfloor \frac{left+right}{2} \rfloor = 6$

이번에는 $A_{mid} \ge 21$이므로 $mid \leq i \leq right$인 모든 $A_i$가 $21$보다 크거나 같다는 것을 알 수 있다.

따라서 탐색 범위를 $right = mid$로 갱신한다.

![](https://github.com/user-attachments/assets/7b88348e-36b7-490c-818c-6408d07263bc)

이제 $left = right$이므로 더 이상 탐색 범위를 줄일 수 없다.

마지막으로 $A_{left} = A_{right}$ 값을 확인한다.

이 값이 $21$이 아니므로 배열 $A$에는 $21$이 존재하지 않는다.

[연습 문제 (백준 1920번)](https://www.acmicpc.net/problem/1920)

``` c++
/** http://boj.kr/13586b0c1d744fe8b0c4f6a8393ed65c 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

int A[100'001];

/**
 * Binary Search
 * 처음 범위 : 0 ~ n-1
 *
 * right가 left보다 큰 동안 :
 * - mid를 (left+right)/2로 설정
 * - mid 위치의 값이 현재 탐색중인 값보다 작다면 left = mid+1
 * - 그렇지 않다면 right = mid
 */
bool binary_search(int val) {
    int left=0, right=n-1;
    while(left<right) {
        int mid = (left+right)/2;
        if(A[mid]<val) left=mid+1;
        else right=mid;
    }
    return A[left] == val;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for(int i=0;i<n;i++) cin >> A[i];
    sort(A, A+n);

    int m; cin >> m;
    while(m--) {
        int val; cin >> val;
        cout << binary_search(val) << '\n';
    }
}
```
