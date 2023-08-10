package com.eunzee.eunzee.info;

public class java {
    public static void main(String[] args) {
        /***** print ******/
        System.out.println("Hello world!");

        /***** variable type *****/
        String name = "eunzee";
        int hour = 9;
        double score = 90.5;
        char grade = 'A';
        boolean isPass = true;
        float f = 3.14f;

        /***** comment *****/
        // single line comment
        /**
         * multiple line comment
         */

        /***** constant variable *****/
        final String KR_COUNTRY_CODE = "+82";
        // KR_COUNTRY_CODE = "+8282"; error

        /***** type change *****/
        int a;
        a = 10 + (int) 3.14;

        String s1 = String.valueOf(93);
        s1 = Integer.toString(93);

        int i = Integer.parseInt("93");

        /***** arithmetic operator *****/
        System.out.println(2 + 3); // 5
        System.out.println(4 - 2); // 2
        System.out.println(4 * 2); // 8
        System.out.println(4 / 2); // 2
        System.out.println(5 / 2); // 2
        System.out.println(2 / 4); // 0
        System.out.println(4 % 2); // 0
        System.out.println(5 % 2); // 1

        // increment, decrement
        int val = 10;

        val++;
        System.out.println(val); // 11

        val--;
        System.out.println(val); // 10

        System.out.println(++val); // 11
        System.out.println(val++); // 11, val = 12

        /***** assignment operator *****/
        int b = 10;
        b = b + 2; // b = 12
        b += 2; // b = 14

        b -= 2;
        b /= 6;
        b *= 3;
        b %= 7;
        System.out.println(b); // 6

        /***** comparison operator *****/
        System.out.println(5 > 3); // true
        System.out.println(5 >= 3); // true
        System.out.println(5 <= 3); // false
        System.out.println(5 < 3); // false
        System.out.println(5 == 3); // false
        System.out.println(5 != 3); // true

        /***** logical operator *****/
        boolean pizza = true;
        boolean pasta = true;
        boolean cocktail = true;

        System.out.println(pizza || pasta || cocktail); // true
        System.out.println(pizza && pasta && cocktail); // true

        System.out.println((5 > 3) && (3 > 1)); // true
        System.out.println((5 < 3) && (3 < 1)); // false

        System.out.println(!(5 == 3)); // true

        /***** conditionary operator *****/
        int result = (5 > 3) ? 5 : 3; // 5

        /***** string *****/
        String s = "I like Java";
        System.out.println(s.length()); // 11
        System.out.println(s.toUpperCase()); // I LIKE JAVA
        System.out.println(s.toLowerCase()); // i like java
        System.out.println(s.contains("Java")); // true
        System.out.println(s.indexOf("Java")); // 7
        System.out.println(s.startsWith("I like")); // true

        s = s.replace("Java", "Python");
        System.out.println(s.substring(7)); // Python
        System.out.println(s.substring(0, 7)); // I like

        s = "          I love Java         ";
        System.out.println(s = s.trim());

        s += " and Python";
        System.out.println(s);
        System.out.println(s.concat(" and C"));

        s = "Java";
        System.out.println(s.equals("Java")); // true
        System.out.println(s.equals("Python")); // false

        s1 = "1234";
        String s2 = "1234";
        System.out.println(s1 == s2); // true

        s1 = new String("1234");
        s2 = new String("1234");
        System.out.println(s1 == s2); // false

        // escape character
        System.out.println("Hello\nWorld");
        System.out.println("pizza\t9000won");
        System.out.println("pasta\t8000won");
        System.out.println("~\\Document");
        System.out.println("He said \"I love you\"");

        /***** conditional statements *****/
        // if
        hour = 16;
        int min = 52;
        if (hour < 18 && min < 60) {
            System.out.println("아이스 아메리카노");
        }

        boolean morningCoffee = false;
        if (morningCoffee) {
            System.out.println("바닐라 얼그레이 티 라떼");
        } else {
            System.out.println("아이스 아메리카노");
        }

        if (morningCoffee) {
            System.out.println("아이스티");
        } else if (!morningCoffee && hour < 20) {
            System.out.println("라떼");
        } else {
            System.out.println("차");
        }

        // switch
        char expression = 'A';
        switch (expression) {
            case 'A':
                System.out.println("very good");
                break;
            case 'B':
                System.out.println("good");
                break;
            case 'C':
                System.out.println("no money");
        }

        /***** loop statements *****/
        for (i=0; i<10; i++) {
            System.out.println(i + "번째 손님 안녕하세요!");
        }

        int move = 0;
        while(move < 10) {
            System.out.println(move);
            move += 3;
        }

        do {
            System.out.println(move);
            move -= 2;
        } while (move > 0);

        for (i=0; i<10; i++) {
            if (i%2==0) continue;
            System.out.println(i); // 1 3 5 7 9
        }

        /***** array *****/
        String[] coffees = {"americano", "cafe mocha", "latte", "cappuccino"};

        System.out.println("one cup of " + coffees[0]);

        for (i=0; i<4; i++) {
            System.out.println("one cup of "+coffees[i]);
        }

        for (String coffee :
                coffees) {
            System.out.println("A cup of "+ coffee);
        }

        String[][] seats = new String[][]{
                {"A1", "A2", "A3"},
                {"B1", "B2", "B3"},
                {"C1", "C2", "C3"}
        };

        for (i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                System.out.println(seats[i][j]);
            }
        }

        /***** ASCII *****/
        char c = 'A';
        System.out.println(c);
        System.out.println((int)c);

        /***** method *****/
        System.out.println(getPhoneNumber());
        System.out.println(sum(1, 2)); // 3
    }
    public static String getPhoneNumber() {
        String phoneNumber = "010-1234-5678";
        return phoneNumber;
    }

    public static int sum(int a, int b) {
        return a + b;
    }

    /***** variable scope *****/
    public static void hi() {
        String hello = "hello";
        System.out.println(hello);
    }

    public static void bye() {
        // System.out.println(hello); error
        System.out.println("bye");
    }
}
