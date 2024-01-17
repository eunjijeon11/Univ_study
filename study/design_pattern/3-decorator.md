# 데코레이터 패턴
주어진 상황과 용도에 따라 동적 혹은 정적으로 어떤 객체에 책임을 덧붙이는 패턴이다.

데코레이터 패턴은 OCP 원칙을 지키기 위해 고안된 패턴이다. 즉, 기존의 코드 변경 없이 새로운 행동을 추가할 수 있다.  
> 📌 OCP 패턴: 클래스는 확장에 대해서는 열려 있어야 하지만 코드 변경에 대해서는 닫혀 있어야 한다.

## 데코레이터 패턴을 사용하지 않는다면?
![image](https://github.com/eunjijeon11/Univ_study/assets/61264183/b23b42a2-9e9c-4972-a897-7d6d92e8271b)
음료라는 추상 클래스를 상속하는 여러 종류의 음료 클래스는 각각 cost라는 함수를 가지고 있다.  
이 cost함수는 각 음료에 대한 값을 반환한다.  

그런데 만약 음료에 휘핑이나 샷을 추가해야한다면? 그때마다 cost 함수에 로직을 추가하고 음료 클래스에 관련 변수를 추가해야할 수 있다.  
하지만 데코레이터 패턴을 사용하면 OCP 원칙을 지키면서 새로운 개념을 추가할 수 있다.

## 자세한 구조
추상 클래스를 상속받는 데코레이터 클래스를 생성한다.  
![image](https://github.com/eunjijeon11/Univ_study/assets/61264183/a459152c-2501-405a-a406-a1871b4a43f0)
![image](https://github.com/eunjijeon11/Univ_study/assets/61264183/a8f66a94-50cc-4935-851d-7d3f65c264c7)
데코레이터 클래스(condimentDecorator)에는 beverage 변수가 있고, 이는 생성 시에 주입받는다.  
데코레이터 클래스의 cost함수에서는 beverage의 cost 함수를 통해 원래 값을 받고, 이에 값을 추가하거나 뺀 값을 리턴한다.  

아래 코드를 통해 실제 사용 방법을 알아보자.
```java
public abstract class Beverage {
  private String description;

  public String getDescription() {
    return description;
  }

  public abstract double cost();
}

public class Mocha extends Beverage {
  public Mocca() {
    description = "Mocha";
  }

  public double cost() {
    return 4000.0;
  }
}
```
```java
public class CondimentDecorator extends Beverage {
  Beverage beverage;

  public abstract String getDescription();
}

public class Whip extends CondimentDecorator {
  public Whip(Beverage beverage) {
    this.beverage = beverage;
  }

  public double cost() {
    return beverage.cost() + 500.0;
  }

  public String getDescription() {
    return beverage.getDescription() + ", 휘핑";
  }
}
```
```java
// main
Beverage beverage = new Mocha();
beverage = new Whip(beverage);

System.out.println(beverage.getDescription() + beverage.cost());
```
## 장단점
### 장점
- 추가 기능과 핵심 기능을 분리할 수 있다.
- 상속 대신 구성과 위임으로 동적으로 새로운 행동을 추가할 수 있다.
### 단점
- 만약 concrete component에서 (Mocha) 메소드를 통해 특별 할인을 한다던지 등의 특별한 작업이 필요하다면? 데코레이터를 거쳐서 나온 값에는 잘 적용이 안되어있을 수 있다.
- 관리해야할 객체가 많아져 실수가 생길 수 있다. => 팩토리나 빌더같은 패턴을 더 많이 이용한다.
- 코드가 복잡해진다.

- 자바의 I/O 스트림은 데코레이터 패턴으로 만들어져있다.
