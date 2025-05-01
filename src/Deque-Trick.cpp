/** https://www.acmicpc.net/problem/21982 제출 코드 */
/** 덱을 이용한 구간 최댓값 트릭 */
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
         * <부피, h> 부피가 단조 감소하도록 덱에 넣기
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
