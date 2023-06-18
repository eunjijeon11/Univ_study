# C cheat sheet (기본 프로그래밍)

## 1. C언어 기본 구조

```c
#include <stdio.h>

int main() {
	// some codes

	return 0;
}
```

## 2. Print, Input, Comment

```c
  printf("I like pizza!\n");
  printf("It's really good!\n");

  // This is a comment blah
  /* oh yeah
      this
      is
      multiline comment~~~
  */

  // escape sequences \n \t
  printf("1\t2\t3\n4\t5\t6\n");
  printf("\"I like pizza\" - me\n");

  // scanf
  int a;
  scanf("%d", &a);

  printf("%d", a);
```

## 3. Variable types

- c언어 변수명은 camel case에 따라 짓는다.

```c
  int x;  //declaration
	x = 123; //initialization

  int y = 321; //declaration + initialization

  int age = 20; //integer
  float gpa = 4.5; //hope
  char grade = 'A';
  char name[] = "eunji"; // no string in C, use array

  printf("hello %s\n", name);
  printf("you are %d years old\n", age);
  printf("your average grade is %c\n", grade);
  printf("your gpa is %f\n", gpa);

  char a = 'C';            // character %c
  char b[] = "hello";      // array of characters %s

  float c = 3.141592;     // floating point(6-7 digits) %f
  double d = 3.141592653589793;  // 15-16 digits %lf
  // double is more precise than float

  bool e = true;       // true or false(1 byte) %d, print->1

  char f = 100;            // -128 to 127, %d: 그대로, %c: 아스키코드값
  unsigned char g = 254;   // 0 to 255 (부호가 없는)

  short int h = 32767;     // (-32768 to 32767)  %d  (==short)
  unsigned short int i = 65535;  // 0 to 65535    %d  (==unsigned short)

  int j = 2147483647;      // -2147483648 to 2147483647  %d  (==long int)
  unsigned int k = 4294967295;  // 0 to 4294967295  %u

  long long int l = 9223372036854775807;  // -9 quintillion to +9 quintillion  %lld
  unsigned long long int m = 1839083083098309835U;  // 0 to 18 quintillion   %llu

  // 범위 초과 시 overflow, 제일 작은 값으로.

  printf("%c\n%s\n%f\n%lf\n%d\n%c\n%c\n%d\n%d\n%d\n%u\n%lld\n%llu\n", a, b, c, d, e, f, g, h, i, j, k, l, m);

  // 소수점 자르기
  float item1 = 5.75;
  float item2 = 10.00;
  float item3 = 100.99;

  printf("Item 1: $%8.2f\n", item1);  // -8.2 : left align
  printf("Item 2: $%8.2f\n", item2);
  printf("Item 3: $%8.2f\n", item3);
```

## 3-2. String

```c
#include <stdio.h>
#include <string.h>

int main(){

    char name[25]; //bytes
    int age;

    printf("What's your name?\n");
    //scanf("%s", name); // no whitespace
    fgets(name, 25, stdin);
    name[strlen(name)-1] = '\0';

    printf("hello, %s\n", name);

    printf("how old are you?\n");
    scanf("%d", &age);

    printf("you are %d years old.\n", age);

    return 0;
}
```

## 3-3. Constant variables

```c
    // constant = fixed value that cannot be altered by the program during its execution

    const float PI = 3.14159;
```

## 4. Operations

```c
    //arithmetic operators

    /*

    + addition
    - substraction
    * multiplication
    / division
    % modulus
    ++ increment
    -- decrement

    */

    int x = 5;
    int y = 2;

    // float z = x / (float) y;  // int/int => int
    int z = x % y;

    x++; // increment
    y--; // decrement

    // augmented assignment operators

    int a = 10;

    a = a + 2;
    a += 2;
    a -= 2;
    a *= 2;
    a /= 2;
    a %= 2;

    // math.h functions

	#include <math.h>

    double A = sqrt(9);
    double B = pow(2, 4);  // 제곱
    int C = round(3.14);  // 반올림
    int D = ceil(3.14);  // 올림
    int E = floor(3.14);  // 내림
    double F = fabs(-100);  // 절댓값
    double G = log(3);
    double H = sin(45);
    double I = cos(45);
    double J = tan(45);

    printf("\n%lf", A);

    return 0;
```

## 5-1. For statement

```c
for (int i=0; i<10; i++) { // i=0 대입, i<10이 참이면 반복, i 1씩 증가
	printf("%d ", i);
}

// 0 1 2 3 4 5 6 7 8 9
```

## 5-2. While statement

```c
int process = 1;

while(process) {
	char input;
	scanf("%c", &input);
	if (input == 'Q') process = 0;
}
```

- do while

