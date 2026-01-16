# Exponentiation by Squaring (빠른 거듭제곱) ⚪ Silver I
$x^N$ (mod m)을 빠르게 구하는 방법

시간복잡도 : O(logN)

$3^5$를 구한다고 가정해보자.  
5(101<sub>2</sub>) = 4(100<sub>2</sub>)+1(001<sub>2</sub>)  
$3^5$ = $3^4$ * $3^1$이다.  
이를 통해 $a^b$는 b를 이진수로 나타냈을 때, 비트가 1인 자리 k에 대해 $a^{2^k}$의 곱으로 표현된다는 사실을 알 수 있다.

이를 재귀 버전과 비재귀 버전 두가지 형태로 구현할 수 있다. 이해하기에는 재귀 버전이 더 쉬울 것이다.

``` c++
ll exPow(ll a, ll b, ll mod) { // 재귀 버전
    if(!b) return 1;
    if(b==1) return a%mod;

    ll tmp = exPow(a, b/2, mod);
    if(b%2) return tmp*tmp%mod*a%mod;
    else return tmp*tmp%mod;
}

ll exPow(ll a, ll b, ll mod) { // 비재귀 버전
    ll ret=1;
    while(b) {
        if(b&1) ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}
```

[연습 문제 (백준 1629번)](https://www.acmicpc.net/problem/1629)

``` c++
/** http://boj.kr/fc4b96bfed33420f852237800d993f50 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll exPow(ll a, ll b, ll mod) {
    ll ret=1;
    while(b) {
        if(b&1) ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll a, b, c; cin >> a >> b >> c;
    cout << exPow(a, b, c);
}
```
