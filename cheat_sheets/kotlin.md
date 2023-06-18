# Kotlin cheat sheet

## 1. 기본

```kotlin
package com.example.myapplication

import java.lang.Exception

val data1 = 10  // need initializing
var data2 = 10

fun main() {
    println("Hello world")

    /*** var vs val ***/
    // data1 = 20 // error!
    data2 = 20

    /*** type ***/
    val a1: Byte = 0b00001011
    val a2: Int = 123
    val a3: Short = 123
    val a4: Long = 10L
    val a5: Double = 10.0
    val a6: Float = 10.0f

    // all data types in Kotlin are Object! => nullable & can use method

    val a: Char = 'a'
    val str1: String = "Hello \n World"
    val str2: String = "int: $a2, long: $a4"  // string template

    // any type
    val data6: Any = 10
    val data3: Any = User()

    val data5: Int by lazy {
        println("in lazy")
        10
    }

    println(data5 + 10)  // in lazy \n 20

    /*** unit & Nothing ***/
    fun some(): Unit { // no return
        println(10 + 20)
    }

    fun some2(): Nothing {
        throw Exception()
    }

    /*** nullable ***/
    var noNull: Int = 10
    // noNull = null  // error!
    var yesNull: Int? = 10
    yesNull = null

    /*** function ***/
    fun some3(x: Int, y: Int = 10): Int {
        // x = 20  // can't change parameter
        return x * y  // return value
    }

    /*** collection type ***/
    val arr: Array<Int> = Array(3, { 0 })
    arr[0] = 10
    arr[1] = 20
    arr.set(2, 30)

    val arr2: IntArray = IntArray(3, { 0 })
    val arr3 = arrayOf<Int>(10, 20, 30)

    val list = listOf<Int>(10, 20, 30)  // immutable
    val mutableList = mutableListOf<Int>(10, 20, 30)  // mutable

    val set = setOf<Int>(10, 20, 30)
    val mutableSet = mutableSetOf<Int>(10, 20, 30)

    val map = mapOf<String, String>(Pair("one", "hello"), "two" to "world")

    /*** if else ***/
    var z = 10
    if (z > 0) {
        println("z > 0")
    } else if (z <=0 && z == 0) {
        println("z == 0")
    } else {
        println("z <= 0")
    }

    z = if (z > 0) {  // expression
        100
    } else {
        200
    }

    when (z) {  // switch
        100 -> println("z is 100")
        200 -> println("z is 200")
        10, 20 -> println("z is 10 or 20")
        in 0..10 -> println("data is 1...10")
        else -> {
            println("error")
        }
    }

    when {
        z <=0 -> println("z is negative")
        else -> println("z is positive")
    }

    val b = when {
        z > 0 -> "data is positive"
        else -> "data is negative"
    }

    /*** for ***/
    for (i in 1..10) {
        println(i)
    }

    // for (i in 1 until 10)
    // for (i in 2..10 step 2)
    // for (i in 10 downTo 1)
}

class User {
    var data3: Int = 5  // need initializing
    lateinit var data4: String  // succeed (not for Int, Long, Short, Double, Float, Boolean, Byte)
}
```

## 2. object oriented

```kotlin
package com.example.myapplication

class User {
    var name = "eunji"
    constructor(name: String) {
        this.name = name
    }

    fun someFun() {
        println("name: $name")
    }
}

class User1(name: String, age: Int) {
    var name: String
    var age: Int
    init {
        this.name = name
        this.age = age
        println("i am init")
    }
}

class User2(var name: String, var age: Int) {
    init {
        println("name: $name, age: $age")
    }
}

class User3(var name: String, var age: Int) {
    constructor(name: String, age: Int, count: Int): this(name, age) {
        // statements
    }
    constructor(name: String, age: Int, count: Int, email: String): this(name, age, count) {
        // statements
    }
}

/*** inheritance ***/
open class Super(name: String) {
    open var data = 10
    open fun superFun() {
        println("i am superfun: $data")
    }
}

class Sub(name: String): Super(name) {
    override fun superFun() {
        println("override function")
    }
}

/*** visibility modifier (최상위에서) ***/
/*** public: every file
    internal: same module
    protected: no use
    private: same file ***/

class vis {
    /*** visibility modifier (클래스 멤버에서) ***/
    /*** public: every class
    internal: same module
    protected: on sub class
    private: same class ***/
}

/*** data class ***/
class NonDataClass(val name: String, val email: String, val age: Int)

data class DataClass(val name: String, var email: String, val age: Int)

/*** object class ***/
val objt = object: Super("eunji") {
    override var data = 10
    fun some() {
        println("data: $data")
    }
}

/*** companion class ***/
// no need to demonstrate object
class MyClass {
    companion object {
        var data = 10
        fun some() {
            println(data)
        }
    }
}

fun main() {
    val user = User("kim")  // Kotlin do not use "new" keyword
    user.someFun()

    val user1 = User1("eunji", 21)  // i am init

    val obj = Sub("eunji")
    obj.superFun()

    var non1 = NonDataClass("eunji", ".com", 21)
    var non2 = NonDataClass("eunji", ".com", 21)
    var data1 = DataClass("eunji", ".com", 21)
    var data2 = DataClass("eunji", ".com", 21)
    var isSame = non1.equals(non2)  // false
    var isSameData = data1.equals(data2)  // true (only compare main constructor)

    println(non1.toString())  // not valuable
    println(data1.toString())  // valuable

    MyClass.data = 20
}
```

## 3. Useful things

```kotlin
package com.example.myapplication

/*** 5-1 lambda function ***/
fun main() {
    // lambda function
    val sum = {no1: Int, no2: Int -> no1 + no2}
    val result = sum(10, 20);

    val result1 = {no1: Int, no2: Int -> no1 - no2} (10, 20);

    val some: (Int) -> Unit = {println(it)}
    some(10)

    val some1: (Int, Int) -> Int = {no1: Int, no2: Int -> no1 + no2}
}

// type alias
typealias MyInt = Int
typealias MyFunType = (Int, Int) -> Boolean // function type

val someFun: MyFunType = {no1: Int, no2: Int -> no1 == no2}  // can omit var type

// higher order function
fun hofFun(arg: (Int) -> Boolean): () -> String {
    val result = if (arg(10)) {
        "valid"
    } else {
        "invalid"
    }

    return {result}
}

val result = hofFun { num -> num>0 }

/*** 5-2 null safety ***/
/** null: declared, but not initialized, no memory allocation
 * use null -> NullPointException
 */

// null safety
var data: String? = null
val length = data?.length ?: 0
// ? operator : null -> not access to variable
// ?: elvis operator

// null exception operator !!
var len = data!!.length
```
