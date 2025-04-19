/** https://www.acmicpc.net/problem/10999 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/**
 * MAX : 배열 크기
 * _size : 사용할 배열의 크기 (_size/2 ~ _size-1까지 값이 저장됨)
 * arr : 구간 정보를 담아둘 배열
 * lazy : 느린 연산을 위해 담아둘 배열 (모아놨다가 구간합을 구할 때 더해줌)
 */
typedef long long ll;
const int MAX = 3'000'000;
int _size=1;
ll arr[MAX], lazy[MAX];

void construct(int N) {
    while(_size<N) _size<<=1;
    _size<<=1;

    for(int i=_size/2;i<_size/2+N;i++) cin >> arr[i];
    for(int i=_size/2-1;i>0;i--) arr[i]=arr[i*2]+arr[i*2+1];
}

/**
 * 현재 인덱스를 사용할 경우 arr을 lazy에 있던 값으로 업데이트함
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
 * 구간 업데이트
 */
void updateRange(int L, int R, int nodeNum, int nodeL, int nodeR, ll val) {
    updateLazy(nodeNum, nodeL, nodeR);
    if(R<nodeL || nodeR<L) return;
    if(L<=nodeL && nodeR<=R) {
        lazy[nodeNum] += val;
        updateLazy(nodeNum, nodeL, nodeR);
        return;
    }
    int mid = (nodeL+nodeR)/2;
    updateRange(L, R, nodeNum*2, nodeL, mid, val);
    updateRange(L, R, nodeNum*2+1, mid+1, nodeR, val);
    arr[nodeNum] = arr[nodeNum*2] + arr[nodeNum*2+1];
}

/**
 * 세그먼트 트리에서 값 꺼내기 (이 문제에선 구간합)
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
