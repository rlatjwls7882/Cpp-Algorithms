# Euclidean Algorithm (유클리드 호제법) ⚪ Silver IV
두 수의 최대공약수를 찾는 알고리즘

시간복잡도 : O(log(min(A, B)))

60과 18의 최대공약수(GCD, Greatest Common Divisor)를 구해본다고 하자.
이때 A를 큰 수, B를 작은 수로 두면 아래와 같은 과정을 통해 최대공약수를 구할 수 있다.  

1. if(B==0) return A;
2. A%=B;
3. swap(A, B); (2단계를 통해 A<B이 되기 때문에, A>=B 상태를 유지하기 위해서)

60과 18로 시뮬레이션해보면 다음과 같다.  

0. A=60, B=18 (초기 상태)
1. A=6, B=18 (2단계)
2. A=18, B=6 (3단계)
3. A=0, B=6 (2단계)
4. A=6, B=0 (3단계)
5. return A (1단계)

A와 B의 최소공배수(LCM, Least Common Multiple)를 구하는 것은 잘 알려져 있듯이, A * B / gcd(A, B)로 구할 수 있다.  

아래 코드는 gcd와 lcm의 간단한 구현체이다.

``` c++
int gcd(int a, int b) {
    while(b) {
        int tmp = a%b;
        a=b;
        b=tmp;
    }
    return a;
}

int lcm(int a, int b) {
    return a*b/gcd(a, b);
}
```

사실 C++에는 numeric 라이브러리 안에 gcd, lcm 함수가 이미 정의되어 있어, 알고리즘만 이해하면 굳이 구현할 필요는 없다.

[연습 문제 (백준 9770번)](https://www.acmicpc.net/problem/9770)

``` c++
/** http://boj.kr/ca5c761c6eb24e2e9e02964d61cbcb3f 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int> v;
    while(true) {
        int x; cin >> x;
        if(cin.fail()) break;
        v.push_back(x);
    }

    int res=0;
    for(int i=0;i<v.size();i++) {
        for(int j=i+1;j<v.size();j++) {
            res = max(res, gcd(v[i], v[j]));
        }
    }
    cout << res;
}
```
