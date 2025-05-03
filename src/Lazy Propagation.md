## Lazy Propagation
세그먼트 트리에서 구간 업데이트를 지연 방식으로 처리하여, 최적화하는 알고리즘 

시간복잡도 : O(QlogN) (Q : 쿼리의 수)

[연습 문제 (백준 10999번)](https://www.acmicpc.net/problem/10999)

``` c++
/** https://www.acmicpc.net/problem/10999 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/**
 * MAX : 수의 최대 개수
 * _size : 사용할 세그먼트 트리의 크기 (1 ~ _size/2-1까지 구간값, _size/2 ~ _size-1까지 단일값이 저장됨)
 * arr[MAX*4] : 세그먼트 트리 (최악의 경우 MAX*4 크기가 사용됨)
 * lazy[i] : i번 노드가 담당하는 구간 전체에 아직 반영되지 않은 값 (지연된 업데이트)
 * 
 * lazy[1] : 1~N 사이의 지연값
 * lazy[2(1*2)] : 1~N/2 사이의 지연값
 * lazy[3(1*2+1)] : N/2+1~N 사이의 지연값
 * ...
 * lazy[_size/2] : 1~1 사이의 지연값
 * ...
 * lazy[_size/2+N-1] : N~N 사이의 지연값
 */
typedef long long ll;
const int MAX = 1'000'000;

int _size=1;
ll arr[MAX*4], lazy[MAX*4];

void construct(int N) {
    while(_size<N) _size<<=1;
    _size<<=1;

    for(int i=_size/2;i<_size/2+N;i++) cin >> arr[i];
    for(int i=_size/2-1;i>0;i--) arr[i]=arr[i*2]+arr[i*2+1];
}

/**
 * 인덱스를 사용할 때 arr을 업데이트해줌. (사용하지 않을때는 미리 업데이트 예정 값들을 저장해주며 시간 절약)
 * lazy값이 있는 경우:
 * - arr을 lazy에 있던 값으로 업데이트
 * - lazy값을 다음 범위의 lazy에도 전파
 * - 본인 lazy값은 초기화
 */
void updateLazy(int nodeNum, int nodeL, int nodeR) {
    if(lazy[nodeNum]) {
        arr[nodeNum] += (nodeR-nodeL+1)*lazy[nodeNum];
        if(nodeL!=nodeR) {
            lazy[nodeNum*2] += lazy[nodeNum];
            lazy[nodeNum*2+1] += lazy[nodeNum];
        }
        lazy[nodeNum]=0;
    }
}

/**
 * 구간 업데이트를 lazy 범위에 넣어서 지연시키기
 * 지연되지 않은 값(arr)은 업데이트
 */
void updateRange(int L, int R, int nodeNum, int nodeL, int nodeR, ll val) {
    updateLazy(nodeNum, nodeL, nodeR);
    if(R<nodeL || nodeR<L) return; // 업데이트 하는 범위가 현재 세그먼트 트리의 범위를 완전히 벗어나는 경우
    if(L<=nodeL && nodeR<=R) { // 업데이트 하는 범위가 현재 세그먼트 트리의 범위에 완전히 포함되는 경우
        lazy[nodeNum] += val;
        updateLazy(nodeNum, nodeL, nodeR);
        return;
    }
    int mid = (nodeL+nodeR)/2; // 일부분만 포함되는 경우
    updateRange(L, R, nodeNum*2, nodeL, mid, val);
    updateRange(L, R, nodeNum*2+1, mid+1, nodeR, val);
    arr[nodeNum] = arr[nodeNum*2] + arr[nodeNum*2+1];
}

/**
 * 세그먼트 트리에서 값 꺼내기 (이 문제에선 구간합)
 * 세그먼트 트리에서 추가된 것은 맨 처음에 updatelazy(nodeNum, nodeL, nodeR);을 호출하는 부분
 */
ll search(int L, int R, int nodeNum, int nodeL, int nodeR) {
    updateLazy(nodeNum, nodeL, nodeR);
    if(R<nodeL || nodeR<L) return 0;
    if(L<=nodeL && nodeR<=R) return arr[nodeNum];
    int mid = (nodeL+nodeR)/2;
    return search(L, R, nodeNum*2, nodeL, mid) + search(L, R, nodeNum*2+1, mid+1, nodeR);
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N, M, K; cin >> N >> M >> K;
    construct(N);

    for(int i=0;i<M+K;i++) {
        int a, b, c; cin >> a >> b >> c;
        if(a==1) {
            ll d; cin >> d;
            updateRange(b-1, c-1, 1, 0, _size/2-1, d);
        } else {
            cout << search(b-1, c-1, 1, 0, _size/2-1) << '\n';
        }
    }
}
```
