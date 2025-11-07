## KMP (Knuth-Morris-Pratt) Algorithm 🟢 Platinum V
한 문자열에서 다른 문자열이 어디에 등장하는지 찾아주는 문자열 검색 알고리즘

시간복잡도 : O(N+M) (N+M : 두 문자열의 길이 합)

![](https://github.com/user-attachments/assets/caaed2b3-c9ac-4999-90f1-9d84be9f975e)

ABCABCAC (T)에서 ABCAC (P)를 찾는다고 생각해보자.  
먼저 패턴의 부분 일치 테이블 (실패 함수)를 찾아야한다.  
실패 함수란, 위 사진처럼 매칭에 실패했을 때, 어디부터 다시 살펴봐야 하는지 나타내는 함수이다.

![](https://github.com/user-attachments/assets/90938c0a-73c2-4160-b24d-f43107110c7c)

이번에는 패턴 P가 ABCABCAC라 하자.  
0번째에서 실패하면 0번째 문자부터 다시 확인해야 하기에 table(실패 함수)의 0번째 값은 0으로 채운다.

![](https://github.com/user-attachments/assets/161e7510-f30c-4461-a7af-597153cf32f5)

P[i]와 P[idx]가 다르기에 매칭에 실패한다. 0번째 문자보다 더 전에서 시작할 순 없다.  
1번째에서 실패하면 0번째 문자부터 다시 확인해야 하기에 table의 1번째 값은 0(idx)로 채운다.

![](https://github.com/user-attachments/assets/b1397b81-9773-4f23-af4a-c7fed0857503)

P[i]와 P[idx]가 다르기에 매칭에 실패한다. 0번째 문자보다 더 전에서 시작할 순 없다.  
2번째에서 실패하면 0번째 문자부터 다시 확인해야 하기에 table의 2번째 값은 0으로 채운다.

![](https://github.com/user-attachments/assets/cc354ba5-bbb6-4bbe-9fdd-2c71a648ce9d)

P[i]와 P[idx]가 같아 매칭에 성공한다. idx(일치하는 문자 수)가 증가한다..  
3번째에서 실패하면 1번째 문자부터 다시 확인해야 하기에 table의 3번째 값은 1로 채운다. (ABCA 는 이 다음 문자에서 실패하더라도 적어도 A ~ ... 으로는 시작한다)

![](https://github.com/user-attachments/assets/2d29e5b5-c924-40d6-8b05-37ab866da263)

P[i]와 P[idx]가 같아 매칭에 성공한다. idx가 증가한다.  
4번째에서 실패하면 2번째 문자부터 다시 확인해야 하기에 table의 4번째 값은 2로 채운다. (ABCAB 는 이 다음 문자에서 실패하더라도 적어도 AB ~ ... 으로는 시작한다)

![](https://github.com/user-attachments/assets/b8f0f1f1-1f8d-473b-a3ad-627adb581a05)

P[i]와 P[idx]가 같아 매칭에 성공한다. idx가 증가한다.  
5번째에서 실패하면 3번째 문자부터 다시 확인해야 하기에 table의 5번째 값은 3로 채운다. (ABCABC 는 이 다음 문자에서 실패하더라도 적어도 ABC ~ ... 으로는 시작한다)

![](https://github.com/user-attachments/assets/3c8cfdd3-0ce5-4ae7-a8dd-08df4a381d73)

P[i]와 P[idx]가 같아 매칭에 성공한다. idx가 증가한다.  
6번째에서 실패하면 4번째 문자부터 다시 확인해야 하기에 table의 6번째 값은 4로 채운다. (ABCABCA 는 이 다음 문자에서 실패하더라도 적어도 ABCA ~ ... 으로는 시작한다)

![](https://github.com/user-attachments/assets/8dbb193f-801c-4dfb-9b62-6c2243bf33ad)

P[i]와 P[idx]가 다르기에 매칭에 실패한다. idx에 실패함수 값을 받아와 2가 된다. (idx = table[idx-1])  
P[i]와 P[idx]가 다르기에 매칭에 실패한다. idx에 실패함수 값을 받아와 0이 된다.  
7번째에서 실패하면 0번째 문자부터 다시 확인해야 하기에 table의 7번째 값은 0으로 채운다.

![](https://github.com/user-attachments/assets/5ca21cdd-4edc-4b41-8d1c-d3dcd867800c)

문자열 T에서 패턴 P를 찾을 때, 실패함수와 다른 점은 0부터 비교한다는 점과, 문자열에 패턴이 존재하는 경우 (idx == P.length) 모든 발생 위치를 찾을 때 idx를 실패했을 때처럼 되돌려 보내는 것(idx = table[idx-1]) 하나를 제외하곤 없다.

[연습 문제 (백준 1786번)](https://www.acmicpc.net/problem/1786)

``` c++
/** http://boj.kr/085dfffd934f4710a2f39791af06f331 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/** 
 * 패턴 문자열의 부분 일치 테이블 (실패 함수)
 */
int table[1'000'000];

/**
 * 부분 일치 테이블 (실패 함수) 생성
 * table[i] : pattern[0 ~ i]에서 접두사와 접미사가 일치하는 최대 길이
 * 
 * 예시: pattern = "ababaca"
 * table = [0, 0, 1, 2, 3, 0, 1]
 * i번 문자에서 일치하지 않으면 table[i-1]번 문자부터 다시 살펴봄.
 */
void makeTable(string pattern) {
    int idx=0;
    for(int i=1;i<pattern.length();i++) {
        while(idx>0 && pattern[idx]!=pattern[i]) idx = table[idx-1];
        if(pattern[idx]==pattern[i]) table[i] = ++idx;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string T, P; getline(cin, T); getline(cin, P);
    makeTable(P);

    /**
     * T[i]!=P[idx] : 패턴 일치에 실패한 경우 -> 어느 문자부터 살펴봐야 하는지 확인 (실패 함수 실행)
     * 
     * idx==P.length() : 일치하는 패턴이 나온 경우
     * - idx = table[idx-1]; : 패턴을 찾은 경우에도 다음으로 일치하는 위치를 찾기 위해 다시 되돌아감.
     */
    int idx=0;
    vector<int> posList;
    for(int i=0;i<T.length();i++) {
        while(idx>0 && T[i]!=P[idx]) idx = table[idx-1];
        if(T[i]==P[idx]) {
            if(++idx==P.length()) {
                posList.push_back(i-P.length()+2);
                idx = table[idx-1];
            }
        }
    }
    cout << posList.size() << '\n'; // 패턴을 찾은 횟수
    for(int e:posList) cout << e << ' '; // 각 패턴의 등장 위치
}
```
