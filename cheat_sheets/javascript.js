console.log("hello world from main"); //print

/*********************variable***********/
let age = 20; // can re-assign
console.log(age);

const salary = 80000; // cannot re-assign, need initializing
// salary = 70000 --> error
console.log(salary);

/****************data types*****************/
// string, number, boolean, undefined, null, bigInt, Symbol, Objects

const name = "eunji";
const language = "Javascript";

const total = 0;
const PI = 3.14;

const isTrue = true;
const isNew = false;

let result; // undefined
// const result = undefined;
console.log(result);

const data = null; // 비어있는 값은 null을 사용하자

const person = {
    // key: string, value: Any
    firstname: "Bruce",
    lastname: "Eunji", // 마지막에도 , 붙음
};

console.log(person.firstname); // dictionary get item

const oddNumbers = [1, 3, 5, 7, 9]; // array
console.log(oddNumbers[0]);

// data type 정의 필요 없음 (dynamic type)

let a = 10;
a = true; // possible

/****************operators******* */

let x = 10;
let y = 20;

console.log(x + y);

console.log(++x);
console.log(x++);

console.log(x == y);
console.log(x === y); // data type까지 비교

x = 10.0;
y = "10";

console.log(x == y); // true
console.log(x === y); // false wow

let isSame = x == y && x === y;
// && and || or

console.log("Eunji" + "Jeon"); // concat

const isEven = 10 % 2 === 0 ? true : false; // 삼항연산자

/*******************type conversions */
// Implicit conversion : automatic
// Explicit conversion : manually

console.log("10" + 10); // 1010
console.log(true + "3"); // true3
console.log("4" - "2"); // 2
console.log("eunji" - "jeon"); // NaN: not a number
console.log("5" - true);
console.log(4 - false); // 4 - null
console.log(4 + undefined); // NaN

console.log(Number("5")); // returns number 5
console.log(Number("")); // 0
console.log(parseInt("6"));
console.log(parseFloat("5.4"));
console.log(String(undefined));
console.log((500).toString());
console.log(Boolean(10)); // null undefined 0 '' NaN => false

/*****************Equality */
// == Allows coercion
// === not allows coercion

const var1 = "10";
const var2 = 10;

console.log(var1 == var2); // null == undefined => true
console.log(var1 === var2);

/*************************conditional statement */
const num = 5;

if (num > 0) {
    console.log("Number is Positive");
} else if (num == 0) {
    console.log("Number is zero");
} else {
    console.log("Number is Negative");
}

const color = "red";

switch (color) {
    case "red":
        console.log("red");
        break;
    case "yellow":
        console.log("yellow");
        break;
    default:
        console.log("not red or yellow");
}

/*****************************loops */
// for, while, do while, for of

for (let i = 0; i < 3; i++) {
    console.log(i);
}

let i = 0;
while (i < 3) {
    console.log(i);
    i++;
}

// for of loop
const numArray = [0, 1, 2];
for (const num of numArray) {
    console.log(num);
}

/**********************************functions */
function greet(username) {
    console.log("good night " + username);
}

greet("eunji");
greet("seongju");

function add(a, b) {
    return a + b;
}

let c = add(1, 2);
console.log(c);

const arrowSum = (a, b) => a + b;

const sum = arrowSum(1, 2);
console.log(sum);

/***************************scope */

if (true) {
    const myName = "Eunji";
}
// console.log(myName);  // error

const testFn = () => {
    const myName = "eunji";
};
// console.log(myName); // error

// global scope
const myNum = 10;
const fun = () => console.log(myNum);
fun();
