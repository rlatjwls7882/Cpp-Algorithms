## Square Root Decomposition (평방 분할)
값을 √N개씩 연속된 구간들로 나누어 관리하여 특정 구간에 대한 쿼리를 O(√N) 시간에 처리하는 알고리즘

시간복잡도 : O(Q√N) (Q : 쿼리의 수)

[연습 문제 (백준 2912번)](https://www.acmicpc.net/problem/2912)

![](https://github.com/user-attachments/assets/de79bbcb-12c2-4b97-9293-d8d4e4fb88af)

이러한 N개의 숫자들과, 범위 안에서 과반수가 되는 수를 찾는 쿼리가 주어진다고 생각해보자.

![](https://github.com/user-attachments/assets/5c4c5ae6-5a6d-4a68-8489-d103b6d6f7cf)

이 때, √N개씩 쪼개서 관리하면 더 빨리 쿼리를 해결할 수 있다.  
int(√8)이어서 여기선 2개씩 쪼개서 bucket에 저장한다.  
저장하는 값은 해당 범위에서 과반수가 가능한 후보들을 담는다. (과반수인 수가 없으면 제일 많은 수 중 아무거나)

나중에 수의 등장횟수를 이분탐색으로 빨리 찾기 위해 각 수들이 등장하는 위치를 idx라는 이차원 벡터에 오름차순으로 저장해놓는다.

![](https://github.com/user-attachments/assets/36c96830-c0c5-4a29-b2ae-0ab4db52e0c5)

2 ~ 4 범위에서 과반수를 찾아보겠다.  
이 범위에서는 bucket 부분만 살펴보면 된다.  
후보인 1과 3을 모두 살펴본 결과 과반수가 없다. (upper_bound(4) - lower_bound(2))  
2를 확인하지 않는 이유는 어느 구간에서도 과반수인 경우가 없어 전체 구간에서도 과반수일 수가 없다.

![](https://github.com/user-attachments/assets/dd7b2f6b-ea41-4229-a2fb-4e6da13e5b1e)

이번에는 1 ~ 4 범위에서 과반수를 찾아보겠다.  
이 범위에서는 bucket 부분과 bucket에 포함 안되는 왼쪽 조금 부분을 살펴보면 된다.  
후보인 1, 2, 3을 모두 살펴본 결과 2가 3개 등장하여 과반수가 된다.

``` c++
/** http://boj.kr/6c8a6509be2042e3adaae1d068ddb015 */
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
