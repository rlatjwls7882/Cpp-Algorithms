## DSU (Disjoint Set Union, 분리 집합) 🟡 Gold V
서로 겹치지 않는(서로소) 집합을 관리하여 합치기와 대표 원소 찾기 연산을 효율적으로 처리하는 자료구조

시간복잡도: $O(\alpha(N))$ ($\alpha(x)$: 역아커만 함수 $\approx$ 상수 시간, $N$: 데이터 개수)

DSU는 서로소 집합을 관리하기 위한 자료구조로, **Find** 연산과 **Union** 연산을 제공한다.

**Find** 연산은 특정 원소가 속한 집합의 대표 원소를 찾는 연산이며, 이 과정에서 경로 압축을 적용할 수 있다.

**Union** 연산은 두 원소가 속한 집합의 대표 원소를 찾아 두 집합을 하나로 합치는 연산이다.

![](https://github.com/user-attachments/assets/ef5d71ec-8a42-4c79-ac39-b09bdf15d4f9)

다음과 같이 7개의 원소가 각각 독립된 집합으로 존재한다고 하자.

![](https://github.com/user-attachments/assets/b4cc5855-b735-46b1-b5bf-6e2565b5de23)

먼저 $2$와 $4$를 Union하고, $3$과 $5$를 Union하면 다음과 같은 구조가 된다. (여기서는 각 집합에서 가장 작은 원소를 대표 원소로 사용한다고 가정한다.)

![](https://github.com/user-attachments/assets/39a27eba-708e-454a-80c5-bf9ddb7cb48a)

이후 $1$과 $4$를 Union하면 다음과 같이 집합이 합쳐진다.

![](https://github.com/user-attachments/assets/2f3b7b8c-5916-4ef3-a3f3-993c1f20cc14)

이 상태에서 $4$와 $5$를 Union하면 단순한 트리 구조에서는 다음과 같이 연결될 수 있다. 하지만 이러한 방식은 트리의 높이가 커질 수 있으며, Find 연산의 시간 복잡도가 최악의 경우 $O(N)$까지 증가할 수 있다.

이를 방지하기 위해 **경로 압축**을 사용해야 한다. 경로 압축은 Find 연산을 수행하는 과정에서 탐색 경로에 있는 모든 노드가 직접 대표 원소를 가리키도록 만드는 방법이다.

![](https://github.com/user-attachments/assets/610f8f03-4877-4996-9ef1-9bb41573ffb3)

이렇게 하면 트리의 높이가 크게 줄어들어 Union과 Find 연산을 거의 상수 시간인 $O(\alpha(N))$에 수행할 수 있다.

[연습 문제 (백준 1717번)](https://www.acmicpc.net/problem/1717)

``` c++
/** http://boj.kr/61d6f3b974084fc3ab1aca437121bcb9 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

int parent[1'000'000]; // parent[i] : 원소 i가 속한 집합의 대표 원소

/** 
 * x와 같은 집합에 속한 가장 작은 원소를 parent로 설정(경로 압축)하고 추출
 */
int _find(int x) {
    if(parent[x]==x) return x;
    return parent[x] = _find(parent[x]);
}

/** 
 * x가 속한 집합과 y가 속한 집합을 합치는 연산
 * - x가 속한 집합의 가장 작은 원소 추출
 * - y가 속한 집합의 가장 작은 원소 추출
 * - x와 y중 작은 원소를 부모로 설정
 */
void _union(int x, int y) {
    x = _find(x);
    y = _find(y);
    if(x<y) parent[y]=x;
    else parent[x]=y;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for(int i=0;i<=n;i++) parent[i]=i; // i의 부모를 i로 설정 -> 각각이 고유의 집합이 됨

    while(m--) {
        int op, a, b; cin >> op >> a >> b;
        if(op==0) _union(a, b); // a가 속한 집합과 b가 속한 집합 합치기
        else cout << (_find(a) == _find(b) ? "YES\n" : "NO\n"); // a가 속한 집합의 가장 작은 원소와 b가 속한 집합의 가장 작은 원소가 같은지 확인
    }
}
```
