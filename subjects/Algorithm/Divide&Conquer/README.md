# Divide and Conquer (분할 정복)
- 분할: 문제를 작은 부분으로 나눈다
- 정복: 나눈 문제를 각각 해결한다
- 통합: 해결된 답을 모아 원래 문제의 해답을 구한다

## Examples
- Merge Sort
- Quick Sort
- Binary Tree Traversal
- Karatsuba Algorithm (Large Integers Multiplication)
- Strassen's Algorithm (Matrix Multiplication)
- Closest-pair Algorithm
- Convex-hull Algorithm

## Merge Sort (합병 정렬)
- n 길이의 배열을 n/2 개의 배열 두개로 분할
- 더이상 나눠지지 않을 때까지 재귀적으로 반복
- 합병

## Quick Sort (빠른 정렬)
- pivot 보다 작은 수를 왼쪽으로, 큰 수를 오른쪽으로 분할
- 재귀적으로 반복하여 정렬

## Binary Tree Traversal
- Preorder (Root - Left - Right)
- Inorder (Left - Root - Right)
- Postorder (Left - Right - Root)

## Karatsuba Algorithm
- 충분히 큰 n자리수 곱셈의 연산횟수를 줄임
![image](https://github.com/eunjijeon11/Univ_study/assets/61264183/cde6b106-6bfa-4ac9-93eb-e1677bec4ded)

## Strassen's Algorithm
- 행렬 곱셈
![image](https://github.com/eunjijeon11/Univ_study/assets/61264183/c1524690-538f-40ae-a2ea-0ad57820e171)

## Closest-Pair Algorithm
- point를 x값을 기준으로 두개로 분할
- 각 부분에서 가장 가까운 포인트를 찾기
- 각각 영역에서 min 값 이내에 최근접 점이 있는지 확인 (경계선 쪽에서)
- 재귀적으로 영역을 계속 분할하면 더 효율적으로 찾을 수 있음

## Convex Hull
- 최소개수의 꼭지점으로 이루어진 볼록 다각형을 만들어 볼록 다각형 내부에 모든 점을 포함
- point를 x값 기준으로 두 부분으로 분할
- 각 부분에서 convex hull 찾기
- 두 도형을 합치기: 가장 왼쪽, 오른쪽에 있는 점끼리 잇기 -> 볼록 다각형이 되도록 점 바꾸기
