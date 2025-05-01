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
    * Kuhn's Algorithm (Maximum-Bipartite-Matching, 이분 매칭)
    * Edmonds Karp Algorithm
    * Dinic's Algorithm
    * MCMF (Min-Cost-Max-Flow)
  * 컴포넌트 분해
    * SCC (Strongly Connected Component)
    * 2-SAT (2-Satisfiability Problem)
  * 트리
    * Heavy-Light Decomposition

* 문자열
  * KMP (Knuth-Morris-Pratt) Algorithm
  * Trie
  * Aho-Corasick

* 기하
  * Line Intersection

* 세그먼트 트리
  * Segment Tree
  * Lazy Propagation

* DP
  * TSP (Traveling Salesman Problem)
  * Deque Trick

## [Kuhn's Algorithm(Maximum-Bipartite-Matching, 이분 매칭)](/Kuhn's%20Algorithm(Maximum-Bipartite-Matching).md)
그래프를 [이분 그래프](https://ko.wikipedia.org/wiki/%EC%9D%B4%EB%B6%84_%EA%B7%B8%EB%9E%98%ED%94%84)로 나타내었을 때 최대 매칭 수(왼쪽 정점과 오른쪽 정점의 쌍의 수)를 찾는 알고리즘

시간복잡도 : O(VE) (V : 양쪽 그룹 중 더 큰 정점의 크기)

## [Edmonds-Karp Algorithm](Edmonds-Karp%20Algorithm.md)
그래프에서 시작 지점에서 유량을 흘려서, 도착지점까지 유량이 얼마나 도착하는지 찾는 알고리즘

시간복잡도 : O(VE²)

## [Dinic's Algorithm](/Dinic's%20Algorithm.md)
Edmonds-Karp 알고리즘을 최적화한 알고리즘

시간복잡도 : O(V²E)

## [MCMF(Min-Cost-Max-Flow) Algorithm](/MCMF(Min-Cost-Max-Flow)%20Algorithm.md)
Edmonds-Karp 알고리즘과 비슷한 모양을 한 최대의 유량을 흘리면서, 그 중에서 최소 비용을 찾는 알고리즘

시간복잡도 : O(FVE) (F : 최대 유량)
