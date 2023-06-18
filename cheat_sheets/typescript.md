# Typescript cheat sheet

## 1. variables

```ts
let sales: number = 123_456_789; // let sales = 123456789
let course: string = "Typescript";
let is_published: boolean = true;

let level; // any type
level = 1;
level = "a"; // nooo.. avoid using any type

function render(document: any) {
  // any
  console.log(document);
}
```

## 1-2. arrays

```ts
let numbers = [1, 2, "3"]; // valid in js
// let nums: number[] = [1, 2, '3']  // error in ts
let arr = []; // type: any[]

let nums: number[] = [1, 2, 3];

let user: [number, string] = [1, "mose"];
user.push(1);
```

## 1-3. enum

```ts
const enum Size { //const : more optimized
  Small = 1,
  Medium,
  Large,
} // Pascal Case
let mySize: Size = Size.Medium;
console.log(mySize);
```

## 2. functions

```ts
function calculateTax(income: number = 2022): number {
  // void if no return value
  if (income < 50_000) {
    return 0;
  }
  return 1;
} // typescript need exactly same number of parameters
```

## 3. type

```ts
type Employee = {
  // pascal
  readonly id: number;
  name: string;
  retire: (date: Date) => void;
};
```

## 3-2. object

```ts
let employee: Employee = {
  id: 1,
  name: "eunji",
  retire: (date: Date) => {
    console.log(date);
  },
};
// employee.id = 0
```

## 3-3. union type

```ts
function kgToLbs(weight: number | string) {
  // Narrowing
  if (typeof weight === "number") {
    return weight * 2.2;
  } else {
    return parseInt(weight) * 2.2;
  }
}
```

## 3-4. type intersection

```ts
type Draggable = {
  drag: () => void;
};

type Resizable = {
  resize: () => void;
};

type UIWidget = Draggable & Resizable;

let textBox: UIWidget = {
  drag: () => {},
  resize: () => {},
};
```

## 3-5. other

```ts
// literal types (exact, specific)
type Quantity = 50 | 100;
let quantity: Quantity = 50; // only 50 or 100

// nullable types
function greet(name: string | null | undefined) {
  if (name) console.log(name.toUpperCase());
  else console.log("Hola!");
}

greet(null); // hola!
```

## 4. optional chaining

```ts
type Customer = {
  birthday?: Date;
};

function getCustomer(id: number): Customer | null | undefined {
  return id === 0 ? null : { birthday: new Date() };
}

let customer = getCustomer(1);
// optional property access operator
console.log(customer?.birthday?.getFullYear());
```

## 4-2. optional access

```ts
//optional element access operator
customers?.[0];

// optional call
let log: any = (message: string) => console.log(message);
let log: any = null;
log?.("a"); // log or undefined
```
