## Binary Search (이분 탐색)
정렬된 데이터에서 원하는 값을 찾기 위해 탐색 범위를 절반씩 줄여가는 알고리즘

시간복잡도 : O(MlogN) (N : 데이터 개수, M : 탐색 횟수)

![binary search animation](https://d18l82el6cdm1i.cloudfront.net/uploads/bePceUMnSG-binary_search_gif.gif)

[연습 문제 (백준 1920번)](https://www.acmicpc.net/problem/1920)

``` c++
/** https://www.acmicpc.net/problem/1920 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

int n;
int A[100'001];

/** 
 * Binary Search
 * 처음 범위 : 0 ~ n-1
 * 
 * right가 left보다 큰 동안 :
 * - mid를 (left+right)으로 설정
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
