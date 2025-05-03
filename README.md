# 미래의 나(와 혹시 모를 다른사람들)를 위한 알고리즘 정리

## 목표
* 증명보다는 알고리즘 설명 위주로 설명 추가
* 알고리즘 복습 및 추가
  * LCA
  * BCC
  * mos
  * Extended Euclidean

## 목차
* 그래프
  * 유량
    * Kuhn's Algorithm (Maximum Bipartite Matching, 이분 매칭)
    * Edmonds-Karp Algorithm
    * Dinic's Algorithm
    * MCMF (Min Cost Max Flow) Algorithm
  * 컴포넌트 분해
    * Tarjan’s Algorithm (SCC)
    * 2-SAT (2-Satisfiability Problem)
  * 트리
    * Segment Tree
    * Lazy Propagation
    * HLD(Heavy Light Decomposition)

* 문자열
  * KMP (Knuth-Morris-Pratt) Algorithm
  * Trie
  * Aho-Corasick

* 기하
  * Line Intersection

* DP
  * TSP (Traveling Salesman Problem, 외판원 순회 문제)
  * Deque Trick

## [Kuhn's Algorithm (Maximum Bipartite Matching, 이분 매칭)](src/Kuhn's%20Algorithm(Maximum%20Bipartite%20Matching).md)
그래프를 [이분 그래프](https://ko.wikipedia.org/wiki/%EC%9D%B4%EB%B6%84_%EA%B7%B8%EB%9E%98%ED%94%84)로 나타내었을 때 최대 매칭 수(왼쪽 정점과 오른쪽 정점의 쌍의 수)를 찾는 알고리즘

시간복잡도 : O(VE) (V : 양쪽 그룹 중 더 큰 정점의 크기)

## [Edmonds-Karp Algorithm](src/Edmonds-Karp%20Algorithm.md)
그래프에서 시작 지점에서 유량을 흘려서, 도착지점까지 유량이 얼마나 도착하는지 찾는 알고리즘

시간복잡도 : O(VE²)

## [Dinic's Algorithm](src/Dinic's%20Algorithm.md)
Edmonds-Karp 알고리즘을 최적화한 알고리즘

시간복잡도 : O(V²E)

## [MCMF (Min Cost Max Flow) Algorithm](src/MCMF(Min%20Cost%20Max%20Flow)%20Algorithm.md)
Edmonds-Karp 알고리즘에 SPFA(Shortest Path Faster Algorithm)를 합쳐 최대의 유량을 흘리면서, 그 중에서 최소 비용을 찾는 알고리즘

시간복잡도 : O(FVE) (F : 최대 유량)

## [Tarjan’s Algorithm (SCC)](src/Tarjan’s%20Algorithm(SCC).md)
그래프에서 나타나는 [SCC (Strongly Connected Component)](https://ko.wikipedia.org/wiki/%EA%B0%95%ED%95%9C_%EC%97%B0%EA%B2%B0_%EC%9A%94%EC%86%8C)을 한번의 dfs로 뽑아내는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

## [2-SAT (2-Satisfiability Problem)](src/2-SAT(2-Satisfiability%20Problem).md)
2개의 변수로 이루어진 [CNF](https://ko.wikipedia.org/wiki/%EB%85%BC%EB%A6%AC%EA%B3%B1_%ED%91%9C%EC%A4%80%ED%98%95)가 주어졌을 때, 이를 만족시도록 변수에 (True/False)를 대입 가능한지 [Implication Graph](https://en.wikipedia.org/wiki/Implication_graph)를 만들어 SCC를 형성해 확인하는 문제

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

## [Segment Tree](src/Segment%20Tree.md)
포화 이진 트리 구조를 이용하여 구간 쿼리를 최적화하는 알고리즘

시간복잡도 : O(QlogN) (Q : 쿼리의 수)

## [Lazy Propagation](src/Lazy%20Propagation.md)
세그먼트 트리에서 구간 업데이트를 지연 방식으로 처리하여, 최적화하는 알고리즘 

시간복잡도 : O(QlogN) (Q : 쿼리의 수)

## [HLD (Heavy Light Decomposition)](src/HLD(Heavy%20Light%20Decomposition).md)
트리에서 세그먼트 트리로 구간 쿼리를 최적화하는 알고리즘

시간복잡도 : O(Qlog²N) (Q : 쿼리의 수)

## KMP (Knuth-Morris-Pratt) Algorithm
한 문자열에서 다른 문자열의 포함 여부를 찾는(문자열 검색) 알고리즘

시간복잡도 : O(N+M) (N+M : 두 문자열의 길이 합)

## Trie
여러 문자열을 공통 접두사로 압축해 저장하는 자료구조

시간복잡도 : O(S) (S : 모든 문자열의 길이)

## Aho-Corasick
Trie구조를 활용한 일대다 패턴매칭 알고리즘

시간복잡도 : O(S) (S : 모든 문자열의 길이)

## Line Intersection
선분 교차 판별하는 알고리즘

시간복잡도 : O(1)

## TSP (Traveling Salesman Problem, 외판원 순회 문제)
비트마스킹 DP를 이용하여 외판원 순회에 필요한 최소 비용을 계산하는 알고리즘

시간복잡도 : O(N x 2<sup>N</sup>)

## Deque Trick
덱에 단조 증가 또는 단조 감소하는 인덱스를 유지하여 슬라이딩 윈도우 내에서 최소값 또는 최대값을 O(1)에 찾는 알고리즘

시간복잡도 : O(N)
