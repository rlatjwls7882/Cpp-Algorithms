## Two Pointer (두 포인터) ⚪ Silver III
두 개의 포인터를 움직이며 배열에서 조건을 만족하는 쌍을 효율적으로 찾는 알고리즘

시간복잡도: $O(N)$ ($N$: 데이터 개수)

![](https://github.com/user-attachments/assets/a6fdf51a-8df6-4c60-bddd-327060570c47)

다음과 같은 배열 $A$에서 두 수의 합이 $9$가 되는 쌍을 찾는다고 하자.

![](https://github.com/user-attachments/assets/8a3ba921-cded-4de3-9286-28cb72e03410)

처음에는 왼쪽 포인터 $left$를 배열의 왼쪽 끝에, 오른쪽 포인터 $right$를 배열의 오른쪽 끝에 두고 탐색을 시작한다.

$A_{\text{left}} + A_{\text{right}} = 9$이므로 $cnt$를 $1$ 증가시키고, 해당 조합을 다시 사용하지 않도록  
$left$를 $1$ 증가시키고 $right$를 $1$ 감소시킨다.

![](https://github.com/user-attachments/assets/62471380-8337-4568-844e-7a4b924a583a)

$A_{\text{left}} + A_{\text{right}} > 9$이므로 합을 줄이기 위해 $right$를 $1$ 감소시킨다.

![](https://github.com/user-attachments/assets/e44552ce-91d8-4b8d-a3d0-347ac0aea451)

$A_{\text{left}} + A_{\text{right}} = 9$이므로 $cnt$를 $1$ 증가시키고, 해당 조합을 다시 사용하지 않도록  
$left$를 $1$ 증가시키고 $right$를 $1$ 감소시킨다.

![](https://github.com/user-attachments/assets/4aea4b00-6c64-4202-a5e3-e59b2dbf07fb)

$A_{\text{left}} + A_{\text{right}} < 9$이므로 합을 늘리기 위해 $left$를 $1$ 증가시킨다.

![](https://github.com/user-attachments/assets/6128e62c-e983-472f-a582-c358e988f76b)

$A_{\text{left}} + A_{\text{right}} > 9$이므로 $right$를 $1$ 감소시킨다. $left \ge right$가 되었으므로 탐색을 종료한다.

이와 같이 $left < right$인 동안 위 과정을 반복하면 두 수의 합이 $9$가 되는 모든 쌍을 찾을 수 있다.

[연습 문제 (백준 3273번)](https://www.acmicpc.net/problem/3273)

``` c++
/** http://boj.kr/bba07bce85944877bf61c2508cd6a062 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

int a[100'000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for(int i=0;i<n;i++) cin >> a[i];
    int val; cin >> val;
    sort(a, a+n); // 정렬

    int cnt=0, left=0, right=n-1; // left와 right는 각각 왼쪽 끝에 위치한 포인터, 오른쪽 끝에 위치한 포인터
    while(left<right) {
        if(a[left]+a[right]<val) { // 두 원소의 합이 val보다 작으면
            left++; // 왼쪽 포인터를 오른쪽으로 이동
        } else if(a[left]+a[right]>val) { // 두 원소의 합이 val보다 크면
            right--; // 오른쪽 포인터를 왼쪽으로 이동
        } else { // 두 원소의 합이 val과 동일하면
            cnt++;
            left++; // 왼쪽 포인터를 오른쪽으로, 오른쪽 포인터를 왼쪽으로 이동 (사용한 원소 제외)
            right--;
        }
    }
    cout << cnt;
}
```
