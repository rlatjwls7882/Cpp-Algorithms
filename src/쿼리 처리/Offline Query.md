## Offline Query
복잡한 연산을 단순화하기 위해, 쿼리의 처리 순서를 바꿔 답을 찾는 테크닉

[연습 문제 (백준 13306번)](https://www.acmicpc.net/problem/13306)

해당 문제에서는 간선을 끊는 연산 N-1번, 두 정점 사이에 경로가 있는지 찾는 연산 Q번을 해야 한다.

이미 있는 길을 끊고, 연결성을 확인하는 것은 시간 안에 해결할 수 없어 보인다.

하지만 반대로 생각해보면, 입력된 쿼리를 마지막부터 거꾸로 없는 길을 만들면서 연결성을 확인하는 것은 DSU를 써서 쉽게 판별할 수 있다.

이렇게 오프라인 쿼리의 핵심은 하기 힘든 연산을 하기 쉬운 연산으로 가공하여 해결하는 것이다.

이 문제에서의 시간복잡도 : O(Q*α(N))

``` c++
/** https://www.acmicpc.net/problem/13306 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 200'001;

int parent[MAX], p[MAX];

struct q {
    int a, b, c;
};

int find(int x) {
    if(x==parent[x]) return x;
    return parent[x] = find(parent[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);

    if(x<y) parent[y] = x;
    else parent[x] = y;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N, Q; cin >> N >> Q;
    for(int i=2;i<=N;i++) cin >> p[i];
    for(int i=1;i<=N;i++) parent[i]=i;

    /** 미리 쿼리를 전부 받아놓음 */
    vector<q> query(Q+N-1);
    for(int i=0;i<Q+N-1;i++) {
        cin >> query[i].a >> query[i].b;
        if(query[i].a==1) cin >> query[i].c;
    }

    /** 마지막 쿼리부터 거꾸로 연결 확인함 (같은 집합에 속하면 서로 연결됨) */
    stack<string> stk;
    for (int i=Q+N-2;i>=0;i--) {
        if(query[i].a==0) {
            merge(query[i].b, p[query[i].b]);
        } else {
            if(find(query[i].b)==find(query[i].c)) stk.push("YES\n");
            else stk.push("NO\n");
        }
    }
    while(!stk.empty()) {
        cout << stk.top(); stk.pop();
    }
}
```
