## Segment Tree
포화 이진 트리 구조를 이용하여 구간 쿼리를 최적화하는 알고리즘

시간복잡도 : O(QlogN) (Q : 쿼리의 수)

[연습 문제 (백준 2042번)](https://www.acmicpc.net/problem/2042)

``` c++
/** https://www.acmicpc.net/problem/2042 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/**
 * MAX : 수의 최대 개수
 * _size : 사용할 세그먼트 트리의 크기 (_size/2 ~ _size-1까지 값이 저장됨)
 * arr[MAX*4] : 세그먼트 트리 (최악의 경우 MAX*4 크기가 사용됨)
 * 
 * arr[1] : 1~N 사이의 구간값
 * arr[2(1*2)] : 1~N/2 사이의 구간값
 * arr[3(1*2+1)] : N/2+1~N 사이의 구간값
 * ...
 * arr[_size/2] : 1~1 사이의 구간값
 * ...
 * arr[_size/2+N-1] : N~N 사이의 구간값
 */
typedef long long ll;
const int MAX = 1'000'000;

int _size=1;
ll arr[MAX*4];

/**
 * 세그먼트 트리에서 구간값 꺼내기 (이 문제에선 구간합, 값을 요구하는 쿼리)
 * L : 찾고자 하는 범위의 왼쪽 인덱스
 * R : 찾고자 하는 범위의 오른쪽 인덱스
 * nodeNum : 현재 세그먼트 트리에서의 인덱스 (노드 번호)
 * nodeL : 현재 노드 번호에서의 세그먼트 트리의 왼쪽 끝
 * nodeR : 현재 노드 번호에서의 세그먼트 트리의 오른쪽 끝
 */
ll sum(int L, int R, int nodeNum, int nodeL, int nodeR) {
    if(R<nodeL || nodeR<L) return 0; // 찾고자 하는 범위가 세그먼트 트리의 범위를 완전히 벗어나는 경우
    if(L<=nodeL && nodeR<=R) return arr[nodeNum]; // 찾고자 하는 범위가 세그먼트 트리의 범위에 완전히 포함되는 경우
    int mid = (nodeL+nodeR)/2; // 일부분이 포함되는 경우
    return sum(L, R, nodeNum*2, nodeL, mid) + sum(L, R, nodeNum*2+1, mid+1, nodeR);
}

/**
 * 세그먼트 트리에 값 넣기 (값을 변경하는 쿼리)
 * arr[_size/2+인덱스]에 값 업데이트
 * nodeNum을 2로 나누면서 변경된 부분만 새로운 구간값으로 갱신
 */
void update(int nodeNum, ll val) {
    nodeNum += _size/2;
    arr[nodeNum]=val;
    while(nodeNum>1) {
        nodeNum/=2;
        arr[nodeNum]=arr[nodeNum*2]+arr[nodeNum*2+1];
    }
}

/** 
 * 세그먼트 트리 초기 설정
 * 세그먼트 트리의 사용 크기(_size)를 N*2<=_size인 최소 2의 거듭제곱수로 설정 (세그먼트 트리가 포화 이진 트리기이 때문)
 * _size/2부터 _size/2+N-1까지 값 넣고
 * _size/2-1부터 1까지 초기 구간값 설정
 */
void init(int N) {
    while(_size<N) _size<<=1;
    _size<<=1;

    for(int i=_size/2;i<_size/2+N;i++) cin >> arr[i];

    for(int nodeNum=_size/2-1;nodeNum>0;nodeNum--) {
        arr[nodeNum]=arr[nodeNum*2]+arr[nodeNum*2+1];
    }
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N, M, K; cin >> N >> M >> K;
    init(N);

    for(int i=0;i<M+K;i++) {
        ll a, b, c; cin >> a >> b >> c;
        if(a==1) {
            update(b-1, c);
        } else {
            cout << sum(b-1, c-1, 1, 0, _size/2-1) << endl;
        }
    }
}
```
