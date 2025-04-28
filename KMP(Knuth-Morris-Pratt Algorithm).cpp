/** https://www.acmicpc.net/problem/1786 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

int table[1'000'000];

/**
 * 부분 일치 테이블 생성
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
    cout << posList.size() << '\n';
    for(int e:posList) cout << e << ' ';
}
