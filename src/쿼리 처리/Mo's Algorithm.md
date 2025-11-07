## Mo's Algorithm 🟢 Platinum II
제곱근 분할을 구간 쿼리에 적용시켜 전체 쿼리를 O(Q√N) 시간에 해결하는 알고리즘

시간복잡도 : O(Q√N)

[연습 문제 (백준 13547번)](https://www.acmicpc.net/problem/13547)

![](https://github.com/user-attachments/assets/1a1d83d7-76f9-4444-b54c-014db484b7c5)

이런 값들을 가진 수열이 있다.  
그리고 쿼리가 어떤 범위에서 존재하는 서로 다른 수의 개수를 구하는 것이고 이렇게 0 ~ 4, 2 ~ 3, 3 ~ 5 쿼리 3개가 들어온다고 하자.  
쿼리를 잘 살펴보면 각 쿼리끼리 겹치는 것들이 있어 모두 버리고 처음부터 구하는 것보단, 최대한 잘 겹치게 재배열한 후 겹치는 곳들을 재사용하는 것이 좋아보인다.  
Mo's Algorithm은 이렇게 값의 수정 없이 구간 쿼리가 반복해서 주어질 때, 쿼리의 겹치는 구간만큼 덜 계산해서 계산 속도를 늘리자는 아이디어이다.

![](https://github.com/user-attachments/assets/2c942b94-1516-4267-857e-dbbe4ecac385)

이번에 분할할 크기(int(√N))는 2이고, 쿼리에 분할을 적용시킬 것이다.  
이를 위해 쿼리의 시작 부분의 버킷 위치, 쿼리의 끝 부분 위치로 오름차순으로 정렬한다.  
이렇게 정렬하면 버킷이 같은 쿼리끼리는 시작 지점이 최대 √N-1개 차이나 더 잘 겹치게 된다.

![](https://github.com/user-attachments/assets/82069372-1e45-4141-a377-c21149e35027)

첫 번째 쿼리의 범위까지 늘려보면(5번 이동), 1 2번 등장, 2 2번 등장, 3 3번 등장으로 총 3개의 숫자가 존재한다.

![](https://github.com/user-attachments/assets/126d0d41-3ca8-45b6-b835-d0c7661685ed)

두 번째 쿼리는 첫 번째 쿼리에서 왼쪽과 오른쪽을 좁혀 찾을 수 있다. (이전 쿼리에서 3번 이동) 1 1번 등장, 2 1번 등장으로 총 2개의 숫자가 존재한다.

![](https://github.com/user-attachments/assets/53eb42ae-d2cd-427e-a2b5-816b9f475e97)

세 번째 쿼리는 두 번째 쿼리에서 왼쪽과 오른쪽을 오른쪽으로 늘려 찾을 수 있다. (이전 쿼리에서 3번 이동) 2 2번 등장, 3 1번 등장으로 총 2개의 숫자가 존재한다.

``` c++
/** http://boj.kr/dbdab89923f3446d966697a737b956a4 제출 코드 */
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
