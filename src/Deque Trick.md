## Deque Trick
덱에 단조 증가 또는 단조 감소하는 인덱스를 유지하여 슬라이딩 윈도우 내에서 최소값 또는 최대값을 O(1)에 찾는 알고리즘

시간복잡도 : O(N)

덱 트릭은 범위의 크기가 일정하게 정해져있고, 최댓값 혹은 최솟값 중 한가지만 정해서 찾을 때 덱에서 최대 한번씩 삽입 / 삭제 연산을 하기에 O(N)에 찾을 수 있다.

[연습 문제 (백준 21982번)](https://www.acmicpc.net/problem/21982)

``` c++
/** https://www.acmicpc.net/problem/21982 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll h[5'000'000], w[5'000'000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, x; cin >> n >> x;
        ll hs, ha, hb, hc, ws, wa, wb, wc; cin >> hs >> ha >> hb >> hc >> ws >> wa  >> wb >> wc;
        h[0] = hs%hc + 1;
        w[0] = ws%wc + 1;
        for(int i=1;i<n;i++) {
            h[i] = h[i-1] + 1 + (h[i-1] * ha + hb) % hc;
            w[i] = (w[i-1] * wa + wb) % wc + 1;
        }

        /** 
         * 이 문제의 목표 : 인덱스 i부터 인덱스 i+x 사이의 두 상자 부피의 합의 최댓값 구하기
         * 
         * <부피, h> 형태로 부피가 단조 감소하도록 덱에 넣기
         * - 현재 덱에 넣을(i번째) 상자와 덱의 맨 앞에 위치하는 (가장 부피가 큰) 상자가 x보다 크게 차이가 나지 않도록 pop
         * - 덱이 비어있지 않다면 현재 덱의 맨 앞에 있는 상자와 i번째 상자의 부피 합 계산
         * 
         * - 덱의 뒤에서부터 i번째 상자의 부피보다 작은 상자를 전부 pop
         * - 즉, 현재 덱에 들어있는 상자들은 i번째의 상자보다 더 먼저 들어왔기에 더 멀리 떨어져 있음 (부피가 i번째 상자보다 크지 않다면 절대 선택할 리가 없음)
         * 
         * - 덱에 i번째 상자 넣기
         * 
         * 따라서 맨 앞에 위치하는 원소는 부피가 가장 큼 : 덱의 맨 앞 원소의 부피 + i번째 부피가 지금 가능한 최선의 선택임.
         */
        long long maxV=-1;
        deque<pair<ll, ll>> dq;
        for(int i=0;i<n;i++) {
            while(!dq.empty() && h[i]-dq.front().second > x) dq.pop_front();
            ll curV = w[i]*h[i];
            if(!dq.empty()) maxV = max(maxV, dq.front().first+curV);

            while(!dq.empty() && dq.back().first < curV) dq.pop_back();
            dq.push_back({curV, h[i]});
        }
        cout << maxV << '\n';
    }
}
```
