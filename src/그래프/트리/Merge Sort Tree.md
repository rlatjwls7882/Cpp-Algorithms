## Merge Sort Tree 🟢 Platinum III
세그먼트 트리에 합병 정렬된 내용을 담아 범위탐색 시간을 줄인 알고리즘 

시간복잡도 : O(NlogN), 공간복잡도 : O(NlogN)

![](https://github.com/user-attachments/assets/52fcb02f-adaf-43b6-993a-1364d14d343f)

이번에도 이전 설명과 같이 원소 4개를 저장한다고 하자.  
4 ~ 7 정점까지 값을 하나 넣고, 4, 5를 병합 정렬하여 2번 정점에 채워넣고, 6, 7을 병합 정렬하여 3번 정점에 채워넣고, etc ...

[연습 문제 (백준 13544번)](https://www.acmicpc.net/problem/13544)

``` c++
/** http://boj.kr/4f92e7d51e5c4383b2ae01963d1dea9d 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 100'000;

int _size;
vector<int> arr[MAX*4];

void init() {
    int n; cin >> n;
    _size=1;
    while(_size<n) _size<<=1;
    _size<<=1;

    for(int i=0;i<n;i++) {
        int A; cin >> A;
        arr[_size/2+i].push_back(A);
    }

    /**
     * 세그먼트 트리와는 다르게, 각 노드에 해당 범위의 정렬된 리스트를 저장함.
     * - 각각의 arr[i]에 대해 arr[i*2]와 arr[i*2+1]를 머지 소트하여 저장
     * 
     * [2, 5, 1, 0, 8, 2]를 머지 소트 트리에 담는다고 하면 :
     * arr[1] = {0, 1, 2, 2, 5, 8}
     * arr[2] = {0, 1, 2, 2}
     * arr[3] = {5, 8}
     * arr[4] = {0, 1}
     * arr[5] = {2, 2}
     * arr[6] = {5, 8}
     * arr[7] = {}
     * arr[8] = {0}
     * arr[9] = {1}
     * arr[10] = {2}
     * arr[11] = {2}
     * arr[12] = {5}
     * arr[13] = {8}
     */
    for(int i=_size/2-1;i>0;i--) {
        int l=0, r=0;
        while(l<arr[i*2].size() || r<arr[i*2+1].size()) {
            if(l==arr[i*2].size() || r<arr[i*2+1].size() && arr[i*2][l] > arr[i*2+1][r]) {
                arr[i].push_back(arr[i*2+1][r++]);
            } else {
                arr[i].push_back(arr[i*2][l++]);
            }
        }
    }
}

/**
 * 이 문제에서의 목표는 임의의 범위에서 k보다 큰 수를 찾는 것
 * 이분탐색을 사용해서 각각의 쿼리에서 찾는 값의 개수를 logN개까지 줄여줘서 이 문제에 대해서는 시간복잡도가 O(log²N)임
 */
int getCnt(int L, int R, int nodeNum, int nodeL, int nodeR, int val) {
    if(R<nodeL || nodeR<L) return 0;
    if(L<=nodeL && nodeR<=R) {
        return arr[nodeNum].end() - upper_bound(arr[nodeNum].begin(), arr[nodeNum].end(), val);
    }
    int mid = (nodeL+nodeR)/2;
    return getCnt(L, R, nodeNum*2, nodeL, mid, val) + getCnt(L, R, nodeNum*2+1, mid+1, nodeR, val);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();

    int lastAns=0;
    int m; cin >> m;
    while(m--) {
        int a, b, c; cin >> a >> b >> c;
        int i = a^lastAns;
        int j = b^lastAns;
        int k = c^lastAns;
        lastAns = getCnt(i-1, j-1, 1, 0, _size/2-1, k);
        cout << lastAns << '\n';
    }
}
```
