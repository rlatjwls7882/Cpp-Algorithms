## Two Pointer
두 개의 포인터를 움직이며 배열이나 리스트에서 원하는 조건을 만족하는 구간을 효율적으로 찾는 알고리즘

시간복잡도 : O(NlogN) (N : 데이터 개수, 정렬 O(NlogN) + 스캔 O(N))

![tp1](https://github.com/user-attachments/assets/a6fdf51a-8df6-4c60-bddd-327060570c47)

배열 A가 위와 같이 주어졌고, 두 수의 합이 9가 되는 쌍을 구한다고 하자.

![tp2](https://github.com/user-attachments/assets/8a3ba921-cded-4de3-9286-28cb72e03410)

left를 왼쪽 끝, right를 오른쪽 끝으로 두고 비교를 시작한다.

A[left]+A[right]가 9와 같기에 cnt를 1 증가, left를 1 증가, right를 1 감소시킨다.

![tp3](https://github.com/user-attachments/assets/62471380-8337-4568-844e-7a4b924a583a)

A[left]+A[right]가 9보다 크기에 right를 1 감소시킨다.

![tp4](https://github.com/user-attachments/assets/e44552ce-91d8-4b8d-a3d0-347ac0aea451)

A[left]+A[right]가 9와 같기에 cnt를 1 증가, left를 1 증가, right를 1 감소시킨다.

![tp5](https://github.com/user-attachments/assets/4aea4b00-6c64-4202-a5e3-e59b2dbf07fb)

A[left]+A[right]가 9보다 작기에 left를 1 증가시킨다.

![tp6](https://github.com/user-attachments/assets/6128e62c-e983-472f-a582-c358e988f76b)

A[left]+A[right]가 9보다 크기에 right를 1 감소시킨다.

[연습 문제 (백준 3273번)](https://www.acmicpc.net/problem/3273)

``` c++
/** https://www.acmicpc.net/problem/3273 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

int a[100'000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for(int i=0;i<n;i++) cin >> a[i];
    int val; cin >> val;
    sort(a, a+n); // 정렬

    int cnt=0, left=0, right=n-1; // left와 right는 각각 왼쪽 끝에 위치한 피벗, 오른쪽 끝에 위치한 피벗
    while(left<right) {
        if(a[left]+a[right]<val) { // 두 원소의 합이 val보다 작으면
            left++; // 왼쪽 피벗을 오른쪽으로 이동
        } else if(a[left]+a[right]>val) { // 두 원소의 합이 val보다 크면
            right--; // 오른쪽 피벗을 왼쪽으로 이동
        } else { // 두 원소의 합이 val과 동일하면
            cnt++;
            left++; // 왼쪽 피벗을 오른쪽으로, 오른쪽 피벗을 왼쪽으로 이동 (사용한 원소 제외)
            right--;
        }
    }
    cout << cnt;
}
```
