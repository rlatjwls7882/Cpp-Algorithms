## Sieve of Eratosthenes (에라토스테네스의 체)
1부터 N까지의 소수를 미리 구하는 전처리 알고리즘

시간복잡도 : $O(N\log{\log{N}})$

![](https://github.com/user-attachments/assets/34b0529c-9389-4800-8470-ff8c23735702)

30까지의 소수를 찾는다고 하자.

![](https://github.com/user-attachments/assets/cf2659ca-c5c4-42d8-a124-76f6efb5e588)

1은 제외하고 제외되지 않은 다음수인 2를 확인한다. 2를 소수로 체크하고, 2의 배수들을 전부 배제한다.

![](https://github.com/user-attachments/assets/27c89c94-9a7a-488d-b61f-e993e7762e51)

제외되지 않은 다음수인 3을 확인한다. 3을 소수로 체크하고, 3의 배수들을 전부 배제한다.

![](https://github.com/user-attachments/assets/8dd0bdac-f369-456e-82ae-e4c9182a45aa)

제외되지 않은 다음수인 5를 확인한다. 5를 소수로 체크하고, 5의 배수들을 전부 배제한다.

![](https://github.com/user-attachments/assets/5657319e-67ab-4e54-bb5d-6f366075db98)

√30보다 작은 수는 없으니 확인을 종료한다.  
소수 판정에서 √N까지만 확인하는 것과 같은 이유로 배제되지 않은 수들을 전부 소수로 체크한다.  
따라서 30 이하의 소수들을 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 총 10개이다.

[연습 문제 (백준 1929번)](https://www.acmicpc.net/problem/1929)

``` c++
/** http://boj.kr/e8e3af892f354fe3aac6d5f887eb6a02 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 1'000'001;

bool notPrime[MAX] = {1, 1};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    for(int i=2;i*i<MAX;i++) {
        if(!notPrime[i]) {
            // j를 i*i부터 시작하는 이유: i*k (k<i)인 위치는 이미 k의 배수로써 방문했기 때문
            for(int j=i*i;j<MAX;j+=i) notPrime[j]=true;
        }
    }

    int m, n; cin >> m >> n;
    for(int i=m;i<=n;i++) {
        if(!notPrime[i]) cout << i << '\n';
    }
}
```
