/** https://www.acmicpc.net/problem/2042 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/**
 * MAX : 배열 크기
 * _size : 사용할 배열의 크기 (_size/2 ~ _size-1까지 값이 저장됨)
 * arr : 구간 정보를 담아둘 배열
 */
typedef long long ll;
const int MAX = 3'000'000;
int _size=1;
ll arr[MAX];

/**
 * 세그먼트 트리에서 값 꺼내기 (이 문제에선 구간합)
 */
ll sum(int L, int R, int nodeNum, int nodeL, int nodeR) {
    if(R<nodeL || nodeR<L) return 0;
    if(L<=nodeL && nodeR<=R) return arr[nodeNum];
    int mid = (nodeL+nodeR)/2;
    return sum(L, R, nodeNum*2, nodeL, mid) + sum(L, R, nodeNum*2+1, mid+1, nodeR);
}

/**
 * 세그먼트 트리에 값 넣기
 */
void update(int nodeNum, ll val) {
    nodeNum += _size/2;
    arr[nodeNum]=val;
    while(nodeNum>1) {
        nodeNum/=2;
        arr[nodeNum]=arr[nodeNum*2]+arr[nodeNum*2+1];
    }
}

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