```c
char input;

do { // execute at least one time
	scanf("%c", &input);
	printf("hihi\n");
} while(input != 'Q');
```

## 6-1. If-else statement

```c
int age;

printf("enter your age: ");
scanf("%d", &age);

if(age >= 18){
  printf("Boom");
}
else if(age == 0){
  printf("you can't sign up");
}
else if(age < 0){
  printf("no~~~~");
}
else{
  printf("nonono");
}
```

## 6-2. Switch statement

- switch: A more efficient alternative to using many "else if" statements
- allows a value to be tested for equality against many cases

```c
    char grade = 'A';

    switch(grade){
        case 'A':
            printf("perfect");
            break;
        case 'B':
            printf("good");
            break;
        case 'C':
            printf("okay");
            break;
        case 'D':
            printf("no...");
            break;
        case 'F':
            printf("NOOOOoooo");
            break;
        default:
            printf("not a grade");
    }
```

## 6-3. Logical operators

- &&: all condition must be true
- ||: or logical operator
- !: not logical operator

```c
		// and
    float temp = 40;

    if(temp >= 0 && temp <= 30){
        printf("\nweather is good");
    }
    else{
        printf("\ncold!");
    }

    // or
    float temp1 = 25;

    if(temp <= 0 || temp >= 30){
        printf("\nweather is bad");
    }
    else{
        printf("\nweather is good!");
    }

    // not
    bool sunny = true;

    if(sunny){
        printf("\nIt's sunny outside");
    }
    else{
        printf("\nIt's cloudy outside");
    }
```

## 7. Functions

- must have return type, parameters, function name
- must be declared before using

```c
void print_hello() {
	printf("hello!\n");
}

print_hello();

// 또는 함수의 원형(prototype)을 먼저 선언

int sum(int a, int b);

int z = sum(2, 3);

int sum(int a, int b) {return a+b;}
```

- with return

```c
int sum(int a, int b) {
	return a+b;
}

int result = sum(1, 2); // 3
```

- 문자열을 넘길때는 포인터로 넘긴다

```c
void print(char *str) {printf("%s", str);}

//main
char msg[15] = "Hello World!\n";
print(msg);
```

- 위와 같이 pointer를 넘기면 함수 안에서 인자의 변화가 함수 밖에서도 적용됨 (pointer 설명은 뒤에서 계속)

```c
void encrement(int *num) {num++;}

//main
int a = 1;
encrement(a);
printf("%d", a); // 2
```

## 7-2. Library functions

- can import library/user defined functions

```c
#include <stdio.h> // library functions
#include "myfunc.h" // user defined functions
```

## 8. Local var vs Global var

```c
#include <stdio.h>

int maxCount = 10; // global var

int main() {

	int count = 0; // local var of function main()

	for (int i=0; i<maxCount; i++) { // can access global var
		int isEven = 0; // local var in for statement
		if (i%2 == 0) isEven = 1;
		count += isEven; // can access local var in same function
	}

	printf("%d", isEven); // error!!
	printf("%d", count); // 5

	return 0;
}
```

## 8-2. extern, static

- 다른 파일의 전역 변수 사용하기

```c
// myfunc.c
int MAX_COUNT = 10;
static localCount = 5;
```

```c
#include "myfunc.h"

extern int MAX_COUNT;
extern int localCount; // error!!
```

static으로 선언되지 않은 전역변수는 다른 파일에서 extern을 통해 선언하면 사용할 수 있다.

## 9. Pointer

- 변수가 저장된 주기억장치의 주소값을 변수에 담을 수 있다.

```c
int var = 5;
int *ptr;
ptr = &var;

printf("var: %d, %u, %p\n", var, &var, &var);
printf("ptr: %d, %u, %p\n", *ptr, ptr, ptr);
// same!!
```

- 간접 연산자로 포인터가 가리키는 변수의 값에 접근 가능

```c
// continued
printf("%d\n", *ptr);
```

- 포인터 변수의 특징

```c
int *a;
*a = 10;

int *b = a;
*b = 20;

printf("%d\n", *a); // 20
```

## 9-2. Array and Pointer

- 배열명은 배열의 시작 주소(포인터)
- 배열의 원소들은 연속된 주소에 저장되어있음
- 포인터 연산으로 배열 원소 접근 가능

```c
char msg[10]; // msg는 pointer
// initialize

printf("%c %c\n", *msg, msg[0]);
printf("%c %c\n", *(msg+1), msg[1]);
// same!!
```

## 10. Structure

- 새로운 type 만들기

```c
struct Node{
	int value;
	struct Node *next;
}

// main
struct Node myNode;
```

- typedef

```c
typedef struct LinkedList{
	struct Node *head;
	int count;
} linkedList;

linkedList myList;
```
