# Brute Force
- 가장 단순하고 직관적인 방법
- 더 많은 작업을 하게 될 수 있음
- 사용하기 쉽다
- 항상 최적의 방법(Optimal Solution)을 찾아낸다
- 모든 가능한 경우를 enumerate 하고 문제를 해결한다

## Examples
- Selection Sort
- Bubble Sort
- String Matching
- Sequential Search
- Exhaustive Search
  - Traveling Salesman Problem (Hamilton Circuits)
  - Knapsack Problem
  - Job Assignment Problem
 
## Selection Sort (선택 정렬)
- 가장 작은 값을 찾아서 맨 앞의 값과 자리 바꾸기
- n번 반복
- O(n^2)

## Bubble Sort (버블 정렬)
- 인접한 두 원소(i, i+1) 비교, 왼쪽이 더 크면 자리바꾸기
- 가장 큰 자료부터 정렬됨
- 0~n-1 자리까지를 n번 반복
- O(n^2)

## String Matching
- 맨 앞 문자부터 한 문자씩 비교
- 다른 문자가 나타나면 시작문자를 한 칸 옮겨서 다시 비교
- O(m*n) m: 패턴 길이 n: 텍스트 길이

## Sequential Search (순차 탐색) (Linear Search 선형 탐색)
- 처음부터 끝까지 차례대로 원소를 비교하며 탐색
- O(n)

## Exhaustive Search (완전 탐색)
### Traveling Salesman Problem
- 모든 vertex를 한번씩만 지나 시작 지점으로 돌아오기
- Brute force로 풀 경우 Optimal Hamiltonian Circuits 라고 한다
### Knapsack problem
- item 별 weight와 value 가 있음
- 가방에 넣을 수 있는 최대 weight가 있음
- weight를 넘지 않도록 하면서 가장 많은 value 담기
- O(2^n)
### Job Assignment Problem
- n명에게 n개의 작업을 할당할 때 cost를 최소화시키자
- O(n!)
