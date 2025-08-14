## DSU (Disjoint Set Union, 분리 집합)
서로 겹치지 않는 집합을 관리하고 합치거나 찾는 연산을 효율적으로 처리하는 자료구조

시간복잡도 : O(α(N)) (α : 역아커만 함수 ≒ 상수 시간, N : 데이터 개수)

![dsu image](https://cp-algorithms.com/data_structures/DSU_path_compression.png)

[연습 문제 (백준 1717번)](https://www.acmicpc.net/problem/1717)

``` c++
/** https://www.acmicpc.net/problem/1717 제출 코드 */
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
