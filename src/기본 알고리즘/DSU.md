## DSU (Disjoint Set Union, 분리 집합)
서로 겹치지 않는 집합을 관리하고 합치거나 찾는 연산을 효율적으로 처리하는 자료구조

시간복잡도 : O(α(N)) (α : 역아커만 함수 ≒ 상수 시간, N : 데이터 개수)

DSU에는 union 연산과, find 연산이 존재한다.

find 연산은 해당 그룹의 대표 원소를 반환하는 연산이고 (경로 압축까지 포함), union 연산은 두 그룹의 대표 원소를 연결하여 합치는 연산이다. (대표 원소 찾을때 각각 find 연산 사용)

![](https://github.com/user-attachments/assets/ef5d71ec-8a42-4c79-ac39-b09bdf15d4f9)

다음과 같이 7개의 점이 있다고 생각하자.

![](https://github.com/user-attachments/assets/b4cc5855-b735-46b1-b5bf-6e2565b5de23)

2와 4를 union하고 3과 5를 union하면 다음과 같다. (해당 집합의 가장 작은 원소가 대표 원소)

![](https://github.com/user-attachments/assets/39a27eba-708e-454a-80c5-bf9ddb7cb48a)

이후 1과 4를 union하면 다음과 같다.

![](https://github.com/user-attachments/assets/2f3b7b8c-5916-4ef3-a3f3-993c1f20cc14)

여기서 4와 5를 union하면 이렇게 되야 할까?

O(N²) DSU에서는 그렇지만 O(α(N)) DSU에서는 경로 압축 해주어 자신보다 위에 있는 원소들이 전부 대표 원소를 가리키게 해야 한다.

![](https://github.com/user-attachments/assets/610f8f03-4877-4996-9ef1-9bb41573ffb3)

따라서 이 사진과 같게 되어야 한다.

[연습 문제 (백준 1717번)](https://www.acmicpc.net/problem/1717)

``` c++
/** http://boj.kr/61d6f3b974084fc3ab1aca437121bcb9 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 1'000'000;

int parent[MAX]; // parent[i] : 같은 집합에 속한 부모 원소 (최상위 원소이면 자기 자신)

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
