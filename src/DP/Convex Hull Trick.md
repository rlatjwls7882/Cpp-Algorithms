# Convex Hull Trick 🟢 Platinum II
DP를 볼록껍질 형태로 나타내 최적화하는 방법

시간복잡도 : $O(N \log N)$

[연습문제 (백준 13263번)](https://www.acmicpc.net/problem/13263)

해당 문제에서 $dp_i$를 나무 i를 높이 1로 만들 때의 최소 비용이라 두고, $N^2$ DP식을 세우면 $dp_i = \min_{1 \leq j < i}(b_j a_i + dp_j)$가 된다.

이때 x가 $a_i$, 기울기가 $b_j$, y절편이 $dp_j$인 직선의 방정식이라고 생각할 수 있고, 이를 좌표평면 위에 나타내면 다음과 같이 나타난다.

![](https://github.com/user-attachments/assets/5ae15e9b-1a59-4892-b902-0884745fe7e4)

여기서 사용할 의미있는 구간만 남기면 다음과 같이 볼록 껍질로 나타난다.

![](https://github.com/user-attachments/assets/f4dd5596-14f2-4d01-8202-a1df02e0d7bc)

이제 어느 구간을 사용할 것인지는 교점의 x좌표로 이분탐색하여 찾아낼 수 있다.

볼록 껍질의 성질을 이용한 것이기에 기울기가 단조 증가 / 감소할 때 최적화할 수 있다.

구현 팁) 조건이 $dp_i = \min_{1 \leq j < i}(b_j a_i + dp_j)$라면 { $b_{i-1}, dp_{i-1}$ }로 설정하고, $dp_i = \min_{1 \leq j \leq i}(b_j a_i + dp_j)$라면 { $b_i, dp_i$ }로 설정한다.

``` c++
/** http://boj.kr/eb87a8abf29945d991dca11565d78cb8 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const int MAX = 100'001;

ll a[MAX], b[MAX], dp[MAX];

struct element {
    ll a, b;
    ld x=1e-150;
};

ld meetX(element a, element b) {
    return (ld)(a.b-b.b)/(b.a-a.a);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];

    vector<element> stk;
    for(int i=2;i<=n;i++) {
        ll x = a[i];
        element cur = {b[i-1], dp[i-1]};
        while(!stk.empty()) {
            cur.x = meetX(stk.back(), cur);
            if(cur.x>stk.back().x) break;
            stk.pop_back();
        }
        stk.push_back(cur);

        int l=0, r=stk.size()-1;
        while(l<r) {
            int mid = l+r+1>>1;
            if(x<=stk[mid].x) r=mid-1;
            else l=mid;
        }
        dp[i] = stk[l].a*x + stk[l].b;
    }
    cout << dp[n];
}
```
