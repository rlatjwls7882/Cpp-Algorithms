# Modular Multiplicative Inverse (모듈러 곱셈의 역원) 🟡 Gold I
모듈러가 소수일 때 곱셈의 역원을 찾는 알고리즘

시간복잡도 : O(logN)

(a+b)%m = (a%m+b%m)%m과 (a*b)%m = ((a%m) * (b%m))%m은 성립하는 것이 자명하다.  
하지만 (a/b)%m = ((a%m)/(b%m))%m은 성립하지 않는다. 나누는 수가 작다면 직접 b를 구해 답을 찾는것이 가능하지만 수가 커지면 시간이 오래걸린다.  
(a/b)%m이 그대로는 시간 내에 불가능하니 b의 역원인 $b^{-1}$를 찾아 a * $b^{-1}$ % m을 구하는 것이 목적이다.  

먼저 $b^{-1}$가 b의 역원이므로 b * $b^{-1}$ % m = 1이다.  
해당 문서에서는 페르마의 소정리를 이용해서 모듈러 곱셈의 역원을 찾는다.  
페르마의 소정리는 소수 m에 대해 $b^{m-1}$ % m = 1이 성립한다는 정리이다.

여기서 식을 정리하면 b * $b^{m-2}$ % m = 1 라는 식이 나오는데, $b^{m-2}$ 이것이 모듈러 곱셈의 역원이고 $b^{-1}$이다.  
이를 빠른 거듭제곱으로 로그 시간에 구하면 된다. 만약 m이 소수이고 b가 m의 배수가 아니라면, b의 역원이 항상 존재해 이 방법이 성립한다.

[연습 문제 (백준 16134번)](https://www.acmicpc.net/problem/16134)

$nCr$은 $\frac{n!}{(n-r)!r!}$로 나타낼 수 있고 분모인 (n-r)!r!의 곱셈의 역원을 구해 n!에 곱해주면 된다.

``` c++
/** http://boj.kr/2d1d279029f64546ae8e3f6040170beb 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1e9+7;

ll fact[1'000'001];

ll pow(ll a, ll b) {
    ll ret=1;
    while(b) {
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

ll comb(ll n, ll r) {
    if(r<0 || r>n) return 0;
    return fact[n]*pow(fact[n-r]*fact[r]%MOD, MOD-2)%MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, r; cin >> n >> r;
    fact[0]=1;
    for(int i=1;i<=n;i++) fact[i]=fact[i-1]*i%MOD;
    cout << comb(n, r);
}
```
