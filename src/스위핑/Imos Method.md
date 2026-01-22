## Imos Method (いもす法) 🟢 Platinum IV
구간(또는 영역)의 증가·감소량을 차분 배열(Difference Array)에 기록한 뒤, 최종적으로 누적 합을 구해 전체 상태를 복원하는 알고리즘

시간복잡도 : O($N^D+Q$) (N : 각 차원의 크기, D : 차원 수, Q : 쿼리 수)

![](https://github.com/user-attachments/assets/b583f51a-1765-44a7-a79d-c0adca081ecb)

Imos Method로 사각형을 구하는 방식은 4군데를 마킹한 후 오른쪽으로 쓸고, 아래로 쓸면 된다. 자세한 내용은 [Imos Lab](https://imoz.jp/algorithms/imos_method.html)에서 확인 가능하다.

Imos Method로 한 변의 길이가 4인 직각 삼각형을 구해보자.

![](https://github.com/user-attachments/assets/71a8c27f-c47d-4123-b08c-188e24646a08)

이런식으로 6군데를 마킹한 후

![](https://github.com/user-attachments/assets/0bb2a49b-42f1-45fe-8ff4-d43c6b37da08)

오른쪽으로 한번 쓸고

![](https://github.com/user-attachments/assets/73e9d5e5-a615-4c5d-aff0-2e5782f126e6)

아래로 한번 쓸고

![](https://github.com/user-attachments/assets/671e6c95-a31d-4a34-8d64-1ce51e341f32)

오른쪽 대각선 아래로 한번 쓸면 완성된다.

[연습 문제 (백준 5541번)](https://www.acmicpc.net/problem/5541)

![](https://github.com/user-attachments/assets/ffab57aa-4395-43fa-a73c-986b836cfc0d)

연습 문제의 최종 결과는 이렇게 된다.

``` c++
/** http://boj.kr/c40c3fb76ea245d4879b7d038344cf7e 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 5002;

int board[MAX][MAX];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    while(m--) {
        int a, b, x; cin >> a >> b >> x;
        board[a-1][b-1]++;
        board[a-1][b]--;
        board[a+x][b-1]--;
        board[a+x][b+x+1]++;
        board[a+x+1][b]++;
        board[a+x+1][b+x+1]--;
    }

    // 오른쪽
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=n;j++) {
            board[i][j+1] += board[i][j];
        }
    }

    // 아래쪽
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=n;j++) {
            board[i+1][j] += board[i][j];
        }
    }

    // 오른쪽 대각선 아래
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=n;j++) {
            board[i+1][j+1] += board[i][j];
        }
    }

    int cnt=0;
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=n;j++) {
            if(board[i][j]) cnt++;
        }
    }
    cout << cnt;
}
```
