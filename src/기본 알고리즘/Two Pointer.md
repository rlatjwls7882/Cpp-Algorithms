## Two Pointer
두 개의 포인터를 움직이며 배열이나 리스트에서 원하는 조건을 만족하는 구간을 효율적으로 찾는 알고리즘

시간복잡도 : O(N) (N : 데이터 개수)

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
