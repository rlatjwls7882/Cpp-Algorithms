## Segment Tree 🟡 Gold I
완전 이진 트리 형태로 구간 정보를 저장하여 구간 쿼리와 업데이트를 $O(\log N)$에 처리하는 자료구조

시간복잡도: $O(Q\log N)$ ($Q$: 쿼리의 수)

![](https://github.com/user-attachments/assets/427fa5a0-e1b0-4e4b-8b2c-1bf0e61925e1)

4개의 값을 저장하는 세그먼트 트리를 생각해보자. 세그먼트 트리는 완전 이진 트리 구조를 이용하여 배열의 구간 정보를 저장하는 자료구조이다. 그림에서 4~7번 정점은 각각 하나의 값을 저장하는 리프 노드이다. 4번과 5번 정점의 부모인 2번 정점은 구간 [1,2]의 정보를 저장하고, 6번과 7번 정점의 부모인 3번 정점은 구간 [3,4]의 정보를 저장한다. 같은 방식으로 2번과 3번 정점의 부모인 1번 정점은 전체 구간 [1,4]의 정보를 저장한다. 세그먼트 트리를 배열로 구현할 때는 보통 0번 인덱스를 사용하지 않는다. 이는 정점 번호가 n일 때 왼쪽 자식을 2n, 오른쪽 자식을 2n+1로 표현하기 위해서이다.

![](https://github.com/user-attachments/assets/e7542a8d-eb12-430e-92f9-aa2436358ace)

이제 세그먼트 트리를 이용해 구간 최솟값을 구해보자. 초기 배열이 {3, 6, 9, 2}라고 하자. 현재 상태는 리프 노드에 값만 채워진 상태이다.

![](https://github.com/user-attachments/assets/052c46ad-8dbb-4fb0-9041-187455a9b7a9)

초기화 단계에서는 리프 노드에서부터 부모로 올라가며 값을 채운다. 각 정점에는 두 자식 노드의 값 중 최솟값을 저장한다.

$$
arr[i] = \min(arr[2i], arr[2i+1])
$$

![](https://github.com/user-attachments/assets/b549b9ed-cf28-4e4d-9bdb-c54d8cc24700)

예를 들어 구간 [1,2]의 최솟값을 구한다고 하자. 모든 원소를 직접 확인하면 두 값을 모두 확인해야 한다. 하지만 세그먼트 트리를 사용하면 해당 구간을 담당하는 부모 정점 하나만 확인하면 된다.

![](https://github.com/user-attachments/assets/9988a4d7-be1b-4cb5-bfa4-6420bf785f69)

구간 [1,3]의 경우에는 두 개의 정점을 이용해 구간을 표현할 수 있다.

![](https://github.com/user-attachments/assets/15b78367-ef32-4186-9443-bfdbc1ed987f)

구간 [1,4]의 경우에는 루트 노드 하나만으로 바로 최솟값을 구할 수 있다.

![](https://github.com/user-attachments/assets/07801bf9-85bf-467e-9123-e0279ca78fa5)

실제 구현에서는 재귀를 이용해 트리를 탐색한다. nodeNum은 현재 정점 번호이고 L과 R은 현재 정점이 담당하는 구간이며 nodeL과 nodeR은 우리가 찾고 싶은 구간이다. (0-index 기준) 루트 노드에서 시작해 현재 구간이 질의 구간과 완전히 겹치지 않으면 구간을 나누어 자식 노드로 내려가 탐색한다.

![](https://github.com/user-attachments/assets/804c36d3-ea31-4521-b53e-a3d459bc153a)

2번 정점에 도착하면 현재 정점이 담당하는 구간이 질의 구간에 완전히 포함되므로 해당 정점의 값을 그대로 반환한다.

![](https://github.com/user-attachments/assets/f08a4ded-bc18-47c6-9548-4adde5db47eb)

다음으로 1번 정점의 오른쪽 자식인 3번 정점으로 이동한다. 현재 구간이 질의 구간과 일부만 겹치므로 다시 구간을 나누어 탐색한다.

![](https://github.com/user-attachments/assets/6e77bffc-fc96-49e6-bc34-eb4b4cff5d97)

3번 정점의 왼쪽 자식인 6번 정점은 질의 구간에 완전히 포함되므로 이 정점의 값을 반환한다.

![](https://github.com/user-attachments/assets/4e8ac334-3f48-4c36-82bf-867ed1392a23)

3번 정점의 오른쪽 자식인 7번 정점은 질의 범위 밖이므로 결과에 영향을 주지 않는 매우 큰 값을 반환한다.

![](https://github.com/user-attachments/assets/d1ac6160-eef2-4119-b7e6-a58b4aa9b85f)

3번 정점에서는 왼쪽에서 반환된 값과 오른쪽에서 반환된 값 중 최솟값을 선택한다.

$$
\min(9, MAX) = 9
$$

![](https://github.com/user-attachments/assets/d65437fd-bbfa-4fd6-b993-c97e0f48a20a)

마지막으로 루트 노드에서는 왼쪽 결과와 오른쪽 결과 중 최솟값을 반환한다.

$$
\min(3, 9) = 3
$$

![](https://github.com/user-attachments/assets/ea4ef09e-aaed-4f6c-bdb2-dec367cae2d6)

이제 값 업데이트 연산을 살펴보자. 예를 들어 세 번째 원소(6번 정점)를 1로 변경한다고 하자. 값을 변경한 뒤 루트 노드까지 올라가면서 부모 노드의 값을 다시 계산한다.

$$
arr[i] = \min(arr[2i], arr[2i+1])
$$

이 과정을 통해 변경된 값이 포함된 모든 구간의 정보가 갱신된다.

[연습 문제 (백준 2042번)](https://www.acmicpc.net/problem/2042)

``` c++
/** 재귀 버전 http://boj.kr/4dbb42cb6d1d492c912cecadf4ab776b 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/**
 * MAX : 수의 최대 개수
 * SZ : 사용할 세그먼트 트리의 크기 (1 ~ SZ-1까지 구간값, SZ ~ SZ*2-1까지 단일값이 저장됨)
 * arr[MAX*4] : 세그먼트 트리 (최악의 경우 MAX*4 크기가 사용됨)
 * 
 * arr[1] : 1~N 사이의 구간값
 * arr[2(1*2)] : 1~N/2 사이의 구간값
 * arr[3(1*2+1)] : N/2+1~N 사이의 구간값
 * ...
 * arr[SZ] : 1~1 사이의 구간값
 * ...
 * arr[SZ+N-1] : N~N 사이의 구간값
 */
typedef long long ll;
const int MAX = 1'000'000;

int SZ=1;
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
 * arr[SZ+인덱스]에 값 업데이트
 * nodeNum을 2로 나누면서 변경된 부분만 새로운 구간값으로 갱신
 */
void update(int nodeNum, ll val) {
    nodeNum+=SZ;
    arr[nodeNum]=val;
    while(nodeNum>1) {
        nodeNum>>=1;
        arr[nodeNum]=arr[nodeNum*2]+arr[nodeNum*2+1];
    }
}

/** 
 * 세그먼트 트리 초기 설정
 * 세그먼트 트리의 크기를 N*2<=SZ인 최소 2의 거듭제곱수로 설정 (세그먼트 트리가 완전 이진 트리이기 때문)
 * SZ부터 SZ+N-1까지 값 넣고
 * SZ-1부터 1까지 초기 구간값 설정
 */
void init(int N) {
    while(SZ<N) SZ<<=1;
    for(int i=SZ;i<SZ+N;i++) cin >> arr[i];
    for(int i=SZ-1;i>0;i--) arr[i]=arr[i*2]+arr[i*2+1];
}

int main(void) {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, K; cin >> N >> M >> K;
    init(N);

    for(int i=0;i<M+K;i++) {
        ll a, b, c; cin >> a >> b >> c;
        if(a==1) update(b-1, c);
        else cout << sum(b-1, c-1, 1, 0, SZ-1) << '\n';
    }
}

/** 비재귀 버전 http://boj.kr/67c494b624864f5bbf943c6557578ff0 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX = 1'000'001;

ll SZ=1, arr[MAX*4];

void update(int i, ll val) {
    i+=SZ;
    arr[i]=val;
    while(i>1) {
        i>>=1;
        arr[i] = arr[i*2]+arr[i*2+1];
    }
}

ll query(int L, int R) {
    ll ret=0;
    for(L+=SZ, R+=SZ;L<=R;L>>=1, R>>=1) {
        if(L&1) ret += arr[L++];
        if(!(R&1)) ret += arr[R--];
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k; cin >> n >> m >> k;
    while(SZ<n) SZ<<=1;
    for(int i=SZ+1;i<=SZ+n;i++) cin >> arr[i];
    for(int i=SZ-1;i>0;i--) arr[i] = arr[i*2]+arr[i*2+1];

    for(int i=0;i<m+k;i++) {
        ll a, b, c; cin >> a >> b >> c;
        if(a==1) update(b, c);
        else cout << query(b, c) << '\n';
    }
}
```
