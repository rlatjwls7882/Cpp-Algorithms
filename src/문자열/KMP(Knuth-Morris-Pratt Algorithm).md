## KMP (Knuth-Morris-Pratt) Algorithm
한 문자열에서 다른 문자열이 어디에 등장하는지 찾아주는 문자열 검색 알고리즘

시간복잡도 : O(N+M) (N+M : 두 문자열의 길이 합)

[연습 문제 (백준 1786번)](https://www.acmicpc.net/problem/1786)

``` c++
/** https://www.acmicpc.net/problem/1786 제출 코드 */
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
