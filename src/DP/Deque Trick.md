## Deque Trick
덱에 단조 증가 또는 단조 감소하는 인덱스를 유지하여 슬라이딩 윈도우 내에서 최소값 또는 최대값을 O(1)에 찾는 알고리즘

시간복잡도 : O(N)

![](https://github.com/user-attachments/assets/3f3d9f96-8019-461c-aaf8-79933d4ab0fc)

i번째 상자의 높이를 나타내는 H 배열과, 너비를 나타내는 W 배열이 있다고 하자.  
이 때, 높이 차(X)가 최대 7인 두 상자의 최대 부피를 찾는다고 하자. (높이는 오름차순으로 정렬되어 있는 상태이다.)

![](https://github.com/user-attachments/assets/136eb892-6b2b-48b6-9d13-7cdaced935a5)

첫 번째 상자의 (부피, 높이) 쌍을 덱에 넣어놓는다.

![](https://github.com/user-attachments/assets/8e60a69a-16b2-4472-a1f4-41f2cbb95c0f)

두 번째 상자의 높이가 덱의 가장 앞 상자(가장 부피가 큼)의 높이와 7 차이나기 때문에 덱을 그대로 유지한다.  
이번에 넣을 상자와 덱에 들어있는 상자와의 부피 합을 계산한다.  

두 번째 상자를 넣기 전, 덱의 뒤부터 지금 상자보다 부피가 작은 상자들을 다 빼낸다. (높이가 오름차순으로 정렬되어 있기 때문에, 나중에 넣는 상자의 높이가 더 커서 앞에 있는 상자가 현재 상자보다 부피가 작거나 같으면 선택하는 우선순위가 현재 상자보다 낮다.)  
덱이 비어있어 더 이상 덱에서 상자를 빼지 않고 덱의 뒤에 두 번째 상자를 넣는다.

![](https://github.com/user-attachments/assets/27cda404-92f6-4845-986a-3822a0bc2b3d)

세 번째 상자의 높이가 덱의 가장 앞 상자의 높이와 8 차이나기 때문에 덱의 맨 앞에 있는 상자를 뺀다.  
상자가 덱에 없어서 이번에는 부피를 계산할 수 없다.

덱이 비어있어 더 이상 덱에서 상자를 빼지 않고 세 번째 상자를 넣는다.

![](https://github.com/user-attachments/assets/5f422c4d-d311-472d-8058-6eaba2e372c4)

네 번째 상자의 높이가 덱의 가장 앞 상자의 높이와 2 차이나기 때문에 덱을 그대로 유지한다.  
이번에 넣을 상자와 덱에 들어있는 상자와의 부피 합을 계산한다.

네 번째 상자를 넣기 전, 덱의 맨 뒤 상자가 지금 상자보다 부피가 커서 빼지 않는다.  
덱의 뒤에 네 번째 상자를 넣는다.  

더 이상 확인할 상자가 없어 반복을 종료한다.

[연습 문제 (백준 21982번)](https://www.acmicpc.net/problem/21982)

``` c++
/** http://boj.kr/8df2798dd2e74aa39e1d0b8c3b3b9e20 제출 코드 */
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
         * 이 문제의 목표 : 높이 i부터 높이 i+x 사이의 두 상자 부피의 합의 최댓값 구하기
         * 
         * <부피, h> 형태로 부피가 단조 감소하도록 덱에 넣기
         * - 현재 덱에 넣을(i번째) 상자와 덱의 맨 앞에 위치하는 (가장 부피가 큰) 상자가 높이가 x보다 크게 차이가 나지 않도록 pop
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
