## Segment Tree
완전 이진 트리 구조를 이용하여 구간 쿼리를 최적화하는 알고리즘

시간복잡도 : O(QlogN) (Q : 쿼리의 수)

![](https://github.com/user-attachments/assets/427fa5a0-e1b0-4e4b-8b2c-1bf0e61925e1)

4개의 정보를 저장하는 세그먼트 트리를 그리면 다음과 같습니다.  
4 ~ 7번 정점이 각각의 고유한 정보를 저장하는 정점입니다. 4, 5번 정점의 부모인 2번 정점이 4 ~ 5 범위에 대한 정보를 저장하는 정점이고, 6, 7번 정점의 부모인 3번 정점이 6 ~ 7 범위에 대한 정보를 저장하는 정점입니다. 똑같은 방식으로 2, 3의 부모 정점인 1번 정점이 4 ~ 7 범위의 정보를 저장하는 정점입니다.  
세그먼트 트리를 배열로 구현할 때, 0번 정점 (배열의 0번 원소)를 쓰지 않는 이유는 모든 정점에 대해 왼쪽 자식을 n * 2(n : 정점번호)로, 오른쪽 자식을 n * 2+1로 나타내기 위함입니다.

![](https://github.com/user-attachments/assets/e7542a8d-eb12-430e-92f9-aa2436358ace)

세그먼트 트리로 구간 최솟값을 구해보겠습니다.  
4개의 초기값이 {3, 6, 9, 2} 라고 하겠습니다.  
처음에 4개의 값을 넣기만 한 상태입니다.

![](https://github.com/user-attachments/assets/052c46ad-8dbb-4fb0-9041-187455a9b7a9)

이 상태는 초기 세팅을 한 상태입니다. 3번 정점부터 1번 정점까지 자식 정점들 중 최솟값을 저장하면 됩니다. (arr[i] = min(arr[i * 2], arr[i * 2+1]))

![](https://github.com/user-attachments/assets/b549b9ed-cf28-4e4d-9bdb-c54d8cc24700)

만약 1 ~ 2 범위의 최솟값을 찾는다고 하면 빨간색 부분처럼 2개를 전부 확인해 찾을 수도 있습니다.  
하지만 파란색 부분처럼 1 ~ 2 범위의 최솟값을 저장하는 부모를 이용한다면 1개의 정점만으로 더 빨리 확인할 수 있습니다.

![](https://github.com/user-attachments/assets/9988a4d7-be1b-4cb5-bfa4-6420bf785f69)

1 ~ 3 범위에 대해서는 이렇게 2개의 정점으로, 

![](https://github.com/user-attachments/assets/15b78367-ef32-4186-9443-bfdbc1ed987f)

1 ~ 4 범위에선 이렇게 1개의 정점으로 빠르게 찾을 수 있습니다.  

![](https://github.com/user-attachments/assets/07801bf9-85bf-467e-9123-e0279ca78fa5)

실제 구현에 대해서는 재귀로 부모에서 자식으로 내려가는 방식으로 구현합니다.  
nodeNum은 현재 정점 번호이고, L R은 현재 정점이 나타내는 구간의 범위, nodeL nodeR은 찾아야 하는 범위입니다. (0-Index로 구현했습니다.)  
1번 정점부터 시작합니다. 현재 정점의 범위가 찾아야 하는 범위보다 일부 벗어나기에 범위를 반으로 잘라서 탐색해야 합니다.  
왼쪽 자식부터 확인해보겠습니다.

![](https://github.com/user-attachments/assets/804c36d3-ea31-4521-b53e-a3d459bc153a)

2번 정점에 도착했습니다.  
현재 정점이 나타내는 범위가 찾아야 하는 범위에 완전히 속하기 때문에 이 정점의 값을 리턴합니다.

![](https://github.com/user-attachments/assets/f08a4ded-bc18-47c6-9548-4adde5db47eb)

이번엔 1번 정점의 오른쪽 자식인 3번 정점에 도착했습니다.  
현재 정점이 나타내는 범위가 찾아야 하는 범위를 초과하기 때문에 이 정점의 범위도 잘라서 확인해봅니다.

![](https://github.com/user-attachments/assets/6e77bffc-fc96-49e6-bc34-eb4b4cff5d97)

3번 정점의 왼쪽 자식인 6번 정점에 도착했습니다.  
현재 정점이 나타내는 범위가 찾아야 하는 범위에 완전히 속하기 때문에 이 정점의 값을 리턴합니다.

![](https://github.com/user-attachments/assets/4e8ac334-3f48-4c36-82bf-867ed1392a23)

3번 정점의 오른쪽 자식인 7번 정점에 도착했습니다.  
현재 정점이 나타내는 범위가 찾아야 하는 범위를 초과하고 범위가 더 자를 수 없기 때문에 정답에 영향을 미치지 않는 굉장히 큰 수를 리턴합니다.

![](https://github.com/user-attachments/assets/d1ac6160-eef2-4119-b7e6-a58b4aa9b85f)

2번 정점의 범위를 더 자를 수 없기 때문에 왼쪽에서 온 9와, 오른쪽에서 온 MAX 중 최솟값인 9를 리턴합니다.

![](https://github.com/user-attachments/assets/d65437fd-bbfa-4fd6-b993-c97e0f48a20a)

1번 정점에선 왼쪽에서 온 3과 오른쪽에서 온 9 중 최솟값을 정답으로 리턴합니다.

![](https://github.com/user-attachments/assets/ea4ef09e-aaed-4f6c-bdb2-dec367cae2d6)

한 개의 원소을 바꾸는 연산을 해보겠습니다. 3번 원소(6번 정점)을 1로 바꾸겠습니다.  
바꾼 다움 루트에 도달할 때까지, 자신의 부모로 이동해(i/=2) 부모 값을 자식 중 작은 값으로 업데이트합니다(arr[i] = min(arr[i * 2], arr[i * 2+1])).

[연습 문제 (백준 2042번)](https://www.acmicpc.net/problem/2042)

``` c++
/** https://www.acmicpc.net/problem/2042 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/**
 * MAX : 수의 최대 개수
 * _size : 사용할 세그먼트 트리의 크기 (1 ~ _size/2-1까지 구간값, _size/2 ~ _size-1까지 단일값이 저장됨)
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
 * 세그먼트 트리의 사용 크기(_size)를 N*2<=_size인 최소 2의 거듭제곱수로 설정 (세그먼트 트리가 완전 이진 트리이기 때문)
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
