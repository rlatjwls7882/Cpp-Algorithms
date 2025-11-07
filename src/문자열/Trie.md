## Trie 🟢 Platinum IV
여러 문자열을 공통 접두사로 압축해 저장하는 자료구조

시간복잡도 : O(S), 공간복잡도 : O(S) (S : 모든 문자열의 길이)

![](https://github.com/user-attachments/assets/3c91f65b-7b0a-435a-b0b4-6d1b6dd1f9c9)

처음에는 이렇게 루트만 존재한다.  
she라는 단어를 집어넣어 보겠다.

![](https://github.com/user-attachments/assets/f526c261-917f-4927-b3fb-ee701a37303f)

root에서 s로 가는 길이 없어 새로 생성한다.  
s로 이동한다.

![](https://github.com/user-attachments/assets/70fdbe7f-c2fe-46d3-b433-16ec86c2ca52)

s에서 h로 가는 길이 없어 새로 생성한다.  
h로 이동한다.

![](https://github.com/user-attachments/assets/89202832-30f3-448c-8836-e04dd79b780e)

h에서 e로 가는 길이 없어 새로 생성한다.  
e로 이동한다.

![](https://github.com/user-attachments/assets/21544fb6-f507-42a6-b599-1026ce002d90)

더이상 방문할 문자가 없다.  
현재 정점에서 끝나는 단어의 수를 1 증가시킨다.

![](https://github.com/user-attachments/assets/6c6cd2d7-5f57-4436-9f8e-695657393058)

이번엔 he라는 단어를 집어넣겠다.  
root -> h -> e로 가는 길이 없어 새로 생성하고 e에서 끝나는 단어의 수를 1 증가시킨다.

![](https://github.com/user-attachments/assets/9b928c17-c922-47e4-a4d0-999050a02c5b)

이번엔 her이라는 단어를 집어넣겠다.  
root -> h -> e로 가는 길이 이미 있어 따라 가고 e -> r로 가는 길은 없어 새로 생성한다.  
r에서 끝나는 단어의 수를 1 증가시킨다.

[연습 문제 (백준 5670번)](https://www.acmicpc.net/problem/5670)

연습문제의 테스트케이스 3가지를 트라이 구조로 나타내면 다음과 같다

![](https://github.com/user-attachments/assets/c4d9fff1-4e5f-4f95-92d8-c2ea5982a1ff)

모양이 이렇기 때문에 접두사 트리 (Prefix Tree)라고도 부른다.

``` c++
/** http://boj.kr/a9405512ef8f4c4e835bc367d7ea851a 제출 코드 */
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
