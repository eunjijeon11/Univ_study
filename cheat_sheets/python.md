# 컴퓨팅사고와 SW코딩 실습내용 정리

## Index

- [week2-python I/O](#1-week2-python-%EC%9E%85%EC%B6%9C%EB%A0%A5-%EC%B2%98%EB%A6%AC)
- [week3-variable and types](#2-week3-%EB%B3%80%EC%88%98%EC%99%80-%EA%B8%B0%EB%B3%B8-%EC%9E%90%EB%A3%8C%ED%98%95)
- [week4-string data processing](#3-week4-%EB%AC%B8%EC%9E%90%EC%97%B4-%EC%9E%90%EB%A3%8C)

## 1. Week2-python 입출력 처리

- 일반 입력 처리: `input("text: ")`

  ```python
  >>> name = input("name: ")
  name: eunji
  >>> print(name)
  'eunji'
  ```

  입력 받은 자료는 문자열(str)로 저장됨  
   자료형 변환을 할 수 있음

  ```python
  radius = int(input("r: "))
  pi = float(input("pi: "))
  ```

- 일반 출력 처리: `print()`

  ```python
  print(value, ..., sep=' ', end='\n', file=sys.stdout, flush=False)
  ```

  - value: print()함수에서 반드시 요구되는 값, 출력할 내용 (복수도 가능)
  - sep: value가 복수일 때 구분자, 기본값은 ' '(space)
  - end: 출력내용이 끝난 후 마지막 내용, 기본값은 '\n'(줄바꿈)
  - file: 프린트할 대상, 기본값은 모니터 화면
  - flush: True로 지정하면 print한 내용을 출력 후 강제삭제시킴. 기본값 False

  ex)

  ```python
  >>> print("a"); print("b"); print("c")
  a
  b
  c
  >>> print("a", end = ' '); print("b", end = ' '); print("c", end = ' ')
  a b c
  ```

- 문자열 포맷 코드 %
  print()함수에서 출력할 내용이 여러개인 경우 콤마(,)로 나열하여 출력

  ```python
  >>> print("hello", "good night")
  hello good night
  ```

  이미 저장된 자료들을 출력 문자열에 포함시키기: %s, %d, %f 등등 사용

  ```python
  >>> x = 5; y = 10
  >>> print("%d*2 = %d"%(x,y))
  5*2 = 10
  ```

  %로 자리수 지정

  ```python
  >>> print("%d 나누기 %d = %2f"%(10, 3, 10/3))
  10 나누기 3 = 3.33
  ```

  print()에서 사용하는 포맷 코드  
  |코드|설명|
  |:---:|:---:|
  |%s|string|
  |%c|char|
  |%d|integer(digit)|
  |%f|float|
  |%o|octal(8진수)|
  |%x|hexadecimal(16진수)|
  |%%|percent sign|

- format() 함수 활용 출력
  value 내용 안에 중괄호 {}를 표시하여 자료를 지정하여 출력
  ```python
  >>> print("{} x {} = {}".format(2, 3, 6))
  2 x 3 = 6
  >>> print("{0} + {0} = {1}".format(2, 4))
  2 + 2 = 4
  ```
- 실습코드
  - 2-1: input으로 받은 두 수 사칙연산하기
    - int()로 형변환
  - 2-2: 고백 문장
    - %, format() 사용
  - turtle 모듈
    - turtle 에서는 input 대신 turtle.textinput("title", "text") 사용
    - if문, for문 등장

---

## 2. Week3-변수와 기본 자료형

- Python 변수명 생성 규칙

  - 의미 있는 이름을 사용
  - 소문자와 대문자 구분
  - 영문자, 숫자, 밑줄(\_) 이용
  - 공백( ) 사용 못함
  - 숫자로 변수명 시작 못함
  - #, $, & 등의 특수문자 사용 불가

- python 기본 자료형

  - string(문자열), int(정수형), float(실수형), bool(참/거짓)
  - type() 함수로 자료형 확인
    ```python
    >>> type("hello")
    <class 'str'>
    >>> type(3)
    <class 'int'>
    ```
  - 자료형 변환

    ```python
    >>> int("128")
    128
    >>> str(2022)
    '2022'
    # float(), bool() 가능

    #caution
    >>> bool("False")
    True
    ```

  - python 진법 변환

    ```python
    #ex) int('number_expression', base)
    >>> int('0x80', 16) #16진법(hex) 80을 10진법 정수로 전환
    128
    >>> int('0o200', 8) #8진법(oct) 200을 10진법 정수로 변환
    128
    >>> int('0b10000000', 2) #2진법(binary) 10000000을 10진법 정수로 변환
    128

    #이렇게 변환하면 type은 str
    >>> bin(15)
    '0b1111'
    >>> oct(15)
    '0o17'
    >>> hex(15)
    '0xf'
    ```

- 변수의 생성 및 삭제

  ```python
  var1 = 10
  var2 = var1
  var1 = 20
  # var1 = 20, var2 = 10

  # 연속대입
  x = y = z = 100

  # 변수삭제
  >>> del x
  >>> x
  !!error~~
  ```

- 실습코드
  - 3-1: 입력받은 10개의 수의 합과 평균을 출력
    - initializing 개념
  - 3-2: 입력받은 수를 다양한 진법으로 표현
  - 3-3: turtle로 그래프 그리기
  - 과제1: 오류수정하기 2.42e-4 = 0.000242
  - 과제2: 변수 생성하기

---

## 3. Week4-문자열 자료

- 문자열 생성
  ```python
  >>> "hello"
  'hello'
  >>> 'hi'
  'hi'
  >>> """hello"""
  'hello'
  >>> '''hi'''
  'hi'
  >>> "this is'
  !!SyntaxError
  ```
- 문장 표현 방법

  ```python
  >>> print('He said "python is nice"')
  He said "python is nice"
  >>> print("Han's \"python\" class!")
  Han's "python" class!
  >>> "Han's \"python\" class!"
  'Han\'s "python" class!'

  >>> """a
  ... b
  ... c"""
  a\nb\nc         # \n이렇게 저장되고 print로 출력될때 줄바꿈되는듯...
  >>> print("""a
  ... b
  ... c""")
  a
  b
  c
  ```

- escape code
  |코드|내용|
  |:---:|:---:|
  |\n|new line|
  |\t|tab|
  |\\\\ | \\ |
  |\\'|'|
  |\\"|"|
- 문자열 연결

  ```python
  >>> a = "h"; b = "i"
  >>> a + b
  'hi'

  # int vs str
  >>> print(100 + 200)
  300
  >>> print("100" + "200")
  100200
  >>> print("100" + 200)
  !!error

  # 문자열 반복
  >>> hi = hello
  >>> hi * 3
  hellohellohello
  ```

- 인덱싱&슬라이싱

  ```python
  # indexing starts at 0
  >>> text = "Slow and Steady wins the race."
  >>> text[3]
  'w'
  >>> text[-1]
  'y'
  >>> text[5] = 'i'
  !!error

  # slicing slice before the end index
  >>> text[0:3]  # text[:3]
  'Slo'
  >>> text[-4:]
  'race'
  >>> text[16:-9]
  'wins'
  ```

- 문자열 포맷팅 (week1 참고)

  - 너비 지정 포맷팅

    ```python
    >>> string = "funny %10s class!"%"python"
    #string = "funny {0:>10} class!".format(string)
    >>> string
    'funny     python class!'

    >>> string = "funny %-10s class!"%"python"
    #string = "funny {0:<10} class!".format(string)
    >>> string
    'funny python     class!'

    >>> string = "funny %10s class!"%"python".center(10)
    #string = "funny {0:^10} class!".format(string)
    >>> string
    'funny   python   class!'
    ```

- 실습코드
  - 4-1: 문자열 생성-스케쥴 입력
    - while, continue, break
  - 4-2: 문자열 인덱싱-짝수번째 글자만
    - pass (continue와 다름 주의), len() 함수
  - 4-3: 문자열 수정-이름바꾸기
  - 4-4: 문자열 포맷팅-생일카드쓰기
