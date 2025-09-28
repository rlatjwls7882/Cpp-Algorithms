## Binary Search (이분 탐색)
정렬된 데이터에서 원하는 값을 찾기 위해 탐색 범위를 절반씩 줄여가는 알고리즘

시간복잡도 : O(MlogN) (N : 데이터 개수, M : 탐색 횟수)

![](https://github.com/user-attachments/assets/1f4ee66c-4b08-4ab5-ba4d-f8dff4e8c1e8)

정렬된 배열 A에서 21이라는 값을 찾는다면 초기의 left와 right 값은 다음과 같고, 전체 범위를 나타냅니다.

![](https://github.com/user-attachments/assets/2613290c-f15a-4205-9e92-2dc45827b02a)

첫번 째 반복에서는, mid=3으로 찾는 값 21보다 A[mid]인 10이 작아 자동으로 0~mid까지 모든 값이 21보다 작은 것을 알 수 있다. (left = mid+1)

![](https://github.com/user-attachments/assets/4b4658a1-bb3b-4d80-b80e-cb065d8d6d18)

두번 째 반복에서는, mid=5로 찾는 값 21보다 A[mid]인 20이 작아 자동으로 0~mid까지 모든 값이 21보다 작은 것을 알 수 있다. (left = mid+1)

![](https://github.com/user-attachments/assets/50309bc0-aedc-450f-94b0-a24148d95c4a)

세번 째 반복에서는, mid=6로 찾는 값 21보다 A[mid]인 30이 크거나 같아 자동으로 mid+1~right까지 모든 값이 21보다 크거나 같은 것을 알 수 있다. (right = mid)

![](https://github.com/user-attachments/assets/7b88348e-36b7-490c-818c-6408d07263bc)

마지막으로 A[left]나 A[right]이 찾는 값인 21과 같다면 이 배열에 21이 존재한다.

[연습 문제 (백준 1920번)](https://www.acmicpc.net/problem/1920)

``` c++
/** http://boj.kr/13586b0c1d744fe8b0c4f6a8393ed65c 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

int n;
int A[100'001];

/** 
 * Binary Search
 * 처음 범위 : 0 ~ n-1
 * 
 * right가 left보다 큰 동안 :
 * - mid를 (left+right)/2으로 설정
 * - mid 위치의 값이 현재 탐색중인 값보다 작다면 left = mid+1 (left ~ mid의 값은 전부 작다는 것이 확정되었으니 커팅)
 * - 그렇지 않다면 right = mid (mid+1 ~ right의 값은 전부 크다는 것이 확정되었으니 커팅)
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
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i=0;i<n;i++) cin >> A[i];
    sort(A, A+n); // 오름차순으로 정렬

    int m; cin >> m;
    while(m--) {
        int val; cin >> val; // 현재 탐색할 값
        cout << binary_search(val) << '\n';
    }
}
```
