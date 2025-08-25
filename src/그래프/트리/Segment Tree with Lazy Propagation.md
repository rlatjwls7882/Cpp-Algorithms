## Segment Tree with Lazy Propagation
세그먼트 트리에서 구간 업데이트를 지연 방식으로 처리하여, 최적화하는 알고리즘 

시간복잡도 : O(QlogN) (Q : 쿼리의 수)

![](https://github.com/user-attachments/assets/c639c195-a149-47c7-ada4-de2a39bde53b)

4개의 정보를 구성하는 세그먼트 트리이다.  
여기서 추가로 lazy 배열을 사용하여 범위 업데이트를 기억만 하고 있다 필요할 때만 하도록 구현한다.  
4개의 데이터는 이전 세그먼트 트리와 같고, 이번에는 범위의 합을 계산한다고 하자.  

![](https://github.com/user-attachments/assets/d0733581-6ae1-4332-84ec-2f8d9c7b5c76)

먼저 1 ~ 4 범위를 +1씩 해준다고 하자. 가존 방식으로는 그 범위를 나타내는 1번 정점과 그 하위 모든 값의 업데이트가 필요하다.  
여기서 하지만 1번 정점까지 원래 세그먼트 트리에 업데이트 해주고, 1번 정점의 자식들만 lazy 배열에서 업데이트 해주면 더 빠른 시간 내에 해결 가능하다.  
그 결과 1번 정점의 arr는 1 (값) * 4 (해당 범위의 정점 개수) 를 해주어 24가 되고, 자식인 2, 3번 정점의 lazy에 1을 더해준다(전파).

![](https://github.com/user-attachments/assets/3a6e44e5-4d61-4141-8933-d73adce2fd04)

이번엔 1 ~ 3 범위를 +2씩 해준다고 하자.  
1번 정점에 도착한다.  
1번 정점의 lazy는 비어있어서 추가 연산이 없다.  
현재 범위가 업데이트 하려는 범위보다 크다. 왼쪽 자식으로 간다.

![](https://github.com/user-attachments/assets/09194dea-580f-45d2-9e59-a35bcd1ceb23)

2번 정점에 도착한다.  
2번 정점의 lazy가 있어서 업데이트를 한다. 2번 정점의 arr에 1 * 2(lazy값 * 범위)를 더해준다. 2번 정점의 lazy는 그 자식들인 4, 5번 정점의 lazy로 전파된다.  

![](https://github.com/user-attachments/assets/a70fe965-8524-40f5-8a3c-583af148e789)

현재 범위가 업데이트 하려는 범위에 속한다.  
2번 정점의 arr에 2 * 2(업데이트 값 * 범위)를 더해주고 lazy를 자식들에 전파한다.

![](https://github.com/user-attachments/assets/830d6130-35d3-4095-8cbf-0362a034ab83)

이번엔 1번 정점의 오른쪽 자식인 3번 정점으로 간다.  
3번 정점의 lazy가 있어서 업데이트를 한다. 3번 정점의 arr에 1 * 2를 더해준다. 3번 정점의 lazy는 그 자식들인 6, 7번 정점의 lazy로 전파된다.  
현재 범위가 업데이트 하려는 범위보다 크다. 왼쪽 자식으로 간다.

![](https://github.com/user-attachments/assets/a3786122-88a2-4ea2-8239-77aed9ecb5f3)

6번 정점에 도착한다.  
6번 정점의 lazy가 있어서 업데이트를 한다. 6번 정점의 arr에 1 * 1를 더해준다. 6번 정점의 lazy는 자식이 없어서 전파되지 않는다.  
현재 범위가 업데이트 하려는 범위에 속한다.  
6번 정점의 arr에 2 * 1을 더해주고 자식이 없어 lazy를 전파하지 않는다.

![](https://github.com/user-attachments/assets/0fbaac57-7b92-4d7f-994b-7051bb218b72)

이번엔 3번 정점의 오른쪽 자식인 7번 정점에 도착한다.  
7번 정점의 lazy가 있어서 업데이트를 한다. 7번 정점의 arr에 1 * 1 더해준다. 7번 정점의 lazy는 자식이 없어서 전파되지 않는다.  
현재 범위가 업데이트 하려는 범위를 벗어난다.

![](https://github.com/user-attachments/assets/c01d6d98-6df8-458f-8442-d68118bff296)

3번 정점으로 돌아간다.  
3번 정점의 arr를 자식들의 합으로 업데이트한다. (arr[3] = arr[6]+arr[7])

![](https://github.com/user-attachments/assets/bb65d8d4-795a-49fe-91fc-3b28448a1ea2)

1번 정점으로 돌아간다.  
1번 정점의 arr를 자식들의 합으로 업데이트한다. (arr[1] = arr[2]+arr[3])  

범위 값을 찾는 연산은 한 정점에 도착하면 지금까지 했던 arr을 lazy로 업데이트 하고, 자식들에 lazy를 전파해야 하는 것 빼고는 일반 세그먼트 트리와 동일해 설명을 생략한다.

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
