## Mo's Algorithm
Sqrt Decomposition을 구간 쿼리에 적용시켜 전체 쿼리를 O(Q√N) 시간에 해결하는 알고리즘

시간복잡도 : O(Q√N)

값의 수정 없이 구간 쿼리가 반복해서 주어질 때, 쿼리의 겹치는 구간만큼 덜 계산해서 계산 속도를 늘리자는 아이디어입니다.

[연습 문제 (백준 13547번)](https://www.acmicpc.net/problem/13547)

``` c++
/** https://www.acmicpc.net/problem/13547 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX_VAL = 1'000'001;
const int MAX = 100'001;

int sqrtN, A[MAX], chk[MAX_VAL];

struct query {
    int s, e, i;
    bool operator<(const query q2) const {
        if(s/sqrtN != q2.s/sqrtN) return s/sqrtN < q2.s/sqrtN;
        return e < q2.e;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for(int i=1;i<=n;i++) cin >> A[i];
    sqrtN = sqrt(n);
    
    /** 
     * {s/√N, e} 를 기준으로 쿼리 정렬
     */
    int m; cin >> m;
    vector<query> queries(m);
    for(int i=0;i<m;i++) {
        cin >> queries[i].s >> queries[i].e;
        queries[i].i=i;
    }
    sort(queries.begin(), queries.end());

    /** 
     * 마지막으로 계산한 쿼리의 결과에서 조금만 움직여 다음 쿼리 결과 계산
     * 
     * s/√N이 같은 경우:
     * - s는 한번의 연산에서 최대 √N번씩 이동해야함 O(N√N)
     * - e는 s/√N이 같은 값에서 최대 N번씩 이동해야함. O(N√N)
     * 
     * s/√N이 다른 경우 (최대 √N개 등장):
     * - s는 한번의 연산에서 최대 N번씩 이동해야함. O(N√N)
     * - e는 한번의 연산에서 최대 N번씩 이동해야함. O(N√N)
     * 
     * 총 시간복잡도 : O(N√N)
     */
    vector<int> res(m);
    int cnt=0, left=0, right=0;
    for(int i=0;i<m;i++) {
        while(queries[i].s<left) if(++chk[A[--left]]==1) cnt++;
        while(right<queries[i].e) if(++chk[A[++right]]==1) cnt++;
        while(left<queries[i].s) if(--chk[A[left++]]==0) cnt--;
        while(queries[i].e<right) if(--chk[A[right--]]==0) cnt--;
        res[queries[i].i]=cnt;
    }
    for(int e:res) cout << e << '\n';
}
```
