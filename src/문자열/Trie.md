## Trie
여러 문자열을 공통 접두사로 압축해 저장하는 자료구조

시간복잡도 : O(S) (S : 모든 문자열의 길이)

[연습 문제 (백준 5670번)](https://www.acmicpc.net/problem/5670)

연습문제의 테스트케이스 3가지를 트라이 구조로 나타내면 다음과 같다
![img1](https://github.com/user-attachments/assets/c4d9fff1-4e5f-4f95-92d8-c2ea5982a1ff)

모양이 이렇기 때문에 접두사 트리 (Prefix Tree)라고도 부른다.

``` c++
/** https://www.acmicpc.net/problem/5670 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

struct trie {
    /** 
     * go[26] : 해당 문제에서는 알파벳 소문자만 들어오기에 최대 26개의 자식 필요
     * branch : 이 노드에서의 분기 수
     * wordCnt : 이 노드까지 도달한 단어의 수
     */
    trie* go[26] = {0, };
    int branch=0, wordCnt=0;

    /** 
     * 소멸자
     * 존재하는 자식들 먼저 제거하고 자신을 제거
     */
    ~trie() {
        for(int i=0;i<26;i++) {
            if(go[i]) delete go[i];
        }
    }

    /** 
     * 단어가 이 노드에서 끝나는 경우도 하나의 분기로 간주 (branch 증가)
     * 새로운 문자 경로라면 새 노드를 생성하고 분기 수(branch) 증가
     * 해당 노드까지 도달한 단어의 수(wordCnt) 증가
     */
    void insert(char* ch) {
        if(*ch==NULL) {
            branch++;
            return;
        }
        if(!go[*ch-'a']) {
            go[*ch-'a'] = new trie;
            branch++;
        }
        wordCnt++;
        go[*ch-'a']->insert(ch+1);
    }

    /** 
     * 첫 글자이거나, 분기가 2가지 이상이라면 자판을 입력해야함.
     * 이 경우 이 노드를 거치는 모든 단어들(wordCnt)만큼 자판을 눌러야 함.
     */
    long long getCnt(int depth) {
        long long res=0;
        if(depth==0 || branch>=2) res += wordCnt;
        for(int i=0;i<26;i++) {
            if(go[i]) res += go[i]->getCnt(depth+1);
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while(true) {
        int n; cin >> n;
        if(cin.fail()) break;

        trie* root = new trie;
        for(int i=0;i<n;i++) {
            string s; cin >> s;
            root->insert(&s[0]);
        }
        cout << setprecision(2) << fixed << root->getCnt(0) / (double)n << '\n';
        delete root;
    }
}
```
