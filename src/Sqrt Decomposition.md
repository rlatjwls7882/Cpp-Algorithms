## Sqrt Decomposition (평방 분할)
값을 √N개씩 연속된 구간들로 나누어 관리하여 특정 구간에 대한 쿼리를 O(√N) 시간에 처리하는 알고리즘

시간복잡도 : O(Q√N) (Q : 쿼리의 수)

[연습 문제 (백준 2912번)](https://www.acmicpc.net/problem/2912)

``` c++
/** https://www.acmicpc.net/problem/2912 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 300'000;
const int MAX_COLOR = 10'001;
const int SQRT_MAX = 600;

/** 
 * _size : 분할된 구간의 크기 (평방분할이니 sqrt(n)개씩)
 * arr[i] : i번째 노드가 나타내는 과반수의 후보
 * bucket[i] : i번째 블록(최대 sqrt(n)의 크기를 가짐)가 나타내는 과반수의 후보
 * idx[i] : 모자색상 i가 등장한 위치들
 */
int n, c, _size;
int arr[MAX], bucket[SQRT_MAX];
vector<vector<int>> idx(MAX);

/** 
 * 과반수가 될 수 있는 모든 수의 후보들을 평방분할하여 담음
 * - 해당 범위에서 어떤 한 색이 과반수가 아니면 후보가 될 수 없음
 * - - prof. 어떤 한 범위에서 a가 과반수가 아니다.
 * - - 하지만 추가로 주위의 범위를 더 선택해 a를 과반수로 만드는 범위를 선택하고 싶다.
 * - - 그렇게 a를 과반수로 만드는 범위를 선택하면, 새로 선택되는 범위만 선택해도 a는 과반수이다.
 */
void init() {
    _size = sqrt(n);
    for(int i=0;i<n;i++) {
        cin >> arr[i];
    }

    for(int i=0;i<n;i+=_size) {
        vector<int> cnt(c+1);
        int maxColor=0;
        for(int j=i;j<i+_size && j<n;j++) {
            if(++cnt[arr[j]] > maxColor) {
                maxColor = arr[j];
            }
            idx[arr[j]].push_back(j);
        }
        bucket[i/_size] = maxColor;
    }
}

/** 
 * 모자의 색 k가 l과, r 사이에 몇개가 있는지 반환함.
 * - 각각의 k(0~10000)에 대해 각자의 값이 등장하는 모든 인덱스를 오름차순으로 담아놓음.
 * - upper_bound(r을 초과하는 첫 위치) - lower_bound(l 이상의 값이 등장하는 첫 위치)로 개수 계산
 */
int findCnt(int l, int r, int k) {
    return upper_bound(idx[k].begin(), idx[k].end(), r) - lower_bound(idx[k].begin(), idx[k].end(), l);
}

/** 
 * 순서대로 각각의 반복문은 
 * - 왼쪽의 단일 노드들 처리.
 * - 오른쪽의 단일 노드들 처리.
 * - _size개의 노드가 합쳐진 블록 처리.
 * 를 나타냄.
 */
void query(int l, int r) {
    l--; r--;
    int i=l, j=r;
    while(i%_size!=0 && i<=r) {
        if(findCnt(l, r, arr[i])>(r-l+1)/2) {
            cout << "yes " << arr[i] << '\n';
            return;
        }
        i++;
    }
    while((j+1)%_size!=0 && l<=j) {
        if(findCnt(l, r, arr[j])>(r-l+1)/2) {
            cout << "yes " << arr[j] << '\n';
            return;
        }
        j--;
    }
    while(i<=j) {
        if(findCnt(l, r, bucket[i/_size])>(r-l+1)/2) {
            cout << "yes " << bucket[i/_size] << '\n';
            return;
        }
        i += _size;
    }
    cout << "no\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> c;
    init();

    int m; cin >> m;
    while(m--) {
        int a, b; cin >> a >> b;
        query(a, b);
    }
}
```
